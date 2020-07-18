#include "temp_hum.h"
#include "ui_temp_hum.h"

#include <QMessageBox>
#include <QChartView>
#include <QTimer>
#include <QChart>
#include <QDialog>

temp_hum::temp_hum(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::temp_hum)


{
    ui->setupUi(this);
    arduino = new QSerialPort();
    serialBuffer = "";

    QChartView * chartView = new QChartView();
    ui->horizontalLayouthum->addWidget(chartView);

    chartView->setRenderHint(QPainter::Antialiasing);
    QLineSeries *series = new QLineSeries();
 /*   series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);*/

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    axisX->append("TIME [s]", 30);

    axisX->setRange(0, 30);

    axisY->append("HUMIDITY [%RH]",30);
    axisY->setRange(0, 30);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chartView->setChart(chart);




    QChartView * chartView1 = new QChartView();
    ui->horizontalLayouttemp->addWidget(chartView1);

    chartView->setRenderHint(QPainter::Antialiasing);
    QLineSeries *series1 = new QLineSeries();
 /*   series1->append(0, 6);
    series1->append(2, 4);
    series1->append(3, 8);
    series1->append(7, 4);
    series1->append(10, 5);
    *series1 << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);*/

    QChart *chart1 = new QChart();
    chart1->legend()->hide();
    chart1->addSeries(series1);
    chart1->createDefaultAxes();

    QCategoryAxis *axisX1 = new QCategoryAxis();
    QCategoryAxis *axisY1 = new QCategoryAxis();

    axisX1->append("TIME [s]", 30);

    axisX1->setRange(0, 30);

    axisY1->append("TEMPERATURE [°C]",30);
    axisY1->setRange(0, 30);

    chart1->addAxis(axisX1, Qt::AlignBottom);
    chart1->addAxis(axisY1, Qt::AlignLeft);
    series1->attachAxis(axisX1);
    series1->attachAxis(axisY1);
    chartView1->setChart(chart1);



    for(auto serialPort: QSerialPortInfo::availablePorts())
    {
        ui->portsComboBox->addItem(serialPort.portName());
    }

    ui->portsComboBox->model()->sort(0);

    connect(ui->connectionButton, &QPushButton::clicked, this, &temp_hum::connectArduino);

    connect(ui->StopButton, &QPushButton::clicked, this, &temp_hum::readSerial);

}

void temp_hum::connectArduino()
{
    if(!arduino->isOpen())
    {
        arduino->setPortName(ui->portsComboBox->currentText());
        if(!arduino->open(QSerialPort::ReadWrite))
        {
            QMessageBox::critical(this, "Error", "Could not open serial port!");
            return;
        }

        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));

        ui->connectionButton->setText("Disconnect");
        ui->connectionStatusLabel->setText("Connected");

    }

    else
    {
        arduino->close();

        ui->connectionButton->setText("Connect");
        ui->connectionStatusLabel->setText("Disconnected");

}

}
void temp_hum::readSerial()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&temp_hum::update));
    timer->start(2000);

    if(arduino->isWritable())
    {
   // QByteArray serialData = arduino->readAll();
    serialData = arduino->readLine();
    serialBuffer += QString::fromStdString(serialData.toStdString());
    qDebug() << serialBuffer;

//    ui->TempNumber->display(data);
//    ui->HumNumber->display(data);

  //  QObject::connect(ui->StopButton, &QPushButton::clicked, this, &temp_hum::readSerial);
  //  ui->StopButton->setText("Stop");
}
}

temp_hum::~temp_hum()
{
    delete ui;
}

