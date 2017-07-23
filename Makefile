ROOT=$(shell pwd)
SERVER=$(ROOT)/server
CLIENT=$(ROOT)/client
LOG=$(ROOT)/log
POOL=$(ROOT)/data_pool
COMM=$(ROOT)/comm
LIB=$(ROOT)/lib
WINDOW=$(ROOT)/window
CONF=$(ROOT)/conf
PLUGIN=$(ROOT)/plugin


SERVER_BIN=chat_system
CLIENT_BIN=chat_client


INCLUDE=-I$(POOL) -I$(LOG) -I$(COMM) -I$(LIB)/include -I$(WINDOW)
LDFLAGS= -L$(LIB)/lib -lpthread -ljson -lncurses 

SERVER_OBJ=$(shell ls $(SERVER) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(LOG) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(POOL) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(COMM) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
CLIENT_OBJ=$(shell ls $(CLIENT) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/g')
CLIENT_OBJ+=$(shell ls $(LOG) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
CLIENT_OBJ+=$(shell ls $(COMM) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
CLIENT_OBJ+=$(shell ls $(WINDOW) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')

CC=g++

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "linking [$^] to [$@] .....done"
$(CLIENT_BIN):$(CLIENT_OBJ) 
	@$(CC) -o $@ $^ $(LDFLAGS) 
	@echo "linking [$^] to [$@] .....done"

%.o:$(CLIENT)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "comping [$^] to [$@]......done"
%.o:$(SERVER)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "comping [$^] to [$@]......done"
%.o:$(POOL)/%.cpp
	@$(CC) -c $<
	@echo "comping [$^] to [$@]......done"
%.o:$(LOG)/%.cpp
	@$(CC) -c $<
	@echo "comping [$^] to [$@]......done"
%.o:$(COMM)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "comping [$^] to [$@]......done"
%.o:$(WINDOW)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "comping [$^] to [$@]......done"

.PHONY:debug
debug:
	echo $(SERVER_OBJ)
	echo $(CLIENT_OBJ)
.PHONY:output
output:
	mkdir -p output/server
	mkdir -p output/client
	mkdir -p output/server/log
	cp $(SERVER_BIN) output/server
	cp $(CLIENT_BIN) output/client
	cp $(PLUGIN)/ctl_server.sh output/server
	cp -rf $(CONF) output/server
.PHONY:clean
clean:
	rm -rf *.o $(SERVER_BIN) $(CLIENT_BIN) output


