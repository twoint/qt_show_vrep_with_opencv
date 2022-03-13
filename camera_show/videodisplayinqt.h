#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_videodisplayinqt.h"
#include <opencv2\opencv.hpp>
#include <QTimer>

using namespace cv;

class videodisplayinqt : public QMainWindow
{
	Q_OBJECT

public:
	videodisplayinqt(QWidget *parent = Q_NULLPTR);

private:
	Ui::videodisplayinqtClass ui;
	VideoCapture capture;
	QTimer *timer;
	Mat frame;
	bool isCamera = 0;

private slots:
	void on_comboBox_currentIndexChanged();
	void importFrame();
	void on_displayButton_clicked();
	void on_stopButton_clicked();
};
