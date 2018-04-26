#ifndef CANVASRENDERER_HPP
#define CANVASRENDERER_HPP

#include <QWidget>

#include "Shapes/shape.hpp"

class CanvasRenderer : public QWidget {
  Q_OBJECT
public:
  explicit CanvasRenderer(QWidget *parent = nullptr);

  QList<QList<QSharedPointer<Shape>>> shapes() const;
  void setShapes(const QList<QList<QSharedPointer<Shape>>> &shapes);

  QColor backgroundColour() const;
  void setBackgroundColour(const QColor &backgroundColour);
  void clear();

protected:
  void paintEvent(QPaintEvent *event) override;

signals:

public slots:
  void render();

private:
  QList<QList<QSharedPointer<Shape>>> mShapes;
  QColor mBackgroundColour = QColor(Qt::white);
  QImage image;
};

#endif // CANVASRENDERER_HPP
