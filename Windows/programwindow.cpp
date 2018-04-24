#include <QPaintEvent>
#include <QPainter>
#include <QScreen>

#include "programwindow.hpp"
#include "ui_programwindow.h"

ProgramWindow::ProgramWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProgramWindow) {
  ui->setupUi(this);

  ui->canvas->setGeometry(
      QGuiApplication::primaryScreen()->availableGeometry());
}

ProgramWindow::~ProgramWindow() { delete ui; }

void ProgramWindow::addShape(const QList<QSharedPointer<Shape>> &shape) {
  mShapes.append(shape);
}

void ProgramWindow::draw() {
  ui->canvas->setShapes(getShapes());
  ui->canvas->setBackgroundColour(backgroundColour);
  ui->canvas->render();
  update();
}

const QList<QList<QSharedPointer<Shape>>> &ProgramWindow::getShapes() const {
  return mShapes;
}

void ProgramWindow::setShapes(
    const QList<QList<QSharedPointer<Shape>>> &shapes) {
  mShapes = shapes;
}
