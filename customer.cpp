#include "customer.h"

#include <vector>
#include <string>
#include <map>

using namespace std;

Customer::Customer(map<string,string>& command_elements, int _id)
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