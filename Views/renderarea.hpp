#ifndef RENDERAREA_HPP
#define RENDERAREA_HPP

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

#include <memory>

#include "Shapes/shape.hpp"

namespace Shapes {
enum Shape {
  Line,
  Points,
  Polyline,
  Polygon,
  Rect,
  RoundedRect,
  Ellipse,
  Arc,
  Chord,
  Pie,
  Path,
  Text,
  Pixmap,
  Triangle
};
}

class RenderArea : public QWidget {
  Q_OBJECT

public:
  RenderArea(QWidget *parent = 0);
  ~RenderArea() {}

  const QList<QSharedPointer<Shape>> shapes() const { return mShapes; }

protected:
  void mousePressEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void paintEvent(QPaintEvent *event) override;

  void draw(const QPoint &endPoint);
  void clearImage();
  void push();

public slots:
  void setFromString(QString string);
  void setShape(Shapes::Shape shape);
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setAntialiased(bool antialiased);
  void setTransformed(bool transformed);
  void setPenColour(const QColor &);
  void setBrushColor(const QColor &);
  void setPenWidth(int);
  void changeSize();

private:
  QColor penColour;
  QColor fillColour;
  Shapes::Shape shape;
  QPen pen;
  QBrush brush;
  bool antialiased;
  bool transformed;
  bool scribbling{false};
  QPixmap pixmap;
  QImage image;

  QSharedPointer<Shape> currentShape;
  QList<QSharedPointer<Shape>> mShapes;

  QPoint startPoint;
};

#endif // RENDERAREA_HPP
