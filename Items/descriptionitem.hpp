#ifndef DESCRIPTIONITEM_HPP
#define DESCRIPTIONITEM_HPP

#include <QDebug>

#include "Shapes/line.hpp"
#include "Shapes/path.hpp"
#include "Shapes/rectangle.hpp"
#include "Shapes/shape.hpp"
#include "Shapes/triangle.hpp"

#include "rootitem.hpp"

class QPainter;
class ShapeItem;

class DescriptionItem : public RootItem {
public:
  explicit DescriptionItem(ShapeItem *parent);
  ~DescriptionItem() override = default;

  ShapeItem *parent() const;

  void setShapes(const QList<QSharedPointer<Shape>> &tShapes) {
    mShapes.clear();
    for (auto &&shape : tShapes) {
      addShape(shape);
    }
  }
  void addShape(const QSharedPointer<Shape> &shape) {
    mShapes.append(QSharedPointer<Shape>(shape->clone()));
  }
  void addShapes(const QList<QSharedPointer<Shape>> &tShapes) {
    for (auto &&shape : tShapes) {
      addShape(shape);
    }
  }
  void render(QPainter *painter);

  bool isDescription() const final { return true; }

  const QList<QSharedPointer<Shape>> &shapes() const { return mShapes; }

private:
  ShapeItem *mParent;
  QList<QSharedPointer<Shape>> mShapes;
};

#endif // DESCRIPTIONITEM_HPP
