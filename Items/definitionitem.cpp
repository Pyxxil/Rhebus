#include "definitionitem.hpp"
#include "descriptionitem.hpp"

#include <QDebug>

DefinitionItem::DefinitionItem(RootDefinitionItem *parent, const QString &tName)
    : RootItem(QVector<QVariant>() << tName, parent), mName(tName) {}

void DefinitionItem::addDescription(
    const QList<QSharedPointer<Shape>> &tShapes) {
  DescriptionItem *desc = new DescriptionItem(this);
  desc->addShapes(tShapes);

  descriptions.append(desc);
  children().append(desc);
}

DescriptionItem *DefinitionItem::description(int number) {
  return descriptions.value(number);
}

QVariant DefinitionItem::data(int) const { return mName; }

int DefinitionItem::childCount() const { return descriptions.count(); }

int DefinitionItem::childNumber() {
  if (parent()) {
    return parent()->definitions().indexOf(const_cast<DefinitionItem *>(this));
  }

  return 0;
}

int DefinitionItem::columnCount() const { return 1; }
