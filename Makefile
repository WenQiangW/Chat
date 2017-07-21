ROOT=$(shell pwd)
SERVER=$(ROOT)/server
CLIENT=$(ROOT)/client
LOG=$(ROOT)/log
POOL=$(ROOT)/data_pool
COMM=$(ROOT)/comm
LIB=$(ROOT)/lib
WINDOW=$(ROOT)/window

SERVER_BIN=chat_system
CLIENT_BIN=chat_client


INCLUDE=-I$(POOL) -I$(LOG) -I$(COMM) -I$(LIB)/include -I$(WINDOW)
LDFLAGS=-lpthread -ljson -lncurses

SERVER_OBJ=$(shell ls $(SERVER) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(LOG) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(POOL) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
CLIENT_OBJ=$(shell ls $(CLIENT) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/g')
CLIENT_OBJ+=$(shell ls $(LOG) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
CLIENT_OBJ+=$(shell ls $(COMM) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
CLIENT_OBJ+=$(shell ls $(WINDOW) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')

CC=g++

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -L$(LIB)/lib
$(CLIENT_BIN):$(CLIENT_OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS) -L$(LIB)/lib

%.o:$(CLIENT)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(SERVER)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(POOL)/%.cpp
	$(CC) -c $<
%.o:$(LOG)/%.cpp
	$(CC) -c $<
%.o:$(COMM)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(WINDOW)/%.cpp
	$(CC) -c $< $(INCLUDE)

.PHONY:debug
debug:
	echo $(SERVER_OBJ)
	echo $(CLIENT_OBJ)

.PHONY:clean
clean:
	rm -f *.o $(SERVER_BIN) $(CLIENT_BIN)


