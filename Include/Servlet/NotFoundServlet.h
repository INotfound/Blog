/*
 * @Author: INotFound
 * @Date: 2021-01-06 02:51:48
 * @LastEditTime: 2021-01-06 02:53:37
 */
#pragma once
#include <Magic/Utilty/Config.h>
#include <Magic/NetWork/Http/HttpServlet.h>

namespace Blog{
    using namespace Magic::NetWork;
    class NotFoundServlet :public Http::IHttpServlet{
    public:
        NotFoundServlet();
        bool handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response) override;
    };
}
