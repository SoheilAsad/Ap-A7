#include "publisher.h"

#include <vector>

using namespace std;

Publisher::Publisher(map<string,string>& command_elements, int _id)
    : Customer(command_elements, _id)
{
}

string Publisher::get_type()
{
    return "publisher";
}