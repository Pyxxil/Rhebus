#include <QMenu>

#include "definitionview.hpp"

DefinitionView::DefinitionView(QWidget *parent) : QTreeView(parent) {
  setContextMenuPolicy(Qt::CustomContextMenu);
}
