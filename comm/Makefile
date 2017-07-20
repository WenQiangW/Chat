LIB=/home/admin/Project/Chat/lib

data:data.o base_json.o
	g++ -o $@ $^ -ljson -L$(LIB)/lib 

%.o:%.cpp
	g++ -c $< -I$(LIB)/include

.PHONY:clean
clean:
	rm -f data *.o
