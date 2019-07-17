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
    int F4, F6;
    if( (display = XOpenDisplay(NULL)) == NULL )
        return -1;



    window = DefaultRootWindow(display);
//    XAllowEvents(display, AsyncBoth, CurrentTime);

//    XGrabKey(display,XKeysymToKeycode(display,XK_D),None,window,1,GrabModeAsync,GrabModeAsync);

//    F4 = XKeysymToKeycode(display, XStringToKeysym("F5"));
    //XGrabKey(display, F4, 0, window, True, GrabModeAsync, GrabModeAsync);
//    int result = XGrabKey(display, F4, 0, window, 1, GrabModeAsync, GrabModeAsync);
//    printf("F4 = %d\t result = %d\n",F4,result);
//    XGrabKeyboard(display,
//                 window,
//                 0,
//                 GrabModeAsync,
//                 GrabModeAsync,
//                 CurrentTime);


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
                printf("%d\n",xevent.xkey.keycode);
                break;
            case KeyRelease:
                printf("%d\n",xevent.xkey.keycode);
                break;
        case MappingNotify:
            printf("%ud\n",xevent.xkey.keycode);
            break;
        }

//        //if(xevent.xkey.keycode == 10)
        XUngrabKeyboard(display,CurrentTime);


        Window winFocus;
        int    revert;
         XGetInputFocus(display, &winFocus, &revert);
      XKeyEvent event = createKeyEvent(display, winFocus, window, true, xevent.xkey.keycode, 0);
      XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
       printf("keydown\n");

    usleep(10000);

    // Send a fake key release event to the window.XKeysymToKeycode(display,XK_D)
    event = createKeyEvent(display, winFocus, window, false, xevent.xkey.keycode, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    printf("keyup\n");
            //getchar();
    }
    getchar();
    return 0;
}
