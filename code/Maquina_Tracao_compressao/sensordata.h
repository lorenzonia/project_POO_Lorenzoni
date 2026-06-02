#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QDateTime>

class SensorData
{
public:
    SensorData();
    SensorData(float forca, float pressao, float posicao);

    // Getters
    float getForca() const;
    float getPressao() const;
    float getPosicao() const;
    QDateTime getTimestamp() const;

    // Setters
    void setForca(float value);
    void setPressao(float value);
    void setPosicao(float value);
    void setTimestamp(const QDateTime &time);

private:
    float forca;
    float pressao;
    float posicao;
    QDateTime timestamp;
};

#endif // SENSORDATA_H