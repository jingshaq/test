#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(500, 300);

    output = NULL;
    input = NULL;

    btnStart = new QPushButton();
    btnStart->setParent(this);
    btnStart->setText("start");
    btnStart->setGeometry(50, 80, 130, 50);

    btnStop = new QPushButton();
    btnStop->setParent(this);
    btnStop->setText("stop");
    btnStop->setGeometry(200, 80, 130, 50);

    btnPlay = new QPushButton();
    btnPlay->setParent(this);
    btnPlay->setText("play");
    btnPlay->setGeometry(350, 80, 130, 50);
    connect(btnStart, SIGNAL(clicked()), this, SLOT(on_start_clicked()));
    connect(btnStop, SIGNAL(clicked()), this, SLOT(on_finish_clicked()));
    connect(btnPlay, SIGNAL(clicked()), this, SLOT(on_play_clicked()));

    volume = new QLabel(this);
    volume->setText("音量:");
    volume->setGeometry(50, 150, 130, 50);

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setGeometry(100, 165, 200, 20);
    slider->setMinimum(0);
    slider->setMaximum(100);

    value = new QLineEdit(this);
    value->setGeometry(320, 160, 30, 30);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(on_slider_changed()));

    mute = new QCheckBox("静音");
    mute->setParent(this);
    mute->setGeometry(400, 160, 130, 30);
    connect(mute, SIGNAL(clicked()), this, SLOT(on_checkbox_clicked()));
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


//测试读取录音数据
/*
void MainWindow::on_start_clicked()
{
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
    char buf[88*1024];
    QIODevice *io = input->start();
    while(1){
        int len =  io->read(buf, sizeof(buf));
        if (len > 0)
        {
            qDebug()<<"len = "<< len <<endl;
        }
        //QThread::msleep(1);
    }
}
*/

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
    char buf[10] = {0};
    int val = output->volume()*100;
    sprintf(buf, "%d", val);
    value->setText(buf);

    output->start(file);
    qDebug()<<"Playing...end"<<endl;
}

//设置音量
void MainWindow::on_slider_changed()
{
    float val = 0.0f;
    char buf[10] = {0};
    sprintf(buf, "%d", slider->value());
    value->setText(buf);
    if(output != NULL){
        val = slider->value()/100.0f;
        output->setVolume(val);
    }
    qDebug()<<"Set Volume..."<<endl;
}

//静量
void MainWindow::on_checkbox_clicked()
{
    if(output != NULL){
        output->setVolume(0);
        value->setText("0");
    }
    qDebug()<<"Set Mute..."<<endl;
}
