#include <iostream>

#include "exception.h"
#include "command_handeler.h"
#include "channel.h"

using namespace std;

int main()
{
    CommandHandeler* command_handeler = new CommandHandeler();
    Channel* channel = new Channel(command_handeler);
    while (true)
    {
        command_handeler->read_line();
        channel->set_command_elements(command_handeler->get_command());
        try{
            channel->do_primitive_commands();
        }catch(Exception &ex){
            ex.what();
            command_handeler->clear_the_map();
            continue;
        }
        command_handeler->clear_the_map();
        break;
    }
    while(true)
    {
        command_handeler->read_line();
        channel->set_command_elements(command_handeler->get_command());
        try{
            channel->do_command();
        }catch(Exception &ex){
            ex.what();
        }
        command_handeler->clear_the_map();
     }
}