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
  for (int i = 0; i < objects.length(); ++i) {
    QList<QSharedPointer<Shape>> shapes;

    for (auto &&shape : objects[i]) {
      qDebug() << "Rect:" << image.rect();
      shapes.append(QSharedPointer<Shape>(
          shape->moveToRealZero(QPoint(image.rect().bottomLeft().x() + 200 * i,
                                       image.rect().bottomLeft().y()))));
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

void CanvasRenderer::clear() {
  image = QImage(width(), height(), QImage::Format_RGB32);
  image.fill(backgroundColour());
}

void CanvasRenderer::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, this->image, dirtyRect);
}

void CanvasRenderer::render() {
  clear();
  QPainter painter(&(this->image));
  for (auto &shape : mShapes) {
    for (auto &obj : shape) {
      obj->redraw(&painter);
    }
  }

  update();
}
