#include "channel.h"

#include <vector>
#include <iostream>

#include "customer.h"
#include "exception.h"
#include "command_handeler.h"


using namespace std;

bool Channel::is_username_used(std::string username)
{
    for(int i = 0; i < customer_list.size(); i++)
        if(customer_list[i]->get_name() == command_elements["username"]);
            return true;
    return false;
}

Customer* Channel::find_customer_to_login()
{
    for(int i = 0; i < customer_list.size(); i++)
        if(customer_list[i]->get_name() == command_elements["username"] && customer_list[i]->get_password() == stoi(command_elements["password"]))
            return customer_list[i];
    return NULL;
}

void Channel::do_primitive_commands()
{
    if(command_elements["order_type"] == "POST")
    {
        if(command_elements["order"] == "singup?")
            singup_customer();
        else if(command_elements["order"] == "login?")
            login_customer();
        else
            throw NotFound();
    }
    else
        throw BadRequest();
}

void Channel::singup_customer()
{
    if(is_username_used(command_elements["username"]))
        throw BadRequest();
    command_handeler->check_singup_syntax_correction();
    customer_list.push_back(new Customer(command_elements,customer_num)); //check for publisher
    customer = customer_list.back();
}

void Channel::login_customer()
{
    command_handeler->check_login_syntax_correction();
    customer = find_customer_to_login();
    if(customer == NULL)
        throw BadRequest();
}