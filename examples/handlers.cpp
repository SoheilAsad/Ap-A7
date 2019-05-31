#include "handlers.hpp"
#include <sstream>
#include <string>
#include <fstream>


using namespace std;

Response *SignupHandler::callback(Request *req) {
    Response *res;
    map<string,string> command;
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
    res->setSessionId(to_string(channel->get_user_id()));
    return res;
}

Response *LoginHandler::callback(Request *req) {
    Response *res;
    map<string,string> command;
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
    res->setSessionId(to_string(channel->get_user_id()));
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
    channel->get_publisher_films_info(&body,req->getQueryParam("director"));
    body += "</table>\n";
    body += "<form action=\"/publish\" method=\"get\">\n";
    body += "<button type=\"submit\" >publish film</button>\n";
    body += "</form>\n";
    body += "<h4>Films</h4>\n";
    body += "<table id=\"t01\">\n";
    body += "<tr>\n";
    body += "<th>Name</th>\n";
    body += "<th>Price</th>\n";
    body += "<th>Year</th>\n";
    body += "<th>Length</th>\n";
    body += "<th>Rate</th>\n";
    body += "<th>Director</th>\n";
    body += "</tr>\n";
    channel->get_another_films_info(&body);
     body += "</table>\n";
    body += "</body>\n";
    body += "</html>";
    res->setBody(body);
    return res;
}

Response* PublishHandler::callback(Request *req)
{
    Response *res;
    map<string,string> command;
    command["name"] = req->getBodyParam("name");
    command["price"] = req->getBodyParam("price");
    command["director"] = req->getBodyParam("director");
    command["length"] = req->getBodyParam("length");
    command["year"] = req->getBodyParam("year");
    command["summary"] = req->getBodyParam("summary");
    channel->set_command_elements(command);
    channel->publish_the_film();
    res = Response::redirect("/p_home");
    return res;
}

Response* ProfileHandler::callback(Request *req)
{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    if(req->getQueryParam("amount") != "")
        channel->increase_money(req->getQueryParam("amount"));
    string body;
    ifstream f("./static/profile");
    if(f) {
        ostringstream ss;
        ss << f.rdbuf();
        body = ss.str();
    }
    channel->get_buyed_films_info(&body);
    body += "</table>\n";
    body += "<h4>Your Credit : " + to_string(channel->get_user_money()) + "</h4>";
    body += "<form action=\"/profile\" method=\"get\">\n";
    body += "<input name=\"amount\" type=\"text\" placeholder=\"amount\" />";
    body += "<button type=\"submit\" >add cretid</button>\n";
    body += "</body>\n";
    body += "</html>";
    res->setBody(body);
    return res;
}

Response* DeleteHandler::callback(Request *req)
{
    Response *res;
    int film_id = stoi(req->getQueryParam("id"));
    channel->delete_film(film_id);
    res = Response::redirect("/p_home");
    return res;
}

Response* DetailHandler::callback(Request *req)
{
     Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>\n";
    body += "<html>\n";
    body += "<body>\n";
    body += "<h2>Film Details</h2>\n";
    channel->get_film_details(stoi(req->getQueryParam("id")),&body);
    body += "</body>\n";
    body += "</html>\n";
    res->setBody(body);
    return res;
}