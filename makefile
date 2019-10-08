still: main.cc
	g++ -g -o still main.cc -Wall -Wextra -Werror -O2 -ftrapv `pkg-config --cflags --libs opencv`

clean: -rm still *.jpeg