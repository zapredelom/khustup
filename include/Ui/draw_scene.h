#pragma once

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QTimer>

class DrawScene : public QGraphicsScene {
public:
    explicit DrawScene(QObject *parent = 0);
    ~DrawScene();

private:
    QPointF previousPoint;  // The coordinates of the previous point

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};