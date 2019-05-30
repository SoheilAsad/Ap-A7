#include "channel.h"

#include <vector>
#include <iostream>
#include <math.h>

#include "customer.h"
#include "publisher.h"
#include "film.h"

using namespace std;

const string BUYING_MASSAGE = " buy your film ";
const string RATING_MASSAGE = " rate your film ";
const string COMMENTING_MASSAGE = " comment on your film ";

Channel::Channel()
    : films_graf(vector<vector<int>>())
{
    customer_num = 1;
    film_num = 1;
}

Channel::~Channel()
{
    for(int i = 0; i < customer_list.size(); i++)
        delete customer_list[i];
    for(int i = 0; i < film_list.size(); i++)
        delete film_list[i];
}

void Channel::set_command_elements(map<string,string> _command_elements)
{
    command_elements = _command_elements;
}

bool Channel::is_username_used(std::string username)
{
    for(int i = 0; i < customer_list.size(); i++)
        if(customer_list[i]->get_name() == username)
            return true;
    return false;
}

Customer* Channel::find_customer_to_login()
{
    for(int i = 0; i < customer_list.size(); i++)
        if(customer_list[i]->get_name() == command_elements["username"] &&
            customer_list[i]->get_password() == command_elements["password"])
            return customer_list[i];
    return NULL;
}

bool Channel::is_customer_signup_before()
{
    customer = find_customer_to_login();
    if(customer == NULL)
        return false;
    return true;
}

bool Channel::is_customer_a_publisher()
{
    if(command_elements["publisher"] == "true")
		return true;
    return false;
}

