
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <stdio.h>

void getMousePosition(int* mouseX,int* mouseY){
	Display* dpy;
	XEvent e;

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
			*mouseX = e.xmotion.x_root;
			*mouseY = e.xmotion.y_root;
			break;/*监测到点击后，记录鼠标坐标，便立即退出while循环*/
		}
	}

	XCloseDisplay(dpy);/*关闭x11 Display*/
}

int main(int argc, char *argv[]){
	int x,y;
	getMousePosition(&x,&y);
	printf("x=%d y=%d\n",x,y);
	return 0;
}


