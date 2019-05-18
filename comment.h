#ifndef COMMENT_H
#define COMMENT_H

#include <vector>
#include <string>

class Comment
{
public:
    Comment(int _id, std::string _content, int _customer_id);

    int get_writer_id();
    int get_id();
    void write_repley(std::string _content);
    void show_info();
private:
    int id;
    std::string content;
    std::vector<std::string> replyes;
    int customer_id;
};

#endif