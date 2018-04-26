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
} // namespace Shapes

class RenderArea : public QWidget {
  Q_OBJECT

public:
  explicit RenderArea(QWidget *parent = nullptr);
  ~RenderArea() override {}

  const QList<QSharedPointer<Shape>> shapes() const { return mShapes; }

  void setShapes(QList<QSharedPointer<Shape>> shapes);

protected:
  void mousePressEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void paintEvent(QPaintEvent *event) override;

  void draw(const QPoint &endPoint);
  void clearImage();
  void push();

public slots:
  void setFromString(const QString &string);
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
  Shapes::Shape shape;
  QColor penColour;
  QColor fillColour;
  QBrush brush;
  QPen pen;
  QImage image;
  bool antialiased;
  bool transformed;
  bool scribbling{false};
  bool selected{false};
  bool moving{true};

  QSharedPointer<Shape> currentShape;
  QList<QSharedPointer<Shape>> mShapes;

  QPoint startPoint;
};

#endif // RENDERAREA_HPP
