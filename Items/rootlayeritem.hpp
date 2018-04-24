#ifndef ROOTLAYER_HPP
#define ROOTLAYER_HPP

#include "rootitem.hpp"

class LayerItem;

class RootLayerItem : public RootItem {
public:
  explicit RootLayerItem(RootItem *parent);
  ~RootLayerItem() = default;

  void addLayer(const QString &name);
  LayerItem *layer(int row) const { return mLayers[row]; }

  const QList<LayerItem *> &layers() const { return mLayers; }

  bool isRootLayer() const final { return true; }

private:
  QList<LayerItem *> mLayers;
};

#endif // ROOTLAYER_HPP
