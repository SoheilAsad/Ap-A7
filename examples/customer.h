#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <string>
#include <map>

class Customer
{
public:
    Customer(std::map<std::string,std::string>& command_elements, int _id);
    std::string get_name();
    std::string get_password();
    virtual std::string get_type();
    bool do_you_have_money(int price);
    int get_id();
    int get_money();
    void increase_money(int amout);
    void pay_money(int price);
protected:
    int id;
    std::string username;
    std::string password;
    std::string email;
    int age;
    int money;
};

#endif