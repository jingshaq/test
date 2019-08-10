#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("Cursor Setting"));
    this->setCursor(QCursor(QPixmap("D:/test.bmp")));
    m_penAction = new QAction(this);
    m_penAction->setIcon(QIcon("D:/test.bmp"));
    m_brushAction = new QAction(this);
    m_brushAction->setIcon(QIcon("D:/test1.bmp"));
    m_eraseAction = new QAction(this);
    m_eraseAction->setIcon(QIcon("D:/test2.bmp"));

    ui->mainToolBar->addAction(m_penAction);
    ui->mainToolBar->addAction(m_brushAction);
    ui->mainToolBar->addAction(m_eraseAction);

    connect(ui->mainToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(showCursorSlot(QAction*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCursorSlot(QAction* action)
{
    if (action == m_penAction)
    {
        this->setCursor(QCursor(QPixmap("D:/test.bmp")));
    }
    else if (action == m_brushAction)
    {
        this->setCursor(QCursor(QPixmap("D:/test1.bmp")));
    }
    else
    {
        this->setCursor(QCursor(QPixmap("D:/test2.bmp")));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        this->setCursor(QCursor(QPixmap("D:/test.bmp")));
    }
}


