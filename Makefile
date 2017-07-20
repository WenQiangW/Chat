ROOT=$(shell pwd)
SERVER=$(ROOT)/server
CLIENT=$(ROOT)/client
LOG=$(ROOT)/log
POOL=$(ROOT)/data_pool

SERVER_BIN=chat_system
CLIENT_BIN=chat_client

INCLUDE=-I$(POOL) -I$(LOG)
LDFLAGS=-lpthread

SERVER_OBJ=$(shell ls $(SERVER) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(LOG) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(POOL) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')
CLIENT_OBJ=$(shell ls $(CLIENT) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/g')
CLIENT_OBJ+=$(shell ls $(LOG) | grep -E '\.cpp$$' | sed 's/\.cpp/\.o/')

CC=g++

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
$(CLIENT_BIN):$(CLIENT_OBJ)
	$(CC) -o $@ $^

%.o:$(CLIENT)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(SERVER)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(POOL)/%.cpp
	$(CC) -c $<
%.o:$(LOG)/%.cpp
	$(CC) -c $<


.PHONY:debug
debug:
	echo $(SERVER_OBJ)

.PHONY:clean
clean:
	rm -f *.o $(SERVER_BIN) $(CLIENT_BIN)


