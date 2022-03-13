#pragma once

#include "ui_OpencvShow.h"
#include <QtWidgets/QMainWindow>




class OpencvShow : public QMainWindow
{
    Q_OBJECT

public:
    OpencvShow(QWidget *parent = Q_NULLPTR);

private:

    Ui::OpencvShowClass ui;



private slots:
	void on_btn_show();
};
