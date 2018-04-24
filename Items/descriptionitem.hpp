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
  virtual ~DescriptionItem() = default;

  ShapeItem *parent() const;

  void setShapes(const QList<QSharedPointer<Shape>> &tShapes) {
    mShapes.clear();
    for (auto &&shape : tShapes) {
      addShape(shape);
    }
  }
  void addShape(const QSharedPointer<Shape> &shape) {
    mShapes.append(QSharedPointer<Shape>(shape->clone()));
    //    const QString &t = shape->name();
    //    qDebug() << "Adding shape:" << t;
    //    if (t == "Triangle") {
    //      Triangle *n = static_cast<Triangle *>(shape.data())->clone();
    //      mShapes.append(QSharedPointer<Shape>(n));
    //    } else if (t == "Rectangle") {
    //      Rectangle *n = static_cast<Rectangle *>(shape.data())->clone();
    //      mShapes.append(QSharedPointer<Shape>(n));
    //    } else if (t == "Line") {
    //      Line *n = static_cast<Line *>(shape.data())->clone();
    //      mShapes.append(QSharedPointer<Shape>(n));
    //    } else if (t == "Path") {
    //      Path *n = static_cast<Path *>(shape.data())->clone();
    //      mShapes.append(QSharedPointer<Shape>(n));
    //    }
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
