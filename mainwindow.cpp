#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize UI constraints and serial defaults
    ui->sensitivitySpinBox->setMaximum(10);
    serial.setBaudRate(QSerialPort::Baud115200);

    // Populate the dropdown with active USB serial ports
    populateSerialPorts();
}

MainWindow::~MainWindow()
{
    if (serial.isOpen()) {
        serial.close();
    }
    delete ui;
}

void MainWindow::populateSerialPorts()
{
    ui->portComboBox->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        QString name = port.portName();
        // Filter for common Linux USB-to-Serial identifiers
        if (name.startsWith("ttyUSB") || name.startsWith("ttyACM")) {
            ui->portComboBox->addItem(name);
        }
    }
}

void MainWindow::on_connectButton_clicked()
{
    if (serial.isOpen()) {
        serial.close();
        ui->connectButton->setText("Connect");
        qInfo() << "Disconnected from serial port.";
        return;
    }

    QString selectedPort = ui->portComboBox->currentText();
    if (selectedPort.isEmpty()) {
        qWarning() << "Connection failed: No serial port selected.";
        return;
    }

    serial.setPortName(selectedPort);
    if (serial.open(QIODevice::ReadWrite)) {
        ui->connectButton->setText("Disconnect");
        qInfo() << "Successfully connected to" << selectedPort;
    } else {
        qWarning() << "Failed to open serial port:" << serial.errorString();
    }
}

void MainWindow::sendCommand(const QString &command)
{
    if (serial.isOpen()) {
        serial.write(command.toUtf8());
        serial.waitForBytesWritten(100);
    } else {
        qWarning() << "Command transmission failed: Serial port is not open.";
    }
}

void MainWindow::on_calibrateButton_clicked()
{
    sendCommand("c");
    qInfo() << "Calibration sequence initiated.";
}

void MainWindow::on_deadzoneSpinBox_valueChanged(int value)
{
    QString command = QString("d%1").arg(value);
    sendCommand(command);
    qInfo() << "Deadzone parameter adjusted to:" << value;
}

void MainWindow::on_sensitivitySpinBox_valueChanged(int value)
{
    QString command = QString("s%1").arg(value);
    sendCommand(command);
    qInfo() << "Sensitivity parameter adjusted to:" << value;
}
