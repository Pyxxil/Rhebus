#include "mainwindow.hpp"

#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QDebug>

#include "Items/descriptionitem.hpp"
#include "Items/layeritem.hpp"
#include "Items/objectitem.hpp"
#include "Items/shapeitem.hpp"
#include "Models/definitionmodel.hpp"
#include "adddefinitionwizard.hpp"
#include "layerdialog.hpp"
#include "objectdialog.hpp"
#include "programwindow.hpp"

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

  // Auto-Expand each node after rows are inserted
  connect(definitionModel, &QAbstractItemModel::rowsInserted,
          [&](const QModelIndex &parent, int first, int last) {
            for (; first <= last; ++first) {
              ui->definitionView->expand(
                  definitionModel->index(first, 0, parent));
            }
          });

  QAction *run = new QAction(tr("Run"));
  connect(run, SIGNAL(triggered(bool)), this, SLOT(runProgram(bool)));
  QMenu *runMenu = new QMenu(tr("Run"));
  ui->menuBar->addMenu(runMenu);
  runMenu->addAction(run);

  setMenuBar(ui->menuBar);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::customMenuRequested(QPoint point) {
  QModelIndex index = ui->definitionView->indexAt(point);

  QMenu menu(this);

  QAction *addDef = new QAction(tr("Add Shape"), this);
  menu.addAction(addDef);
  connect(addDef, SIGNAL(triggered(bool)), this, SLOT(addDefinition(bool)));

  QAction *addLay = new QAction(tr("Add Layer"), this);
  menu.addAction(addLay);
  connect(addLay, SIGNAL(triggered(bool)), this, SLOT(addLayer(bool)));

  if (index.isValid()) {
    RootItem *item = static_cast<RootItem *>(index.internalPointer());

    if (item->isRootLayer()) {
      QAction *changeBackgroundColour = new QAction(tr("Change Background"));
      menu.addAction(changeBackgroundColour);
      connect(changeBackgroundColour, SIGNAL(triggered(bool)), this,
              SLOT(changeBGColour(bool)));
    } else if (item->isDescription() || item->isDefinition()) {
      QAction *editDef = new QAction(tr("Edit Shape"), this);
      menu.addAction(editDef);
      connect(editDef, SIGNAL(triggered(bool)), this,
              SLOT(editDefinition(bool)));

      if (item->isDescription()) {
        QAction *copyDescription = new QAction(tr("Copy Description"));
        menu.addAction(copyDescription);
        connect(copyDescription, SIGNAL(triggered(bool)), this,
                SLOT(copyDescription(bool)));
      }
    } else if (item->isLayer()) {
      QAction *addObj = new QAction(tr("Add Object"));
      menu.addAction(addObj);
      connect(addObj, SIGNAL(triggered(bool)), this, SLOT(addObject(bool)));
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

  ShapeItem *item;

  if (selected->isDescription()) {
    item = static_cast<ShapeItem *>(selected->parent());
  } else {
    item = static_cast<ShapeItem *>(selected);
  }

  wizard.setDefinitionName(item->name());
  wizard.setShapes(item->description(0)->shapes());
  wizard.setUpdater(item);

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

void MainWindow::addLayer(bool) {
  LayerDialog layerDialog;
  connect(&layerDialog, SIGNAL(accepted()), this, SLOT(addLayerAccepted()));
  layerDialog.exec();
}

void MainWindow::addObject(bool) {
  ObjectDialog objDialog;
  LayerItem *selected = static_cast<LayerItem *>(
      ui->definitionView->currentIndex().internalPointer());
  objDialog.setUpdater(selected);
  for (auto &&shape : definitionModel->definitions()->definitions()) {
    objDialog.addObject(shape->name());
  }
  connect(&objDialog, SIGNAL(accepted()), this, SLOT(addObjectAccepted()));
  objDialog.exec();
}

void MainWindow::changeBGColour(bool) {
  QColorDialog backgroundColourChooser;
  backgroundColourChooser.setModal(true);
  connect(&backgroundColourChooser, SIGNAL(currentColorChanged(QColor)),
          definitionModel, SLOT(setBackgroundColour(QColor)));
  backgroundColourChooser.exec();
}

void MainWindow::addDefinitionWizardAccepted() {
  AddDefinitionWizard *wizard = static_cast<AddDefinitionWizard *>(sender());
  ShapeItem *up = wizard->updater();
  if (up != nullptr) {
    up->setData(0, wizard->definitionName());
    up->description(0)->setShapes(wizard->shapes());
    if (up == ui->definitionView->currentIndex().internalPointer()) {
      emit ui->definitionView->render(up->description(0));
    }
  } else {
    definitionModel->insertDefinition(wizard->definitionName(),
                                      wizard->shapes());
  }
}

void MainWindow::addLayerAccepted() {
  LayerDialog *dialog = static_cast<LayerDialog *>(sender());
  definitionModel->insertLayer(dialog->getLayerName());
}

void MainWindow::addObjectAccepted() {
  ObjectDialog *dialog = static_cast<ObjectDialog *>(sender());
  definitionModel->insertObject(dialog->getUpdater(), dialog->selected());
  LayerItem *layerToUpdate = definitionModel->layers()->layer(
      definitionModel->layers()->childCount() - 1);
  ObjectItem *objectToUpdate =
      layerToUpdate->object(layerToUpdate->childCount() - 1);
  DescriptionItem *desc = static_cast<DescriptionItem *>(
      definitionModel->definitions()->findByName(dialog->selected())->child(0));
  objectToUpdate->setShapes(desc->shapes());
}

void MainWindow::runProgram(bool) {
  ProgramWindow program;

  for (auto &&layer : definitionModel->layers()->layers()) {
    for (auto &&object : layer->objects()) {
      program.addShape(object->shapes());
    }
  }
  program.setBackgroundColour(definitionModel->backgroundColour());
  program.draw();
  program.showFullScreen();

  QEventLoop loop;
  connect(&program, SIGNAL(destroyed()), &loop, SLOT(quit()));
  loop.exec();
}
