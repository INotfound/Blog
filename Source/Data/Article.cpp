/*
 * @Author: INotFound
 * @Date: 2020-12-31 10:18:18
 * @LastEditTime: 2021-01-17 11:44:36
 */
#include <exception>
#include "Data/Article.h"

namespace Blog{
    Article::Article(){
    }

    uint64_t Article::getId() const{
        return m_Id;
    }

    uint64_t Article::getViews() const{
        return m_Views;
    }

    time_t Article::getCreateTime() const{
        return m_CreateTime;
    }
    
    time_t Article::getUpdateIime() const{
        return m_UpdateTime;
    }

    const std::string& Article::getTitle() const{
        return m_Title;
    }
    
    const std::string& Article::getAbout() const{
        return m_About;
    }
    
    const std::string& Article::getContent() const{
        return m_Content;
    }
    
    void Article::setId(uint64_t id){
        m_Id = id;
    }

    void Article::setViews(uint64_t views){
        m_Views = views;
    }

    void Article::setCreateTime(time_t time){
        m_CreateTime = time;
    }

    void Article::setUpdateIime(time_t time){
        m_UpdateTime = time;
    }

    void Article::setTitle(const std::string& title){
        m_Title = title;
    }

    void Article::setAbout(const std::string& about){
        m_About = about;
    }

    void Article::setContent(const std::string& content){
        m_Content = content;
    }

    bool ArticleDao::Insert(const Safe<pqxx::connection>& conn,const Safe<Article>& article){
        if(!conn && !conn->is_open()){
            MAGIC_ERROR() << "PostgreSql Connection failed!";
            return false;
        }
        try{
            pqxx::work work(*conn);
            work.exec_prepared("Insert",article->getTitle(),article->getAbout(),article->getContent());
            work.commit();
        }catch(const std::exception& e){
            MAGIC_ERROR() << e.what();
            return false;
        }
        return true;
    }

    bool ArticleDao::Update(const Safe<pqxx::connection>& conn,const Safe<Article>& article){
        if(!conn && !conn->is_open()){
            MAGIC_ERROR() << "PostgreSql Connection failed!";
            return false;
        }
        try{
            pqxx::work work(*conn);
            work.exec_prepared("Update",article->getId(),article->getTitle(),article->getAbout(),article->getContent());
            work.commit();
        }catch(std::exception& e){
            MAGIC_ERROR() << e.what();
            return false;
        }
        return true;
    }

    bool ArticleDao::QueryOne(const Safe<pqxx::connection>& conn,uint64_t aId,const Safe<Article>& refArticle){
        if(!conn && !conn->is_open()){
            MAGIC_ERROR() << "PostgreSql Connection failed!";
            return false;
        }
        if(aId == 0){
            MAGIC_WARN() << "Query Bad Argument[AId == 0]!";
            return false;
        }
        
        try{
            pqxx::work work(*conn);
            pqxx::result result(work.exec_prepared("QueryOne",aId));
            work.commit();

            if(result.size() == 0){
                MAGIC_DEBUG() << "Query Result[Size == 0]!";
                return false;
            }
            for(auto row : result){                
                refArticle->setId(row[0].as(0));
                refArticle->setTitle(row[1].c_str());
                refArticle->setAbout(row[2].c_str());
                refArticle->setContent(row[3].c_str());
                refArticle->setViews(row[4].as(0));
                refArticle->setCreateTime(static_cast<time_t>(row[5].as(0.0)));
                refArticle->setUpdateIime(static_cast<time_t>(row[6].as(0.0)));
            }
        }catch(std::exception& e){
            MAGIC_ERROR() << e.what();
            return false;
        }
        return true;
    }

    bool ArticleDao::QueryNew(const Safe<pqxx::connection>& conn,std::vector<Safe<Article>>& refArticles,uint32_t page,uint32_t count){
        if(!conn && !conn->is_open()){
            MAGIC_ERROR() << "PostgreSql Connection failed!";
            return false;
        }
        if(count <= 0){
            MAGIC_WARN() << "Query Bad Argument[Count <= 0]!";
            return false;
        }
        
        try{
            pqxx::work work(*conn);
            pqxx::result result(work.exec_prepared("QueryNew",count,(page-1) * count));
            work.commit();

            if(result.size() == 0){
                MAGIC_DEBUG() << "Query Result[Size == 0]!";
                return false;
            }
            for(auto row : result){
                Safe<Article> article = std::make_shared<Article>();
                article->setId(row[0].as(0));
                article->setTitle(row[1].c_str());
                article->setAbout(row[2].c_str());
                article->setContent(row[3].c_str());
                article->setViews(row[4].as(0));
                article->setCreateTime(static_cast<time_t>(row[5].as(0.0)));
                article->setUpdateIime(static_cast<time_t>(row[6].as(0.0)));
                refArticles.emplace_back(std::move(article));
            }
        }catch(std::exception& e){
            MAGIC_ERROR() << e.what();
            return false;
        }
        return true;
    }

    void ArticleDao::Init(const Safe<pqxx::connection>& conn){
        conn->prepare("Update","UPDATE Article SET Title = $2, About = $3, Content = $4, Updatetime = now() WHERE Id = $1;");
        conn->prepare("Insert","INSERT INTO Article(Title,About,Content,Views,Createtime,Updatetime) VALUES ($1,$2,$3,0,now(),now())");
        conn->prepare("QueryNew","SELECT Id,Title,About,Content,Views,EXTRACT(epoch FROM Createtime),EXTRACT(epoch FROM Updatetime) FROM Article ORDER BY Id DESC LIMIT $1 OFFSET $2");
        conn->prepare("QueryOne","SELECT Id,Title,About,Content,Views,EXTRACT(epoch FROM Createtime),EXTRACT(epoch FROM Updatetime) FROM Article WHERE Id = $1");
    }
}