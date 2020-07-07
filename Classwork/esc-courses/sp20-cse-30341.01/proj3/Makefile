all: fractal fractalthread fractaltask

fractal: fractal.c
	gcc fractal.c gfx.c -g -Wall --std=c99 -lX11 -lm -o fractal

fractalthread: fractalthread.c
	gcc fractalthread.c gfx.c -g -Wall --std=c99 -lX11 -lm -lpthread -o fractalthread

fractaltask: fractaltask.c
	gcc fractaltask.c gfx.c -g -Wall --std=c99 -lX11 -lm -lpthread -o fractaltask

clean:
	rm -f fractal
