CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC = CSEP/community.c src/gen_tokenizer.c src/io.c
OBJ = $(SRC:.c=.o)
TARGET = CSEP
CSEP/community.o: CSEP/community.c include/gen_tokenize.h include/io.h

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
