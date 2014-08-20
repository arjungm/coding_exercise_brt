CC := g++
CFLAGS := -g -Wall
INCLUDES := -Iinclude
SRCDIR := src

QuestionMenu.o: $(SRCDIR)/QuestionMenu.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/QuestionMenu.cpp

Browser.o: $(SRCDIR)/Browser.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/Browser.cpp

SExprReader.o: $(SRCDIR)/SExprReader.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/SExprReader.cpp

main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/main.cpp

test.o: $(SRCDIR)/test.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/test.cpp

all: QuestionMenu.o Browser.o SExprReader.o main.o test.o
	$(CC) $(CFLAGS) $(INCLUDES) -o main main.o Browser.o QuestionMenu.o SExprReader.o
	$(CC) $(CFLAGS) $(INCLUDES) -o test test.o SExprReader.o

clean:
	rm *.o
	rm test
	rm main
