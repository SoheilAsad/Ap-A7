CC=g++
STD=-std=c++11 -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/channel.o: examples/channel.cpp examples/channel.h examples/publisher.h examples/customer.h examples/film.h examples/comment.h
	$(CC) $(CF) -c examples/channel.cpp -o $(BUILD_DIR)/channel.o

$(BUILD_DIR)/publisher.o: examples/publisher.cpp examples/channel.h examples/publisher.h examples/customer.h examples/film.h examples/comment.h
	$(CC) $(CF) -c examples/publisher.cpp -o $(BUILD_DIR)/publisher.o

$(BUILD_DIR)/customer.o: examples/customer.cpp examples/channel.h examples/publisher.h examples/customer.h examples/film.h examples/comment.h
	$(CC) $(CF) -c examples/customer.cpp -o $(BUILD_DIR)/customer.o

$(BUILD_DIR)/film.o: examples/film.cpp examples/channel.h examples/publisher.h examples/customer.h examples/film.h examples/comment.h
	$(CC) $(CF) -c examples/film.cpp -o $(BUILD_DIR)/film.o

$(BUILD_DIR)/comment.o: examples/comment.cpp examples/channel.h examples/publisher.h examples/customer.h examples/film.h examples/comment.h
	$(CC) $(CF) -c examples/comment.cpp -o $(BUILD_DIR)/comment.o

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp examples/channel.h
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp examples/channel.h
	$(CC) $(CF) -c examples/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/channel.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/customer.o $(BUILD_DIR)/film.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/template_parser.o 
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/channel.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/customer.o $(BUILD_DIR)/film.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/template_parser.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null