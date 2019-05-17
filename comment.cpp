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