#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    setWindowTitle("Client");

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::connected, [=]
    {
        ui->textEditRead->setText("Connected to the server successfully!");
    });

    connect(tcpSocket, &QTcpSocket::readyRead, [=]
    {
        //take all the sent text from the server then display it in the message box
        QByteArray ary = tcpSocket->readAll();
        ui->textEditRead->append(QString(ary));
    });

    connect(tcpSocket, &QTcpSocket::disconnected, [=]
    {
        ui->textEditRead->append("Disconnected from the server!");
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    if(ui->lineEditIP == NULL || ui->lineEditPort == NULL) return;

    QString ip = ui->lineEditIP->text();
    quint16 portNum = ui->lineEditPort->text().toInt();
    tcpSocket->connectToHost(ip, portNum);
}


void ClientWidget::on_buttonSend_clicked()
{
    if(!tcpSocket) return;
    //get the current text in the text box
    QString str = ui->textEditWrite->toPlainText();
    ui->textEditWrite->setText("");

    //then write it to the socket stack
    tcpSocket->write(str.toStdString().data());
}


void ClientWidget::on_buttonClose_clicked()
{
    if(!tcpSocket) return;
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

