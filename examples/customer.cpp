#include "customer.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>


using namespace std;

Customer::Customer(map<string,string>& command_elements, int _id)
    :new_massages(vector<string>()), readed_massages(vector<string>())
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

void Customer::add_massage_to_new_massages(string massage)
{
    new_massages.push_back(massage);
}

void Customer::add_customer_to_followers(int follower_id)
{
    // throw BadRequest();
}

std::vector<int> Customer::get_followers()
{
}

void Customer::pay_money(int price)
{
    // if(money < price)
    //     throw PermissionDenied();
    money -= price ;
}

void Customer::print_info()
{
    cout <<id <<" | " <<username <<" | " <<email ;
}

void Customer::show_unread_massages()
{
    cout <<"#. Notification Message" <<endl;
    for(int i = new_massages.size()-1; i >= 0; i--)
        cout <<new_massages.size()-i <<". " <<new_massages[i] <<endl;
}

void Customer::move_unread_massages_to_readed_box()
{
    for(int i =0; i < new_massages.size(); i)
    {
        readed_massages.push_back(new_massages[i]);
        new_massages.erase(new_massages.begin(),new_massages.begin()+1);
    }
}

void Customer::show_readed_massages(int limit)
{
    if(limit > readed_massages.size())
        limit = readed_massages.size();
     cout <<"#. Notification Message" <<endl;
    for(int i = readed_massages.size()-1; i >= readed_massages.size()-limit; i--)
        cout <<readed_massages.size()-i <<". " <<readed_massages[i] <<endl;
}