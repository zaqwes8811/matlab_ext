CXXFLAGS=-O3 -std=c++11 -Wall -g

SOURCES= $(wildcard *.cpp)

OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

TARGET=$(lastword $(subst /, ,$(realpath .)))

LINKS= -lglut -lGL -lGLU

CXX=g++

all: $(TARGET)
	@echo ImpulseEngine built

$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o impulseengine.bin $(OBJECTS) $(LINKS)

clean:
	rm -rf $(OBJECTS) $(TARGET) *.bin
