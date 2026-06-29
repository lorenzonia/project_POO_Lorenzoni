#include "mainwindow.h"

#include <QString>
#include <cmath>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // Variáveis de controle
    tempo = 0;
    posicaoAtual = 0.0;
    deslocamentoMinimo = 0.0;
    deslocamentoMaximo = 150.0; // mm

    // Enum de modo de operacao
    modoAtual = ModoOperacao::Manual;

    // dentro do modo manual
    estadoEnsaio = EstadoEnsaio::Aproximacao;

    // Instancia controller
    controller = new Controller(this);

    // Instancia sensor
    sensor = new SensorSimulator();

    // Cria interface
    setupUI();

    // Define campo pressão de teste
    pressaoTesteSetpoint = campoPressaoTeste->text().toDouble();

    // Conexões de botões
    connect(btnStart, &QPushButton::clicked,
            this, &MainWindow::iniciarSistema);

    connect(btnStop, &QPushButton::clicked,
            this, &MainWindow::pararSistema);   

    // Conexão com Controller
    connect(controller, &Controller::dadosAtualizados,
            this, &MainWindow::atualizarInterface);

    // Conexão com o Slider
    connect(sliderPressao, &QSlider::valueChanged, this, [=](int value){
        double pressaoBar = value / 10.0;
        labelPressaoControle->setText("Pressão Ajuste: " + QString::number(pressaoBar) + " bar");
    });
}

MainWindow::~MainWindow()
{
    // Qt cuida da memória automaticamente via parent-child
}

