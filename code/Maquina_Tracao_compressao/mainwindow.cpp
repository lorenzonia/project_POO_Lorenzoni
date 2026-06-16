#include "MainWindow.h"

#include <QString>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // Variáveis de controle
    tempo = 0;
    posicaoAtual = 0.0;
    deslocamentoMinimo = 0.0;
    deslocamentoMaximo = 150.0; // mm

    // Cria interface
    setupUI();

    // Instancia controller
    controller = new Controller(this);

    // Instancia sensor
    sensor = new SensorSimulator();

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
    // LAYOUT PRINCIPAL
    // =========================
    QVBoxLayout *mainLayout = new QVBoxLayout();

    // =========================
    // BOTÕES
    // =========================
    btnStart = new QPushButton("Iniciar");
    btnStop = new QPushButton("Parar");

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
    // SLIDER PRESSÃO
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
    // SLIDER VAZÃO
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
    // DIREÇÃO
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
    // GRÁFICO
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
    // CONFIGURAÇÕES
    // =========================
    QVBoxLayout *configLayout = new QVBoxLayout();

    configLayout->addWidget(labelPressaoControle);
    configLayout->addWidget(sliderPressao);
    configLayout->addWidget(labelVazao);
    configLayout->addWidget(sliderVazao);
    configLayout->addWidget(grupoDirecao);

    QGroupBox *grupoConfig = new QGroupBox("Configurações");
    grupoConfig->setLayout(configLayout);

    // =========================
    // CILINDRO
    // =========================
    cilindroView = new CilindroView();

    // =========================
    // LAYOUT LATERAL (AQUI É A MUDANÇA)
    // =========================
    QHBoxLayout *areaLateral = new QHBoxLayout();

    areaLateral->addWidget(grupoConfig);   // esquerda
    areaLateral->addWidget(cilindroView);  // direita

    areaLateral->setStretch(0, 2); // config maior
    areaLateral->setStretch(1, 1); // cilindro menor

    mainLayout->addLayout(areaLateral);

    // =========================
    // CONTROLES
    // =========================
    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(btnStart);
    controlLayout->addWidget(btnStop);
    controlLayout->addWidget(labelForca);
    controlLayout->addWidget(labelPressao);
    controlLayout->addWidget(labelPosicao);

    QGroupBox *grupoControle = new QGroupBox("Operação");
    grupoControle->setLayout(controlLayout);

    mainLayout->addWidget(grupoControle);

    // =========================
    // PROPORÇÕES
    // =========================
    mainLayout->setStretch(0, 3); // gráfico
    mainLayout->setStretch(1, 2); // área lateral
    mainLayout->setStretch(2, 1); // controle

    setLayout(mainLayout);

    // =========================
    // JANELA
    // =========================
    setWindowTitle("Máquina de Tração e Compressão - Simulação");
    resize(900, 650);
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
    Q_UNUSED(dados);

    // =========================
    // PRESSÃO
    // =========================
    double pressaoBar = sliderPressao->value() / 10.0;
    double pressaoPa = pressaoBar * 100000;

    // =========================
    // GEOMETRIA DO CILINDRO
    // =========================
    double D = 0.063; // diâmetro êmbolo (m)
    double d = 0.025; // diâmetro haste (m)

    double areaAvanco = M_PI * pow(D, 2) / 4.0;
    double areaRetorno = M_PI * (pow(D, 2) - pow(d, 2)) / 4.0;

    double area;

    // =========================
    // VAZÃO → VELOCIDADE (FÍSICO)
    // =========================
    double vazao = sliderVazao->value() / 10.0;       // L/min
    double vazao_m3s = vazao / 60000.0;               // m³/s

    double velocidade_m_s;
    double velocidade; // mm por ciclo

    // Define área e direção
    if (radioAvanco->isChecked())
    {
        area = areaAvanco;
    }
    else
    {
        area = areaRetorno;
    }

    // velocidade física m/s
    if (area <= 0.0)
        return;
    velocidade_m_s = vazao_m3s / area;

    // conversão para mm / ciclo (ajuste de tempo discreto)
    velocidade = velocidade_m_s * 1000 * 0.1;

    // =========================
    // MOVIMENTO DO CILINDRO
    // =========================
    if (radioAvanco->isChecked())
    {
        posicaoAtual += velocidade;

        if (posicaoAtual > deslocamentoMaximo)
            posicaoAtual = deslocamentoMaximo;
    }
    else
    {
        posicaoAtual -= velocidade;

        if (posicaoAtual < deslocamentoMinimo)
            posicaoAtual = deslocamentoMinimo;
    }

    // =========================
    // FORÇA
    // =========================
    double forca = pressaoPa * area;

    // =========================
    // APLICA RUÍDO (SENSORES)
    // =========================
    double forcaMedida = sensor->aplicarRuido(forca, 0.02);           // 2%
    double pressaoMedida = sensor->aplicarRuido(pressaoBar, 0.01);    // 1%
    double posicaoMedida = sensor->aplicarRuido(posicaoAtual, 0.005); // 0.5%

    // =========================
    // ATUALIZA INTERFACE
    // =========================
    labelForca->setText("Força: " + QString::number(forcaMedida, 'f', 0) + " N");
    labelPressao->setText("Pressão: " + QString::number(pressaoMedida, 'f', 2) + " bar");
    labelPosicao->setText("Posição: " + QString::number(posicaoMedida, 'f', 1) + " mm");

    // =========================
    // GRÁFICO
    // =========================
    curvaForca->addData(tempo, forcaMedida);

    grafico->xAxis->setRange(tempo, 50, Qt::AlignRight);
    grafico->yAxis->rescale(true);
    grafico->replot();

    cilindroView->setPosicao(posicaoAtual, deslocamentoMaximo);

    // =========================
    // TEMPO
    // =========================
    tempo++;
}