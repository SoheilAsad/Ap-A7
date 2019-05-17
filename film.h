#ifndef FILM_H
#define FILM_H

#include <vector>
#include <string>
#include <map>

class Comment;

class Film
{
public:
    Film(int _id, std::map<std::string,std::string> command_elements, int _publisher_id);

private:
    int id;
    std::string name;
    int year;
    int length;
    int price;
    std::string summery;
    std::string director;
    int publisher_id;
    std::map<int,int> retes;
    std::string film_state;
    int comment_num;
    std::vector<int> buyers_id;
    std::vector<Comment*> comments;
};

#endif