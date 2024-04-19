
CC = g++
FLAGS = -Wall -Werror -Wno-unknown-pragmas -std=c++23 -Wpedantic
CLASSES_PATH = -I inc -I classes

SRC = src
MAIN = main.cpp
TARGET = app.exe

all: clean build

build: $(TARGET)

debug: FLAGS += -g
debug: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SRC)/$(MAIN)
	$(CC) $(FLAGS) $< -o $@ $(CLASSES_PATH)