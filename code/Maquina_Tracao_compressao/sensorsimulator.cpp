#include "sensorsimulator.h"
#include <QRandomGenerator>
#include <cmath>

SensorSimulator::SensorSimulator()
{
}

float SensorSimulator::aplicarRuido(float valorReal, float percentual)
{
    // desvio padrão proporcional ao valor
    float desvio = valorReal * percentual;

    double u1 = QRandomGenerator::global()->generateDouble();
    double u2 = QRandomGenerator::global()->generateDouble();

    double z0 = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);

    float ruido = z0 * desvio;

    return valorReal + ruido;
}