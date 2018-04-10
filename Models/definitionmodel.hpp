#ifndef DEFINITIONMODEL_HPP
#define DEFINITIONMODEL_HPP

#include <QAbstractItemModel>

class RootItem;
class Shape;
class RootDefinitionItem;
class RootLayerItem;
class ShapeItem;

class DefinitionModel : public QAbstractItemModel {
  Q_OBJECT
public:
  DefinitionModel(QObject *parent = nullptr);

  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const;
  QModelIndex parent(const QModelIndex &child) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;

  bool setData(const QModelIndex &index, const QVariant &value, int role);
  bool setHeaderData(int section, Qt::Orientation orientation,
                     const QVariant &value, int role);
  bool insertColumns(int column, int count, const QModelIndex &parent);
  bool removeColumns(int column, int count, const QModelIndex &parent);
  bool insertRows(int row, int count, const QModelIndex &parent);
  bool removeRows(int row, int count, const QModelIndex &parent);

  RootItem *getItem(const QModelIndex &index) const;

  void insertDefinition(const QString &name,
                        const QList<QSharedPointer<Shape>> shapes);

  RootDefinitionItem *definitions() const { return mDefinitions; }

private:
  void setupModelData(RootItem *parent);

  RootItem *rootItem;
  RootDefinitionItem *mDefinitions;
  RootLayerItem *layers;
};

#endif // DEFINITIONMODEL_HPP
