#include <QtGui>

#include "Shapes/line.hpp"
#include "Shapes/path.hpp"
#include "Shapes/rectangle.hpp"
#include "Shapes/shape.hpp"
#include "Shapes/triangle.hpp"

#include "renderarea.hpp"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {
  antialiased = false;
  transformed = false;

  setAutoFillBackground(true);
  image = QImage(400, 400, QImage::Format_RGB32);
  image.fill(qRgb(255, 255, 255));
}

void RenderArea::setShape(Shapes::Shape shape) {
  this->shape = shape;
  update();
}

void RenderArea::setPen(const QPen &pen) {
  this->pen = pen;
  update();
}

void RenderArea::setPenColour(const QColor &colour) {
  this->pen.setColor(colour);
  update();
}

void RenderArea::setBrushColor(const QColor &colour) {
  this->brush.setColor(colour);
}

void RenderArea::setPenWidth(int width) { this->pen.setWidth(width); }

void RenderArea::setBrush(const QBrush &brush) {
  this->brush = brush;
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
  if (event->button() == Qt::LeftButton) {
    startPoint = event->pos();
    scribbling = true;
  }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event) {
  if ((event->buttons() & Qt::LeftButton) && scribbling)
    draw(event->pos());
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton && scribbling) {
    draw(event->pos());
    // Should push it to the stack here
    push();
    scribbling = false;
  }
}

void RenderArea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, this->image, dirtyRect);
}

template <typename T> inline static T min(T x, T y) { return x < y ? x : y; }

template <typename T> inline static T max(T x, T y) { return x < y ? x : y; }

template <typename T> inline static T max(T x) { return x < 0 ? -x : x; }

void RenderArea::draw(const QPoint &endPoint) {
  clearImage();

  QRect rect(startPoint, endPoint);

  QPainterPath path;
  path.moveTo(20, 80);
  path.lineTo(20, 30);
  path.cubicTo(80, 0, 50, 50, 80, 80);

  int startAngle = 20 * 16;
  int arcLength = 120 * 16;

  QPainter painter(&(this->image));
  // painter.setPen(
  //    QPen(Qt::black, qrand() % 10, Qt::SolidLine, Qt::RoundCap,
  //    Qt::RoundJoin));
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
          static_cast<Path *>(currentShape.data())->allPoints();
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
    painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
    break;
  case Shapes::Ellipse:
    painter.drawEllipse(rect);
    break;
  case Shapes::Arc:
    painter.drawArc(rect, startAngle, arcLength);
    break;
  case Shapes::Chord:
    painter.drawChord(rect, startAngle, arcLength);
    break;
  case Shapes::Pie:
    painter.drawPie(rect, startAngle, arcLength);
    break;
  case Shapes::Text:
    painter.drawText(rect, Qt::AlignCenter, tr("Qt"));
    break;
  case Shapes::Pixmap:
    painter.drawPixmap(10, 10, pixmap);
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
  mShapes.push_back(std::move(currentShape));
  currentShape = nullptr;
}

void RenderArea::setFromString(QString string) {
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
