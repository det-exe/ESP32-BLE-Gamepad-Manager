#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial.setPortName("/dev/ttyUSB0");
    serial.setBaudRate(QSerialPort::Baud115200);
}

MainWindow::~MainWindow()
{
    if (serial.isOpen()) {
        serial.close();
    }
    delete ui;
}

void MainWindow::sendCommand(const QString &command)
{
    if (!serial.isOpen()) {
        serial.open(QIODevice::ReadWrite);
    }

    if (serial.isOpen()) {
        serial.write(command.toUtf8());
        serial.waitForBytesWritten(100);
    } else {
        qWarning() << "Failed to open the serial port.";
    }
}

void MainWindow::on_calibrateButton_clicked()
{
    sendCommand("c");
}

void MainWindow::on_deadzoneSpinBox_valueChanged(int value)
{
    QString command = QString("d%1").arg(value);
    sendCommand(command);
}

void MainWindow::on_sensitivitySpinBox_valueChanged(int value)
{
    QString command = QString("s%1").arg(value);
    sendCommand(command);
}
