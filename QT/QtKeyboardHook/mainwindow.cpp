#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    count = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent *>(event);
        qDebug() << count++ <<" --- key press " << keyEvent->key();

        return true;
    }

    if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent *>(event);
        qDebug() << count<< " key release " << keyEvent->key();

        return true;
    }

    return QObject::eventFilter(obj, event);
}

