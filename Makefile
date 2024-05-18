#https://makefiletutorial.com/
CC = g++
CFLAGS = -Iinclude -o
INC = include
hello:
	echo "Hello, World"

chapter1:
	$(CC) $(CFLAGS) chap1 Algorithims.cpp chapter1_exercises.cpp

chapter3:
	$(CC) $(CFLAGS) chap3 Algorithims.cpp chapter3_exercises.cpp

# Pattern rule to compile .cpp files to .o files, considering header files in include directory
%.o: %.cpp $(INC)/%.h
	$(CC) -I$(INC) -c $< -o $@

clean:
	rm -f *.o chapter1 chapter3