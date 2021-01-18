/*
 * @Author: INotFound
 * @Date: 2021-01-06 10:01:13
 * @LastEditTime: 2021-01-12 08:07:17
 */
#include <sstream>
#include <fstream>
#include "Data/Article.h"
#include "Servlet/ResourceServlet.h"

namespace Blog{
    ResourceServlet::ResourceServlet(const Safe<Magic::DataBase::ConnectionPool<pqxx::connection>>& pool)
        :Http::IHttpServlet("^/?(.*)$",Http::HttpServletType::Global){
        pool->initialize([](const Safe<pqxx::connection>& entity){
            ArticleDao::Init(entity);
        });
    }

    bool ResourceServlet::handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response){
        response->setStatus(Http::HttpStatus::OK);
        std::ifstream stream;
        std::string res = "www";
        std::string path = request->getPath();
        if(path == "/"){
            path = "/index.html";
        }
        stream.open(res + path,std::ios::in);
        if(stream.is_open()){
            std::ostringstream staticRes;
            staticRes << stream.rdbuf();
            response->setBody(staticRes.str());
            response->setContentType(Http::FileTypeToHttpContentType(path));
            stream.close();
            return true;
        }else{ // rewrite to index.html
            path = "/index.html";
            stream.open(res + path,std::ios::in);
            if(!stream.is_open()){
                return false;
            }
            std::ostringstream staticRes;
            staticRes << stream.rdbuf();
            response->setBody(staticRes.str());
            response->setContentType(Http::FileTypeToHttpContentType(path));
            stream.close();
        }
        return true;
    }
}