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
    void set_command_elements(std::map<std::string,std::string> _command_elements);
    void singup_customer();
    void login_customer();
    bool is_username_used(std::string username);
    void get_publisher_films_info(std::string* body,std::string director);
    int get_user_id();
    bool is_id_in_command_elements();
    Customer* find_customer_to_login();
    bool is_customer_a_publisher();
    Film* find_film(int film_id);
    Customer* find_customer(int id);
    void send_reply_massage(int writer_id);
    void send_publishing_massage_to_followers();
    void send_following_massage(int publisher_id);
    void send_massage_to_publisher(Film* film, std::string massage_type);
    std::vector<Customer*> find_followers(std::vector<int> followers_id);
    void add_money_to_channel(Film* film);
    int calculate_publisher_share(int price, float rate);
    void print_followers_info(std::vector<Customer*> followers);
    void print_films_info(std::vector<Film*> publisher_films);
    std::vector<Film*> find_publisher_films(int publisher_id);
    std::vector<Film*> find_films_are_on();
    std::vector<Film*> find_customer_buyed_films();
    void show_recommendation_films(int film_id);
    std::vector<Film*> find_best_film(int film_id);
    void add_film_to_graf();
    void update_films_graf(int film_id);
    void erase_repetitious_film_id(std::vector<int> &films, int film_id);
    bool is_customer_signup_before();
    std::string get_user_type();
    
    std::vector<Customer*> sort_by_id(std::vector<Customer*> followers, int followers_num);
    std::vector<Film*> sort_film_by_id(std::vector<Film*> publisher_films);
    std::vector<int> sort_film_by_graf(int film_id);
    std::vector<Film*> filter_films_by_name(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_min_rate(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_min_year(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_price(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_max_year(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_director(std::vector<Film*> publisher_films,std::string director);
    
    void do_primitive_commands();
    void do_command();
    void do_post_command();
    void do_get_command();
    void publish_the_film();
    void give_money_to_publisher();
    void reply_to_comment();
    void follow_publisher();
    void increase_money();
    void buy_the_film();
    void rate_to_film();
    void comment_on_the_film();
    void show_followers();
    void show_publisher_films();
    void search_in_films();
    void show_film_details();
    void show_customer_purchased_films();
    void show_massages();
    void delete_film();
    void delete_comment();
    void edit_film_info();
    void show_money();

private:
    std::map<std::string,std::string> command_elements;
    Customer* customer;
    std::vector<Customer*> customer_list;
    std::vector<Film*> film_list;
    std::map<int,int> publishers_money;
    std::vector< std::vector<int> > films_graf;
    int customer_num;
    int film_num;

};

#endif