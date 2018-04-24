#include "Items/layeritem.hpp"
#include "Items/objectitem.hpp"

LayerItem::LayerItem(RootItem *parent, const QString &tName)
    : RootItem(QVector<QVariant>() << tName, parent), mName(tName) {}

void LayerItem::addObject(const QString &name) {
  ObjectItem *obj = new ObjectItem(this, name);
  mObjects.append(obj);
  children().append(obj);
}

ObjectItem *LayerItem::object(int number) { return mObjects.value(number); }

QVariant LayerItem::data(int) const { return mName; }

int LayerItem::childCount() const { return mObjects.count(); }

int LayerItem::childNumber() {
  if (parent()) {
    return static_cast<RootLayerItem *>(parent())->layers().indexOf(
        const_cast<LayerItem *>(this));
  }

  return 0;
}

const QList<ObjectItem *> &LayerItem::objects() const { return mObjects; }

void LayerItem::setObjects(const QList<ObjectItem *> &objects) {
  mObjects = objects;
}
