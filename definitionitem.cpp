#include "definitionitem.hpp"

#include <QDebug>

DefinitionItem::DefinitionItem(const QVector<QVariant> &data,
                               DefinitionItem *parent)
    : itemData(data), parentItem(parent) {}

DefinitionItem::~DefinitionItem() { qDeleteAll(childItems); }

DefinitionItem *DefinitionItem::child(int number) {
  return childItems.value(number);
}

DefinitionItem *DefinitionItem::parent() { return parentItem; }

QVariant DefinitionItem::data(int column) const {
  return itemData.value(column);
}

int DefinitionItem::childCount() const { return childItems.count(); }

int DefinitionItem::childNumber() const {
  if (parentItem) {
    return parentItem->childItems.indexOf(const_cast<DefinitionItem *>(this));
  }

  return 0;
}

int DefinitionItem::columnCount() const { return itemData.count(); }

bool DefinitionItem::insertChildren(int position, int count, int columns) {
  if (position < 0 || position > childItems.count()) {
    return false;
  }

  for (int row = 0; row < count; ++row) {
    QVector<QVariant> data(columns);
    DefinitionItem *item = new DefinitionItem(data, this);
    childItems.insert(position, item);
  }

  return true;
}

bool DefinitionItem::insertColumns(int position, int columns) {
  if (position < 0 || position > childItems.count()) {
    return false;
  }

  for (int column = 0; column < columns; ++column) {
    itemData.insert(position, QVariant());
  }

  foreach (DefinitionItem *child, childItems) {
    child->insertColumns(position, columns);
  }

  return true;
}

bool DefinitionItem::removeChildren(int position, int count) {
  if (position < 0 || position > childItems.count()) {
    return false;
  }

  for (int row = 0; row < count; ++row) {
    delete childItems.takeAt(position);
  }

  return true;
}

bool DefinitionItem::removeColumns(int position, int columns) {
  if (position < 0 || position > childItems.count()) {
    return false;
  }

  for (int column = 0; column < columns; ++column) {
    itemData.removeAt(position);
  }

  foreach (DefinitionItem *child, childItems) {
    child->removeColumns(position, columns);
  }

  return true;
}

bool DefinitionItem::setData(int column, const QVariant &value) {
  if (column < 0 || column > itemData.size()) {
    return false;
  }

  itemData[column] = value;
  return true;
}
