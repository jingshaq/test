#include <stdio.h>
#include <X11/Xlib.h>

int main(){
	Window root;
	XEvent e;
	int F4, F6;

	//Open the display
	Display *dpy = XOpenDisplay(0);
	if(!dpy)
		return 1;

	root = DefaultRootWindow(dpy);

	F4 = XKeysymToKeycode(dpy, XStringToKeysym("F4"));
	F6 = XKeysymToKeycode(dpy, XStringToKeysym("F6"));

	//Register the keys
	XGrabKey(dpy, F4, 0, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, F6, 0, root, True, GrabModeAsync, GrabModeAsync);

	//Wait for events
	for(;;){
		XNextEvent(dpy, &e);
		if(e.type == KeyPress){
			if(e.xkey.keycode == F4)
				break;
			else if(e.xkey.keycode == F6)
				printf("F6 pressed\n");
		}
	}

	XUngrabKey(dpy, F4, 0, root);
	XUngrabKey(dpy, F6, 0, root);
}
