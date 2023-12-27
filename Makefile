CXX = g++
CXXFLAGS = -std=c++11

SRC_FILES = main.cpp 
HEADER_FILES = entities.h enums.h commands.h helpers.h utils.h core.h
TARGET = sputify.out

$(TARGET): $(SRC_FILES) $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

.PHONY: clean

clean:
	rm -f $(TARGET)
