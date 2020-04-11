/*
 * @file: StaticServlet.h
 * @Author: INotFound
 * @Date: 2020-04-06 20:12:42
 * @LastEditTime: 2020-04-06 20:14:51
 */
#pragma once
#include "Magic.h"

namespace Web{
    class StaticServlet :public Magic::Http::HttpServlet{
    public:
        StaticServlet(const std::string& path);
    protected:
        bool handle(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response) override;
    };
}