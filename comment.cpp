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

int Comment::get_writer_id()
{
    return customer_id;
}

int Comment::get_id()
{
    return id;
}

void Comment::write_repley(string _content)
{
    replyes.push_back(_content);
}

void Comment::show_info()
{
    cout <<id <<". " <<content <<endl;
    for(int i = 0; i < replyes.size(); i++)
        cout <<id <<"." <<i+1 <<". " <<replyes[i] <<endl;
}