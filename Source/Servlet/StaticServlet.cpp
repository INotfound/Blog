/*
 * @file: StaticServlet.cpp
 * @Author: INotFound
 * @Date: 2020-04-06 20:12:18
 * @LastEditTime: 2020-04-06 20:15:29
 */
#include "StaticServlet.h"
namespace Web{
    StaticServlet::StaticServlet(const std::string& path)
        :HttpServlet(path){
    }
    bool StaticServlet::handle(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response){
        std::string path = request->getPath();
        if(path == "/"){
            path += ".html";
        }
        const std::string& cache = Magic::Http::HttpStaticCache::GetInstance()->getCache(path);
        if(!cache.empty()){
            response->setCache(false);
            response->setStatus(Magic::Http::HttpStatus::OK);
            response->setBody(cache);
            return true;
        }
        return false;
    }
}