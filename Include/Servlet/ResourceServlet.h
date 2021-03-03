/*
 * @Author: INotFound
 * @Date: 2021-01-06 10:01:06
 * @LastEditTime: 2021-01-08 14:06:59
 */
#pragma once
#include <pqxx/pqxx>
#include <Magic/DataBase/ConnectionPool.h>
#include <Magic/NetWork/Http/HttpServlet.h>

namespace Blog{
    using namespace Magic::NetWork;
    class ResourceServlet :public Http::IHttpServlet{
    public:
        ResourceServlet(const Safe<Magic::DataBase::ConnectionPool<pqxx::connection>>& pool);
        bool handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response) override;
    };
}
