#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(500, 300);
    btnStart = new QPushButton();
    btnStart->setParent(this);
    btnStart->setText("start");
    btnStart->setGeometry(50, 100, 130, 50);

    btnStop = new QPushButton();
    btnStop->setParent(this);
    btnStop->setText("stop");
    btnStop->setGeometry(200, 100, 130, 50);

    btnPlay = new QPushButton();
    btnPlay->setParent(this);
    btnPlay->setText("play");
    btnPlay->setGeometry(350, 100, 130, 50);
    connect(btnStart, SIGNAL(clicked()), this, SLOT(on_start_clicked()));
    connect(btnStop, SIGNAL(clicked()), this, SLOT(on_finish_clicked()));
    connect(btnPlay, SIGNAL(clicked()), this, SLOT(on_play_clicked()));
}

MainWindow::~MainWindow()
{
    delete btnStart;
    delete btnStop;
    delete ui;
}
//开始录音
void MainWindow::on_start_clicked()
{
    file =new QFile();
    file->setFileName("D:\\test.wav");//设置其实设置音频文件的存放路径(输入音频名及存放路径)
    bool is_open =file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    if(!is_open)
    {
        qDebug()<<"打开失败失败"<<endl;
        exit(1);
    }

    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    QString str=info.deviceName();
    qDebug()<<"使用的录音设备是:"<<str<<endl;
    if(!info.isFormatSupported(format))
    {
        format = info.nearestFormat(format);
    }
    input = new QAudioInput(format, this);
    qDebug()<<"Recording...start"<<endl;
    input->start(file);

}

//停止录音
void MainWindow::on_finish_clicked()
{
    input->stop();
    file->close();
    qDebug()<<"Recording...end"<<endl;
}
//播放录音
void MainWindow::on_play_clicked()
{
     file->setFileName("D:\\test.wav");
     file->open(QIODevice::ReadOnly);
     qDebug()<<"Playing..."<<endl;
     QAudioFormat format;
     format.setSampleRate(48000);
     format.setChannelCount(2);
     format.setSampleSize(16);
     format.setCodec("audio/pcm");
     format.setByteOrder(QAudioFormat::LittleEndian);
     format.setSampleType(QAudioFormat::UnSignedInt);

     output = new QAudioOutput(format);
     output->start(file);
     qDebug()<<"Playing...end"<<endl;
}


