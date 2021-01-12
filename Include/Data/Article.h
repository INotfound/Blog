/*
 * @Author: INotFound
 * @Date: 2020-12-31 10:16:26
 * @LastEditTime: 2021-01-11 10:24:02
 */
#include <Magic>
#include <vector>
#include <pqxx/pqxx>

namespace Blog{
    class Article{
    public:
        Article();
        uint64_t getId() const;
        uint64_t getViews() const;
        time_t getCreateTime() const;
        time_t getUpdateIime() const;
        const std::string& getTitle() const;
        const std::string& getAbout() const;
        const std::string& getContent() const;

        void setId(uint64_t id);
        void setViews(uint64_t views);
        void setCreateTime(time_t time);
        void setUpdateIime(time_t time);
        void setTitle(const std::string& title);
        void setAbout(const std::string& about);
        void setContent(const std::string& content);
    private:
        uint64_t m_Id;
        uint64_t m_Views;
        std::string m_Title;
        std::string m_About;
        time_t m_CreateTime;
        time_t m_UpdateTime;
        std::string m_Content;
    };

    class ArticleDao{
    public:
        static bool Insert(const Safe<pqxx::connection>& conn,const Safe<Article>& article);
        static bool Update(const Safe<pqxx::connection>& conn,const Safe<Article>& article);
        static bool QueryOne(const Safe<pqxx::connection>& conn,uint64_t aId,const Safe<Article>& refArticle);
        static bool QueryNew(const Safe<pqxx::connection>& conn,std::vector<Safe<Article>>& refArticles,uint32_t page,uint32_t count =6);
        static void Init(const Safe<pqxx::connection>& conn);
    };
}