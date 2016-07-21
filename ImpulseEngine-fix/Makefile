CXXFLAGS=-O3 -Wall -g

SOURCES= $(wildcard *.cpp)

OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

TARGET=$(lastword $(subst /, ,$(realpath .)))

LINKS= -lglut -lGL -lGLU -lboost_system -lboost_chrono

CXX=g++

all: $(TARGET)
	@echo ImpulseEngine built

$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o impulseengine.bin $(OBJECTS) $(LINKS)

clean:
	rm -rf $(OBJECTS) $(TARGET) *.bin
