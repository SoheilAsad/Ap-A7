#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <vector>
#include <string>

#include "customer.h"

class Publisher : public Customer
{
public:
    Publisher(std::map<std::string,std::string>& command_elements, int _id);
    virtual std::string get_type();
    virtual void add_customer_to_followers(int follower_id);
    virtual std::vector<int> get_followers();
    bool is_customer_followed_before(int follower_id);

private:
    std::vector<int> followers_id;
};

#endif