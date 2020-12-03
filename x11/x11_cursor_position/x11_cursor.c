
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <stdio.h>

typedef struct POINT{
	int x;
	int y;
}POINT;

void getMousePosition(POINT *pos)
{
    Display* dpy;
    XEvent e;
    int mouseX=-1,mouseY=-1;

    dpy = XOpenDisplay(NULL);
    Window root = XDefaultRootWindow(dpy);
    Window root_return;
    Window child_return;
    int root_x_return;
    int root_y_return;
    int win_x_return;
    int win_y_return;
    unsigned int mask_return;

    while (1){
        if (XQueryPointer(dpy, root, &root_return, &child_return, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return) == True){
            mouseX = root_x_return;
            mouseY = root_y_return;
            break;
        }
    }

    if(mouseX >=0 && mouseY >=0){
        pos->x = mouseX;
        pos->y = mouseY;
    }
    XCloseDisplay(dpy);
}

void getMousePosition0(POINT *pos)
{
	Display* dpy;
	XEvent e;
	int mouseX=-1,mouseY=-1;

	dpy = XOpenDisplay(NULL);/*获取默认的x11 Display*/
	//关注全局鼠标点击事件,注意该函数必须调用，否则XNextEvent()无法捕获到鼠标点击事件
	XGrabPointer(dpy,
			DefaultRootWindow(dpy),
			1,
			PointerMotionMask | ButtonPressMask | ButtonReleaseMask ,/*依次表示鼠标的移动、按下、抬起事件掩码*/
			GrabModeAsync,
			GrabModeAsync,
			None,
			None,
			CurrentTime);/*CurrentTime == 0,是宏定义*/

	while(1){
		//使用如下事件模拟鼠标点击事件
		XTestFakeButtonEvent(dpy,1,1,CurrentTime);//鼠标按下Press
		XTestFakeButtonEvent(dpy,1,0,CurrentTime);//鼠标抬起Release

		//XNextEvent()会阻塞等待事件产生
		XNextEvent(dpy,&e);
		if(e.type == ButtonPress){/*监测到鼠标点击事件*/
			mouseX = e.xmotion.x_root;
			mouseY = e.xmotion.y_root;
			break;/*监测到点击后，记录鼠标坐标，便立即退出while循环*/
		}
	}

	if(mouseX >=0 && mouseY >=0){
		pos->x = mouseX;
		pos->y = mouseY;
	}
	XCloseDisplay(dpy);/*关闭x11 Display*/
}

int main(int argc, char *argv[]){
	POINT pos;
	getMousePosition(&pos);
	printf("x=%d y=%d\n",pos.x,pos.y);
	return 0;
}


