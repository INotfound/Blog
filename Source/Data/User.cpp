/*
 * @File: User.cpp
 * @Author: INotFound
 * @Date: 2020-04-27 16:13:12
 * @LastEditTime: 2020-04-28 18:03:51
 */
#include "User.h"
namespace Blog{
    User::User()
        :m_Id(0)
        ,m_LoginTime(0)
        ,m_CreateTime(0)
        ,m_UpdateTime(0){
    }
    const uint64_t& User::getId(){
        return m_Id;
    }
    const std::string& User::getName(){
        return m_Name;
    }
    const std::string& User::getEMail(){
        return m_EMail;
    }
    const std::string& User::getAccount(){
        return m_Account;
    }
    const std::string& User::getPassword(){
        return m_Password;
    }
    const time_t& User::getLoginTime(){
        return m_LoginTime;
    }
    const time_t& User::getCreateTime(){
        return m_CreateTime;
    }
    const time_t& User::getUpdateTime(){
        return m_UpdateTime;
    }
    void User::setId(uint64_t val){
        m_Id = val;
    }
    void User::setName(const std::string& val){
        m_Name = val;
    }
    void User::setEMail(const std::string& val){
        m_EMail = val;
    }
    void User::setAccount(const std::string& val){
        m_Account = val;
    }
    void User::setPassword(const std::string& val){
        m_Password = val;
    }
    void User::setLoginTime(const time_t& val){
        m_LoginTime = val;
    }
    void User::setCreateTime(const time_t& val){
        m_CreateTime = val;
    }
    void User::setUpdateTime(const time_t& val){
        m_UpdateTime = val;
    }


    static const std::string g_SqlDelete = "DELETE FROM User WHERE Id = ?";
    static const std::string g_SqlQueryAll = "SELECT Id,Name,EMail,Account,Password,LoginTime,CreateTime,UpdateTime FROM User";
    static const std::string g_SqlQuery = "SELECT Name,EMail,Account,Password,LoginTime,CreateTime,UpdateTime FROM User WHERE Id = ?";
    static const std::string g_SqlInsert = "INSERT INTO User (Name,EMail,Account,Password,LoginTime,CreateTime,UpdateTime) values (?,?,?,?,?,?,?)";
    static const std::string g_SqlUpdate = "UPDATA User SET Name = ?,EMail = ?,Account = ?,Password = ?,LoginTime = ?,CreateTime = ?,UpdateTime = ? where Id = ?";

    bool UserDao::CreateTable(Safe<Magic::DB::MySql>& dateBase){
        return dateBase->execute(R"Template(
            CREATE TABLE IF NOT EXISTS User(
            `Id` bigint AUTO_INCREMENT COMMENT '用户ID',
            `Name` varchar(30) NOT NULL DEFAULT '' COMMENT '名称',
            `EMail` varchar(50) NOT NULL DEFAULT '' COMMENT '邮件',
            `Account` varchar(30) NOT NULL DEFAULT '' COMMENT '账号',
            `Password` varchar(30) NOT NULL DEFAULT '' COMMENT '密码',
            `LoginTime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '登录时间',
            `CreateTime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',
            `UpdateTime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' ON UPDATE current_timestamp  COMMENT '修改时间',
            PRIMARY KEY(`Id`),
            UNIQUE KEY `UName` (`Name`)),
            UNIQUE KEY `UEMail` (`EMail`),
            UNIQUE KEY `UAccount` (`Account`)
        )Template");
    }

    /*
        stmt->bind(0,);
        stmt->bind(1,"");
        stmt->bind(2,"");
        stmt->bind(3,"");
        stmt->bind(4,"");
        stmt->bind(5,"");
        stmt->bind(6,"");
        stmt->bind(7,"");
    */

    bool UserDao::Insert(Safe<Magic::DB::MySql>& dateBase,Safe<User>& refValue){
        Safe<Magic::DB::MySqlStmt> stmt(new Magic::DB::MySqlStmt(dateBase));
        bool isOk = stmt->prepare(g_SqlInsert);
        if(!isOk){
            stmt->printError();
            return false;
        }
        stmt->bind(0,refValue->getName());
        stmt->bind(1,refValue->getEMail());
        stmt->bind(2,refValue->getAccount());
        stmt->bind(3,refValue->getPassword());
        stmt->bind(4,refValue->getLoginTime());
        stmt->bind(5,refValue->getCreateTime());
        stmt->bind(6,refValue->getUpdateTime());
        return stmt->execute();
    }

    bool UserDao::Query(Safe<Magic::DB::MySql>& dateBase,uint64_t id,Safe<User>& refValue){
        Safe<Magic::DB::MySqlStmt> stmt(new Magic::DB::MySqlStmt(dateBase));
        bool isOk = stmt->prepare(g_SqlUpdate);
        if(!isOk){
            stmt->printError();
            return false;
        }
        stmt->bind(0,id);
        isOk = stmt->query();
        if(isOk){
            isOk = stmt->next();
            if(isOk){
                refValue->setId(id);
                refValue->setName(stmt->getString(0));
                refValue->setEMail(stmt->getString(1));
                refValue->setAccount(stmt->getString(2));
                refValue->setPassword(stmt->getString(3));
                refValue->setLoginTime(stmt->getTime(4));
                refValue->setCreateTime(stmt->getTime(5));
                refValue->setUpdateTime(stmt->getTime(6));
                return true;
            }
        }
        return false;
    }
    bool UserDao::Update(Safe<Magic::DB::MySql>& dateBase,uint64_t id,Safe<User>& refValue){
        Safe<Magic::DB::MySqlStmt> stmt(new Magic::DB::MySqlStmt(dateBase));
        bool isOk = stmt->prepare(g_SqlQuery);
        if(!isOk){
            stmt->printError();
            return false;
        }
        stmt->bind(0,refValue->getName());
        stmt->bind(1,refValue->getEMail());
        stmt->bind(2,refValue->getAccount());
        stmt->bind(3,refValue->getPassword());
        stmt->bind(4,refValue->getLoginTime());
        stmt->bind(5,refValue->getCreateTime());
        stmt->bind(6,refValue->getUpdateTime());
        stmt->bind(7,refValue->getId());
        return stmt->execute();
    }
    bool UserDao::Delete(Safe<Magic::DB::MySql>& dateBase,uint64_t id,Safe<User>& refValue){
        Safe<Magic::DB::MySqlStmt> stmt(new Magic::DB::MySqlStmt(dateBase));
        bool isOk = stmt->prepare(g_SqlDelete);
        if(!isOk){
            stmt->printError();
            return false;
        }


        return false;
    }
    bool UserDao::QueryAll(Safe<Magic::DB::MySql>& dateBase,std::unordered_map<uint64_t,Safe<User>>& refValueMap){
        Safe<Magic::DB::MySqlStmt> stmt(new Magic::DB::MySqlStmt(dateBase));
        bool isOk = stmt->prepare(g_SqlUpdate);
        if(!isOk){
            stmt->printError();
            return false;
        }
        isOk = stmt->query();
        if(isOk){
            while(stmt->next()){
                Safe<User> refValue(new User);
                refValue->setId(stmt->getUint64(0));
                refValue->setName(stmt->getString(1));
                refValue->setEMail(stmt->getString(2));
                refValue->setAccount(stmt->getString(3));
                refValue->setPassword(stmt->getString(4));
                refValue->setLoginTime(stmt->getTime(5));
                refValue->setCreateTime(stmt->getTime(6));
                refValue->setUpdateTime(stmt->getTime(7));
                refValueMap.emplace(refValue->getId(),std::move(refValue));
            }
            return true;
        }
        return false;
    }
}