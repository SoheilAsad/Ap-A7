#include <vector>
#include <string>
#include <map>

#include "customer.h"

using namespace std;

Customer::Customer(map<string,string>& command_elements)
{
    username = command_elements["username"];
    password = stoi(command_elements["password"]);
    email = command_elements["email"];
    age = stoi(command_elements["age"]);
    money = 0;
}