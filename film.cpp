#include "film.h"

#include <vector>
#include <string>
#include <map>

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
    comment_num = 0;
}