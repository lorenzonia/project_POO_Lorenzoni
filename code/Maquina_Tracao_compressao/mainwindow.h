#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include <QRadioButton>
#include <QGroupBox>

#include "Controller.h"
#include "SensorData.h"
#include "SensorSimulator.h"
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
    void atualizarInterface(const SensorData &dados);

private:
    void setupUI();
    CilindroView *cilindroView;

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
    // ESTADO DO SISTEMA
    // =========================
    double tempo;
    double posicaoAtual;
    double deslocamentoMaximo;
    double deslocamentoMinimo;
};

#endif // MAINWINDOW_H
