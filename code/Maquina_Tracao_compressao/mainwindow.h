#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "Controller.h"
#include "SensorData.h"

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
    void setupUI();  // construção manual da interface

    Controller *controller;

    // Componentes da interface
    QPushButton *btnStart;
    QPushButton *btnStop;

    QLabel *labelForca;
    QLabel *labelPressao;
    QLabel *labelPosicao;

    QVBoxLayout *layout;
};

#endif // MAINWINDOW_H