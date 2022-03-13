#include "videodisplayinqt.h"

videodisplayinqt::videodisplayinqt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(importFrame()));//import frame when timeout
	connect(ui.btn_open, SIGNAL(clicked()), this, SLOT(on_displayButton_clicked()));
	connect(ui.btn_close, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()));

}

void videodisplayinqt::on_comboBox_currentIndexChanged()//whether the camera import or not
{
	if (ui.comboBox->currentIndex())
		isCamera = 1;
	else
		isCamera = 0;
}

void videodisplayinqt::importFrame()
{
	capture >> frame;
	cvtColor(frame, frame, CV_BGR2RGB);//only RGB of Qt
	QImage srcQImage = QImage((uchar*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
	ui.label->setPixmap(QPixmap::fromImage(srcQImage));
	ui.label->resize(srcQImage.size());
	ui.label->show();
}

void videodisplayinqt::on_displayButton_clicked()
{
	if (isCamera)
	{
		capture.open(0);
	}
	else
	{
		capture.open("1.mp4");
	}
	timer->start(33);// Start timing, Signal out when timeout
}

void videodisplayinqt::on_stopButton_clicked()
{
	timer->stop();
	capture.release();
}
