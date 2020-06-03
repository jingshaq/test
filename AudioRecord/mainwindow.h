#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultimedia>
#include <QFile>
#include <QDebug>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QTimer>
#include <QAudioOutput>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_start_clicked();

    void on_finish_clicked();

    void on_play_clicked();


private:
    Ui::MainWindow *ui;
    QFile *file;
    QAudioInput * input;
    QAudioOutput* output;
    QPushButton* btnStart;
    QPushButton* btnStop;
    QPushButton* btnPlay;
};

#endif // MAINWINDOW_H
