#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    setWindowTitle("Server");

    //create a tcp server object
    tcpServer = new QTcpServer(this);
    //bind + listen
    tcpServer->listen(QHostAddress::Any, 9527); //listen all network interfaces, and listen port 8888

    connect(tcpServer, &QTcpServer::newConnection, [=]
    {
        tcpSocket = tcpServer->nextPendingConnection(); //wait for the next pending connection

        //get the information of the current socket, ip address, port number
        QString ip = tcpSocket->peerAddress().toString();
        quint16 portNum = tcpSocket->peerPort();

        QString str = QString("%1:%2 Connected successfully!").arg(ip).arg(portNum);
        ui->textEditRead->setText(str);

        connect(tcpSocket, &QTcpSocket::readyRead, [=]
        {
            //get the text from the text edit write box
            QString str = tcpSocket->readAll();

            //append the new str to the current read box
            ui->textEditRead->append(str);
        });
    });
}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_buttonSend_clicked()
{
    if(!tcpSocket) return;
    //get the current text in the text box
    QString str = ui->textEditWrite->toPlainText();
    ui->textEditWrite->setText("");

    //then write it to the socket stack
    tcpSocket->write(str.toStdString().data());
}


void ServerWidget::on_buttonClose_clicked()
{
    if(!tcpSocket) return;
    //the tcp socket will disconected from the server
    tcpSocket->disconnectFromHost();
    //close the current tcp socket
    tcpSocket->close();
    tcpSocket = NULL;
}

