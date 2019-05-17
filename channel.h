#ifndef CHANNEL_H
#define CHANNEL_H

#include <map>
#include <vector>

class Customer;
class CommandHandeler;

class Channel
{
public:
    void do_primitive_commands();
    void singup_customer();
    void login_customer();
    bool is_username_used(std::string username);
    Customer* find_customer_to_login();
    bool is_customer_a_publisher();

private:
    std::map<std::string,std::string> command_elements;
    Customer* customer;
    std::vector<Customer*> customer_list;
    CommandHandeler* command_handeler;
    int customer_num;
    int film_num;

};







#endif