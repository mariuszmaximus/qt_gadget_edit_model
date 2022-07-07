#include "selectitemforedit.h"
#include "./ui_selectitemforedit.h"

#include <GadgetDataModel.h>

SelectItemForEdit::SelectItemForEdit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SelectItemForEdit)
{
    ui->setupUi(this);

    mGadgetModel = new GadgetDataModel(this);
    ui->gadgetView->setModel(mGadgetModel);
}

SelectItemForEdit::~SelectItemForEdit()
{
    delete ui;
}


void SelectItemForEdit::on_testFooButto_clicked()
{
    mGadgetModel->setGadget(&mFoo);
}


void SelectItemForEdit::on_testBarButton_clicked()
{
    mGadgetModel->setGadget(&mBar);
}


void SelectItemForEdit::on_testBuzButton_clicked()
{
    mGadgetModel->setGadget(&mBaz);
}
