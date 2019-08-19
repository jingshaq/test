#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void showCursorSlot(QAction*);

private:
    Ui::MainWindow *ui;
    QAction *m_penAction;
    QAction *m_brushAction;
    QAction *m_eraseAction;
};

#endif // MAINWINDOW_H
