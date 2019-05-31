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

class PublisherHomeHandler : public RequestHandler {
public:
    PublisherHomeHandler(Channel* _channel) : channel(_channel){}
    Response *callback(Request *);
private:
    Channel* channel;
};

class PublishHandler : public RequestHandler {
public:
    PublishHandler(Channel* _channel) : channel(_channel){}
    Response *callback(Request *);
private:
    Channel* channel;
};

class ProfileHandler : public RequestHandler {
public:
    ProfileHandler(Channel* _channel) : channel(_channel){}
    Response *callback(Request *);
private:
    Channel* channel;
};

class DeleteHandler : public RequestHandler {
public:
    DeleteHandler(Channel* _channel) : channel(_channel){}
    Response *callback(Request *);
private:
    Channel* channel;
};

#endif
