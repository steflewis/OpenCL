TARGET = $(shell find . -name "*.cpp" | head -n 1 | sed 's/\.cpp$$//')
CXXFLAGS = -O3 -g -Wall -Werror -ansi

all: $(TARGET)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -Iinclude/ -c $< -o $@

$(TARGET) : $(TARGET).o 
	$(CXX) $(CXXFLAGS) $< -lOpenCL -lpng  -o $@

clean :	
	rm -f *.o $(TARGET)
