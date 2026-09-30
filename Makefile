CC = gcc
CFLAGS = -Wall -Wextra -g -pthread
TARGET = app
OBJS = main.o pthreadfuncs.o
OUTPUT = output.log trace.log

.PHONY: all clean run log

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

log:
	cat output.log

clean:
	rm -f $(OBJS) $(TARGET) $(OUTPUT)

