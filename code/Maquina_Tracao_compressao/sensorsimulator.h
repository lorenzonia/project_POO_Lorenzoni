#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include "SensorData.h"

class SensorSimulator
{
public:
    SensorSimulator();

    SensorData gerarDados();

private:
    float gerarForca();
    float gerarPressao();
    float gerarPosicao();
};

#endif // SENSORSIMULATOR_H