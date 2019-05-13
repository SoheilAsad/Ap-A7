#ifndef GET_COMMAND
#define GET_COMMAND

#include <vector>
#include <map>

class GetCommand
{
public:
    void read_line();
    void separate_words_in_line(std::string all_line);
    void split_up_in_space_place(std::string& all_words, int space_place);
    void separate_command_elements();
    std::map<std::string,std::string> get_command();
private:
    std::vector< std::string > command_line ;
    std::map<std::string,std::string> command_elements ;
};

#endif