void MainWindow::setupUI()
{
    // =========================
    // MAIN LAYOUT
    // =========================
    QVBoxLayout *mainLayout = new QVBoxLayout();

    // =========================
    // BUTTONS
    // =========================
    btnStart = new QPushButton("Iniciar");
    btnStop = new QPushButton("Parar");
    btnReset = new QPushButton("Reset");

    connect(btnReset, &QPushButton::clicked, this,

            [this]()

            {
                estadoEnsaio = EstadoEnsaio::Aproximacao;

                if (radioAvanco->isChecked())
                    posicaoAtual = deslocamentoMinimo;   // 0
                else
                    posicaoAtual = deslocamentoMaximo;   // 150

                tempo = 0;

                curvaForca->data()->clear();
                grafico->replot();
            });


    // =========================
    // LABELS
    // =========================
    labelForca = new QLabel("Força: --");
    labelPressao = new QLabel("Pressão: --");
    labelPosicao = new QLabel("Posição: --");

    labelForca->setAlignment(Qt::AlignCenter);
    labelPressao->setAlignment(Qt::AlignCenter);
    labelPosicao->setAlignment(Qt::AlignCenter);

    // =========================
    // PRESSURE SLIDER
    // =========================
    sliderPressao = new QSlider(Qt::Horizontal);
    sliderPressao->setRange(0, 70);
    sliderPressao->setValue(30);

    labelPressaoControle = new QLabel("Pressão: 3.0 bar");

    connect(sliderPressao, &QSlider::valueChanged, this,
            [this](int value)
            {
                double p = value / 10.0;
                labelPressaoControle->setText("Pressão: " + QString::number(p, 'f', 1) + " bar");
            });

    // =========================
    // FLOW SLIDER
    // =========================
    sliderVazao = new QSlider(Qt::Horizontal);
    sliderVazao->setRange(0, 500);
    sliderVazao->setValue(100);

    labelVazao = new QLabel("Vazão: 10.0 L/min");

    connect(sliderVazao, &QSlider::valueChanged, this,
            [this](int value)
            {
                double v = value / 10.0;
                labelVazao->setText("Vazão: " + QString::number(v, 'f', 1) + " L/min");
            });

    // =========================
    // DIRECTION
    // =========================
    radioAvanco = new QRadioButton("Compressão (Avanço)");
    radioRetorno = new QRadioButton("Tração (Retorno)");
    radioAvanco->setChecked(true);

    QVBoxLayout *direcaoLayout = new QVBoxLayout();
    direcaoLayout->addWidget(radioAvanco);
    direcaoLayout->addWidget(radioRetorno);

    QGroupBox *grupoDirecao = new QGroupBox("Direção");
    grupoDirecao->setLayout(direcaoLayout);

    // =========================
    // OPERATION MODE
    // =========================
    QRadioButton *radioManual = new QRadioButton("Manual");
    QRadioButton *radioAutomatico = new QRadioButton("Automático");
    radioManual->setChecked(true);

    QVBoxLayout *modoLayout = new QVBoxLayout();
    modoLayout->addWidget(radioManual);
    modoLayout->addWidget(radioAutomatico);

    QGroupBox *grupoModo = new QGroupBox("Modo de Operação");
    grupoModo->setLayout(modoLayout);

    QHBoxLayout *modoDirecaoLayout = new QHBoxLayout();
    modoDirecaoLayout->addWidget(grupoModo);
    modoDirecaoLayout->addWidget(grupoDirecao);
    modoDirecaoLayout->setSpacing(20);
    modoDirecaoLayout->setStretch(0, 1);
    modoDirecaoLayout->setStretch(1, 1);

    // =========================
    // MODE CONNECTS
    // =========================
    connect(radioManual, &QRadioButton::clicked, this,
            [this]()
            {
                modoAtual = ModoOperacao::Manual;
                atualizarUIParaModo();
            });

    connect(radioAutomatico, &QRadioButton::clicked, this,
            [this]()
            {
                modoAtual = ModoOperacao::Automatico;
                atualizarUIParaModo();
            });

    // =========================
    // GRAPH
    // =========================
    tempo = 0;

    grafico = new QCustomPlot();
    curvaForca = grafico->addGraph();
    curvaForca->setPen(QPen(Qt::blue));
    curvaForca->setName("Força");

    grafico->xAxis->setLabel("Tempo");
    grafico->yAxis->setLabel("Força (N)");

    grafico->legend->setVisible(true);
    grafico->setInteraction(QCP::iRangeDrag, true);
    grafico->setInteraction(QCP::iRangeZoom, true);
    grafico->setMinimumHeight(250);

    mainLayout->addWidget(grafico);

    // =========================
    // CONFIGURATION LAYOUT
    // =========================
    QVBoxLayout *configLayout = new QVBoxLayout();

    configLayout->addLayout(modoDirecaoLayout);

    // manual controls
    configLayout->addWidget(labelPressaoControle);
    configLayout->addWidget(sliderPressao);
    configLayout->addWidget(labelVazao);
    configLayout->addWidget(sliderVazao);

    // =========================
    // TEST CONFIG
    // =========================
    QGridLayout *testeLayout = new QGridLayout();

    QLabel *labelAltura = new QLabel("Altura do objeto (mm)");
    campoAltura = new QLineEdit("50");

    QLabel *labelVelAprox = new QLabel("Velocidade Aproximação (L/min)");
    campoVelAprox = new QLineEdit("5");

    QLabel *labelPressaoAprox = new QLabel("Pressão Aproximação (bar)");
    campoPressaoAprox = new QLineEdit("1");

    QLabel *labelVelTeste = new QLabel("Velocidade Teste (L/min)");
    campoVelTeste = new QLineEdit("1");

    QLabel *labelPressaoTeste = new QLabel("Pressão Teste (bar)");
    campoPressaoTeste = new QLineEdit("1");

    // grid layout
    testeLayout->addWidget(labelAltura, 0, 0);
    testeLayout->addWidget(campoAltura, 0, 1);
    testeLayout->addWidget(labelVelAprox, 0, 2);
    testeLayout->addWidget(campoVelAprox, 0, 3);

    testeLayout->addWidget(labelPressaoAprox, 1, 0);
    testeLayout->addWidget(campoPressaoAprox, 1, 1);
    testeLayout->addWidget(labelVelTeste, 1, 2);
    testeLayout->addWidget(campoVelTeste, 1, 3);

    testeLayout->addWidget(labelPressaoTeste, 2, 0);
    testeLayout->addWidget(campoPressaoTeste, 2, 1);

    testeLayout->setHorizontalSpacing(15);
    testeLayout->setVerticalSpacing(10);
    testeLayout->setColumnStretch(1, 1);
    testeLayout->setColumnStretch(3, 1);

    grupoTeste = new QGroupBox("Configuração de Ensaio");
    grupoTeste->setLayout(testeLayout);
    grupoTeste->setVisible(false);

    configLayout->addWidget(grupoTeste);

    QGroupBox *grupoConfig = new QGroupBox("Configurações");
    grupoConfig->setLayout(configLayout);

    // =========================
    // CYLINDER
    // =========================
    cilindroView = new CilindroView();

    QHBoxLayout *areaLateral = new QHBoxLayout();
    areaLateral->addWidget(grupoConfig);
    areaLateral->addWidget(cilindroView);

    areaLateral->setStretch(0, 2);
    areaLateral->setStretch(1, 1);

    mainLayout->addLayout(areaLateral);

    // =========================
    // CONTROL PANEL
    // =========================
    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(btnStart);
    controlLayout->addWidget(btnStop);
    controlLayout->addWidget(btnReset);
    controlLayout->addWidget(labelForca);
    controlLayout->addWidget(labelPressao);
    controlLayout->addWidget(labelPosicao);

    QGroupBox *grupoControle = new QGroupBox("Operação");
    grupoControle->setLayout(controlLayout);

    mainLayout->addWidget(grupoControle);

    // layout stretch
    mainLayout->setStretch(0, 3);
    mainLayout->setStretch(1, 2);
    mainLayout->setStretch(2, 1);

    setLayout(mainLayout);

    setWindowTitle("Máquina de Tração e Compressão - Simulação");
    resize(1100, 650);

    atualizarUIParaModo();
}


