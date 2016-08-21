TARGET = test.out
SRCS = main.cc mnist_loader.cc
OBJS = $(subst .cc,.o,$(SRCS))
CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall -o
RM = rm -f

$(TARGET): $(OBJS)
	$(CC) $(DEBUG) $(LFLAGS) $(TARGET) $(OBJS)

mnist_loader.o: mnist_loader.cc mnist_loader.h
	$(CC) $(CFLAGS) $(DEBUG) mnist_loader.cc

main.o: main.cc
	$(CC) $(CFLAGS) $(DEBUG) main.cc

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
