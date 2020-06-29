CXX = clang++
CXXFLAGS = -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS = -fsanitize=address

VPATH = src
SRC = ./src
BIN = ./bin
OBJ = main.o 
EXEC = main.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)