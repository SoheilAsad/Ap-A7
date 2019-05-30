#include <iostream>

#include "exception.h"
#include "command_handeler.h"
#include "channel.h"

using namespace std;

map<string,string> make_admin_info()
{
    map<string,string> admin ;
    admin.insert(pair<string,string>("username","admin"));
    admin.insert(pair<string,string>("password","admin"));
    admin.insert(pair<string,string>("email","admin@yahoo.com"));
    admin.insert(pair<string,string>("age","18"));
    return admin;
}

int main()
{
    CommandHandeler* command_handeler = new CommandHandeler();
    Channel* channel = new Channel(command_handeler,make_admin_info());
    while (true)
    {
        command_handeler->read_line();
        channel->set_command_elements(command_handeler->get_command());
        try{
            channel->do_primitive_commands();
        }catch(Exception &ex){
            ex.what();
        }
        command_handeler->clear_the_map();

        while(channel->get_channel_loop())
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
}