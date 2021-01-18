/*
 * @Author: INotFound
 * @Date: 2021-01-06 03:52:51
 * @LastEditTime: 2021-01-12 08:11:01
 */
#include <pqxx/pqxx>
#include "Data/Article.h"
#include "RapidJson/writer.h"
#include "RapidJson/rapidjson.h"
#include "RapidJson/stringbuffer.h"
#include "Servlet/DetailsServlet.h"

namespace Blog{
    DetailsServlet::DetailsServlet(const Safe<Magic::DataBase::ConnectionPool<pqxx::connection>>& pool)
        :Http::IHttpServlet("/getDetails",Http::HttpServletType::Normal)
        ,m_ConnectionPool(pool){
    }
    
    bool DetailsServlet::handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response){
        std::string body;
        uint64_t aId = Magic::StringAs<uint64_t>(request->getParam("Id"));
        if(aId > 0){
            Safe<Article> article = std::make_shared<Article>();
            
            if(ArticleDao::QueryOne(*m_ConnectionPool->getConnection(),aId,article)){
                rapidjson::StringBuffer strBuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

                writer.StartObject();
                writer.Key("Id");
                writer.Uint64(article->getId());
                writer.Key("Title");
                writer.String(article->getTitle().c_str());
                writer.Key("Content");
                writer.String(article->getContent().c_str());
                writer.Key("Views");
                writer.Uint64(article->getViews());
                writer.Key("CreateTime");
                writer.String(Magic::TimeToString(article->getCreateTime(),"%Y-%m-%d").c_str());
                writer.Key("Code");
                writer.Uint(1);
                writer.EndObject();

                body.assign(strBuf.GetString());
            }
        }else{
            body.assign("{\"Code\":0}");
        }
        response->setBody(body);
        response->setStatus(Http::HttpStatus::OK);
        response->setContentType(Http::HttpContentType::APPLICATION_JSON);
        return true;
    }
}