string Channel::get_user_type()
{
    return customer->get_type();
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
        if(film_list[i]->get_id() == film_id && film_list[i]->get_film_state()=="on")
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

void Channel::send_massage_to_publisher(Film* film,string massage_type)
{
    string massage;
    massage = "User " + customer->get_name() + " with id " + to_string(customer->get_id()) + massage_type
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
    Customer* admin = find_customer(0);
    admin->increase_money(film->get_price() - money);
}

vector<Customer*> Channel::sort_by_id(vector<Customer*> followers ,int followers_num)
{
   for (int i = 0; i < followers_num-1; i++)           
       for (int j = 0; j < followers_num-i-1; j++)  
            if (followers[j]->get_id() > followers[j+1]->get_id()) 
                swap(followers[j], followers[j+1]); 
    return followers;
}

void Channel::print_followers_info(std::vector<Customer*> followers)
{
    cout <<"List of Followers" <<endl;
    cout << "#. User Id | User Username | User Email" <<endl;
    for(int i = 0; i < followers.size(); i++)
    {
        cout <<i+1 <<". " ;
        followers[i]->print_info();
        cout <<endl;
    }
}

void Channel::print_films_info(vector<Film*> publisher_films)
{
    cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" <<endl;
    for(int i = 0; i < publisher_films.size(); i++)
    {
        cout <<i+1 <<". " ;
        publisher_films[i]->print_info();
        cout <<endl;
    }
}

void Channel::add_film_to_graf()
{
    for(int i = 0 ; i < films_graf.size(); i++)
        films_graf[i].push_back(0);
    films_graf.push_back(vector<int>(film_num,0));
}

void Channel::update_films_graf(int film_id)
{
    for(int i = 0; i < film_list.size(); i++)
        if(film_list[i]->is_customer_buyed_film_before(customer->get_id()) && film_id != film_list[i]->get_id())
            films_graf[film_id-1][film_list[i]->get_id()-1]++;
}

vector<Film*> Channel::find_films_are_on()
{
    vector<Film*> films;
    for(int i = 0; i < film_list.size(); i++)
        if(film_list[i]->get_film_state()=="on")
            films.push_back(film_list[i]);
    return films;
}

vector<Film*> Channel::find_customer_buyed_films()
{
    vector<Film*> films;
    for(int i = 0; i < film_list.size(); i++)
        if(film_list[i]->is_customer_buyed_film_before(customer->get_id()))
            films.push_back(film_list[i]);
    return films;
}

vector<Film*> Channel::find_publisher_films(int publisher_id)
{
    vector<Film*> publisher_films;
    for(int i = 0; i < film_list.size(); i++)
        if(film_list[i]->get_publisher_id() == publisher_id && film_list[i]->get_film_state()=="on")
            publisher_films.push_back(film_list[i]);
    return publisher_films;
}

vector<Film*> Channel::sort_film_by_id(vector<Film*> publisher_films)
{
    int size = publisher_films.size();
    for (int i = 0; i < size-1; i++)
       for (int j = 0; j < publisher_films.size()-i-1; j++)  
            if (publisher_films[j]->get_id() > publisher_films[j+1]->get_id()) 
                swap(publisher_films[j], publisher_films[j+1]); 
    return publisher_films;
}

vector<Film*> Channel::filter_films_by_name(vector<Film*> publisher_films)
{
    vector<Film*> sorted_films;
    for(int i = 0; i < publisher_films.size(); i++) 
        if(publisher_films[i]->get_name() == command_elements["name"])
            sorted_films.push_back(publisher_films[i]);
    return sorted_films;
}

vector<Film*> Channel::filter_films_by_min_rate(vector<Film*> publisher_films)
{
    vector<Film*> sorted_films;
    for(int i = 0; i < publisher_films.size(); i++) 
        if(publisher_films[i]->get_rate() >= stoi(command_elements["min_rate"]))
            sorted_films.push_back(publisher_films[i]);
    return sorted_films;
}

vector<Film*> Channel::filter_films_by_min_year(vector<Film*> publisher_films)
{
    vector<Film*> sorted_films;
    for(int i = 0; i < publisher_films.size(); i++) 
        if(publisher_films[i]->get_year() >= stoi(command_elements["min_year"]))
            sorted_films.push_back(publisher_films[i]);
    return sorted_films;
}

vector<Film*> Channel::filter_films_by_price(vector<Film*> publisher_films)
{
    vector<Film*> sorted_films;
    for(int i = 0; i < publisher_films.size(); i++) 
        if(publisher_films[i]->get_price() == stoi(command_elements["price"]))
            sorted_films.push_back(publisher_films[i]);
    return sorted_films;
}

vector<Film*> Channel::filter_films_by_max_year(vector<Film*> publisher_films)
{
    vector<Film*> sorted_films;
    for(int i = 0; i < publisher_films.size(); i++) 
        if(publisher_films[i]->get_year() <= stoi(command_elements["max_year"]))
            sorted_films.push_back(publisher_films[i]);
    return sorted_films;
}

vector<Film*> Channel::filter_films_by_director(vector<Film*> publisher_films)
{
    vector<Film*> sorted_films;
    for(int i = 0; i < publisher_films.size(); i++) 
        if(publisher_films[i]->get_director_name() == command_elements["director"])
            sorted_films.push_back(publisher_films[i]);
    return sorted_films;
}

vector<Film*> Channel::filter_films_list(vector<Film*> publisher_films)
{
    publisher_films = sort_film_by_id(publisher_films);
    if(command_elements.count("name"))
        publisher_films = filter_films_by_name(publisher_films);
    if(command_elements.count("min_rate"))
        publisher_films = filter_films_by_min_rate(publisher_films);
    if(command_elements.count("min_year"))
        publisher_films = filter_films_by_min_year(publisher_films);
    if(command_elements.count("price"))
        publisher_films = filter_films_by_price(publisher_films);
    if(command_elements.count("max_year"))
        publisher_films = filter_films_by_max_year(publisher_films);
    if(command_elements.count("director"))
        publisher_films = filter_films_by_director(publisher_films);
    return publisher_films;
}

vector<int> Channel::sort_film_by_graf(int film_id)
{
    vector<int> graf_row ;
    for(int i = 0; i < films_graf[film_id -1].size(); i++)
        graf_row.push_back(films_graf[i][film_id -1]);
    vector<int> film_row; 
    for(int i = 0; i < films_graf[film_id -1].size(); i++)
        film_row.push_back(i+1);
    for (int i = 0; i < graf_row.size()-1; i++)           
       for (int j = 0; j < graf_row.size()-i-1; j++)
            if(graf_row[j] >= graf_row[j+1])
            {
                swap(film_row[j], film_row[j+1]);
                swap(graf_row[j], graf_row[j+1]);
            }
    return film_row;
}

void Channel::erase_repetitious_film_id(vector<int> &films, int film_id)
{
    for(int i= 0; i < films.size(); i++)
        if(films[i] == film_id || find_film(films[i]) == NULL )
        {
            films.erase(films.begin()+i,films.begin()+i+1);
            i--;
        }
    for(int i= 0; i < films.size(); i++)
        if(find_film(films[i])->is_customer_buyed_film_before(customer->get_id()) )
        {
            films.erase(films.begin()+i,films.begin()+i+1);
            i--;
        }
}
vector<Film*> Channel::find_best_film(int film_id)
{
    vector<int> best_films_id = sort_film_by_graf(film_id);
    vector<Film*> top_films;
    erase_repetitious_film_id(best_films_id,film_id);
    int size = best_films_id.size() ;
    if(size > 3)
        for(int i = size-1 ; i > size-5 ; i--)
                top_films.push_back(find_film(best_films_id[i]));
    else
        for(int i = size-1 ; i >= 0 ; i--)
                top_films.push_back(find_film(best_films_id[i]));
    return top_films;
}

void Channel::show_recommendation_films(int film_id)
{
    vector<Film*> films = find_best_film(film_id);
    cout << "Recommendation Film" <<endl; 
    cout <<"#. Film Id | Film Name | Film Length | Film Director" <<endl;
    for(int i = 0; i < films.size(); i++)
    {
        cout <<i+1 <<". " ;
        films[i]->print_berif_info();
        cout <<endl;
    }
}

void Channel::singup_customer()
{
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
    customer = find_customer_to_login();
}

void Channel::do_primitive_commands()
{
    if(command_elements["order_type"] == "POST")
    {
        if(command_elements["order"] == "signup?")
            singup_customer();
        else if(command_elements["order"] == "login?")
            login_customer();
        // else
        //     throw PermissionDenied();
    }
    // else
    //     throw BadRequest();
}

void Channel::publish_the_film()
{
    // if(customer->get_type() == "customer")
    //     throw PermissionDenied();
    film_list.push_back(new Film(film_num,command_elements,customer->get_id()));
    add_film_to_graf();
    send_publishing_massage_to_followers();
    film_num++;
    cout << "OK" <<endl;
}

void Channel::give_money_to_publisher()
{   
    customer->increase_money(publishers_money[customer->get_id()]);
    publishers_money[customer->get_id()] = 0 ;
    cout << "OK" <<endl;
}

void Channel::reply_to_comment()
{
    // if(customer->get_type() == "customer")
    //     throw PermissionDenied();
    Film* film = find_film(stoi(command_elements["film_id"]));
    // if(film == NULL)
    //     throw NotFound();
    // if(film->get_publisher_id() != customer->get_id())
    //     throw PermissionDenied();
    int writer_id = film->get_comment_writer_id(stoi(command_elements["comment_id"]));
    film->write_repley_in_comment_box(stoi(command_elements["comment_id"]),command_elements["content"]);
    send_reply_massage(writer_id);
    cout <<"OK" <<endl;
}

void Channel::follow_publisher()
{
    Customer* publisher = find_customer(stoi(command_elements["user_id"]));
    // if(publisher == NULL)
    //     throw NotFound();
    publisher->add_customer_to_followers(customer->get_id());
    send_following_massage(publisher->get_id());
    cout <<"OK" <<endl;
}

void Channel::increase_money()
{
    customer->increase_money(stoi(command_elements["amount"]));
    cout <<"OK" <<endl;
}

void Channel::buy_the_film()
{
    Film* film = find_film(stoi(command_elements["film_id"]));
    // if(film == NULL)
    //     throw NotFound();    // if(film == NULL)
    //     throw NotFound();
    if(!film->is_customer_buyed_film_before(customer->get_id()))
    {
        customer->pay_money(film->get_price());
        add_money_to_channel(film);
        update_films_graf(film->get_id());
        film->add_customer_to_buyer(customer->get_id());
        send_massage_to_publisher(film,BUYING_MASSAGE);
    }
    cout <<"OK" <<endl;
}

void Channel::rate_to_film()
{

    Film* film = find_film(stoi(command_elements["film_id"]));
    // if(film == NULL)
    //     throw NotFound();
    // if(!film->is_customer_buyed_film_before(customer->get_id()))
    //     throw PermissionDenied();
    film->record_rate(customer->get_id(),stoi(command_elements["score"]));
    send_massage_to_publisher(film,RATING_MASSAGE);
    cout <<"OK" <<endl;
}

void Channel::comment_on_the_film()
{
    Film* film = find_film(stoi(command_elements["film_id"]));
    // if(film == NULL)
    //     throw NotFound();
    // if(!film->is_customer_buyed_film_before(customer->get_id()))
    //     throw PermissionDenied();
    film->add_comment_to_film(command_elements["content"], customer->get_id());
    send_massage_to_publisher(film,COMMENTING_MASSAGE);
    cout <<"OK" <<endl;
}

void Channel::show_followers()
{
    // if(customer->get_type() == "customer")
    //     throw PermissionDenied();
    vector<int> followers_id = customer->get_followers();
    vector<Customer*> followers = find_followers(followers_id);
    followers = sort_by_id(followers, followers.size());
    print_followers_info(followers);
}

void Channel::show_publisher_films()
{
    // if(customer->get_type() == "customer")
    //     throw PermissionDenied();
    vector<Film*> publisher_films = find_publisher_films(customer->get_id());
    publisher_films = filter_films_list(publisher_films);
    print_films_info(publisher_films);
}

void Channel::search_in_films()
{
    vector<Film*>films = find_films_are_on();
    films = filter_films_list(films);
    print_films_info(films);
}

void Channel::show_film_details()
{
    Film* film = find_film(stoi(command_elements["film_id"]));
    // if(film == NULL)
    //     throw NotFound();
    film->show_details();
    show_recommendation_films(film->get_id());
}

void Channel::show_customer_purchased_films()
{
    vector<Film*>films = find_customer_buyed_films();
    films = filter_films_list(films);
    print_films_info(films);
}

void Channel::show_massages()
{
    if(command_elements.size() == 2)
    {
        customer->show_unread_massages();
        customer->move_unread_massages_to_readed_box();
    }
    else
        customer->show_readed_massages(stoi(command_elements["limit"]));
}

void Channel::delete_film()
{
    // if(customer->get_type() == "customer")
    //     throw PermissionDenied();
    Film* film = find_film(stoi(command_elements["film_id"]));
    // if(film == NULL)
    //     throw NotFound();
    film->delete_film();
    cout <<"OK" <<endl;
}

void Channel::delete_comment()
{
    // if(customer->get_type() == "customer")
    //     throw PermissionDenied();
    Film* film = find_film(stoi(command_elements["film_id"]));
    // if(film == NULL)
    //     throw NotFound();
    // if(film->get_publisher_id() != customer->get_id())
    //     throw PermissionDenied();
    film->delete_comment(stoi(command_elements["comment_id"]));
    cout <<"OK" <<endl;
}

void Channel::edit_film_info()
{
    // if(customer->get_type() == "customer")
    //     throw PermissionDenied();
    Film* film = find_film(stoi(command_elements["film_id"]));
    // if(film == NULL)
    //     throw NotFound();
    // if(film->get_publisher_id() != customer->get_id())
    //     throw PermissionDenied();
    film->change_film_info(command_elements);
    cout <<"OK" <<endl;
}

void Channel::show_money()
{
    cout << customer->get_money() <<endl;
}

void Channel::do_post_command()
{
    if(command_elements["order"] == "delete_films?")
        delete_film();
    else if(command_elements["order"] == "delete_comments?")
        delete_comment();
    else if(command_elements["order"] == "put_films?")
        edit_film_info();
    else if(command_elements["order"] == "films?")
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
    // else
    //     throw NotFound();
}

void Channel::do_get_command()
{
    if(command_elements["order"] == "followers")
        show_followers();
    else if(command_elements["order"] == "published" || command_elements["order"] == "published?")
        show_publisher_films();
    else if(command_elements["order"] == "films?" || command_elements["order"] == "films")
    {
        if(is_id_in_command_elements())
            show_film_details();
        else
            search_in_films();
    }
    else if(command_elements["order"] == "purchased?" || command_elements["order"] == "purchased")
        show_customer_purchased_films();
    else if(command_elements["order"] == "notifications")
        show_massages();
    else if(command_elements["order"] == "money")
        show_money();
    // else
    //     throw NotFound();
}

void Channel::do_command()
{
    if(command_elements["order_type"] == "POST")
        do_post_command();
    else if(command_elements["order_type"] == "GET")
        do_get_command();
    // else 
    //     throw BadRequest();
}