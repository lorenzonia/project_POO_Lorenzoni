#include "CilindroView.h"

CilindroView::CilindroView(QWidget *parent)
    : QGraphicsView(parent), posicaoMax(150)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    setMinimumHeight(150);

    int y = 50;

    // Corpo do cilindro
    corpo = scene->addRect(0, y, 300, 20, QPen(), QBrush(Qt::gray));

    // Haste (movimento)
    haste = scene->addRect(0, y + 5, 0, 10, QPen(), QBrush(Qt::blue));

    // Pistão
    pistao = scene->addEllipse(0, y - 5, 10, 30, QPen(), QBrush(Qt::red));
}

void CilindroView::setPosicao(double pos, double maxPos)
{
    posicaoMax = maxPos;

    double proporcao = pos / posicaoMax;

    int comprimento = 300;
    int x = proporcao * comprimento;

    // Atualiza haste
    haste->setRect(0, 55, x, 10);

    // Atualiza pistão
    pistao->setRect(x - 5, 45, 10, 30);
}