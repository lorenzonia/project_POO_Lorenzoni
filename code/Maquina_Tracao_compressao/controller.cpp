#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject(parent),
    emExecucao(false),
    intervalo(100) // 100 ms (10 Hz)
{
    // Instancia componentes
    simulador = new SensorSimulator();
    cilindro = new Cilindro();

    timer = new QTimer(this);

    // Conecta timer ao processamento
    connect(timer, &QTimer::timeout,
            this, &Controller::processarDados);
}

void Controller::start()
{
    if (emExecucao)
        return;

    emExecucao = true;
    timer->start(intervalo);
}

void Controller::stop()
{
    if (!emExecucao)
        return;

    emExecucao = false;
    timer->stop();
}


void Controller::processarDados()
{
    SensorData dados;
    emit dadosAtualizados(dados);

    // Atualiza cilindro
    cilindro->avancar();

    // Sincroniza posição simulada com cilindro
    dados.setPosicao(cilindro->getPosicao());

    if (verificarLimites(dados)) {
        stop();
    }

    emit dadosAtualizados(dados);
}


bool Controller::verificarLimites(const SensorData &dados)
{
    // Limites simples para exemplo

    if (dados.getForca() > 100.0)
        return true;

    if (dados.getPressao() > 70.0)
        return true;

    if (dados.getPosicao() < 0 || dados.getPosicao() > 500)
        return true;

    return false;
}