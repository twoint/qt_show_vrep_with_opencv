#pragma once

#include "ui_OpencvShow.h"
#include <QtWidgets/QMainWindow>
#include <opencv2\opencv.hpp>
#include <QTimer>



class OpencvShow : public QMainWindow
{
    Q_OBJECT

public:
    OpencvShow(QWidget *parent = Q_NULLPTR);

private:

    Ui::OpencvShowClass ui;
	QTimer *timer;




private slots:
	void on_btn_show();
	void on_btn_close();
	void importFrame();
};
