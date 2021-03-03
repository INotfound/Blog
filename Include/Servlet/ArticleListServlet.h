/*
 * @Author: INotFound
 * @Date: 2021-01-05 09:52:24
 * @LastEditTime: 2021-01-12 03:52:51
 */
#pragma once
#include <pqxx/pqxx>
#include <Magic/DataBase/ConnectionPool.h>
#include <Magic/NetWork/Http/HttpServlet.h>

namespace Blog{
    using namespace Magic::NetWork;
    class ArticleListServlet :public Http::IHttpServlet{
    public:
        ArticleListServlet(const Safe<Magic::DataBase::ConnectionPool<pqxx::connection>>& pool);
        bool handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response) override;
    private:
        Safe<Magic::DataBase::ConnectionPool<pqxx::connection>> m_ConnectionPool;
    };
}
