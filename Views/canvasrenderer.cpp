#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

#include "Shapes/shape.hpp"
#include "canvasrenderer.hpp"

CanvasRenderer::CanvasRenderer(QWidget *parent) : QWidget(parent) {
  setAutoFillBackground(true);
  image = QImage(width(), height(), QImage::Format_RGB32);
  image.fill(backgroundColour());
}

QList<QList<QSharedPointer<Shape>>> CanvasRenderer::shapes() const {
  return mShapes;
}

void CanvasRenderer::setShapes(
    const QList<QList<QSharedPointer<Shape>>> &objects) {
  for (auto &&obj : objects) {
    QList<QSharedPointer<Shape>> shapes;

    for (auto &&shape : obj) {
      shapes.append(QSharedPointer<Shape>(
          shape->moveToRealZero(image.rect().bottomLeft())));
    }

    if (!shapes.empty()) {
      mShapes.append(shapes);
    }
  }
  render();
}

QColor CanvasRenderer::backgroundColour() const { return mBackgroundColour; }

void CanvasRenderer::setBackgroundColour(const QColor &backgroundColour) {
  mBackgroundColour = backgroundColour;
  render();
}

void CanvasRenderer::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, this->image, dirtyRect);
}

void CanvasRenderer::render() {
  image = QImage(width(), height(), QImage::Format_RGB32);
  image.fill(backgroundColour());

  QPainter painter(&(this->image));
  for (auto &shape : mShapes) {
    for (auto &obj : shape) {
      obj->redraw(&painter);
    }
  }

  update();
}
