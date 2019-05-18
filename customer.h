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
    void increase_money(int amout);
    void add_massage_to_new_massages(std::string massage);
    virtual void add_customer_to_followers(int follower_id);
    virtual std::vector<int> get_followers();
    void pay_money(int price);
    void print_info();
    void show_unread_massages();
    void move_unread_massages_to_readed_box();
    void show_readed_massages(int limit);
protected:
    int id;
    std::string username;
    int password;
    std::string email;
    int age;
    std::vector<std::string> new_massages;
    std::vector<std::string> readed_massages;
    int money;
};

#endif