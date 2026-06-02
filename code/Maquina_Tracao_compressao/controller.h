#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "SensorSimulator.h"
#include "SensorData.h"
#include "Cilindro.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);

    void start();
    void stop();

signals:
    void dadosAtualizados(const SensorData &dados);

private slots:
    void processarDados();

private:
    bool verificarLimites(const SensorData &dados);

    QTimer *timer;
    SensorSimulator *simulador;
    Cilindro *cilindro;

    bool emExecucao;
    int intervalo; // ms
};

#endif // CONTROLLER_H