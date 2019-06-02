#ifndef CHANNEL_H
#define CHANNEL_H

#include <map>
#include <vector>

class Customer;
class Film;

class Channel
{
public:
    Channel();
    ~Channel();
    void set_online_user(int customer_id);
    void set_command_elements(std::map<std::string,std::string> _command_elements);
    void singup_customer();
    void login_customer();
    bool is_username_used(std::string username);
    void get_publisher_films_info(std::string* body,std::string director);
    int get_user_id();
    void get_another_films_info(std::string* body);
    void get_buyed_films_info(std::string* body);
    bool is_film_publisher(Film* film);
    int get_user_money();
    bool is_customer_buyed_film(int film_id);
    bool is_cretid_enough(int film_id);
    bool is_film_on(int film_id);
    Customer* find_customer_to_login();
    bool is_customer_a_publisher();
    Film* find_film(int film_id);
    Customer* find_customer(int id);
    void print_followers_info(std::vector<Customer*> followers);
    void print_films_info(std::vector<Film*> publisher_films);
    std::vector<Film*> find_publisher_films(int publisher_id);
    std::vector<Film*> find_films_are_on();
    std::vector<Film*> find_customer_buyed_films();
    void get_recommendation_films(int film_id,std::string* body);
    std::vector<Film*> find_best_film(int film_id);
    void add_film_to_graf();
    void update_films_graf(int film_id);
    void erase_repetitious_film_id(std::vector<int> &films, int film_id);
    bool is_customer_signup_before();
    std::string get_user_type();
    
    std::vector<Film*> sort_film_by_id(std::vector<Film*> publisher_films);
    std::vector<int> sort_film_by_graf(int film_id);
    std::vector<Film*> filter_films_by_director(std::vector<Film*> publisher_films,std::string director);
    
    void publish_the_film();
    void increase_money(std::string amount);
    void buy_the_film(int film_id);
    void rate_to_film(int film_id,int rate);
    void comment_on_the_film(int film_id, std::string content);
    void get_film_details(int film_id,std::string* body);
    void delete_film(int film_id);
    void show_money();

private:
    std::map<std::string,std::string> command_elements;
    Customer* customer;
    std::vector<Customer*> customer_list;
    std::vector<Film*> film_list;
    std::vector< std::vector<int> > films_graf;
    int customer_num;
    int film_num;

};

#endif