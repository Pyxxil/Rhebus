#include "layerdialog.hpp"
#include "ui_layerdialog.h"

LayerDialog::LayerDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LayerDialog) {
  ui->setupUi(this);
}

LayerDialog::~LayerDialog() { delete ui; }

QString LayerDialog::getLayerName() const { return ui->layerName->text(); }
