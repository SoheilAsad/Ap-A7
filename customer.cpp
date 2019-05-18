#include "customer.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "exception.h"

using namespace std;

Customer::Customer(map<string,string>& command_elements, int _id)
    :new_massages(vector<string>()), readed_massages(vector<string>())
{
    id = _id ;
    username = command_elements["username"];
    password = stoi(command_elements["password"]);
    email = command_elements["email"];
    age = stoi(command_elements["age"]);
    money = 0;
}

string Customer::get_name()
{
    return username;
}

int Customer::get_password()
{
    return password;
}

string Customer::get_type()
{
    return "customer";
}

int Customer::get_id()
{
    return id;
}

void Customer::increase_money(int amout)
{
    money += amout;
}

void Customer::add_massage_to_new_massages(string massage)
{
    new_massages.push_back(massage);
}

void Customer::add_customer_to_followers(int follower_id)
{
    throw BadRequest();
}

std::vector<int> Customer::get_followers()
{
}

void Customer::pay_money(int price)
{
    if(money < price)
        throw PermissionDenied();
    money -= price ;
}

void Customer::print_info()
{
    cout <<id <<" | " <<username <<" | " <<email ;
}