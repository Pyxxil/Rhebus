#include "mainwindow.hpp"
#include <QPaintEngine>

#include "ui_mainwindow.h"

#include "definitionitem.hpp"
#include "definitionmodel.hpp"
#include "adddefinitionwizard.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->definitionView->setModel(new DefinitionModel);

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->definitionView, SIGNAL(customContextMenuRequested(QPoint)),
          SLOT(customMenuRequested(QPoint)));

  definitionModel = static_cast<DefinitionModel *>(ui->definitionView->model());

  //static_cast<DefinitionModel *>(ui->definitionView->model())
  //    ->insertDefinition(DefinitionItem(
//          QVector<QVariant>() << "Hello",
//          static_cast<DefinitionModel *>(ui->definitionView->model())
//              ->getItem(QModelIndex())));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::customMenuRequested(QPoint point) {
  QModelIndex index = ui->definitionView->indexAt(point);

  QMenu menu(this);
  QAction addDef(tr("Add Definition"), this);
  menu.addAction(&addDef);
  connect(&addDef, SIGNAL(triggered(bool)), this, SLOT(addDefinition(bool)));

  if (index.isValid()) {
    QAction editDef(tr("Edit Definition"));
    menu.addAction(&editDef);
    connect(&editDef, SIGNAL(triggered(bool)), this,
            SLOT(editDefinition(bool)));
  }

  menu.exec(ui->definitionView->viewport()->mapToGlobal(point));
}

void MainWindow::addDefinition(bool) {
  AddDefinitionWizard wizard;
  connect(&wizard, SIGNAL(accepted()), this, SLOT(addDefinitionWizardAccepted()));
  wizard.exec();
}

void MainWindow::editDefinition(bool) {}

void MainWindow::addDefinitionWizardAccepted()
{
  AddDefinitionWizard *wizard = static_cast<AddDefinitionWizard *>(sender());
  definitionModel->insertDefinition(DefinitionItem(QVector<QVariant>() << wizard->definitionName(),
                                                   definitionModel->getItem((QModelIndex()))));
}
