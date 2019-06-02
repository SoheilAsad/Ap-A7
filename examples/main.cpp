#include "handlers.hpp"
#include "my_server.hpp"
#include "channel.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    try {
        MyServer server(argc > 1 ? atoi(argv[1]) : 5000);

        Channel* channel = new Channel();
        server.setNotFoundErrPage("static/404.html");
        server.get("/signup", new ShowPage("static/signup.html"));
        server.post("/signup", new SignupHandler(channel));
        server.get("/bad_request", new ShowPage("static/bad_request.html"));
        server.get("/bad_name", new ShowPage("static/bad_name.html"));
        server.get("/", new ShowPage("static/home.html"));
        server.get("/c_home", new CustomerHomeHandler(channel));
        server.get("/p_home", new PublisherHomeHandler(channel));
        server.get("/login", new ShowPage("static/login.html"));
        server.post("/login", new LoginHandler(channel));
        server.get("/publish", new ShowPage("static/publish.html"));
        server.post("/publish", new PublishHandler(channel));
        server.get("/profile", new ProfileHandler(channel));
        server.post("/delete", new DeleteHandler(channel));
        server.get("/detail", new DetailHandler(channel));
        server.post("/buy", new BuyHandler(channel));
        server.post("/rate", new RateHandler(channel));
        server.post("/comment", new CommentHandler(channel));

        server.run();
    }catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
}