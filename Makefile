# Digital Diary Makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = digital_diary
SOURCES = main.cpp diary.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean install

# Dependencies
main.o: main.cpp diary.h
diary.o: diary.cpp diary.h