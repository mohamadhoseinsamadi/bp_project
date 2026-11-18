CC = gcc
CFLAGS = -Wall -Wextra -O2
SRCS = main.c config.c incident.c log.c map.c simulation.c unit.c utils.c
TARGET = simulation

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe *.o log_*.txt

.PHONY: clean