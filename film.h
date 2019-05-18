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

    int get_id();
    int get_comment_writer_id(int comment_id);
    Comment* find_comment(int comment_id);
    void write_repley_in_comment_box(int comment_id,std::string content);
    int get_price();
    int get_publisher_id();
    float get_rate();
    std::string get_name();
    bool is_customer_buyed_film_before(int customer_id);
    void add_customer_to_buyer(int customer_id);
private:
    int id;
    std::string name;
    int year;
    int length;
    int price;
    std::string summery;
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