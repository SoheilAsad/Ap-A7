#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <iostream>
#include "channel.h"

class SignupHandler : public RequestHandler {
public:
    SignupHandler(Channel* _channel) : channel(_channel){}
    Response *callback(Request *);
private:
    Channel* channel;
};

class LoginHandler : public RequestHandler {
public:
    LoginHandler(Channel* _channel) : channel(_channel){}
    Response *callback(Request *);
private:
    Channel* channel;
};

#endif
