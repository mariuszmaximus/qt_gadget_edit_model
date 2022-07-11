#include "selectitemforedit.h"
#include "./ui_selectitemforedit.h"

#include <GadgetDataModel.h>

#include <QDebug>


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

#include <edit_struct_base.h>

class Edit_Foo : public Edit_struct::Edit_struct_base
{
public:
    gadget::Foo *ob{nullptr};
    Edit_Foo(gadget::Foo &ob_)
    {
        ob = &ob_;
    }
    virtual void init_rows()
    {
        Edit_struct_base::add_separator("Sekcja 1");

        Edit_struct_base::add_edit("Nazwa a",row_int, &ob->a, "opis 1");
        Edit_struct_base::add_edit("Nazwa x",row_double,  &ob->x, "opis 2    dlugi dlugi dlugi dlugi dlugi dlugi dlugi dlugi dlugi dlugi dlugi dlugi dlugi dlugi \ndlugi dlugi dlugi dlugi dlugi ");
        Edit_struct_base::add_combo("Nazwa x",row_int,  &ob->x, "lista rozwijana ", {{"aaaa",1}, {"bbb",0}, {"cccc",5}});
        Edit_struct_base::add_slider("test slider x",row_int,  &ob->x, "slider -5 ..3", {-5,3});
        
        Edit_struct_base::add_separator("Sekcja 2");
        Edit_struct_base::add_edit("Nazwa a",row_int,nullptr,"puste pole ");
        Edit_struct_base::add_edit("Nazwa x",row_double,nullptr,"puste pole");

        Edit_struct_base::add_page("page 2");
        Edit_struct_base::add_edit("Nazwa a",row_int,nullptr,"desc");
        Edit_struct_base::add_edit("Nazwa x",row_double,nullptr,"desc");
    }
};

void SelectItemForEdit::on_testFooButto20_clicked()
{
    Edit_Foo * f = new Edit_Foo (mFoo);
    f->execute([this](){ qDebug() << "SEND EXECUE";
                      qDebug() << "a=" << this->mFoo.a; 
                      qDebug() << "x=" << this->mFoo.x; });
    f->resize(600,600);
    f->show();
}

