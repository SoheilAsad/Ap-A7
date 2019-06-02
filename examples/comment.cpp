#include "comment.h"

#include <vector>
#include <iostream>

using namespace std;

Comment::Comment(int _id, std::string _content, int _customer_id)
    : replyes(vector<string>())
{
    id = _id;
    content = _content;
    customer_id = _customer_id;
}

string Comment::get_content()
{
    return content;
}

int Comment::get_id()
{
    return id;
}