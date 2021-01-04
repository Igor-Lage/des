CC= gcc
CXXFLAGS= -Wall -Werror -ansi --pedantic -O3

CPP_O_FILE = keygen.o des.o fk.o main.o
LIB = -lm


all: $(CPP_O_FILE)
	$(CC) $(CXXFLAGS) -o des $(CPP_O_FILE) $(LIB)

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf des
