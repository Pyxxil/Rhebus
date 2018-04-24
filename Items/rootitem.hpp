#ifndef ROOTITEM_HPP
#define ROOTITEM_HPP

#include <QList>

class RootDefinitionItem;
class RootLayerItem;

class RootItem {
public:
  explicit RootItem(const QVector<QVariant> &data, RootItem *parent = nullptr)
      : itemData(data), childItems(), mParent(parent) {}
  virtual ~RootItem();

  RootItem *child(int row);
  int childCount() const;
  int columnCount() const;
  int childNumber() const;

  QVariant data(int column) const;

  bool insertChildren(int position, int count, int columns);
  bool insertColumns(int position, int columns);
  bool removeChildren(int position, int count);
  bool removeColumns(int position, int columns);
  bool setData(int column, const QVariant &value);

  RootItem *parent() const;

  QList<RootItem *> &children() { return childItems; }

  void setUp(RootDefinitionItem **definitions, RootLayerItem **layers);

  virtual bool isDescription() const { return false; }
  virtual bool isDefinition() const { return false; }
  virtual bool isLayer() const { return false; }
  virtual bool isObject() const { return false; }
  virtual bool isRootLayer() const { return false; }

private:
  QVector<QVariant> itemData;
  QList<RootItem *> childItems;
  RootItem *mParent;
};

#endif // ROOTITEM_HPP
