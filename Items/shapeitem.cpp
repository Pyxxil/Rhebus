#include "shapeitem.hpp"
#include "descriptionitem.hpp"

#include <QDebug>

ShapeItem::ShapeItem(RootDefinitionItem *parent, const QString &tName)
    : RootItem(QVector<QVariant>() << tName, parent), mName(tName) {}

ShapeItem::~ShapeItem() { qDeleteAll(descriptions); }

void ShapeItem::addDescription(const QList<QSharedPointer<Shape>> &tShapes) {
  DescriptionItem *desc = new DescriptionItem(this);
  desc->addShapes(tShapes);

  descriptions.append(desc);
  children().append(desc);
}

DescriptionItem *ShapeItem::description(int number) {
  return descriptions.value(number);
}

QVariant ShapeItem::data(int) const { return mName; }

int ShapeItem::childCount() const { return descriptions.count(); }

int ShapeItem::childNumber() {
  if (parent()) {
    return dynamic_cast<RootDefinitionItem *>(parent())->definitions().indexOf(
        this);
  }

  return 0;
}
