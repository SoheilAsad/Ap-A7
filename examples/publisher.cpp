#include "publisher.h"

#include <vector>

using namespace std;

Publisher::Publisher(map<string,string>& command_elements, int _id)
    : Customer(command_elements, _id), followers_id(vector<int>())
{
}

string Publisher::get_type()
{
    return "publisher";
}

bool Publisher::is_customer_followed_before(int follower_id)
{
    for(int i = 0; i < followers_id.size(); i++)
        if(followers_id[i] == follower_id)
            return true;
    return false;
}

void Publisher::add_customer_to_followers(int follower_id)
{
    if(!is_customer_followed_before(follower_id))
        followers_id.push_back(follower_id);
}

vector<int> Publisher::get_followers()
{
    return followers_id;
}