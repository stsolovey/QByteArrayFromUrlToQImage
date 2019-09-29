#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage image;
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl("https://avatars.mds.yandex.net/get-mpic/1767151/img_id7419673329120599287.jpeg/9hq")));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QByteArray qba;

    if(response->isFinished())
    {
        qDebug() << "QByteArray to QImage: Response finished";
        qba = response->readAll();
        image.fromData(qba, "webp");
        //image.loadFromData(qba, "webp");
    }
    else
        qDebug() << "QByteArray to QImage: Response is not finished";


    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

