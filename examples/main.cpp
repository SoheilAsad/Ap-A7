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
        server.get("/home.png", new ShowImage("static/home.png"));
        server.get("/", new ShowPage("static/home.html"));
        server.get("/c_home", new ShowPage("static/customer_home.html"));
        server.get("/p_home", new PublisherHomeHandler(channel));
        server.get("/login", new ShowPage("static/login.html"));
        server.post("/login", new LoginHandler(channel));
        server.get("/publish", new ShowPage("static/publish.html"));
        server.post("/publish", new PublishHandler(channel));
        server.get("/profile", new ProfileHandler(channel));
        server.post("/delete", new DeleteHandler(channel));

        server.run();
    }catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
}