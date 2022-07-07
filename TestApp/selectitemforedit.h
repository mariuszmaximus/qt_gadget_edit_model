#ifndef SELECTITEMFOREDIT_H
#define SELECTITEMFOREDIT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SelectItemForEdit; }
QT_END_NAMESPACE

class GadgetDataModel;

namespace gadget {
    struct Foo
    {
        Q_GADGET
        Q_PROPERTY(int a MEMBER a)
        Q_PROPERTY(double x MEMBER x)

        int a = 1;
        double x = 0.23;
    };

    struct Bar
    {
        Q_GADGET

        Q_PROPERTY(QString s MEMBER s)
        Q_PROPERTY(int x MEMBER x)
        Q_PROPERTY(int y MEMBER y)

        QString s;
        int x = 0;
        int y = 0;
    };

    struct Baz {
        Q_GADGET

        Q_PROPERTY(Priority priority MEMBER priority)

    public:
        enum Priority { High, Low, VeryHigh, VeryLow };
        Q_ENUM(Priority)

        Priority priority = High;
    };
}

class SelectItemForEdit : public QMainWindow
{
    Q_OBJECT

public:
    SelectItemForEdit(QWidget *parent = nullptr);
    ~SelectItemForEdit();

private slots:
    void on_testFooButto_clicked();

    void on_testBarButton_clicked();

    void on_testBuzButton_clicked();

private:
    Ui::SelectItemForEdit *ui;
    GadgetDataModel *mGadgetModel;

    gadget::Foo mFoo;
    gadget::Bar mBar;
    gadget::Baz mBaz;
};
#endif // SELECTITEMFOREDIT_H
