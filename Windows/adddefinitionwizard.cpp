#include <QColorDialog>

#include "adddefinitionwizard.hpp"
#include "ui_adddefinitionwizard.h"

#include "Items/descriptionitem.hpp"

AddDefinitionWizard::AddDefinitionWizard(QWidget *parent)
    : QWizard(parent), ui(new Ui::AddDefinitionWizard), mUpdater(nullptr) {
  ui->setupUi(this);
  ui->renderer->setMinimumWidth(width() - 100);
  ui->renderer->setMinimumHeight(height() - ui->shapeComboBox->height() - 100);

  ui->renderer->setBrush(QBrush(Qt::black));

  ui->penColourButton->setStyleSheet(
      "QPushButton { background-color : black; color : black; }");
  ui->brushColourButton->setStyleSheet(
      "QPushButton { background-color : black; color : black; }");

  connect(this, SIGNAL(updateSizes()), ui->renderer, SLOT(changeSize()));

  connect(ui->penColourButton, SIGNAL(clicked(bool)), this,
          SLOT(openPenColourChooser()));
  connect(ui->brushColourButton, SIGNAL(clicked(bool)), this,
          SLOT(openBrushColourChooser()));

  connect(ui->shapeComboBox, SIGNAL(currentIndexChanged(QString)), ui->renderer,
          SLOT(setFromString(QString)));

  connect(ui->penWidthSpinBox, SIGNAL(valueChanged(int)), ui->renderer,
          SLOT(setPenWidth(int)));

  emit ui->penWidthSpinBox->valueChanged(ui->penWidthSpinBox->value());
  emit ui->shapeComboBox->currentIndexChanged(ui->shapeComboBox->currentText());
  emit updateSizes();
}

AddDefinitionWizard::~AddDefinitionWizard() { delete ui; }

const QString AddDefinitionWizard::definitionName() const {
  return ui->definitionName->text();
}

const QList<QSharedPointer<Shape>> AddDefinitionWizard::shapes() const {
  return ui->renderer->shapes();
}

void AddDefinitionWizard::setDefinitionName(const QString &name) {
  ui->definitionName->setText(name);
}

void AddDefinitionWizard::setDescription(const DescriptionItem *item) {
  ui->renderer->setShapes(item->shapes());
}

void AddDefinitionWizard::setUpdater(ShapeItem *up) { mUpdater = up; }

void AddDefinitionWizard::setShapes(
    const QList<QSharedPointer<Shape>> &shapes) {
  ui->renderer->setShapes(shapes);
}

void AddDefinitionWizard::openPenColourChooser() {
  QColorDialog colourDialog;
  colourDialog.setModal(true);

  connect(&colourDialog, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(penColourChanged(QColor)));
  connect(&colourDialog, SIGNAL(currentColorChanged(QColor)), ui->renderer,
          SLOT(setPenColour(QColor)));

  colourDialog.exec();
}

void AddDefinitionWizard::openBrushColourChooser() {
  QColorDialog colourDialog;
  colourDialog.setModal(true);
  colourDialog.setOption(QColorDialog::ShowAlphaChannel, true);

  connect(&colourDialog, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(brushColourChanged(QColor)));
  connect(&colourDialog, SIGNAL(currentColorChanged(QColor)), ui->renderer,
          SLOT(setBrushColor(QColor)));

  colourDialog.exec();
}

void AddDefinitionWizard::penColourChanged(QColor colour) {
  ui->penColourButton->setStyleSheet(
      QString("QPushButton { background-color : %1; color : %1; }")
          .arg(colour.name()));
}

void AddDefinitionWizard::brushColourChanged(QColor colour) {
  ui->brushColourButton->setStyleSheet(
      QString("QPushButton { background-color : %1; color : %1; }")
          .arg(colour.name()));
}
