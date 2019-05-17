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
    int get_password();
    virtual std::string get_type();
    int get_id();
private:
    int id;
    std::string username;
    int password;
    std::string email;
    int age;
    std::vector< std::vector<std::string> > new_massages;
    std::vector< std::vector<std::string> > readed_massages;
    int money;
};

#endif