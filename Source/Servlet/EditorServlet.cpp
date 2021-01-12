/*
 * @Author: INotFound
 * @Date: 2021-01-06 07:48:00
 * @LastEditTime: 2021-01-08 10:02:41
 */
#include "Data/Article.h"
#include "RapidJson/error/en.h"
#include "RapidJson/document.h"
#include "RapidJson/rapidjson.h"
#include "Servlet/EditorServlet.h"

namespace Blog{
    EditorServlet::EditorServlet(const Safe<Magic::DataBase::ConnectionPool<pqxx::connection>>& pool)
        :Http::IHttpServlet("/commitEditor",Http::HttpServletType::Normal)
        ,m_ConnectionPool(pool){
    }
    
    bool EditorServlet::handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response){
        std::string body;
        Safe<Article> article = std::make_shared<Article>();
        rapidjson::Document articleJson;
        body.assign("{\"Code\":0}");

        if(!articleJson.Parse(request->getBody().c_str()).HasParseError()){
            if(articleJson.HasMember("Title") && articleJson.HasMember("About") && articleJson.HasMember("Content")){
                article->setTitle(articleJson["Title"].GetString());
                article->setAbout(articleJson["About"].GetString());
                article->setContent(articleJson["Content"].GetString());
                if(ArticleDao::Insert(*m_ConnectionPool->getConnection(),article)){
                    body.assign("{\"Code\":1}");
                }
            }
        }

        response->setBody(body);
        response->setStatus(Http::HttpStatus::OK);
        response->setContentType(Http::HttpContentType::APPLICATION_JSON);
        return true;
    }
}