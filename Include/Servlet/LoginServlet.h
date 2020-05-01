/*
 * @File: LoginServlet.h
 * @Author: INotFound
 * @Date: 2020-04-07 13:50:31
 * @LastEditTime: 2020-04-27 14:11:27
 */
#pragma once
#include "Magic.h"
#include "MainServlet.h"
namespace Blog{
    class LoginServlet :public MainServlet{
    public:
        LoginServlet(const std::string& path);
    };
}