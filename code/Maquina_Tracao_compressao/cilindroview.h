#ifndef CILINDROVIEW_H
#define CILINDROVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

class CilindroView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CilindroView(QWidget *parent = nullptr);

    void setPosicao(double pos, double maxPos);

private:
    QGraphicsScene *scene;

    // Componentes
    QGraphicsRectItem *corpo;
    QGraphicsRectItem *haste;
    QGraphicsEllipseItem *pistao;

    // Parâmetros ajustáveis
    double posicaoMax;

    int larguraCena;
    int alturaCena;

    int margem;
    int larguraCorpo;
    int alturaCorpo;

    int offsetX;
    int offsetY;
};

#endif
