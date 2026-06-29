#include "cilindroview.h"

#include <QPen>
#include <QBrush>

CilindroView::CilindroView(QWidget *parent)
    : QGraphicsView(parent),
    posicaoMax(150.0)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    setMinimumHeight(350);

    // =========================
    // GEOMETRIA GERAL
    // =========================

    larguraCena = 260;
    alturaCena  = 350;

    margem = 20;

    larguraCorpo = 40;
    alturaCorpo  = 300;

    offsetX = 150;

    setSceneRect(0, 0, larguraCena, alturaCena);

    // =========================
    // CORPO DO CILINDRO
    // =========================

    corpo = scene->addRect(
        offsetX,
        margem,
        larguraCorpo,
        alturaCorpo,
        QPen(Qt::black),
        QBrush(Qt::lightGray)
        );

    // =========================
    // HASTE
    // =========================

    int larguraHaste = 10;

    int centroCorpo =
        offsetX + larguraCorpo / 2;

    int xHaste =
        centroCorpo - larguraHaste / 2;

    haste = scene->addRect(
        xHaste,
        margem,
        larguraHaste,
        1,
        QPen(Qt::black),
        QBrush(Qt::blue)
        );

    // =========================
    // PISTAO
    // =========================

    pistao = scene->addEllipse(
        offsetX,
        margem,
        larguraCorpo,
        20,
        QPen(Qt::black),
        QBrush(Qt::red)
        );

    // =========================
    // INDICADOR POSICAO
    // =========================

    indicadorPosicao = scene->addLine(
        offsetX - 30,
        margem,
        offsetX + larguraCorpo + 30,
        margem,
        QPen(Qt::yellow, 2)
        );

    // =========================
    // REGUA
    // =========================

    int divisoes = 5;

    for(int i = 0; i <= divisoes; ++i)
    {
        int y =
            margem +
            i * (alturaCorpo / divisoes);

        scene->addLine(
            70,
            y,
            85,
            y
            );

        double proporcao =
            static_cast<double>(i) / divisoes;

        int valor =
            static_cast<int>(
                proporcao * posicaoMax
                );

        auto texto =
            scene->addText(
                QString::number(valor) + " mm"
                );

        texto->setPos(
            10,
            y - 10
            );
    }
}

void CilindroView::setPosicao(double pos,
                              double maxPos)
{
    if(maxPos <= 0.0)
        return;

    posicaoMax = maxPos;

    if(pos < 0.0)
        pos = 0.0;

    if(pos > posicaoMax)
        pos = posicaoMax;

    // =========================
    // CONVERSAO mm -> pixel
    // =========================

    double escala =
        static_cast<double>(alturaCorpo)
        / posicaoMax;

    double y =
        margem + (pos * escala);

    const int alturaPistao = 20;

    // =========================
    // PISTAO
    // =========================

    pistao->setRect(
        offsetX,
        y - alturaPistao / 2,
        larguraCorpo,
        alturaPistao
        );

    // =========================
    // HASTE
    // =========================

    int larguraHaste = 10;

    int centroCorpo =
        offsetX + larguraCorpo / 2;

    int xHaste =
        centroCorpo - larguraHaste / 2;

    haste->setRect(
        xHaste,
        margem,
        larguraHaste,
        y - margem
        );

    // =========================
    // INDICADOR
    // =========================

    indicadorPosicao->setLine(
        offsetX - 30,
        y,
        offsetX + larguraCorpo + 30,
        y
        );

    viewport()->update();
}