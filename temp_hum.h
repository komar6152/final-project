#ifndef TEMP_HUM_H
#define TEMP_HUM_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCharts>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class temp_hum; }
QT_END_NAMESPACE

class temp_hum : public QMainWindow
{
    Q_OBJECT

public:
    temp_hum(QWidget *parent = nullptr);
    ~temp_hum();

private slots:
    void connectArduino();
    void readSerial();  

private:
    Ui::temp_hum *ui;
    QSerialPort *arduino;
    QByteArray serialData;
    QString serialBuffer;
};
#endif // TEMP_HUM_H
