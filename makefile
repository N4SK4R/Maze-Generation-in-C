all: app

app:
	gcc src/*.c -o app `sdl2-config --cflags --libs`