CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = main.cpp raw.cpp input_output.cpp
HEADERS = raw.h input_output.h



OUTPUT = comp

OBJ = $(SRC:.cpp=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CXX) $(OBJ) -o $(OUTPUT)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(OUTPUT)


