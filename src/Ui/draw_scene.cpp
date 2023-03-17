#include "ui/draw_scene.h"

DrawScene::DrawScene(QObject *parent) : QGraphicsScene(parent) {}

DrawScene::~DrawScene() {}

void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // When you press the mouse button, draw the ellipse
    addEllipse(event->scenePos().x() - 5, event->scenePos().y() - 5, 10, 10, QPen(Qt::NoPen), QBrush(Qt::red));
    // Save the coordinates of the point of pressing
    previousPoint = event->scenePos();
}

void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    // We draw the line with the previous coordinates
    addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(), event->scenePos().y(),
            QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
    // Update on the previous coordinate data
    previousPoint = event->scenePos();
}