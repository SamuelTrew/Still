still: main.cc
	g++ -g -o still main.cc main.hh -Wall -Wextra -Werror -O2 -ftrapv `pkg-config --cflags --libs opencv`

clean: -rm still *.jpeg