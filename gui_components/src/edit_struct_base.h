#ifndef EDIT_STRUCT_BASE_H
#define EDIT_STRUCT_BASE_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QtWidgets/QComboBox>
#include "fancySlider_h.h"


//#include <TGC.h> // ?????????????????????????  COS NIE TAK !!!!!!!!!!!!!!!!


namespace Edit_struct
{



class Edit_struct_base : public QWidget
{
    Q_OBJECT

public:
    typedef std::function<void()> Fu_callback;

    enum RowEditType {row_separator,  row_page, row_edit,  row_combo, row_slider, row_none};
    
    enum RowDataType {row_int , row_uint16_t, row_uint8_t,row_float, row_double, row_undefined};

    //std::map <int,std::string> combo_choice{{1, "aaaa"}, {3, "bbb"}, {5, "cccc"}};


    struct RowEdit
    {
        std::string name{""};
        RowEditType type{row_none};
        RowDataType row_data{row_undefined};
        void * ptr{nullptr};
        std::string desc{""};
        std::map <int,std::pair<std::string,int>> combo_data{{0,{"",0}}};
        std::pair<int, int> slider_range{0,0};
    };

    struct RowEditGui
    {
        QLabel * lbl_name;
        QLineEdit * edit_data;
        QLabel * lbl_desc;
        QComboBox * combo;
        FancySlider * slider;
    };


public:
    Edit_struct_base(QWidget *parent = nullptr);
    ~Edit_struct_base();

    void execute(Fu_callback fu);
    virtual void init_rows()=0;   
private:
    std::vector<RowEdit> rows;
    QGridLayout *gridLayout;

    Fu_callback fu_callback{nullptr};
    std::vector<RowEditGui> rowsComponents;

    void on_btnEditParamsClick();
    void update_data();
//protected:
public:

RowEdit add_page(std::string text)
{
    return rows.emplace_back(RowEdit{text,row_page,row_undefined});
}

RowEdit add_separator(std::string text)
{
    return rows.emplace_back(RowEdit{text,row_separator,row_undefined});
}

RowEdit add_edit(std::string text, RowDataType data, void *ptr, std::string desc)
{
    return rows.emplace_back(RowEdit{text,row_edit,data,ptr, desc});
}

RowEdit add_combo(std::string text, RowDataType data, void *ptr, std::string desc, std::map <std::string, int> combo_data)
{
    std::map <int,std::pair<std::string,int>> tmp;
    int i =0;
    for(auto const& x : combo_data)
    {
     tmp.insert({i++,{x.first,x.second}});

    }

    return rows.emplace_back(RowEdit{text,row_combo,data,ptr, desc, tmp});  
}

RowEdit add_slider(std::string text, RowDataType data, void *ptr, std::string desc, std::pair<int,int> range)
{
    return rows.emplace_back(RowEdit{text,row_slider,data,ptr, desc,std::map <int,std::pair<std::string,int>>(),range});
}

};

} // namespace 

#endif // EDIT_DTGC_SETTINGS_H
