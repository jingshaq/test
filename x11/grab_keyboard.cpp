#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <thread>
#include <unistd.h>

XKeyEvent createKeyEvent(Display *display, Window &win,
		Window &winRoot, bool press,
		int keycode, int modifiers)
{
	XKeyEvent event;

	event.display     = display;
	event.window      = win;
	event.root        = winRoot;
	event.subwindow   = None;
	event.time        = CurrentTime;
	event.x           = 1;
	event.y           = 1;
	event.x_root      = 1;
	event.y_root      = 1;
	event.same_screen = True;
	event.keycode     = XKeysymToKeycode(display, keycode);
	event.state       = modifiers;

	if(press)
		event.type = KeyPress;
	else
		event.type = KeyRelease;

	return event;
}

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
