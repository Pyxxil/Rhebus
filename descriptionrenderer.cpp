#include "descriptionrenderer.hpp"

#include <QtGui>

#include "descriptionitem.hpp"

DescriptionRenderer::DescriptionRenderer(QWidget *parent) : QWidget(parent) {
  setAutoFillBackground(true);
  image = QImage(400, 400, QImage::Format_RGB32);
  image.fill(qRgb(255, 255, 255));
}

void DescriptionRenderer::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, this->image, dirtyRect);
}

void DescriptionRenderer::renderDescription(DescriptionItem *desc) {
  image = QImage(400, 400, QImage::Format_RGB32);
  image.fill(qRgb(255, 255, 255));

  QPainter painter(&(this->image));
  desc->render(&painter);
  update();
}

void DescriptionRenderer::changeSize() {
  image = QImage(400, 400, QImage::Format_RGB32);
  image.fill(qRgb(255, 255, 255));
}
