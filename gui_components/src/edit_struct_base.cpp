#include "edit_struct_base.h"
#include <QDebug>
#include <QGridLayout>
#include <QTabBar>
#include <vector>
#include <QTabWidget>
#include <string>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include "fancySlider_h.h"

#include <iostream>

namespace Edit_struct
{

    void Edit_struct_base::update_data()
    {
        // update data
        for (size_t i = 0; i < rows.size(); ++i)
        {
            if ((rowsComponents[i].edit_data || rowsComponents[i].combo) && rows[i].ptr)
            {
                uint8_t tmp_uint8_t;
                uint16_t tmp_uint16_t;
                int tmp_int_t;
                float tmp_float_t;
                double tmp_double_t;
                switch (rows[i].row_data)
                {
                case row_int:
                    if (rows[i].type == row_edit && rows[i].ptr)
                    {
                        tmp_int_t = *((int *)rows[i].ptr);
                        rowsComponents[i].edit_data->setText(QString::number(tmp_int_t));
                    }
                    else if ((rows[i].type == row_combo && rows[i].ptr))
                    {
                        tmp_int_t = *((int *)rows[i].ptr);
                        for (auto const &x : rows[i].combo_data)
                        {
                            if (x.second.second == tmp_int_t)
                                rowsComponents[i].combo->setCurrentIndex(x.first);
                        }
                    }
                    else if ((rows[i].type == row_slider && rows[i].ptr))
                    {
                        tmp_int_t = *((int *)rows[i].ptr);
                        rowsComponents[i].slider->setValue(tmp_int_t);
                    }

                    break;
                case row_uint8_t:
                    if (rows[i].type == row_edit && rows[i].ptr)
                    {
                        tmp_uint8_t = *((uint8_t *)rows[i].ptr);
                        rowsComponents[i].edit_data->setText(QString::number(tmp_uint8_t));
                    }
                    else if ((rows[i].type == row_combo && rows[i].ptr))
                    {
                        tmp_uint8_t = *((uint8_t *)rows[i].ptr);
                        for (auto const &x : rows[i].combo_data)
                        {
                            if (x.second.second == tmp_uint8_t)
                                rowsComponents[i].combo->setCurrentIndex(x.first);
                        }
                    }
                    else if ((rows[i].type == row_slider && rows[i].ptr))
                    {
                        tmp_uint8_t = *((uint8_t *)rows[i].ptr);
                        rowsComponents[i].slider->setValue(tmp_uint8_t);
                    }

                    break;
                case row_uint16_t:
                    if (rows[i].type == row_edit && rows[i].ptr)
                    {
                        tmp_uint16_t = *((uint16_t *)rows[i].ptr);
                        rowsComponents[i].edit_data->setText(QString::number(tmp_uint16_t));
                    }
                    else if ((rows[i].type == row_combo) && rows[i].ptr)
                    {
                        tmp_uint16_t = *((uint16_t *)rows[i].ptr);

                        for (auto const &x : rows[i].combo_data)
                        {
                            if (x.second.second == tmp_uint16_t)
                                rowsComponents[i].combo->setCurrentIndex(x.first);
                        }
                    }
                    else if ((rows[i].type == row_slider)&& rows[i].ptr)
                    {
                        tmp_uint16_t = *((uint16_t *)rows[i].ptr);
                        rowsComponents[i].slider->setValue(tmp_uint16_t);
                    }

                    break;
                case row_float:
                    if (rows[i].type == row_edit && rows[i].ptr)
                    {
                        tmp_float_t = *((float *)rows[i].ptr);
                        rowsComponents[i].edit_data->setText(QString::number(tmp_float_t));
                    }
                    else if ((rows[i].type == row_combo) && rows[i].ptr)
                    {
                        tmp_float_t = *((float *)rows[i].ptr);
                        for (auto const &x : rows[i].combo_data)
                        {
                            if (x.second.second == tmp_float_t)
                                rowsComponents[i].combo->setCurrentIndex(x.first);
                        }
                    }
                    else if ((rows[i].type == row_slider)&& rows[i].ptr)
                    {
                        tmp_float_t = *((float *)rows[i].ptr);
                        rowsComponents[i].slider->setValue(tmp_float_t);
                    }

                    break;

                case row_double:
                    if (rows[i].type == row_edit&& rows[i].ptr)
                    {
                        tmp_double_t = *((double *)rows[i].ptr);
                        rowsComponents[i].edit_data->setText(QString::number(tmp_double_t));
                    }
                    else if ((rows[i].type == row_combo)&& rows[i].ptr)
                    {
                        tmp_double_t = *((double *)rows[i].ptr);
                        for (auto const &x : rows[i].combo_data)
                        {
                            if (x.second.second == tmp_double_t)
                                rowsComponents[i].combo->setCurrentIndex(x.first);
                        }
                    }
                    else if ((rows[i].type == row_slider)&& rows[i].ptr)
                    {
                        tmp_double_t = *((float *)rows[i].ptr);
                        rowsComponents[i].slider->setValue(tmp_double_t);
                    }

                    break;

                default:
                    break;
                }
            }
        }
    }

