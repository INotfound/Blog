/*
 * @File: User.h
 * @Author: INotFound
 * @Date: 2020-04-08 11:07:42
 * @LastEditTime: 2020-04-28 18:10:21
 */
#include "Magic.h"
namespace Blog{
    class User{
    public:
        User();
        const uint64_t& getId();
        const std::string& getName();
        const std::string& getEMail();
        const std::string& getAccount();
        const std::string& getPassword();
        const time_t& getLoginTime();
        const time_t& getCreateTime();
        const time_t& getUpdateTime();

        void setId(uint64_t val);
        void setName(const std::string& val);
        void setEMail(const std::string& val);
        void setAccount(const std::string& val);
        void setPassword(const std::string& val);
        void setLoginTime(const time_t& val);
        void setCreateTime(const time_t& val);
        void setUpdateTime(const time_t& val);
    private:
        uint64_t m_Id;
        std::string m_Name;
        std::string m_EMail;
        std::string m_Account;
        std::string m_Password;
        time_t m_LoginTime;
        time_t m_CreateTime;
        time_t m_UpdateTime;
    };

    class UserDao{
    public:
        static bool CreateTable(Safe<Magic::DB::MySql>& dateBase);
        static bool Insert(Safe<Magic::DB::MySql>& dateBase,Safe<User>& refValue);
        static bool Query(Safe<Magic::DB::MySql>& dateBase,uint64_t id,Safe<User>& refValue);
        static bool Update(Safe<Magic::DB::MySql>& dateBase,uint64_t id,Safe<User>& refValue);
        static bool Delete(Safe<Magic::DB::MySql>& dateBase,uint64_t id,Safe<User>& refValue);
        static bool QueryAll(Safe<Magic::DB::MySql>& dateBase,std::unordered_map<uint64_t,Safe<User>>& refValue);
    };

    class UserManager{
    public:
        UserManager();
    };
}