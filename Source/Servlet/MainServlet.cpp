/*
 * @file: MainServlet.cpp
 * @Author: INotFound
 * @Date: 2020-04-06 16:05:48
 * @LastEditTime: 2020-04-08 11:47:34
 */
#include "Servlet/MainServlet.h"
namespace Web{
    MainServlet::MainServlet(const std::string& path)
        :HttpServlet(path){
    }
    std::string getToken(const std::string& token,uint64_t timeMs){
        // std::stringstream sstream;
        // sstream << id   << "|"
        //     << username << "|"
        //     << password << "|"
        //     << email    << "|"
        //     << token    << "|"
        //     << std::to_string(timeMs);
        // return Magic::MD5HexString(sstream.str());
        return "";
    }

    bool MainServlet::handle(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response){
        //Magic::Http::SessionMgr::GetInstance()->get()
        Magic::Http::HttpMethod method = request->getMethod();
        switch (method){
        case Magic::Http::HttpMethod::GET:
            /* code */
            //this->handleGet(request,response);
            return true;
        case Magic::Http::HttpMethod::POST:
            return true;
        default:
            return false;
        }
    }
    const Safe<Magic::Http::Session>& MainServlet::checkLogin(const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response){
        auto sessionId = request->getCookie(Cookie::SESSEION);
        if(!sessionId.empty()){
            auto& session = Magic::Http::SessionMgr::GetInstance()->get(sessionId);
            if(session){
                return session;
            }
        }
        Safe<Magic::Http::Session> session(new Magic::Http::Session());
        const std::string& sid = session->getId();
        response->setCookie(Cookie::SESSEION,sid,0,"/");
        Magic::Http::SessionMgr::GetInstance()->add(session);
        return Magic::Http::SessionMgr::GetInstance()->get(sid);
    }
    void MainServlet::handleGet(const Safe<Magic::Http::Session>& session,const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response){
    }
    void MainServlet::handlePost(const Safe<Magic::Http::Session>& session,const Safe<Magic::Http::HttpRequest>& request,const Safe<Magic::Http::HttpResponse>& response){
    }
}