    void Edit_struct_base::execute(Fu_callback fu)
    {

        /* QTabBar *m_tabbar = new QTabBar(this);

         m_tabbar->addTab("Hello");
         m_tabbar->addTab("World");
         m_tabbar->setShape(QTabBar::RoundedWest);
         m_tabbar->setGeometry(0,0,this->height(), 200); */

        init_rows();

        int counter = 0;
        int iterator = 0;
        std::vector<long unsigned int> row_by_index;
        std::vector<std::string> tab_name;

        if (rows[0].type != row_page)
        {
            rows.insert(rows.begin(), RowEdit{"General", row_page, row_undefined, nullptr, "", std::map<int, std::pair<std::string, int>>(), {0, 0}});
        }

        for (size_t i = 0; i <= rows.size(); ++i)
        {
            iterator++;
            if (rows[i].type == row_page)
            {
                counter++;
                iterator--;
                row_by_index.push_back(iterator);
                tab_name.push_back(rows[i].name);
            }

            if (i == rows.size())
            {
                counter++;
                iterator--;
                row_by_index.push_back(iterator);
            }
        }

        // printf("%d",counter);

        QVBoxLayout *verticalLayout = new QVBoxLayout(this);

        rowsComponents.resize(rows.size());

        QTabWidget *tabWidget;

        if (counter > 2)
        {
            tabWidget = new QTabWidget(this);
            tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
            verticalLayout->addWidget(tabWidget);
        }
        else
        {
            (void)verticalLayout;
        }

        for (int j = 0; j < counter - 1; j++)
        {

            fu_callback = fu;

            QScrollArea *scrollArea = new QScrollArea();
            scrollArea->setObjectName(QString::fromUtf8("tab"));
            QHBoxLayout *horizontalLayout = new QHBoxLayout(scrollArea);
            (void)horizontalLayout;
            scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
            scrollArea->setWidgetResizable(true);
            QWidget *scrollAreaWidgetContents = new QWidget();
            scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
            scrollArea->setWidget(scrollAreaWidgetContents);
            gridLayout = new QGridLayout(scrollAreaWidgetContents);
            gridLayout->setVerticalSpacing(0);

            if (counter > 2)
            {

                QString str = QString::fromStdString(tab_name.at(j));
                tabWidget->addTab(scrollArea, str);
            }
            else
            {
                verticalLayout->addWidget(scrollArea);
            }
            /* fu_callback = fu;


             QHBoxLayout *horizontalLayout = new QHBoxLayout(tabWidget);
             (void)horizontalLayout;


             QWidget *tab = new QWidget();
             tab->setObjectName(QString::fromUtf8("tab"));
             gridLayout = new QGridLayout(tab);

             QString str = QString::fromStdString(tab_name.at(j));
             tabWidget->addTab(tab,str); */

            QString s = "QWidget {font: 12px; }";
            QString t = "QWidget {font: bold 15px; }";

            // add components
            for (size_t i = row_by_index.at(j) + j + 1; i < (row_by_index.at(j + 1) + 1 + j); ++i)
            {

                //   [lbl_name]   [edit_data] [lbl_desc]
                rowsComponents[i].lbl_name = new QLabel(rows[i].name.c_str());

                if (rows[i].type != row_separator)
                {
                    rowsComponents[i].lbl_name->setStyleSheet(s);

                    if (rows[i].type == row_edit)
                    {
                        rowsComponents[i].edit_data = new QLineEdit();
                        rowsComponents[i].edit_data->setStyleSheet(s);
                    }
                    else if (rows[i].type == row_combo)
                    {
                        rowsComponents[i].combo = new QComboBox();
                        for (auto const &x : rows[i].combo_data)
                        {
                            rowsComponents[i].combo->addItem(QString::fromStdString(x.second.first) + ": " + QString::number(x.second.second));
                        }
                        rowsComponents[i].combo->setStyleSheet(s);
                    }
                    else if (rows[i].type == row_slider)
                    {
                        Qt::Orientation orientation = Qt::Horizontal;
                        rowsComponents[i].slider = new FancySlider(orientation);
                        rowsComponents[i].slider->setMinimum(rows[i].slider_range.first);
                        rowsComponents[i].slider->setMaximum(rows[i].slider_range.second);
                        rowsComponents[i].slider->setStyleSheet(s);
                    }

                    if (rows[i].desc.length() > 80)
                    {
                        std::string message = rows[i].desc.substr(0, 16) + "...";
                        rowsComponents[i].lbl_desc = new QLabel(message.c_str());
                        rowsComponents[i].lbl_desc->setToolTip(rows[i].desc.c_str());
                    }
                    else
                    {
                        rowsComponents[i].lbl_desc = new QLabel(rows[i].desc.c_str());
                    }

                    rowsComponents[i].lbl_desc->setStyleSheet(s);
                }
                else
                {
                    rowsComponents[i].lbl_name->setStyleSheet(t);
                }

                // add to grid
                gridLayout->addWidget(rowsComponents[i].lbl_name, i, 0);
                if (rowsComponents[i].edit_data)
                {
                    gridLayout->addWidget(rowsComponents[i].edit_data, i, 1);
                }
                else if (rowsComponents[i].combo)
                {
                    gridLayout->addWidget(rowsComponents[i].combo, i, 1);
                }
                else if (rowsComponents[i].slider)
                {
                    gridLayout->addWidget(rowsComponents[i].slider, i, 1);
                }

                if (rowsComponents[i].lbl_desc)
                    gridLayout->addWidget(rowsComponents[i].lbl_desc, i, 2);
            }

            // QPushButton *btnEditParams = new QPushButton();
            // btnEditParams->setText("Send");
            // btnEditParams->setMinimumSize(85,34);
            // gridLayout->addWidget(btnEditParams, rows.size()+0, 0);
            // connect(btnEditParams, &QPushButton::clicked, this, &Edit_struct_base::on_btnEditParamsClick);

            QSpacerItem *verticalSpacer;
            verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
            gridLayout->addItem(verticalSpacer, rows.size() + 1, 0, 1, 1);
        }

        update_data();

        QPushButton *btnEditParams = new QPushButton();
        btnEditParams->setText("Send");
        btnEditParams->setMinimumSize(85, 34);
        verticalLayout->addWidget(btnEditParams); ///, rows.size()+0, 0);
        connect(btnEditParams, &QPushButton::clicked, this, &Edit_struct_base::on_btnEditParamsClick);
    }

