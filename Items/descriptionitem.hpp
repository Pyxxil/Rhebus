#ifndef DESCRIPTIONITEM_HPP
#define DESCRIPTIONITEM_HPP

#include "Shapes/line.hpp"
#include "Shapes/path.hpp"
#include "Shapes/rectangle.hpp"
#include "Shapes/shape.hpp"
#include "Shapes/triangle.hpp"

#include "rootitem.hpp"

class QPainter;
class DefinitionItem;

class DescriptionItem : public RootItem {
public:
  explicit DescriptionItem(DefinitionItem *parent);
  ~DescriptionItem() = default;

  DefinitionItem *parent() const;

  void addShape(const QSharedPointer<Shape> &shape) { mShapes.append(shape); }
  void addShapes(const QList<QSharedPointer<Shape>> &tShapes) {
    std::for_each(tShapes.begin(), tShapes.end(),
                  [this](auto &&shape) { addShape(shape); });
  }
  void render(QPainter *painter);

  bool isDescription() const final { return true; }

  const QList<QSharedPointer<Shape>> &shapes() const { return mShapes; }

private:
  DefinitionItem *mParent;
  QList<QSharedPointer<Shape>> mShapes;
};

#endif // DESCRIPTIONITEM_HPP
