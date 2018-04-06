#include "definitionmodel.hpp"
#include "definitionitem.hpp"
#include "rootitem.hpp"

#include <QDebug>

DefinitionModel::DefinitionModel(QObject *parent) : QAbstractItemModel(parent) {
  rootItem = new DefinitionItem(QVector<QVariant>() << QString(""), nullptr);
  setupModelData(rootItem);
}

QModelIndex DefinitionModel::index(int row, int column,
                                   const QModelIndex &parent) const {
  if (parent.isValid() && parent.column() != 0) {
    return QModelIndex();
  }

  DefinitionItem *parentItem = getItem(parent);
  DefinitionItem *childItem = parentItem->child(row);

  if (childItem) {
    return createIndex(row, column, childItem);
  }

  return QModelIndex();
}

QModelIndex DefinitionModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) {
    return QModelIndex();
  }

  DefinitionItem *childItem = getItem(index);
  DefinitionItem *parentItem = childItem->parent();

  if (parentItem == rootItem) {
    return QModelIndex();
  }

  return createIndex(parentItem->childNumber(), 0, parentItem);
}

QVariant DefinitionModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }

  if (role != Qt::DisplayRole && role != Qt::EditRole) {
    return QVariant();
  }

  DefinitionItem *item = getItem(index);

  return item->data(index.column());
}

QVariant DefinitionModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return rootItem->data(section);
  }

  return QVariant();
}

int DefinitionModel::rowCount(const QModelIndex &parent) const {
  DefinitionItem *parentItem = getItem(parent);
  return parentItem->childCount();
}

int DefinitionModel::columnCount(const QModelIndex &) const {
  return rootItem->columnCount();
}

Qt::ItemFlags DefinitionModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return 0;
  }

  return QAbstractItemModel::flags(index);
}

bool DefinitionModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  if (role != Qt::EditRole) {
    return false;
  }

  DefinitionItem *item = getItem(index);

  bool result = item->setData(index.column(), value);

  if (result) {
    emit dataChanged(index, index);
  }

  return result;
}

bool DefinitionModel::setHeaderData(int section, Qt::Orientation orientation,
                                    const QVariant &value, int role) {
  if (role != Qt::EditRole || orientation == Qt::Horizontal) {
    return false;
  }

  bool result = rootItem->setData(section, value);

  if (result) {
    emit headerDataChanged(orientation, section, section);
  }

  return result;
}

bool DefinitionModel::insertColumns(int position, int columns,
                                    const QModelIndex &parent) {
  bool success;

  beginInsertColumns(parent, position, position + columns - 1);
  success = rootItem->insertColumns(position, columns);
  endInsertColumns();

  return success;
}

bool DefinitionModel::removeColumns(int position, int columns,
                                    const QModelIndex &parent) {
  bool success = true;

  beginRemoveColumns(parent, position, position + columns - 1);
  success = rootItem->removeChildren(position, columns);
  endInsertColumns();

  return success;
}

bool DefinitionModel::insertRows(int position, int rows,
                                 const QModelIndex &parent) {
  DefinitionItem *parentItem = getItem(parent);

  bool success;

  beginInsertRows(parent, position, position + rows - 1);
  success = parentItem->insertChildren(position, rows, rootItem->columnCount());
  endInsertRows();

  return success;
}

bool DefinitionModel::removeRows(int position, int rows,
                                 const QModelIndex &parent) {
  DefinitionItem *parentItem = getItem(parent);

  bool success = true;

  beginRemoveRows(parent, position, position + rows - 1);
  success = parentItem->removeChildren(position, rows);
  endRemoveRows();

  return success;
}

DefinitionItem *DefinitionModel::getItem(const QModelIndex &index) const {
  if (index.isValid()) {
    DefinitionItem *item =
        static_cast<DefinitionItem *>(index.internalPointer());

    if (item) {
      return item;
    }
  }

  return rootItem;
}

void DefinitionModel::insertDefinition(const DefinitionItem &def) {
  beginInsertRows(QModelIndex(), 0, 1);
  definitions->insertChildren(definitions->childCount(), 1,
                              rootItem->columnCount());
  definitions->child(definitions->childCount() - 1)->setData(0, def.data(0));
  endInsertRows();
}

void DefinitionModel::setupModelData(DefinitionItem *parent) {
  parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
  parent->child(parent->childCount() - 1)->setData(0, "Definitions");
  definitions = parent->child(parent->childCount() - 1);
}
