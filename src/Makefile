TARGET = test.out
SRCS = main.cc mnist_loader.cc
OBJS = $(subst .cc,.o,$(SRCS))
CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall -o
RM = rm -f

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(TARGET) $(OBJS)

mnist_loader.o: mnist_loader.cc mnist_loader.h
	$(CC) $(CFLAGS) mnist_loader.cc

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
