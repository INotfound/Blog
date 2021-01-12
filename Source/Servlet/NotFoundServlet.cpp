/*
 * @Author: INotFound
 * @Date: 2021-01-06 02:51:57
 * @LastEditTime: 2021-01-08 13:56:46
 */
#include "Servlet/NotFoundServlet.h"

namespace Blog{
    NotFoundServlet::NotFoundServlet()
        :Http::IHttpServlet("",Http::HttpServletType::Deafult){
    }
    
    bool NotFoundServlet::handle(const Safe<Http::HttpRequest>& request,const Safe<Http::HttpResponse>& response){
        std::string notfound(R"Template(<html><head><title>404 Not Found</title></head><body>
            <center><h1>404 Not Found</h1></center><hr><center>Magic/2.0.0</center></body></html>)Template");
        response->setBody(notfound);
        response->setStatus(Http::HttpStatus::NOT_FOUND);
        return true;
    }
}