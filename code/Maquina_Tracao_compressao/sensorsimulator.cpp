#include "SensorSimulator.h"
#include <QRandomGenerator>

SensorSimulator::SensorSimulator()
{
}

SensorData SensorSimulator::gerarDados()
{

    SensorData dados;

    dados.setForca(gerarForca());
    dados.setPressao(gerarPressao());
    dados.setPosicao(gerarPosicao());
    dados.setTimestamp(QDateTime::currentDateTime());


    return dados;
}

float SensorSimulator::gerarForca()
{
    // Simula força de 0 a 100 N
    return QRandomGenerator::global()->bounded(0.0, 100.0);
}

float SensorSimulator::gerarPressao()
{
    // Simula pressão de 10 a 60 bar
    return QRandomGenerator::global()->bounded(10.0, 60.0);
}

float SensorSimulator::gerarPosicao()
{
    // Simula posição de 0 a 500 mm
    return QRandomGenerator::global()->bounded(0.0, 500.0);
}