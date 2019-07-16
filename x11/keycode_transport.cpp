#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

int main(void) 
{
	Display *display;
	char *ptr;
	char c[2] = {0, 0};
	KeySym ksym;
	KeyCode kcode;
	display = XOpenDisplay(0);
	ptr = "a Test";
	while (*ptr) {
		c[0] = *ptr;
		ksym = XStringToKeysym(c);
		printf("ksym = %d\n", ksym);
		printf("Before XKeysymToKeycode(): %s\n", XKeysymToString(ksym));
		kcode = XKeysymToKeycode(display, ksym);
		printf("Key code after XKeysymToKeycode(): %s\n", XKeysymToString(XKeycodeToKeysym(display, kcode, 0)));
		ptr++;
	}
	XCloseDisplay(display);
	return 0;
}

