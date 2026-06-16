#include "CilindroView.h"
#include <QPen>
#include <QBrush>

CilindroView::CilindroView(QWidget *parent)
    : QGraphicsView(parent), posicaoMax(150)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    setMinimumHeight(300);

    // =========================
    // PARÂMETROS
    // =========================
    larguraCena = 200;
    alturaCena = 290;

    margem = 20;

    larguraCorpo = 40;
    alturaCorpo = 230;

    // ✅ CONTROLE GLOBAL DE POSIÇÃO X e Y
    offsetX = 130;
    offsetY = -20;

    setSceneRect(0, 0, larguraCena, alturaCena);

    int topo = margem;

    // =========================
    // CORPO
    // =========================
    corpo = scene->addRect(
        offsetX,
        topo,
        larguraCorpo,
        alturaCorpo,
        QPen(Qt::black),
        QBrush(Qt::lightGray)
        );

    // =========================
    // HASTE (AZUL)
    // =========================
    int larguraHaste = 10;
    int centroLocal = offsetX - ((larguraHaste / 2)-20);

    haste = new QGraphicsRectItem(
        centroLocal,
        offsetY,
        larguraHaste,
        0
        );

    haste->setBrush(Qt::blue);
    haste->setParentItem(corpo);

    // =========================
    // PISTÃO (VERMELHO)
    // =========================
    pistao = new QGraphicsEllipseItem(
        centroLocal - 15,
        0,
        larguraCorpo,
        20
        );

    pistao->setBrush(Qt::red);
    pistao->setPen(QPen(Qt::black));
    pistao->setParentItem(corpo);

    // =========================
    // ESCALA (GLOBAL)
    // =========================
    int divisoes = 5;

    for (int i = 0; i <= divisoes; ++i)
    {
        int y = topo + i * (alturaCorpo / divisoes);

        scene->addLine(10, y, 25, y);

        double proporcao = (double)i / divisoes;
        int valor = (int)(proporcao * posicaoMax);

        auto texto = scene->addText(QString::number(valor) + " mm");
        texto->setPos(5, y - 10);
    }
}

void CilindroView::setPosicao(double pos, double maxPos)
{
    if (maxPos <= 0.0)
        return;

    posicaoMax = maxPos;

    if (pos < 0) pos = 0;
    if (pos > posicaoMax) pos = posicaoMax;

    double proporcao = pos / posicaoMax;

    int yPistao = static_cast<int>(proporcao * alturaCorpo);

    int larguraHaste = 10;
    int centroLocal = offsetX - ((larguraHaste / 2)-20);

    // =========================
    // PISTÃO (VERMELHO)
    // =========================
    pistao->setPos(0, yPistao);

    // =========================
    // HASTE (AZUL)
    // =========================
    haste->setPos(
        centroLocal,
        yPistao
        );

    haste->setRect(
        0,
        -yPistao,
        larguraHaste,
        yPistao
        );

    viewport()->update();
}
