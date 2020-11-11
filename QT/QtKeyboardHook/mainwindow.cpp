#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QKeyEvent>
#include <windows.h>
#include <winuser.h>

#pragma comment(lib,"user32.lib")

#define WINDOWS_HOOK_MODE 1  // 1: use windows hook, 0: use Qt KeyEvent

HHOOK keyHook=NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(WINDOWS_HOOK_MODE){
        setHook();
    }
    qDebug("Started");
}

MainWindow::~MainWindow()
{
    if(WINDOWS_HOOK_MODE){
        unHook();
    }
    delete ui;
}

LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam )
{
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    if(nCode == HC_ACTION)
    {
        if((WM_KEYDOWN == wParam) || (WM_SYSKEYDOWN == wParam))
        {
            qDebug("KEY Down vkCode: %x, %d, extendKey: %d",pkbhs->vkCode, pkbhs->vkCode, pkbhs->flags & 0x01);
        }
        else
        {
            //qDebug("KEY Up vkCode: %x, %d, extendKey: %d",pkbhs->vkCode, pkbhs->vkCode, pkbhs->flags & 0x01);
        }

        return true;
    }

    return CallNextHookEx(keyHook, nCode, wParam, lParam);
}

void MainWindow::setHook()
{
    if(NULL == keyHook)
    {
        keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyProc, GetModuleHandle(NULL), 0);
    }
}

void MainWindow::unHook()
{
    if(NULL != keyHook)
    {
        UnhookWindowsHookEx(keyHook);
        keyHook = NULL;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int nativeScanCode = event->nativeScanCode();
    int nativeModifiers = event->nativeModifiers();

    qDebug(" --- key press 0x%x---%d" , key, key);
    qDebug(" --- nativeScanCode press 0x%x---%d" , nativeScanCode, nativeScanCode);
    qDebug(" --- nativeModifiers press 0x%x---%d" , nativeModifiers, nativeModifiers);
    qDebug() << "";
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
//    int key = event->key();
//    int nativeScanCode = event->nativeScanCode();
//    qDebug(" --- key press 0x%x---%d" , key, key);
//    qDebug(" key release 0x%x---%d" , nativeScanCode, nativeScanCode) ;
}


