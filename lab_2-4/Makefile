CXX = g++

CXXFLAGS = -O2

TARGET1 = lab2_3
TARGET2 = lab4

SRC1 = lab2_3.cpp
SRC2 = lab4.cpp

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(SRC1)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TARGET2): $(SRC2)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGET1) $(TARGET2)

rebuild: clean all

.PHONY: all clean rebuild
