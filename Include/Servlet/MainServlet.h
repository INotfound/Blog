/*
 * @file: MainServlet.h
 * @Author: INotFound
 * @Date: 2020-04-06 16:06:37
 * @LastEditTime: 2020-04-08 11:27:26
 */
#pragma once
#include "Magic.h"

namespace Web{
namespace Cookie{
    const char* TOKEN = "MTOKEN";
    const char* SESSEION ="MSEEION";
    const char* TOKENTIME = "MTOKENTIME";
}
    class MainServlet :public Magic::Http::HttpServlet{
    public:
        MainServlet(const std::string& name);
    protected:
        std::string getToken(const std::string& token,uint64_t timeMs);
        bool handle(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response) override;
        const Safe<Magic::Http::Session>& checkLogin(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response);
        virtual void handleGet(const Safe<Magic::Http::Session>& session,const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response);
        virtual void handlePost(const Safe<Magic::Http::Session>& session,const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response);
    };
}