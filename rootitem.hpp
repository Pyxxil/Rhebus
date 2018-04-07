#ifndef ROOTITEM_HPP
#define ROOTITEM_HPP

#include <QList>

class RootDefinition;
class RootLayer;

class RootItem {
public:
  explicit RootItem(const QVector<QVariant> &data, RootItem *parent)
      : itemData(data), childItems(), mParent(parent) {}
  ~RootItem();

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

  void setUp(RootDefinition **definitions, RootLayer **layers);

  virtual bool isDescription() const { return false; }

private:
  QVector<QVariant> itemData;
  QList<RootItem *> childItems;
  RootItem *mParent;
};

#endif // ROOTITEM_HPP
