CC=gcc
LDFLAGS=-LC:\msys64\mingw64\lib -lncursesw
PPFLAGS=-IC:\msys64\mingw64\include -DNCURSES_STATIC -I./include

bkstr_sys.exe: $(wildcard ./src/*.c)
	$(CC) $^ $(LDFLAGS) $(PPFLAGS) -o ./bin/$@

.PHONY: run
run:
	./bin/bkstr_sys.exe