files := $(wildcard src/*.c)


run: out/ge
	./out/ge


out/ge: $(files)
	gcc -Wall -Werror -o out/ge $(files) $(shell pkg-config --cflags --libs sdl2) -lSDL2_image -lSDL2_ttf -lm


dbg: $(files)
	clang -g -Wall -Werror -o dbg $(files) $(shell pkg-config --cflags --libs sdl2) -lSDL2_image -lSDL2_ttf -lm
	gdb ./dbg
	rm dbg