    Edit_struct_base::Edit_struct_base(QWidget *parent) : QWidget(parent) {}

    Edit_struct_base::~Edit_struct_base() {}

    void Edit_struct_base::on_btnEditParamsClick()
    {
        qDebug() << "buuu";

        for (size_t i = 0; i < rows.size(); ++i)
        {
            if (rows[i].type == row_separator)
            {
            }
            else
            {
                uint8_t tmp_uint8_t;
                uint16_t tmp_uint16_t;
                int tmp_int_t;
                float tmp_float_t;
                double tmp_double_t;
                switch (rows[i].row_data)
                {
                case row_int:
                    if (rows[i].type == row_edit && rows[i].ptr)
                    {
                        tmp_int_t = rowsComponents[i].edit_data->text().toInt();
                        *((int *)rows[i].ptr) = tmp_int_t;
                    }
                    else if ((rows[i].type == row_combo)&& rows[i].ptr)
                    {
                        int index = rowsComponents[i].combo->currentIndex();
                        tmp_int_t = rows[i].combo_data.at(index).second;
                        *((int *)rows[i].ptr) = tmp_int_t;
                    }
                    else if ((rows[i].type == row_slider)&& rows[i].ptr)
                    {
                        tmp_int_t = rowsComponents[i].slider->value();
                        *((int *)rows[i].ptr) = tmp_int_t;
                    }

                    break;
                case row_uint8_t:
                    if (rows[i].type == row_edit&& rows[i].ptr)
                    {
                        tmp_uint8_t = rowsComponents[i].edit_data->text().toInt();
                        *((uint8_t *)rows[i].ptr) = tmp_uint8_t;
                    }
                    else if ((rows[i].type == row_combo)&& rows[i].ptr)
                    {
                        int index = rowsComponents[i].combo->currentIndex();
                        tmp_uint8_t = rows[i].combo_data.at(index).second;
                        *((uint8_t *)rows[i].ptr) = tmp_uint8_t;
                    }
                    else if ((rows[i].type == row_slider)&& rows[i].ptr)
                    {
                        tmp_uint8_t = rowsComponents[i].slider->value();
                        *((uint8_t *)rows[i].ptr) = tmp_uint8_t;
                    }

                    break;
                case row_uint16_t:
                    if (rows[i].type == row_edit && rows[i].ptr)
                    {
                        tmp_uint16_t = rowsComponents[i].edit_data->text().toInt();
                        *((uint16_t *)rows[i].ptr) = tmp_uint16_t;
                    }
                    else if ((rows[i].type == row_combo)&& rows[i].ptr)
                    {
                        int index = rowsComponents[i].combo->currentIndex();
                        tmp_uint16_t = rows[i].combo_data.at(index).second;
                        *((uint16_t *)rows[i].ptr) = tmp_uint16_t;
                        qDebug() << tmp_uint16_t;
                    }
                    else if ((rows[i].type == row_slider)&& rows[i].ptr)
                    {
                        tmp_uint16_t = rowsComponents[i].slider->value();
                        *((uint16_t *)rows[i].ptr) = tmp_uint16_t;
                    }

                    break;

                case row_float:
                    if (rows[i].type == row_edit && rows[i].ptr)
                    {
                        tmp_float_t = rowsComponents[i].edit_data->text().toInt();
                        *((float *)rows[i].ptr) = tmp_float_t;
                    }
                    else if ((rows[i].type == row_combo)&& rows[i].ptr)
                    {
                        int index = rowsComponents[i].combo->currentIndex();
                        tmp_float_t = rows[i].combo_data.at(index).second;
                        *((float *)rows[i].ptr) = tmp_float_t;
                    }
                    else if ((rows[i].type == row_slider)&& rows[i].ptr)
                    {
                        tmp_float_t = rowsComponents[i].slider->value();
                        *((float *)rows[i].ptr) = tmp_float_t;
                    }

                    break;
                
                case row_double:
                    if (rows[i].type == row_edit && rows[i].ptr)
                    {
                        tmp_double_t = rowsComponents[i].edit_data->text().toInt();
                        *((double *)rows[i].ptr) = tmp_double_t;
                    }
                    else if ((rows[i].type == row_combo)&& rows[i].ptr)
                    {
                        int index = rowsComponents[i].combo->currentIndex();
                        tmp_double_t = rows[i].combo_data.at(index).second;
                        *((double *)rows[i].ptr) = tmp_double_t;
                    }
                    else if ((rows[i].type == row_slider)&& rows[i].ptr)
                    {
                        tmp_double_t = rowsComponents[i].slider->value();
                        *((double *)rows[i].ptr) = tmp_double_t;
                    }

                    break;

                default:
                    break;
                }
            }
        }

        // CALL CALLBACK
        if (fu_callback)
        {
            fu_callback();
        }

        update_data();
    }

}
// namespace