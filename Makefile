TARGET = main
CC = gcc
OBJECTS = build/main.o
SRC = src/main.c

all: mkdir $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) -lpthread

mkdir:
ifeq ($(OS),Windows_NT)
	if not exist build mkdir build
else
	mkdir -p build
endif

build/main.o: $(SRC)
	$(CC) -c $(SRC) -o build/main.o

clean:
ifeq ($(OS),Windows_NT)
	del /F /Q $(subst /,\,$(OBJECTS))
	if exist $(subst /,\,$(TARGET).exe) move $(subst /,\,$(TARGET).exe) .\build
else
	rm -f $(OBJECTS)
	if [ -f $(TARGET) ]; then mv $(TARGET) ./build; fi
endif