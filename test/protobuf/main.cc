#include"test.pb.h"
#include<iostream>
#include<string>

int main()
{
    test_proto::LoginRequest req;
    req.set_name("duanran");
    req.set_pwd("gogogo");
    
    std::string serialize;
    if(req.SerializeToString(&serialize))
    {
        // std::cout << serialize << std::endl;
    }

    test_proto::LoginRequest toObj;
    if (toObj.ParseFromString(serialize))
    {
        // std::cout<< toObj.name() << std::endl;
        // std::cout<< toObj.pwd() << std::endl;
    }

    test_proto::User user;
    user.set_name("lihua");
    user.set_age(3);
    user.set_sex(test_proto::User::MAN);
    
    test_proto::UserLists userLists;
    test_proto::Result *pr = userLists.mutable_res();
    
    pr -> set_msg("good");
    pr -> set_statecode(1);
    
    userLists.set_name("test");

    test_proto::User *user1 = userLists.add_users();
    user1 -> set_name(user.name());
    user1 -> set_age(user.age());
    user1 -> set_sex(user.sex());

    std::cout << userLists.users_size() << std::endl;
    for (int i = 0; i < userLists.users_size(); i++)
    {
        test_proto::User *user = userLists.mutable_users(i);
        std::cout << "user: " << user -> name() << std::endl;
        std::cout << "age: " << user -> age() << std::endl;
        std::cout << "Sex: " << user -> sex() << std::endl; 
    }

    if (userLists.SerializeToString(&serialize))
    {
        std::cout << serialize << std::endl;
    }

    return 0;
}