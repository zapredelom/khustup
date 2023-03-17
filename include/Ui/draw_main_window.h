#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "ui/draw_scene.h"

namespace khustup::ui {
class DrawMainWindow : public QWidget {
public:

    DrawMainWindow(QWidget *parent = 0);
private:
    DrawScene* scene;

};
}