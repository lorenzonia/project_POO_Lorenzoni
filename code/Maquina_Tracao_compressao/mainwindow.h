#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include <QRadioButton>
#include <QGroupBox>
#include <QLineEdit>

#include "controller.h"
#include "sensordata.h"
#include "sensorsimulator.h"
#include "qcustomplot.h"
#include "cilindroview.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void iniciarSistema();
    void pararSistema();
    void atualizarUIParaModo();
    void atualizarInterface(const SensorData &dados);

private:
    void setupUI();

    // =========================
    // COMPONENTES PRINCIPAIS
    // =========================
    CilindroView *cilindroView;
    QGroupBox *grupoTeste;

    // =========================
    // CONTROLE
    // =========================
    Controller *controller;
    SensorSimulator *sensor;

    // =========================
    // BOTÕES
    // =========================
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnReset;

    // =========================
    // LABELS (LEITURAS)
    // =========================
    QLabel *labelForca;
    QLabel *labelPressao;
    QLabel *labelPosicao;

    // =========================
    // GRÁFICO
    // =========================
    QCustomPlot *grafico;
    QCPGraph *curvaForca;

    // =========================
    // CONTROLE DE PRESSÃO
    // =========================
    QSlider *sliderPressao;
    QLabel *labelPressaoControle;

    // =========================
    // CONTROLE DE VAZÃO
    // =========================
    QSlider *sliderVazao;
    QLabel *labelVazao;

    // =========================
    // DIREÇÃO
    // =========================
    QRadioButton *radioAvanco;
    QRadioButton *radioRetorno;

    // =========================
    // CAMPOS ENSAIO AUTOMÁTICO
    // =========================
    QLineEdit *campoAltura;
    QLineEdit *campoVelAprox;
    QLineEdit *campoPressaoAprox;
    QLineEdit *campoVelTeste;
    QLineEdit *campoPressaoTeste;

    // =========================
    // ESTADO DO SISTEMA
    // =========================
    double tempo;
    double posicaoAtual;
    double deslocamentoMaximo;
    double deslocamentoMinimo;
    double pressaoTesteSetpoint;

    // =========================
    // MODO DE OPERAÇÃO
    // =========================
    enum class ModoOperacao
    {
        Manual,
        Automatico
    };

    ModoOperacao modoAtual;

    // =========================
    // ESTADO DO ENSAIO
    // =========================
    enum class EstadoEnsaio
    {
        Aproximacao,
        Teste,
        Finalizado
    };


    EstadoEnsaio estadoEnsaio;
};

#endif // MAINWINDOW_H
