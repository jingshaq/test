#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <thread>
#include <unistd.h>

int main(int argc, char **argv)
{
	Display *display;
	XEvent xevent;
	Window window;

	if( (display = XOpenDisplay(NULL)) == NULL )
		return -1;

	window = DefaultRootWindow(display);

	while(1) {

		XGrabKeyboard(display,
				window,
				1,
				GrabModeAsync,
				GrabModeAsync,
				CurrentTime);

		XNextEvent(display, &xevent);

		switch (xevent.type) {
		case KeyPress:
			printf("press: %d\n",xevent.xkey.keycode);
			break;
		case KeyRelease:
			printf("release: %d\n",xevent.xkey.keycode);
			break;
		case MappingNotify:
			printf("map notify: %ud\n",xevent.xkey.keycode);
			break;
		}

		XUngrabKeyboard(display,CurrentTime);
	}
	return 0;
}
