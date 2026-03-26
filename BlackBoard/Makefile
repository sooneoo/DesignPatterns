CC=gcc


CACHE = .cache
RELEASE = $(CACHE)/release
TARGET = blackboard

CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -O2
CFLAGS += -Isrc/include/

LIBS += 


OBJS += $(CACHE)/main.o


all: build


build: env $(RELEASE)/$(TARGET)


$(RELEASE)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(RELEASE)/$(TARGET)


$(CACHE)/main.o: src/blackboard/main.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: exec clean env


exec: build
	$(RELEASE)/$(TARGET)


clean:
	rm -rvf $(CACHE)


env: 
	mkdir -pv $(CACHE)
	mkdir -pv $(RELEASE)


