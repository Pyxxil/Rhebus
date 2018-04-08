#include "mainwindow.hpp"

#include "ui_mainwindow.h"

#include <QDebug>

#include "Items/definitionitem.hpp"
#include "Items/descriptionitem.hpp"
#include "Models/definitionmodel.hpp"
#include "adddefinitionwizard.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->definitionView->setModel(new DefinitionModel);

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->definitionView, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(customMenuRequested(QPoint)));
  connect(ui->definitionView, SIGNAL(render(DescriptionItem *)),
          ui->definitionRenderer, SLOT(renderDescription(DescriptionItem *)));
  ui->definitionRenderer->changeSize();

  definitionModel = static_cast<DefinitionModel *>(ui->definitionView->model());

  // static_cast<DefinitionModel *>(ui->definitionView->model())
  //    ->insertDefinition(DefinitionItem(
  //          QVector<QVariant>() << "Hello",
  //          static_cast<DefinitionModel *>(ui->definitionView->model())
  //              ->getItem(QModelIndex())));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::customMenuRequested(QPoint point) {
  QModelIndex index = ui->definitionView->indexAt(point);

  QMenu menu(this);
  QAction *addDef = new QAction(tr("Add Definition"), this);
  menu.addAction(addDef);
  connect(addDef, SIGNAL(triggered(bool)), this, SLOT(addDefinition(bool)));

  if (index.isValid()) {
    RootItem *item = static_cast<RootItem *>(index.internalPointer());

    if (item->isDescription() || item->isDefinition()) {
      QAction *editDef = new QAction(tr("Edit Definition"), this);
      menu.addAction(editDef);
      connect(editDef, SIGNAL(triggered(bool)), this,
              SLOT(editDefinition(bool)));

      if (item->isDescription()) {
        QAction *copyDescription = new QAction(tr("Copy Description"));
        menu.addAction(copyDescription);
        connect(copyDescription, SIGNAL(triggered(bool)), this,
                SLOT(copyDescription(bool)));
      }
    }
  }

  menu.exec(ui->definitionView->viewport()->mapToGlobal(point));
}

void MainWindow::addDefinition(bool) {
  AddDefinitionWizard wizard;
  connect(&wizard, SIGNAL(accepted()), this,
          SLOT(addDefinitionWizardAccepted()));
  wizard.exec();
}

void MainWindow::editDefinition(bool) {
  AddDefinitionWizard wizard;
  RootItem *selected = static_cast<RootItem *>(
      ui->definitionView->currentIndex().internalPointer());

  DefinitionItem *item;

  if (selected->isDescription()) {
    item = static_cast<DefinitionItem *>(selected->parent());
  } else {
    item = static_cast<DefinitionItem *>(selected);
  }

  wizard.setDefinitionName(item->name());

  connect(&wizard, SIGNAL(accepted()), this,
          SLOT(addDefinitionWizardAccepted()));
  wizard.exec();
}

void MainWindow::copyDescription(bool) {
  AddDefinitionWizard wizard;
  DescriptionItem *selected = static_cast<DescriptionItem *>(
      ui->definitionView->currentIndex().internalPointer());

  wizard.setDescription(selected);

  connect(&wizard, SIGNAL(accepted()), this,
          SLOT(addDefinitionWizardAccepted()));
  wizard.exec();
}

void MainWindow::addDefinitionWizardAccepted() {
  AddDefinitionWizard *wizard = static_cast<AddDefinitionWizard *>(sender());
  definitionModel->insertDefinition(wizard->definitionName(), wizard->shapes());
}
