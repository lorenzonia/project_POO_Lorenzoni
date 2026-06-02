#include "MainWindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // Cria interface
    setupUI();

    // Instancia controller
    controller = new Controller(this);

    // Conexões de botões
    connect(btnStart, &QPushButton::clicked,
            this, &MainWindow::iniciarSistema);

    connect(btnStop, &QPushButton::clicked,
            this, &MainWindow::pararSistema);

    // Conexão com Controller
    connect(controller, &Controller::dadosAtualizados,
            this, &MainWindow::atualizarInterface);
}

MainWindow::~MainWindow()
{
    // Qt cuida da memória automaticamente via parent-child
}

void MainWindow::setupUI()
{
    // Botões
    btnStart = new QPushButton("Iniciar");
    btnStop = new QPushButton("Parar");

    // Labels de dados
    labelForca = new QLabel("Força: --");
    labelPressao = new QLabel("Pressão: --");
    labelPosicao = new QLabel("Posição: --");

    // Layout
    layout = new QVBoxLayout();

    layout->addWidget(btnStart);
    layout->addWidget(btnStop);
    layout->addWidget(labelForca);
    layout->addWidget(labelPressao);
    layout->addWidget(labelPosicao);

    setLayout(layout);

    // Configurações da janela
    setWindowTitle("Máquina de Tração e Compressão");
    resize(300, 200);
}

void MainWindow::iniciarSistema()
{
    controller->start();
}

void MainWindow::pararSistema()
{
    controller->stop();
}

void MainWindow::atualizarInterface(const SensorData &dados)
{
    labelForca->setText("Força: " + QString::number(dados.forca, 'f', 2));
    labelPressao->setText("Pressão: " + QString::number(dados.pressao, 'f', 2));
    labelPosicao->setText("Posição: " + QString::number(dados.posicao, 'f', 2));
}