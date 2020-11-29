CC=g++
CF=-std=c++11 -ggdb
OBJS=pdriver.o visualizer.o colors.o board.o gui.o
OUTPUT=pdriver

all: $(OBJS)
	$(CC) $(CF) $(OBJS) -o $(OUTPUT) -lSDL2 -lSDL2_ttf

%.o: %.cpp
	$(CC) $(CF) -c $< -o $@

clean:
	rm -f *.o
	rm $(OUTPUT)