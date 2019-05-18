#ifndef CHANNEL_H
#define CHANNEL_H

#include <map>
#include <vector>

class Customer;
class CommandHandeler;
class Film;

class Channel
{
public:
    Channel();
    void singup_customer();
    void login_customer();
    bool is_username_used(std::string username);
    bool is_id_in_command_elements();
    Customer* find_customer_to_login();
    bool is_customer_a_publisher();
    Film* find_film(int film_id);
    Customer* find_customer(int id);
    void send_reply_massage(int writer_id);
    void send_publishing_massage_to_followers();
    void send_following_massage(int publisher_id);
    void send_buying_massage_to_publisher(Film* film);
    void send_ratiing_massage(Film* film);
    void send_commenting_massage(Film* film);
    std::vector<Customer*> find_followers(std::vector<int> followers_id);
    void add_money_to_channel(Film* film);
    int calculate_publisher_share(int price, float rate);
    void print_followers_info(std::vector<Customer*> followers);
    void print_films_info(std::vector<Film*> publisher_films);
    std::vector<Film*> find_publisher_films(int publisher_id);

    std::vector<Customer*> sort_by_id(std::vector<Customer*> followers, int followers_num);
    std::vector<Film*> sort_film_by_id(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_list(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_name(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_min_rate(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_min_year(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_price(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_max_year(std::vector<Film*> publisher_films);
    std::vector<Film*> filter_films_by_director(std::vector<Film*> publisher_films);

    void do_primitive_commands();
    void do_command();
    void do_post_command();
    void do_get_command();
    void do_delete_command();
    void do_put_command();

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
    void show_film_details();
    void search_in_films();
    void show_customer_purchased_films();
    void show_massages();

    void delete_film();
    void delete_comment();

    void edit_film_info();

private:
    std::map<std::string,std::string> command_elements;
    Customer* customer;
    std::vector<Customer*> customer_list;
    std::vector<Film*> film_list;
    CommandHandeler* command_handeler;
    std::map<int,int> publishers_money;
    int customer_num;
    int film_num;

};

#endif