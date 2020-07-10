all: compile

compile:
	@gcc -o bin/sixDegree sources/*.c -I includes/ -Wall

run:
	@bin/sixDegree