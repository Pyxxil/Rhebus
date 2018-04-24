#include "objectdialog.hpp"
#include "ui_objectdialog.h"

ObjectDialog::ObjectDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::ObjectDialog) {
  ui->setupUi(this);
}

ObjectDialog::~ObjectDialog() { delete ui; }

void ObjectDialog::addObject(const QString &objName) {
  ui->objectBox->addItem(objName);
}

QString ObjectDialog::selected() const { return ui->objectBox->currentText(); }

LayerItem *ObjectDialog::getUpdater() const { return updater; }

void ObjectDialog::setUpdater(LayerItem *value) { updater = value; }
