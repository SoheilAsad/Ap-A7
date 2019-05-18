#include "channel.h"

#include <vector>
#include <iostream>
#include <math.h>

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
        if(customer_list[i]->get_name() == command_elements["username"] &&
            customer_list[i]->get_password() == stoi(command_elements["password"]))
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

vector<Customer*> Channel::find_followers(vector<int> followers_id)
{
    vector<Customer*> followers;
    for(int i = 0; i < followers_id.size(); i ++)
        followers.push_back(find_customer(followers_id[i]));
    return followers;
}

void Channel::send_reply_massage(int writer_id)
{
    string massage;
    massage = "Publisher " + customer->get_name() + " with id " + to_string(customer->get_id()) 
        + " reply to your comment." ;
    Customer* writer = find_customer(writer_id);
    writer->add_massage_to_new_massages(massage);
}

void Channel::send_publishing_massage_to_followers()
{
    vector<int> followers_id = customer->get_followers();
    vector<Customer*> followers = find_followers(followers_id);
    string massage;
    massage = "Publisher " + customer->get_name() + " with id " + to_string(customer->get_id())
        + " register new film." ;
    for(int i = 0; i < followers.size(); i++)
        followers[i]->add_massage_to_new_massages(massage);
}

void Channel::send_following_massage(int publisher_id)
{
    string massage;
    massage = "User " + customer->get_name() + " with id " + to_string(customer->get_id()) + " follow you." ;
    Customer* publisher = find_customer(publisher_id);
    publisher->add_massage_to_new_massages(massage);
}

void Channel::send_buying_massage_to_publisher(Film* film)
{
    string massage;
    massage = "User " + customer->get_name() + " with id " + to_string(customer->get_id()) + " buy your film "
        + film->get_name() + " with id " + to_string(film->get_id()) + ".";
    Customer* publisher = find_customer(film->get_publisher_id());
    publisher->add_massage_to_new_massages(massage);
}

void Channel::send_ratiing_massage(Film* film)
{
    string massage;
    massage = "User " + customer->get_name() + " with id " + to_string(customer->get_id()) + " rate your film "
        + film->get_name() + " with id " + to_string(film->get_id()) + ".";
    Customer* publisher = find_customer(film->get_publisher_id());
    publisher->add_massage_to_new_massages(massage);
}

int Channel::calculate_publisher_share(int price, float rate)
{
    if(rate < 5)
        return floor(price * 0.8);
    else if(rate < 8)
        return floor(price * 0.9);
    else
        return floor(price * 0.95);
}

void Channel::add_money_to_channel(Film* film)
{
    int money = calculate_publisher_share(film->get_price(),film->get_rate());
    publishers_money[film->get_publisher_id()] += money;
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
    else    customer = customer_list.back();

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
    cout << "OK" <<endl;
}

void Channel::login_customer()
{
    command_handeler->check_login_syntax_correction();
    customer = find_customer_to_login();
    if(customer == NULL)
        throw BadRequest();
    cout << "OK" <<endl;
}

void Channel::publish_the_film()
{
    if(customer->get_type() == "customer")
        throw PermissionDenied();
    command_handeler->check_film_publishing_syntax_correction();
    film_list.push_back(new Film(film_num,command_elements,customer->get_id()));
    send_publishing_massage_to_followers();
    film_num++;
    cout << "OK" <<endl;
}

void Channel::give_money_to_publisher()
{   
    command_handeler->check_getting_money_syntax_correction();
    customer->increase_money(publishers_money[customer->get_id()]);
    publishers_money[customer->get_id()] = 0 ;
    cout << "OK" <<endl;
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
    cout <<"OK" <<endl;
}

void Channel::follow_publisher()
{
    command_handeler->check_following_syntax_correction();
    Customer* publisher = find_customer(stoi(command_elements["user_id"]));
    if(publisher == NULL)
        throw NotFound();
    publisher->add_customer_to_followers(customer->get_id());
    send_following_massage(publisher->get_id());
    cout <<"OK" <<endl;
}

void Channel::increase_money()
{
    command_handeler->check_increase_money_syntax_correction();
    customer->increase_money(stoi(command_elements["amount"]));
    cout <<"OK" <<endl;
}

void Channel::buy_the_film()
{
    command_handeler->check_buy_film_syntax_correction();
    Film* film = find_film(stoi(command_elements["film_id"]));
    if(film == NULL)
        throw NotFound();
    if(!film->is_customer_buyed_film_before(customer->get_id()))
    {
        customer->pay_money(film->get_price());
        add_money_to_channel(film);
        film->add_customer_to_buyer(customer->get_id());
        send_buying_massage_to_publisher(film);
    }
}

void Channel::rate_to_film()
{
    command_handeler->check_rate_film_syntax_correction();
    Film* film = find_film(stoi(command_elements["film_id"]));
    if(film == NULL)
        throw NotFound();
    film->record_rate(customer->get_id(),stoi(command_elements["score"]));
    send_ratiing_massage(film);
    cout <<"OK" <<endl;
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