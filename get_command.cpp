#include <iostream>
#include <vector>
#include <map>

#include "get_command.h"
#include "exception.h"

using namespace std;

void GetCommand::split_up_in_space_place(string& all_words, int space_place)
{
	if (space_place == 0)
		all_words.erase(0, 1);
	else
	{
		string word = all_words.substr(0, space_place);
		all_words.erase(0, space_place + 1);
		command_line.push_back(word);
	}
}

void GetCommand::separate_words_in_line(string all_words)
{
	for (int i = 0; i < all_words.size(); i++)
	{
		if (all_words[i] == ' ' || all_words[i] == '?')
		{
			split_up_in_space_place(all_words, i);
			i = -1;
		}
	}
	command_line.push_back(all_words);
}

void GetCommand::read_line()
{
    string all_line;
    getline(cin,all_line);
    separate_words_in_line(all_line);
    if(command_line.size()%2 != 0)
        throw BadRequest();
    separate_command_elements();
}

void GetCommand::separate_command_elements()
{
    command_elements.insert(pair<string, string>("order_type", command_line[0]));
    command_elements.insert(pair<string, string>("order", command_line[1]));
    for(int i = 2; i < command_line.size(); i+=2)
        command_elements.insert(pair<string, string>(command_line[i], command_line[i+1]));
}

std::map<std::string,std::string> GetCommand::get_command()
{
    return  command_elements;
}

