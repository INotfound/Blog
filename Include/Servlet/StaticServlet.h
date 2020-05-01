/*
 * @File: StaticServlet.h
 * @Author: INotFound
 * @Date: 2020-04-06 20:12:42
 * @LastEditTime: 2020-04-27 14:11:34
 */
#pragma once
#include "Magic.h"

namespace Blog{
    class StaticServlet :public Magic::Http::HttpServlet{
    public:
        StaticServlet(const std::string& path);
    protected:
        bool handle(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response) override;
    };
}