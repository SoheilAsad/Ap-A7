#include "customer.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>


using namespace std;

Customer::Customer(map<string,string>& command_elements, int _id)
{
    id = _id ;
    username = command_elements["username"];
    password = command_elements["password"];
    email = command_elements["email"];
    age = stoi(command_elements["age"]);
    money = 0;
}

string Customer::get_name()
{
    return username;
}

string Customer::get_password()
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

int Customer::get_money()
{
    return money;
}

void Customer::increase_money(int amout)
{
    money += amout;
}

void Customer::pay_money(int price)
{
    money -= price ;
}

bool Customer::do_you_have_money(int price)
{
    if(money >= price)
        return true;
    return false;
}