#include "comment.h"

#include <vector>

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