/*
 * @Author: INotFound
 * @Date: 2021-01-06 07:47:31
 * @LastEditTime: 2021-01-08 14:06:51
 */
#pragma once
#include <Magic>
#include <pqxx/pqxx>

namespace Blog{
    using namespace Magic::NetWork;
    class EditorServlet :public Http::IHttpServlet{
    public:
        EditorServlet(const Safe<Magic::DataBase::ConnectionPool<pqxx::connection>>& pool);
        bool handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response) override;
    private:
        Safe<Magic::DataBase::ConnectionPool<pqxx::connection>> m_ConnectionPool;
    };
}