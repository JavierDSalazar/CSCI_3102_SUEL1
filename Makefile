#https://makefiletutorial.com/
CC = g++
CFLAGS = -o
hello:
	echo "Hello, World"

chapter1:
	$(CC) $(CFLAGS) chap1 Algorithims.cpp chapter1_exercises.cpp

chapter3:
	$(CC) $(CFLAGS) chap3 Algorithims.cpp chapter3_exercises.cpp

clean:
	rm -f chapter1 chapter3