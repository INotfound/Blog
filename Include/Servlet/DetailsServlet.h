/*
 * @Author: INotFound
 * @Date: 2021-01-06 03:53:00
 * @LastEditTime: 2021-01-08 13:57:11
 */
#pragma once
#include <Magic>
#include <pqxx/pqxx>

namespace Blog{
    using namespace Magic::NetWork;
    class DetailsServlet :public Http::IHttpServlet{
    public:
        DetailsServlet(const Safe<Magic::DataBase::ConnectionPool<pqxx::connection>>& pool);
        bool handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response) override;
    private:
        Safe<Magic::DataBase::ConnectionPool<pqxx::connection>> m_ConnectionPool;
    };
}