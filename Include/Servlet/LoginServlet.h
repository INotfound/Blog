/*
 * @file: LoginServlet.h
 * @Author: INotFound
 * @Date: 2020-04-07 13:50:31
 * @LastEditTime: 2020-04-08 11:09:37
 */
#pragma once
#include "Magic.h"
#include "MainServlet.h"
namespace Web{
    class LoginServlet :public MainServlet{
    public:
        LoginServlet(const std::string& path);
    };
}