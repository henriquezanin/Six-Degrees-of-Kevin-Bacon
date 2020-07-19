UNAME_S := $(shell uname -s)
all: compile

compile:
ifeq (${UNAME_S},Linux)
	@gcc -o bin/sixDegree sources/*.c -I includes/ -Wall -lm -ansi
endif
ifeq ($(UNAME_S),Darwin)
	@gcc-9 sources/*.c -o bin/sixDegree -I includes/ -Wall -ansi
endif
run:
	@bin/sixDegree
clean:
	@rm bin/sixDegree
