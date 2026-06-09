#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

class SensorSimulator
{
public:
    SensorSimulator();

    float aplicarRuido(float valorReal, float percentual);
};

#endif