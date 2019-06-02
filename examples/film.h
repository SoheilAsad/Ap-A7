#ifndef FILM_H
#define FILM_H

#include <vector>
#include <string>
#include <map>

class Comment;

class Film
{
public:
    Film(int _id, std::map<std::string,std::string> command_elements, int _publisher_id);
    ~Film();
    void get_films_info(std::string* body);
    void get_film_short_info(std::string* body);
    int get_id();
    int get_price();
    int get_publisher_id();
    float get_rate();
    std::string get_name();
    std::string get_film_state();
    int get_year();
    std::string get_director_name();
    bool is_customer_buyed_film_before(int customer_id);
    void add_customer_to_buyer(int customer_id);
    void record_rate(int customer_id,int score);
    bool is_customer_rate_before(int customer_id);
    void add_comment_to_film(std::string content, int customer_id);
    void get_details(std::string* body);
    void delete_film();
    
private:
    int id;
    std::string name;
    int year;
    int length;
    int price;
    std::string summary;
    std::string director;
    int publisher_id;
    std::map<int,int> rates;
    std::vector<int> raters_id;
    std::string film_state;
    int comment_num;
    std::vector<int> buyers_id;
    std::vector<Comment*> comments_list;
};

#endif