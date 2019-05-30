#include "handlers.hpp"
#include <sstream>
#include <string>
#include <fstream>


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

Response* PublisherHomeHandler::callback(Request *req)
{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    ifstream f("./static/film_table");
    if(f) {
        ostringstream ss;
        ss << f.rdbuf();
        body = ss.str();
    }
    channel->get_publisher_films_info(&body);
    body += "</table>\n";
    body += "</body>\n";
    body += "</html>";
    cerr <<body;
    res->setBody(body);
    return res;
}


// Response *UploadHandler::callback(Request *req) {
//   string name = req->getBodyParam("file_name");
//   string file = req->getBodyParam("file");
//   cout << name << " (" << file.size() << "B):\n" << file << endl;
//   Response *res = Response::redirect("/");
//   return res;
// }

// ColorHandler::ColorHandler(string filePath) : TemplateHandler(filePath) {}

// map<string, string> ColorHandler::handle(Request *req) {
//   map<string, string> context;
//   string newName = "I am " + req->getQueryParam("name");
//   context["name"] = newName;
//   context["color"] = req->getQueryParam("color");
//   return context;
// }

