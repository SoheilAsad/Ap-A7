#include "film.h"

#include <vector>
#include <string>
#include <map>

#include "comment.h"
#include "exception.h"

using namespace std;

Film::Film(int _id, map<string,string> command_elements, int _publisher_id)
    : buyers_id(vector<int>())
{
    id = _id;
    year = stoi(command_elements["year"]);
    length = stoi(command_elements["length"]);
    price = stoi(command_elements["price"]);
    summery = command_elements["summary"];
    director = command_elements["director"];
    publisher_id = _publisher_id;
    film_state = "on";
    comment_num = 1;
}

int Film::get_id()
{
    return id;
}

Comment* Film::find_comment(int comment_id)
{
    for(int i = 0; i < comments_list.size(); i++)
        if(comments_list[i]->get_id() == comment_id)
            return comments_list[i];
    return NULL;
}

int Film::get_comment_writer_id(int comment_id)
{
    Comment* comment = find_comment(comment_id);
    if(comment == NULL)
        throw NotFound();
    return comment->get_writer_id();
}

void Film::write_repley_in_comment_box(int comment_id,string content)
{
    Comment* comment = find_comment(comment_id);
    if(comment == NULL)
        throw NotFound();
    comment->write_repley(content);
}