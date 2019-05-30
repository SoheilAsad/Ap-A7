#include "handlers.hpp"

using namespace std;

Response *SignupHandler::callback(Request *req) {
    Response *res;
    map<string,string> command;
    command["order_type"] = "POST";
    command["order"] = "signup?";
    command["username"] = req->getBodyParam("username");
    command["password"] = req->getBodyParam("password");
    command["age"] = req->getBodyParam("age");
    command["email"] = req->getBodyParam("email");
    command["publisher"] = req->getBodyParam("publisher");
    if(channel->is_username_used(command["username"]))
        return res = Response::redirect("/");
    channel->set_command_elements(command);
    channel->singup_customer();
    if(channel ->is_customer_a_publisher())
        res = Response::redirect("/p_home");
    else 
        res = Response::redirect("/c_home");
    res->setSessionId("SID");
    return res;
}

Response *LoginHandler::callback(Request *req) {
    Response *res;
    map<string,string> command;
    command["order_type"] = "POST";
    command["order"] = "login?";
    command["username"] = req->getBodyParam("username");
    command["password"] = req->getBodyParam("password");
    channel->set_command_elements(command);
    if(!channel->is_customer_signup_before())
        return res = Response::redirect("/");
    channel->login_customer();
    if(channel ->get_user_type() == "publisher")
        res = Response::redirect("/p_home");
    else 
        res = Response::redirect("/c_home");
    res->setSessionId("SID");
    return res;
}


