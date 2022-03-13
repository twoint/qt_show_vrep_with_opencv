#include "OpencvShow.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>  
#include <process.h>
#include <Windows.h>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

extern "C" {
#include "extApi.h"
}

int clientID;
simxInt camera;
simxInt resolution[2];
simxUChar * image;

//构造函数
OpencvShow::OpencvShow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(importFrame()));//import frame when timeout
	connect(ui.btn_show, SIGNAL(clicked()), this, SLOT(on_btn_show()));
	connect(ui.btn_close, SIGNAL(clicked()), this, SLOT(on_btn_close()));
	OutputDebugString(L"调试信息-----构造函数完成\n");


}


void OpencvShow::importFrame()
{
	int retval = simxGetVisionSensorImage(clientID, camera, resolution, &image, 0, simx_opmode_oneshot);
	if (retval != simx_return_ok) {
		OutputDebugString(L"调试信息-----读取失败\n");

		//continue;
	}

	cv::Mat channel(resolution[0], resolution[1], CV_8UC3, image);
	//读回来的图像数据是垂直翻转的,问题应该是在cvMat 和 v-rep 垂直坐标轴的方向相反,flip一下就正常了
	cv::flip(channel, channel, 0);
	//读回来的图像数据时rgb通道分布的，而cvMat 默认bgr
	cv::cvtColor(channel, channel, cv::COLOR_RGB2BGR);
	QImage Qtemp = QImage((const unsigned char*)(channel.data), channel.cols, channel.rows, channel.step, QImage::Format_RGB888);
	ui.label_pic->setPixmap(QPixmap::fromImage(Qtemp));
	ui.label_pic->resize(Qtemp.size());
	ui.label_pic->show();
	//cv::imshow("opencv test", channel);
	//cv::waitKey(10);
	OutputDebugString(L"调试信息-----读取成功%d\n");
}


void OpencvShow::on_btn_show()
{
	OutputDebugString(L"调试信息-----on_btn_show()执行开始\n");

	clientID = simxStart("127.0.0.1", 19997, true, true, 5000, 5);
	simxStartSimulation(clientID, simx_opmode_oneshot);
	simxGetObjectHandle(clientID, "Vision_sensor", &camera, simx_opmode_blocking);
	timer->start(33);// Start timing, Signal out when timeout
	OutputDebugString(L"调试信息-----on_btn_show()执行完成\n");

	//simxInt resolution[2];
	//simxUChar * image = 0;
}


void OpencvShow::on_btn_close()
{
	simxStopSimulation(clientID, simx_opmode_oneshot);
	simxFinish(clientID);
	timer->stop();

}
