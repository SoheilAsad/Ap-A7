#ifndef COMMENT_H
#define COMMENT_H

#include <vector>
#include <string>

class Comment
{
public:
    Comment(int _id, std::string _content, int _customer_id);
    std::string get_content();
    int get_id();
private:
    int id;
    std::string content;
    std::vector<std::string> replyes;
    int customer_id;
};

#endif