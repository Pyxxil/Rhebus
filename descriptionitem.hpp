#ifndef DESCRIPTIONITEM_HPP
#define DESCRIPTIONITEM_HPP

#include "rootitem.hpp"
#include "shape.hpp"

class QPainter;
class DefinitionItem;

class DescriptionItem : public RootItem {
public:
  explicit DescriptionItem(DefinitionItem *parent);
  ~DescriptionItem() = default;

  DefinitionItem *parent() const;

  void addShape(const QSharedPointer<Shape> &shape) { mShapes.append(shape); }
  void addShapes(const QList<QSharedPointer<Shape>> &tShapes) {
    mShapes.append(tShapes);
  }
  void render(QPainter *painter);

  bool isDescription() const final { return true; }

  const QList<QSharedPointer<Shape>> &shapes() const { return mShapes; }

private:
  DefinitionItem *mParent;
  QList<QSharedPointer<Shape>> mShapes;
};

#endif // DESCRIPTIONITEM_HPP
