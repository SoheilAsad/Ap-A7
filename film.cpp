#include "film.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "comment.h"
#include "exception.h"

using namespace std;

Film::Film(int _id, map<string,string> command_elements, int _publisher_id)
    : buyers_id(vector<int>()), raters_id(vector<int>())
{
    id = _id;
    year = stoi(command_elements["year"]);
    length = stoi(command_elements["length"]);
    price = stoi(command_elements["price"]);
    summery = command_elements["summary"];
    director = command_elements["director"];
    publisher_id = _publisher_id;
    film_state = "on";
    comment_num = 1;
}

int Film::get_id()
{
    return id;
}

Comment* Film::find_comment(int comment_id)
{
    for(int i = 0; i < comments_list.size(); i++)
        if(comments_list[i]->get_id() == comment_id)
            return comments_list[i];
    return NULL;
}

int Film::get_comment_writer_id(int comment_id)
{
    Comment* comment = find_comment(comment_id);
    if(comment == NULL)
        throw NotFound();
    return comment->get_writer_id();
}

void Film::write_repley_in_comment_box(int comment_id,string content)
{
    Comment* comment = find_comment(comment_id);
    if(comment == NULL)
        throw NotFound();
    comment->write_repley(content);
}

int Film::get_price()
{
    return price;
}

int Film::get_publisher_id()
{
    return publisher_id;
}

float Film::get_rate()
{
    float rate = 0;
    for(int i = 0; i < raters_id.size(); i++ )
        rate += rates[raters_id[i]];
    rate = rate / raters_id.size();
    float value = (int)(rate * 100 ); 
    rate = (float)value / 100; 
    return rate;
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

void Film::print_info()
{
    cout <<id <<" | " <<name <<" | " <<length <<" | " <<price <<" | " 
        <<get_rate() <<" | " <<year <<" | " <<director ;
}

void Film::show_comments()
{
    cout <<"Comments" <<endl;
    for(int i=0; i < comments_list.size(); i++)
        comments_list[i]->show_info();
}

void Film::show_details()
{
    cout <<"Details of Film " <<name <<endl;
    cout <<"Id = " <<id <<endl;
    cout <<"Director = " <<director <<endl;
    cout <<"Length = " <<length <<endl;
    cout <<"Year = " <<year <<endl;
    cout <<"Summary = " <<summery <<endl;
    cout <<"Rate = " <<get_rate() <<endl;
    cout <<"Price = " <<price <<endl <<endl;
    show_comments();
    cout <<endl;
}

void Film::print_berif_info()
{
    cout <<id <<" | " <<name <<" | " <<length <<" | " <<director ;
}

void Film::delete_film()
{
    film_state = "off";
}

void Film::delete_comment(int comment_id)
{
    for(int i = 0; i < comments_list.size(); i++)
        if(comments_list[i]->get_id() == comment_id)
        {
            delete comments_list[i];
            comments_list.erase(comments_list.begin(),comments_list.begin()+1);
            return;
        }
    throw NotFound();
}