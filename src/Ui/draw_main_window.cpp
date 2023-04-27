#include "Ui/draw_main_window.h"

using namespace khustup::ui;

DrawMainWindow::DrawMainWindow(QWidget* parent): QWidget(parent){

    scene = new DrawScene(this);
}