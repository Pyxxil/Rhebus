#include <QtGui>

#include "Shapes/line.hpp"
#include "Shapes/path.hpp"
#include "Shapes/rectangle.hpp"
#include "Shapes/shape.hpp"
#include "Shapes/triangle.hpp"

#include "renderarea.hpp"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent), shape() {
  antialiased = false;
  transformed = false;

  setAutoFillBackground(true);
  image = QImage(400, 400, QImage::Format_RGB32);
  image.fill(qRgb(255, 255, 255));
}

void RenderArea::setShapes(QList<QSharedPointer<Shape>> shapes) {
  mShapes.clear();
  for (auto &&shape : shapes) {
    mShapes.append(QSharedPointer<Shape>(shape->clone()));
  }
  clearImage();
}

void RenderArea::setShape(Shapes::Shape shape) {
  this->shape = shape;
  update();
}

void RenderArea::setPen(const QPen &pen) {
  this->pen = pen;
  if (selected) {
    QPainter painter(&(this->image));
    currentShape->setPen(this->pen);
    currentShape->redraw(&painter);
  }
  update();
}

void RenderArea::setPenColour(const QColor &colour) {
  this->pen.setColor(colour);
  if (selected) {
    QPainter painter(&(this->image));
    currentShape->setPen(this->pen);
    currentShape->redraw(&painter);
  }
  update();
}

void RenderArea::setBrushColor(const QColor &colour) {
  this->brush.setColor(colour);
  if (selected) {
    QPainter painter(&(this->image));
    currentShape->setBrush(this->brush);
    currentShape->redraw(&painter);
  }
  update();
}

void RenderArea::setPenWidth(int width) {
  this->pen.setWidth(width);
  if (selected) {
    QPainter painter(&(this->image));
    currentShape->setPen(this->pen);
    currentShape->redraw(&painter);
  }
  update();
}

void RenderArea::setBrush(const QBrush &brush) {
  this->brush = brush;
  if (selected) {
    QPainter painter(&(this->image));
    currentShape->setBrush(this->brush);
    currentShape->redraw(&painter);
  }
  update();
}

void RenderArea::setAntialiased(bool antialiased) {
  this->antialiased = antialiased;
  update();
}

void RenderArea::setTransformed(bool transformed) {
  this->transformed = transformed;
  update();
}

void RenderArea::changeSize() {
  image = QImage(400, 400, QImage::Format_RGB32);
  image.fill(qRgb(255, 255, 255));
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
  scribbling = selected = moving = false;

  if (event->button() == Qt::LeftButton) {
    startPoint = event->pos();
  } else if (event->button() == Qt::RightButton) {
    for (int i = mShapes.length(); i > 0; --i) {
      auto shape = mShapes[i - 1];
      if (shape->contains(event->pos())) {
        selected = true;
        currentShape = shape;
        currentShape->setMovingStart(event->pos());
        break;
      }
    }
  }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    scribbling = true;
    draw(event->pos());
  } else if (selected && event->buttons() & Qt::RightButton) {
    moving = true;
    draw(event->pos());
  }
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    draw(event->pos());
    push();
    scribbling = false;
  } else if (event->button() == Qt::RightButton) {
    draw(event->pos());
    moving = false;
  }
}

void RenderArea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, this->image, dirtyRect);
}

void RenderArea::draw(const QPoint &endPoint) {
  clearImage();

  QPainter painter(&(this->image));
  painter.setPen(pen);
  painter.setBrush(brush);

  if (antialiased) {
    painter.setRenderHint(QPainter::Antialiasing, true);
  }

  if (transformed) {
    painter.translate(50, 50);
    painter.rotate(60.0);
    painter.scale(0.6, 0.9);
    painter.translate(-50, -50);
  }

  if (scribbling) {
    QRect rect(startPoint, endPoint);

    switch (shape) {
    case Shapes::Points:
      break;
    case Shapes::Line:
      currentShape = QSharedPointer<Line>(new Line(startPoint, endPoint));
      currentShape->draw(&painter);
      break;
    case Shapes::Path:
      // painter.drawPoints(points, 4);
      if (currentShape) {
        QList<QPoint> points =
            dynamic_cast<Path *>(currentShape.data())->points();
        currentShape = QSharedPointer<Path>(new Path(points << endPoint));
      } else {
        currentShape = QSharedPointer<Path>(
            new Path(QList<QPoint>() << startPoint << endPoint));
      }
      currentShape->draw(&painter);
      break;
    case Shapes::Polyline:
      // painter.drawPolyline(points, 4);
      break;
    case Shapes::Polygon:
      // painter.drawPolygon(points, 4);
      break;
    case Shapes::Rect:
      currentShape = QSharedPointer<Rectangle>(new Rectangle(rect));
      currentShape->draw(&painter);
      break;
    case Shapes::RoundedRect:
      // painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
      break;
    case Shapes::Ellipse:
      painter.drawEllipse(rect);
      break;
    case Shapes::Arc:
      // painter.drawArc(rect, startAngle, arcLength);
      break;
    case Shapes::Chord:
      // painter.drawChord(rect, startAngle, arcLength);
      break;
    case Shapes::Pie:
      // painter.drawPie(rect, startAngle, arcLength);
      break;
    case Shapes::Text:
      // painter.drawText(rect, Qt::AlignCenter, tr("Qt"));
      break;
    case Shapes::Pixmap:
      // painter.drawPixmap(10, 10, pixmap);
      break;
    case Shapes::Triangle:
      currentShape = QSharedPointer<Triangle>(new Triangle(rect));
      currentShape->draw(&painter);
      break;
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

    update(rect);
  } else if (moving) {
    currentShape->move(endPoint, &painter);
    update();
  }
}

void RenderArea::clearImage() {
  image.fill(qRgb(255, 255, 255));
  // modified = true;
  if (!mShapes.empty()) {
    QPainter painter(&(this->image));
    for (auto &&shape : mShapes) {
      shape->redraw(&painter);
    }
  }
  update();
}

void RenderArea::push() {
  mShapes.push_back(currentShape);
  currentShape = nullptr;
}

void RenderArea::setFromString(const QString &string) {
  if (string == "Line") {
    setShape(Shapes::Line);
  } else if (string == "Freeform") {
    setShape(Shapes::Path);
  } else if (string == "Rectangle") {
    setShape(Shapes::Rect);
  } else if (string == "Triangle") {
    setShape(Shapes::Triangle);
  }
}
