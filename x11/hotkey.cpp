#include <stdio.h>
#include <X11/Xlib.h>

int main(){
	Window root;
	XEvent e;
	int F4, F6, a, b, c;

	//Open the display
	Display *dpy = XOpenDisplay(0);
	if(!dpy)
		return 1;

	root = DefaultRootWindow(dpy);

	F4 = XKeysymToKeycode(dpy, XStringToKeysym("F4"));
	F6 = XKeysymToKeycode(dpy, XStringToKeysym("F6"));
	
	a = XKeysymToKeycode(dpy, XStringToKeysym("a"));
	b = XKeysymToKeycode(dpy, XStringToKeysym("b"));
	c = XKeysymToKeycode(dpy, XStringToKeysym("c"));

	printf("F4=%d\n",F4);
	printf("F6=%d\n",F6);
	printf("a=%d\n",a);
	printf("b=%d\n",b);
	printf("c=%d\n",c);

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
			else if(e.xkey.keycode == a)
				printf("a pressed\n");
			else if(e.xkey.keycode == b)
				printf("b pressed\n");
			else if(e.xkey.keycode == c)
				printf("c pressed\n");
		}
	}

	XUngrabKey(dpy, F4, 0, root);
	XUngrabKey(dpy, F6, 0, root);
	XUngrabKey(dpy, a, 0, root);
	XUngrabKey(dpy, b, 0, root);
	XUngrabKey(dpy, c, 0, root);
}
