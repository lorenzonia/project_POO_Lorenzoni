#include "sensordata.h"

SensorData::SensorData()
    : forca(0.0), pressao(0.0), posicao(0.0),
    timestamp(QDateTime::currentDateTime())
{
}

SensorData::SensorData(float f, float p, float pos)
    : forca(f), pressao(p), posicao(pos),
    timestamp(QDateTime::currentDateTime())
{
}

// Getters
float SensorData::getForca() const
{
    return forca;
}

float SensorData::getPressao() const
{
    return pressao;
}

float SensorData::getPosicao() const
{
    return posicao;
}

QDateTime SensorData::getTimestamp() const
{
    return timestamp;
}

// Setters
void SensorData::setForca(float value)
{
    forca = value;
}

void SensorData::setPressao(float value)
{
    pressao = value;
}

void SensorData::setPosicao(float value)
{
    posicao = value;
}

void SensorData::setTimestamp(const QDateTime &time)
{
    timestamp = time;
}