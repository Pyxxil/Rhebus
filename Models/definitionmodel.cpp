#include "definitionmodel.hpp"
#include "Items/layeritem.hpp"
#include "Items/rootdefinitionitem.hpp"
#include "Items/rootitem.hpp"
#include "Items/rootlayeritem.hpp"
#include "Items/shapeitem.hpp"

#include <QDebug>

DefinitionModel::DefinitionModel(QObject *parent)
    : QAbstractItemModel(parent), mDefinitions(), mLayers() {
  rootItem = new RootItem(QVector<QVariant>() << QString(""), nullptr);
  setupModelData(rootItem);
}

QModelIndex DefinitionModel::index(int row, int column,
                                   const QModelIndex &parent) const {
  if (parent.isValid() && parent.column() != 0) {
    return QModelIndex();
  }

  RootItem *parentItem = getItem(parent);
  RootItem *childItem = parentItem->child(row);

  if (childItem) {
    return createIndex(row, column, childItem);
  }

  return QModelIndex();
}

QModelIndex DefinitionModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) {
    return QModelIndex();
  }

  RootItem *childItem = getItem(index);
  RootItem *parentItem = childItem->parent();

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

  RootItem *item = getItem(index);

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
  RootItem *parentItem = getItem(parent);
  return parentItem->childCount();
}

int DefinitionModel::columnCount(const QModelIndex &) const {
  return rootItem->columnCount();
}

Qt::ItemFlags DefinitionModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return nullptr;
  }

  return QAbstractItemModel::flags(index);
}

bool DefinitionModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  if (role != Qt::EditRole) {
    return false;
  }

  RootItem *item = getItem(index);

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
  RootItem *parentItem = getItem(parent);

  bool success;

  beginInsertRows(parent, position, position + rows - 1);
  success = parentItem->insertChildren(position, rows, rootItem->columnCount());
  endInsertRows();

  return success;
}

bool DefinitionModel::removeRows(int position, int rows,
                                 const QModelIndex &parent) {
  RootItem *parentItem = getItem(parent);

  bool success = true;

  beginRemoveRows(parent, position, position + rows - 1);
  success = parentItem->removeChildren(position, rows);
  endRemoveRows();

  return success;
}

RootItem *DefinitionModel::getItem(const QModelIndex &index) const {
  if (index.isValid()) {
    RootItem *item = static_cast<RootItem *>(index.internalPointer());

    if (item) {
      return item;
    }
  }

  return rootItem;
}

void DefinitionModel::insertDefinition(
    const QString &name, const QList<QSharedPointer<Shape>> &shapes) {
  beginInsertRows(QModelIndex(), 0, 1);
  mDefinitions->addDefinition(name);
  mDefinitions->definition(mDefinitions->childCount() - 1)
      ->addDescription(shapes);
  endInsertRows();
}

void DefinitionModel::insertObject(LayerItem *layer, const QString &name) {
  beginInsertRows(QModelIndex(), 0, 1);
  layer->addObject(name);
  endInsertRows();
}

void DefinitionModel::insertLayer(const QString &name) {
  beginInsertRows(QModelIndex(), 0, 1);
  layers()->addLayer(name);
  endInsertRows();
}

void DefinitionModel::setupModelData(RootItem *parent) {
  parent->setUp(&mDefinitions, &mLayers);
}
