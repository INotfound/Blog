/*
 * @Author: INotFound
 * @Date: 2021-01-05 09:52:29
 * @LastEditTime: 2021-01-11 06:37:57
 */
#include "Data/Article.h"
#include "RapidJson/writer.h"
#include "RapidJson/rapidjson.h"
#include "RapidJson/stringbuffer.h"
#include "Servlet/ArticleListServlet.h"

namespace Blog{
    ArticleListServlet::ArticleListServlet(const Safe<Magic::DataBase::ConnectionPool<pqxx::connection>>& pool)
        :Http::IHttpServlet("/getArticleList",Http::HttpServletType::Normal)
        ,m_ConnectionPool(pool){
    }
    
    bool ArticleListServlet::handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response){
        std::string body;
        std::vector<Safe<Article>> articles;

        if(ArticleDao::QueryNew(*m_ConnectionPool->getConnection(),articles)){
            rapidjson::StringBuffer strBuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
            writer.StartObject();
            writer.Key("Obj");
            writer.StartArray();

            for(auto& val : articles){
                writer.StartObject();
                writer.Key("Id");
                writer.Uint64(val->getId());
                writer.Key("Title");
                writer.String(val->getTitle().c_str());
                writer.Key("About");
                writer.String(val->getAbout().c_str());
                writer.Key("Views");
                writer.Uint64(val->getViews());
                writer.Key("CreateTime");
                writer.String(Magic::TimeToString(val->getCreateTime(),"%Y-%m-%d").c_str());
                writer.EndObject();
            }

            writer.EndArray();
            writer.Key("Code");
            writer.Uint(1);
            writer.EndObject();
            body.assign(strBuf.GetString());
        }else{
            body.assign("{\"Code\":0}");
        }

        response->setBody(body);
        response->setStatus(Http::HttpStatus::OK);
        response->setContentType(Http::HttpContentType::APPLICATION_JSON);
        return true;
    }

}