/*
 * @Author: INotFound
 * @Date: 2020-12-31 10:24:44
 * @LastEditTime: 2020-12-31 10:25:34
 */
#include "Blog.h"

int main(int argc, char** argv){
    Blog::Initialize([](const Safe<Magic::Container>& ioc){
        ioc->registerType<Magic::DataBase::ConnectionPool<pqxx::connection>,Magic::Config,Magic::TimingWheel>();
    });
    return EXIT_SUCCESS;
}
