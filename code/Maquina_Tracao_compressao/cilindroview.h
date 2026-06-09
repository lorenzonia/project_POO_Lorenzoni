#ifndef CILINDROVIEW_H
#define CILINDROVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class CilindroView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CilindroView(QWidget *parent = nullptr);

    void setPosicao(double pos, double maxPos);

private:
    QGraphicsScene *scene;

    QGraphicsRectItem *corpo;
    QGraphicsRectItem *haste;
    QGraphicsEllipseItem *pistao;

    double posicaoMax;
};

#endif