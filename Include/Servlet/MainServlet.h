/*
 * @File: MainServlet.h
 * @Author: INotFound
 * @Date: 2020-04-06 16:06:37
 * @LastEditTime: 2020-04-27 14:38:54
 */
#pragma once
#include "Magic.h"

namespace Blog{

    class MainServlet :public Magic::Http::HttpServlet{
    public:
        MainServlet(const std::string& name);
    protected:
        std::string checkToken(const std::string& token,uint64_t timeMs);
        bool handle(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response) override;
        const Safe<Magic::Http::Session>& checkSession(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response);
        virtual void handleGet(const Safe<Magic::Http::Session>& session,const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response);
        virtual void handlePost(const Safe<Magic::Http::Session>& session,const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response);
    };
}