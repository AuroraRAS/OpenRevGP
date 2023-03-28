# Makefile for building DetectionData

# Compiler settings
CC = gcc
CFLAGS = -O2 -Wall

# Name of the executable
TARGET = DetectionData

# Source files
SRCS = DetectionData.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile the source files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

