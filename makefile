CC = gcc
CFLAGS = -I/opt/homebrew/include -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lm -I./src/platform
IFLAGS = -I./src/platform -I./src/gfx -I./src/math -I./src/scene -I./src/third_party -I./src/app
DEBUGFLAGS = -fsanitize=address
TEST_FILES := $(wildcard tests/src/*.c)
SRC_FILES := \
  $(wildcard src/*.c) \
  $(wildcard src/platform/*.c) \
  $(wildcard src/gfx/*.c) \
  $(wildcard src/math/*.c) \
  $(wildcard src/scene/*.c) \
  $(wildcard src/app/*.c)

build: ./build/window
./build/window:
	$(CC) $(SRC_FILES) $(DEBUGFLAGS) -o ./build/window $(CFLAGS) $(LDFLAGS) $(IFLAGS)
clean:
	rm ./build/window ./tests/build/testing
run:
	ASAN_OPTIONS=detect_leaks=1:leak_check_at_exit=0 ./build/window $(ARGS)
run-normal:
	./build/window $(ARGS)
tbuild:
		$(CC) $(TEST_FILES) $(SRC_FILES) -Iinclude -Itests/include $(DEBUGFLAGS) -o ./tests/build/testing $(CFLAGS) $(LDFLAGS)
trun:
		ASAN_OPTIONS=detect_leaks=1:leak_check_at_exit=0 ./tests/build/testing
trun-normal:
	./tests/build/testing
docs:
	pdflatex docs/docs-latex/main.tex
	latexmk -pdf -pvc docs/docs-latex/main.tex 

