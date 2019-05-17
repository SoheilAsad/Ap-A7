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

};

#endif