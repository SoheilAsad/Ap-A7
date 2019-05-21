#include "command_handeler.h"

#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <regex>

#include "exception.h"

using namespace std;

CommandHandeler::CommandHandeler()
	:command_line(vector<string>())
{
}

void CommandHandeler::clear_the_map()
{
	command_elements.clear();
	command_line.clear();
}

void CommandHandeler::split_up_in_space_place(string& all_words, int space_place)
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

void CommandHandeler::separate_words_in_line(string all_words)
{
	for (int i = 0; i < all_words.size(); i++)
	{
		if (all_words[i] == ' ')
		{
			split_up_in_space_place(all_words, i);
			i = -1;
		}
	}
	command_line.push_back(all_words);
}

void CommandHandeler::read_line()
{
    string all_line;
	while(true)
	{
		getline(cin,all_line);
		if(all_line != "")
			break;
	}
    separate_words_in_line(all_line);
    separate_command_elements();
}

void CommandHandeler::separate_command_elements()
{
	if(command_line.size() > 1)
    	separate_command_head_elements();
	if(command_line.size()%2 == 0)
    	for(int i = 2; i < command_line.size(); i+=2)
        	command_elements.insert(pair<string, string>(command_line[i], command_line[i+1]));
}

void CommandHandeler::separate_command_head_elements()
{
	command_elements.insert(pair<string, string>("order_type", command_line[0]));
	if(command_line[2]=="?")
	{
		command_elements.insert(pair<string, string>("order", command_line[1]+command_line[2]));
		command_line.erase(command_line.begin()+2,command_line.begin()+3);
	}
	else
		command_elements.insert(pair<string, string>("order", command_line[1]));
}

std::map<std::string,std::string> CommandHandeler::get_command()
{
    return  command_elements;
}

void CommandHandeler::check_singup_syntax_correction()
{
	if(!command_elements.count("username"))
		throw BadRequest();

	const regex pattern
    ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if(!regex_match(command_elements["email"], pattern))
		throw BadRequest();
        

	try{
        stoi(command_elements["password"]);
		stoi(command_elements["age"]);
    }catch(exception ex){
        throw BadRequest();
    }
}
void CommandHandeler::check_login_syntax_correction()
{
	if(command_elements.size() != 4)
		throw BadRequest();

	if(!command_elements.count("username"))
		throw BadRequest();

	try{
        stoi(command_elements["password"]);
    }catch(exception ex){
        throw BadRequest();
    }
}

void CommandHandeler::check_film_publishing_syntax_correction()
{
	if(command_elements.size() != 8)
		throw BadRequest();

	if(!command_elements.count("name") || !command_elements.count("summary") ||
		!command_elements.count("director"))
		throw BadRequest();
	
	try{
        stoi(command_elements["year"]);
		stoi(command_elements["length"]);
		stoi(command_elements["price"]);
    }catch(exception ex){
        throw BadRequest();
    }
}

void CommandHandeler::check_getting_money_syntax_correction()
{
	if(command_elements.size() != 2)
		throw BadRequest();
}

void CommandHandeler::check_replies_syntax_correction()
{
	if(command_elements.size() != 5)
		throw BadRequest();
	
	if(!command_elements.count("content"))
		throw BadRequest();
	
	try{
        stoi(command_elements["film_id"]);
		stoi(command_elements["comment_id"]);
    }catch(exception ex){
        throw BadRequest();
    }
}

void CommandHandeler::check_following_syntax_correction()
{
	if(command_elements.size() != 3)
		throw BadRequest();
	
	try{
        stoi(command_elements["user_id"]);
    }catch(exception ex){
        throw BadRequest();
    }
}

void CommandHandeler::check_increase_money_syntax_correction()
{
	if(command_elements.size() != 3)
		throw BadRequest();
	
	try{
        stoi(command_elements["amount"]);
    }catch(exception ex){
        throw BadRequest();
    }
}

void CommandHandeler::check_buy_film_syntax_correction()
{
	if(command_elements.size() != 3)
		throw BadRequest();
	
	try{
        stoi(command_elements["film_id"]);
    }catch(exception ex){
        throw BadRequest();
    }
}

void CommandHandeler::check_rate_film_syntax_correction()
{
	if(command_elements.size() != 4)
		throw BadRequest();
	
	try{
        stoi(command_elements["film_id"]);
		stoi(command_elements["score"]);
    }catch(exception ex){
        throw BadRequest();
    }

	if(stoi(command_elements["score"]) < 1 || stoi(command_elements["score"]) > 10)
		throw BadRequest();
}

void CommandHandeler::check_comment_film_syntax_correction()
{
	if(command_elements.size() != 4)
		throw BadRequest();
	
	if(!command_elements.count("content"))
		throw BadRequest();

	try{
        stoi(command_elements["film_id"]);
    }catch(exception ex){
        throw BadRequest();
    }
}

void CommandHandeler::check_show_publisher_films_syntax_correction()
{
	if(command_elements.count("min_rate"))
		try{
        	stoi(command_elements["min_rate"]);
		}catch(exception ex){
        	throw BadRequest();
    	}
	if(command_elements.count("min_year"))
		try{
        	stoi(command_elements["min_year"]);
		}catch(exception ex){
        	throw BadRequest();
    	}
	if(command_elements.count("price"))
		try{
    		stoi(command_elements["price"]);
		}catch(exception ex){
        	throw BadRequest();
    	}
	if(command_elements.count("max_year"))
		try{
        	stoi(command_elements["max_year"]);
		}catch(exception ex){
        	throw BadRequest();
    	}
}

void CommandHandeler::check_get_notification_syntax_correction()
{
	if(command_elements.size() != 4)
		throw BadRequest();
	
	if(command_elements["read"] != "?")
		throw BadRequest();

	try{
    	stoi(command_elements["limit"]);
	}catch(exception ex){
    	throw BadRequest();
    }
}

void CommandHandeler::check_delete_comment_syntax_correction()
{
	if(command_elements.size() != 4)
		throw BadRequest();
	
	try{
        stoi(command_elements["film_id"]);
		stoi(command_elements["comment_id"]);
    }catch(exception ex){
        throw BadRequest();
    }
}

void CommandHandeler::check_edit_film_syntax_correction()
{
	try{
        stoi(command_elements["film_id"]);
    }catch(exception ex){
        throw BadRequest();
    }

	if(command_elements.count("year"))
		try{
    		stoi(command_elements["year"]);
		}catch(exception ex){
        	throw BadRequest();
    	}
	if(command_elements.count("length"))
		try{
        	stoi(command_elements["length"]);
		}catch(exception ex){
        	throw BadRequest();
    	}
}