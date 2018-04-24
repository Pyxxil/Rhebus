#ifndef LAYERITEM_HPP
#define LAYERITEM_HPP

#include "rootitem.hpp"
#include "rootlayeritem.hpp"

class ObjectItem;

class LayerItem : public RootItem {
public:
  explicit LayerItem(RootItem *parent, const QString &tName);
  ~LayerItem() = default;

  const QString &name() const { return mName; }

  void addObject(const QString &);

  ObjectItem *object(int number);
  QVariant data(int column) const;
  int childCount() const;
  int childNumber();
  int columnCount() const { return 1; }

  bool isLayer() const final { return true; }

  const QList<ObjectItem *> &objects() const;
  void setObjects(const QList<ObjectItem *> &objects);

private:
  QList<ObjectItem *> mObjects;
  QString mName;
};

#endif // LAYERITEM_HPP
