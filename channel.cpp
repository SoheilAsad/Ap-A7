#include "channel.h"

#include <vector>
#include <iostream>

#include "customer.h"
#include "publisher.h"
#include "exception.h"
#include "film.h"
#include "command_handeler.h"


using namespace std;

Channel::Channel()
{
    customer_num = 1;
    film_num = 1;
}

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

bool Channel::is_customer_a_publisher()
{
    if(command_elements.count("username"))
		return true;
    return false;
}

bool Channel::is_id_in_command_elements()
{
    if(command_elements.count("film_id"))
		return true;
    return false;
}

Customer* Channel::find_customer(int id)
{
    for(int i = 0; i < customer_list.size(); i++)
        if(customer_list[i]->get_id() == id)
            return customer_list[i];
    return NULL;
}

Film* Channel::find_film(int film_id)
{
    for(int i = 0; i < film_list.size(); i++)
        if(film_list[i]->get_id() == film_id)
            return film_list[i];
    return NULL;
}

void Channel::send_reply_massage(int writer_id)
{
    string massage;
    massage = "Publisher " + customer->get_name() + " with id " + to_string(customer->get_id()) 
        + " reply to your comment." ;
    Customer* writer = find_customer(writer_id);
    writer->add_massage_to_new_massages(massage);
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
    if(is_customer_a_publisher())
    {
        customer_list.push_back(new Publisher(command_elements,customer_num));
        publishers_money.insert(pair<int,int>(customer_num,0));
    }
    else
        customer_list.push_back(new Customer(command_elements,customer_num));
    customer = customer_list.back();
    customer_num++;
}

void Channel::login_customer()
{
    command_handeler->check_login_syntax_correction();
    customer = find_customer_to_login();
    if(customer == NULL)
        throw BadRequest();
}

void Channel::publish_the_film()
{
    if(customer->get_type() == "customer")
        throw PermissionDenied();
    command_handeler->check_film_publishing_syntax_correction();
    film_list.push_back(new Film(film_num,command_elements,customer->get_id()));
    film_num++;
}

void Channel::give_money_to_publisher()
{   
    command_handeler->check_getting_money_syntax_correction();
    customer->increase_money(publishers_money[customer->get_id()]);
    publishers_money[customer->get_id()] = 0 ;
}

void Channel::reply_to_comment()
{
    if(customer->get_type() == "customer")
        throw PermissionDenied();
    command_handeler->check_replies_syntax_correction();
    Film* film = find_film(stoi(command_elements["film_id"]));
    if(film == NULL)
        throw NotFound();
    int writer_id = film->get_comment_writer_id(stoi(command_elements["comment_id"]));
    film->write_repley_in_comment_box(stoi(command_elements["comment_id"]),command_elements["content"]);
    send_reply_massage(writer_id);
}

void Channel::do_post_command()
{
    if(command_elements["order"] == "film?")
        publish_the_film();
    else if(command_elements["order"] == "money")
        give_money_to_publisher();
    else if(command_elements["order"] == "replies?")
        reply_to_comment();
    else if(command_elements["order"] == "followers?")
        follow_publisher();
    else if(command_elements["order"] == "money?")
        increase_money();
    else if(command_elements["order"] == "buy?")
        buy_the_film();
    else if(command_elements["order"] == "rate?")
        rate_to_film();
    else if(command_elements["order"] == "comments?")
        comment_on_the_film();
    else
        throw NotFound();
}

void Channel::do_get_command()
{
    if(command_elements["order"] == "followers")
        show_followers();
    else if(command_elements["order"] == "published?")
        show_publisher_films();
    else if(command_elements["order"] == "film?")
    {
        if(is_id_in_command_elements())
            show_film_details();
        else
            search_in_films();
    }
    else if(command_elements["order"] == "purchased?")
        show_customer_purchased_films();
    else if(command_elements["order"] == "notifications")
        show_massages();
    else
        throw NotFound();
}

void Channel::do_delete_command()
{
    if(command_elements["order"] == "films?")
        delete_film();
    else if(command_elements["order"] == "comments?")
        delete_comment();
    else
        throw NotFound();
}

void Channel::do_put_command()
{
    if(command_elements["order"] == "films?")
        edit_film_info();
    else
        throw NotFound();
}

void Channel::do_command()
{
    if(command_elements["order_type"] == "POST")
        do_post_command();
    else if(command_elements["order_type"] == "GET")
        do_get_command();
    else if(command_elements["order_type"] == "DELETE")
        do_delete_command();
    else if(command_elements["order_type"] == "PUT")
        do_put_command();
    else 
        throw BadRequest();
}