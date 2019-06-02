#include "film.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "comment.h"

using namespace std;

Film::Film(int _id, map<string,string> command_elements, int _publisher_id)
    : buyers_id(vector<int>()), raters_id(vector<int>())
{
    id = _id;
    year = stoi(command_elements["year"]);
    name = command_elements["name"];
    length = stoi(command_elements["length"]);
    price = stoi(command_elements["price"]);
    rates.insert(pair<int,int>(0,0));
    raters_id.push_back(0);
    summary = command_elements["summary"];
    director = command_elements["director"];
    publisher_id = _publisher_id;
    film_state = "on";
    comment_num = 1;
}

Film::~Film()
{
    for(int i = 0; i < comments_list.size(); i++)
        delete comments_list[i];
}

int Film::get_id()
{
    return id;
}

float Film::get_rate()
{
    float rate = 0;
    for(int i = 0; i < rates.size(); i++)
        rate += rates[raters_id[i]];
    if(raters_id.size() != 1)
        rate = rate / (raters_id.size()-1); 
    else
        rate = rate / raters_id.size();
    return rate;
}

string rate_to_string(float rate)
{
    string num = to_string(rate);
    cerr <<"*num" <<num <<endl;
    if(num[2] == '0')
        num.erase(num.begin()+1,num.end());
    else
        num.erase(num.begin()+4,num.end());
    cerr <<"#num" <<num <<endl;
    return num;
}

void Film::get_films_info(string* body)
{
    *body += "<td>" + name + "</td>\n" ;
    *body += "<td>" + to_string(price) + "</td>\n" ;
    *body += "<td>" + to_string(year) + "</td>\n" ;
    *body += "<td>" + to_string(length) + "</td>\n" ;
    *body += "<td>" + rate_to_string(get_rate()) + "</td>\n" ;
    *body += "<td>" + director + "</td>\n" ;
}

void Film::get_film_short_info(std::string* body)
{
    *body += "<td>" + name + "</td>\n" ;
    *body += "<td>" + to_string(length) + "</td>\n" ;
    *body += "<td>" + director + "</td>\n" ;
}

int Film::get_price()
{
    return price;
}

int Film::get_publisher_id()
{
    return publisher_id;
}

bool Film::is_customer_buyed_film_before(int customer_id)
{
    for(int i = 0; i < buyers_id.size(); i++)
        if(buyers_id[i] == customer_id)
            return true;
    return false;
}

void Film::add_customer_to_buyer(int customer_id)
{
    buyers_id.push_back(customer_id);
}

string Film::get_name()
{
    return name;
}

bool Film::is_customer_rate_before(int customer_id)
{
    for(int i = 0; i < raters_id.size(); i++)
        if(raters_id[i] == customer_id)
            return true;
    return false;
}

void Film::record_rate(int customer_id,int score)
{
    if(is_customer_rate_before(customer_id))
        rates[customer_id] = score ;
    else
    {
        rates.insert(pair<int,int>(customer_id,score));
        raters_id.push_back(customer_id);
    }
}

void Film::add_comment_to_film(string content, int customer_id)
{
    comments_list.push_back(new Comment(comment_num,content,customer_id));
    comment_num++;
}

string Film::get_film_state()
{
    return film_state;
}

int Film::get_year()
{
    return year;
}

string Film::get_director_name()
{
    return director;
}

void Film::get_details(string* body)
{
    *body += "<ul>\n";
    *body += "<li>Name : " + name + "</li>\n" ;
    *body += "<li>Length : " + to_string(length) + "</li>\n" ;
    *body += "<li>Price : " + to_string(price) + "</li>\n" ;
    *body += "<li>Rate : " + rate_to_string(get_rate()) + "</li>\n" ;
    *body += "<li>Year : " + to_string(year) + "</li>\n" ;
    *body += "<li>Director : " + director + "</li>\n" ;
    *body += "<li>Summary : " + summary + "</li>\n" ;
    *body += "</ul>\n";
    *body += "<br />";

    *body += "<h3>comments : </h3>";
    if(comments_list.size() != 0)
    {
        *body += "<ol>\n";
        for(int i = 0; i < comments_list.size(); i++)
            *body += "<li>" + comments_list[i]->get_content() + "</li>\n" ;
        *body += "</ol>\n";
    }
}

void Film::delete_film()
{
    film_state = "off";
}