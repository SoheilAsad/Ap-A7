#ifndef GET_COMMAND
#define GET_COMMAND

#include <vector>
#include <map>

class GetCommand
{
public:
    void read_line();
    void separate_words_in_line();
    void separate_command_elements();
    std::vector< std::map<std::string,std::string> > get_command();
private:
    std::vector< std::string > command_line ;
    std::vector< std::map<std::string,std::string> > command_elements ;
};


#endif