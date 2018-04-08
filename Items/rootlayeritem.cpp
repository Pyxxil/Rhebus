#include "rootlayeritem.hpp"
#include "layeritem.hpp"

RootLayerItem::RootLayerItem(RootItem *parent)
    : RootItem(QVector<QVariant>() << "Layers", parent) {}

void RootLayerItem::addLayer(const QString &name) {
  mLayers.append(new LayerItem(this, name));
}