void MainWindow::iniciarSistema()
{
    controller->start();
}

void MainWindow::pararSistema()
{
    controller->stop();
}

void MainWindow::atualizarUIParaModo()
{
    if (modoAtual == ModoOperacao::Manual)
    {
        // manual mode
        sliderPressao->setEnabled(true);
        sliderVazao->setEnabled(true);

        grupoTeste->setVisible(false);
    }
    else
    {
        // automatic mode
        sliderPressao->setEnabled(false);
        sliderVazao->setEnabled(false);

        grupoTeste->setVisible(true);
    }
}


void MainWindow::atualizarInterface(const SensorData &dados)
{
    Q_UNUSED(dados);

    double pressaoBar;
    double vazao;

    // =========================
    // AUTOMATIC MODE WITH STATE
    // =========================
    if (modoAtual == ModoOperacao::Automatico)
    {
        double alturaObjeto = campoAltura->text().toDouble();
        double velAprox = campoVelAprox->text().toDouble();
        double pressaoAprox = campoPressaoAprox->text().toDouble();
        double velTeste = campoVelTeste->text().toDouble();
        if (estadoEnsaio == EstadoEnsaio::Aproximacao)
        {
            pressaoTesteSetpoint = campoPressaoTeste->text().toDouble();
        }


        // contact position based on direction
        double posicaoContato;

        if (radioAvanco->isChecked())
            posicaoContato = deslocamentoMaximo - alturaObjeto;
        else
            posicaoContato = alturaObjeto;

        // =========================
        // STATE MACHINE
        // =========================
        switch (estadoEnsaio)
        {
        case EstadoEnsaio::Aproximacao:
        {
            sliderPressao->setEnabled(false);  // trava

            pressaoBar = pressaoAprox;
            vazao = velAprox;


            if ((radioAvanco->isChecked() && posicaoAtual >= posicaoContato) ||
                (!radioAvanco->isChecked() && posicaoAtual <= posicaoContato))
            {
                estadoEnsaio = EstadoEnsaio::Teste;

                // sincroniza slider com valor digitado pelo usuario
                double pressaoTeste = campoPressaoTeste->text().toDouble();
                sliderPressao->setValue(static_cast<int>(pressaoTeste * 10));
            }


            break;
        }

        case EstadoEnsaio::Teste:
        {
            sliderPressao->setEnabled(true);

            pressaoBar = sliderPressao->value() / 10.0;
            vazao = velTeste;

            // sincroniza setpoint com operador
            pressaoTesteSetpoint = pressaoBar;

            campoPressaoTeste->setText(QString::number(pressaoBar, 'f', 1));

            break;
        }



        case EstadoEnsaio::Finalizado:
        {
            sliderPressao->setEnabled(false);

            pressaoBar = 0;
            vazao = 0;

            break;
        }
        }


        sliderPressao->setValue(static_cast<int>(pressaoTesteSetpoint * 10));
        sliderVazao->setValue(static_cast<int>(vazao * 10));
    }
    else
    {
        // =========================
        // MANUAL MODE
        // =========================
        pressaoBar = sliderPressao->value() / 10.0;
        vazao = sliderVazao->value() / 10.0;

        estadoEnsaio = EstadoEnsaio::Aproximacao;
    }

    // =========================
    // CONVERSION
    // =========================
    double pressaoPa = pressaoBar * 100000;
    double vazao_m3s = vazao / 60000.0;

    // =========================
    // CYLINDER GEOMETRY
    // =========================
    double D = 0.063;
    double d = 0.025;

    double areaAvanco = M_PI * pow(D, 2) / 4.0;
    double areaRetorno = M_PI * (pow(D, 2) - pow(d, 2)) / 4.0;

    double area = radioAvanco->isChecked() ? areaAvanco : areaRetorno;

    if (area <= 0.0)
        return;

    double velocidade_m_s = vazao_m3s / area;
    double velocidade = velocidade_m_s * 1000 * 0.1;

    // =========================
    // MOVEMENT
    // =========================

    double alturaObjeto = campoAltura->text().toDouble();

    double posicaoContato;
    if (radioAvanco->isChecked())
        posicaoContato = deslocamentoMaximo - alturaObjeto;
    else
        posicaoContato = alturaObjeto;

    if (radioAvanco->isChecked())
    {
        posicaoAtual += velocidade;

        if (posicaoAtual > deslocamentoMaximo)
            posicaoAtual = deslocamentoMaximo;

        if (modoAtual == ModoOperacao::Automatico &&
            posicaoAtual > posicaoContato)
        {
            posicaoAtual = posicaoContato;
        }
    }
    else
    {
        posicaoAtual -= velocidade;

        if (posicaoAtual < deslocamentoMinimo)
            posicaoAtual = deslocamentoMinimo;

        if (modoAtual == ModoOperacao::Automatico &&
            posicaoAtual < posicaoContato)
        {
            posicaoAtual = posicaoContato;
        }
    }

    // =========================
    // FORCE
    // =========================
    double forca = pressaoPa * area;

    // =========================
    // SENSOR
    // =========================
    double forcaMedida = sensor->aplicarRuido(forca, 0.02);
    double pressaoMedida = sensor->aplicarRuido(pressaoBar, 0.01);
    double posicaoMedida = sensor->aplicarRuido(posicaoAtual, 0.005);

    // =========================
    // UI
    // =========================
    labelForca->setText("Força: " + QString::number(forcaMedida, 'f', 0) + " N");
    labelPressao->setText("Pressão: " + QString::number(pressaoMedida, 'f', 2) + " bar");
    labelPosicao->setText("Posição: " + QString::number(posicaoMedida, 'f', 1) + " mm");

    // =========================
    // GRAPH
    // =========================
    curvaForca->addData(tempo, forcaMedida);
    grafico->xAxis->setRange(tempo, 50, Qt::AlignRight);
    grafico->yAxis->rescale(true);
    grafico->replot();

    // =========================
    // CYLINDER
    // =========================
    cilindroView->setPosicao(posicaoAtual, deslocamentoMaximo);

    tempo++;
}