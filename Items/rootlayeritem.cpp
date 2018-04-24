#include "rootlayeritem.hpp"
#include "layeritem.hpp"

RootLayerItem::RootLayerItem(RootItem *parent)
    : RootItem(QVector<QVariant>() << "Layers", parent) {}

void RootLayerItem::addLayer(const QString &name) {
  LayerItem *layer = new LayerItem(this, name);
  mLayers.append(layer);
  children().append(layer);
}
