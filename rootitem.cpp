#include "rootitem.hpp"

#include "definitionitem.hpp"

#include <QDebug>

RootItem::RootItem(const QVector<QVariant> &data,
                               RootItem *parent)
    : itemData(data), parentItem(parent) {}

RootItem::~RootItem() { qDeleteAll(childItems); }

DefinitionItem *RootItem::child(int number) {
  return childItems.value(number);
}

RootItem *RootItem::parent() { return parentItem; }

QVariant RootItem::data(int column) const {
  return itemData.value(column);
}

int RootItem::childCount() const { return childItems.count(); }

int RootItem::childNumber() const {
  if (parentItem) {
    //return parentItem->childItems.indexOf(const_cast<RootItem *>(this));
  }

  return 0;
}

int RootItem::columnCount() const { return itemData.count(); }

bool RootItem::insertChildren(int position, int count, int columns) {
  if (position < 0 || position > childItems.count()) {
    return false;
  }

  for (int row = 0; row < count; ++row) {
    QVector<QVariant> data(columns);
    //DefinitionItem *item = new DefinitionItem(data, this);
    //childItems.insert(position, item);
  }

  return true;
}

bool RootItem::insertColumns(int position, int columns) {
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

bool RootItem::removeChildren(int position, int count) {
  if (position < 0 || position > childItems.count()) {
    return false;
  }

  for (int row = 0; row < count; ++row) {
    delete childItems.takeAt(position);
  }

  return true;
}

bool RootItem::removeColumns(int position, int columns) {
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

bool RootItem::setData(int column, const QVariant &value) {
  if (column < 0 || column > itemData.size()) {
    return false;
  }

  itemData[column] = value;
  return true;
}