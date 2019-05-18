#ifndef CommandHandeler_H
#define CommandHandeler_H

#include <vector>
#include <map>

class CommandHandeler
{
public:
    CommandHandeler();
    void read_line();
    void separate_words_in_line(std::string all_line);
    void split_up_in_space_place(std::string& all_words, int space_place);
    void separate_command_elements();
    void separate_command_head_elements();
    std::map<std::string,std::string> get_command();
    
    void check_singup_syntax_correction();
    void check_login_syntax_correction();
    void check_film_publishing_syntax_correction();
    void check_getting_money_syntax_correction();
    void check_replies_syntax_correction();
    void check_following_syntax_correction();

private:
    std::vector< std::string > command_line ;
    std::map<std::string,std::string> command_elements ;
};

#endif