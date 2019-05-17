#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <vector>
#include <string>

#include "customer.h"

class Publisher : public Customer
{
public:
    Publisher(map<string,string>& command_elements, int _id);


};

#endif