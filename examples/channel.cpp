#include "channel.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "customer.h"
#include "publisher.h"
#include "film.h"

using namespace std;

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

int Channel::get_user_id()
{
    return customer->get_id();
}

void Channel::set_online_user(int customer_id)
{
    customer = find_customer(customer_id) ;
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

vector<Film*> Channel::filter_films_by_director(vector<Film*> publisher_films, string director)
{
    vector<Film*> sorted_films;
    for(int i = 0; i < publisher_films.size(); i++) 
        if(publisher_films[i]->get_director_name() == director)
            sorted_films.push_back(publisher_films[i]);
    return sorted_films;
}

void add_detail_item_to_list(Film* film ,string* body)
{
    *body += "<form action=\"detail\" method=\"get\">\n";
    *body += "<input type=\"hidden\" name=\"id\" " "value=" +to_string(film->get_id()) + ">";
    *body += "<button type=\"submit\">details</button>\n";
    *body += "</form> </td>\n";
}

void Channel::get_publisher_films_info(string* body,string director)
{
    vector<Film*> films = find_publisher_films(customer->get_id());
    if(director != "")
        films = filter_films_by_director(films,director);
    films = sort_film_by_id(films);
    for (int i = 0; i < films.size(); i++)
    {
        *body += "<tr>\n" ;
        films[i]->get_films_info(body);
        *body += "<td> <form action=\"delete?id=" +to_string(films[i]->get_id()) + "\" method=\"post\">\n";
        *body += "<button type=\"submit\">delete</button>\n";
        *body += "</form> \n";
        add_detail_item_to_list(films[i],body);
        *body += "</tr>\n" ;
    }
}

bool Channel::is_film_on(int film_id)
{
    Film* film = find_film(film_id);
    if(film->get_film_state() == "on")
        return true;
    return false;
}

bool Channel::is_film_publisher(Film* film)
{
    if(film->get_publisher_id() == customer->get_id())
        return true;
    return false;
}

void Channel::get_another_films_info(string* body)
{
    vector<Film*> films = find_films_are_on();
    for(int i = 0; i < films.size(); i++)
        if(!is_film_publisher(films[i]) && customer->do_you_have_money(films[i]->get_price()) &&
         !films[i]->is_customer_buyed_film_before(customer->get_id()))
        {
            *body += "<tr>\n" ;
            films[i]->get_films_info(body);
            *body += "<td>";
            add_detail_item_to_list(film_list[i],body);
            *body += "</tr>\n" ;
        }
}

void Channel::get_buyed_films_info(string* body)
{
    for(int i = 0; i < film_list.size(); i++)
        if(!is_film_publisher(film_list[i]) && film_list[i]->is_customer_buyed_film_before(customer->get_id()))
        {
            *body += "<tr>\n" ;
            film_list[i]->get_films_info(body);
            *body += "<td>";
            add_detail_item_to_list(film_list[i],body);
            *body += "</tr>\n" ;
        }
}

int Channel::get_user_money()
{
    return customer->get_money();
}

bool Channel::is_customer_buyed_film(int film_id)
{
    Film* film = find_film(film_id);
    if(film->is_customer_buyed_film_before(customer->get_id()))
        return true;
    return false;
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
        if(films[i] == film_id || find_film(films[i])->get_film_state() == "off" )
        {
            films.erase(films.begin()+i,films.begin()+i+1);
            i--;
        }
    for(int i= 0; i < films.size(); i++)
        if(find_film(films[i])->is_customer_buyed_film_before(customer->get_id()) || 
         is_film_publisher(find_film(films[i])))
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

void Channel::get_recommendation_films(int film_id,string* body)
{
    vector<Film*> films = find_best_film(film_id);
    ifstream f("./static/recommend");
    string file;
    if(f) {
        ostringstream ss;
        ss << f.rdbuf();
        file = ss.str();
    }
    *body += file; 
    for(int i = 0; i < films.size(); i++)
    {
        *body += "<tr>\n" ;
        films[i]->get_film_short_info(body);
        *body += "<td>";
        add_detail_item_to_list(film_list[i],body);
        *body += "</tr>\n" ;
    }
    *body += "</table>\n";
}

void Channel::singup_customer()
{
    if(is_customer_a_publisher())
    {
        customer_list.push_back(new Publisher(command_elements,customer_num));
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


void Channel::publish_the_film()
{
    film_list.push_back(new Film(film_num,command_elements,customer->get_id()));
    add_film_to_graf();
    film_num++;
}

void Channel::increase_money(string amount)
{
    customer->increase_money(stoi(amount));
}

bool Channel::is_cretid_enough(int film_id)
{
    Film* film = find_film(film_id);
    if(customer->do_you_have_money(film->get_price()))
        return true;
    return false;
}

void Channel::buy_the_film(int film_id)
{
    Film* film = find_film(film_id);
    customer->pay_money(film->get_price());
    update_films_graf(film->get_id());
    film->add_customer_to_buyer(customer->get_id());
}

void Channel::rate_to_film(int film_id, int rate)
{
    Film* film = find_film(film_id);
    film->record_rate(customer->get_id(),rate);
}

void Channel::comment_on_the_film(int film_id, string content)
{
    Film* film = find_film(film_id);
    film->add_comment_to_film(content, customer->get_id());
}


void Channel::get_film_details(int film_id,string* body)
{
    Film* film = find_film(film_id);
    film->get_details(body);
}

void Channel::delete_film(int film_id)
{
    Film* film = find_film(film_id);
    film->delete_film();
}

void Channel::show_money()
{
    cout << customer->get_money() <<endl;
}