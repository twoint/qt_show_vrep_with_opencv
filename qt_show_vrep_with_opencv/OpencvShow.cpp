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

//���캯��
OpencvShow::OpencvShow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(importFrame()));//import frame when timeout
	connect(ui.btn_show, SIGNAL(clicked()), this, SLOT(on_btn_show()));
	connect(ui.btn_close, SIGNAL(clicked()), this, SLOT(on_btn_close()));
	OutputDebugString(L"������Ϣ-----���캯�����\n");


}


void OpencvShow::importFrame()
{
	int retval = simxGetVisionSensorImage(clientID, camera, resolution, &image, 0, simx_opmode_oneshot);
	if (retval != simx_return_ok) {
		OutputDebugString(L"������Ϣ-----��ȡʧ��\n");

		//continue;
	}

	cv::Mat channel(resolution[0], resolution[1], CV_8UC3, image);
	//��������ͼ�������Ǵ�ֱ��ת��,����Ӧ������cvMat �� v-rep ��ֱ������ķ����෴,flipһ�¾�������
	cv::flip(channel, channel, 0);
	//��������ͼ������ʱrgbͨ���ֲ��ģ���cvMat Ĭ��bgr
	cv::cvtColor(channel, channel, cv::COLOR_RGB2BGR);
	QImage Qtemp = QImage((const unsigned char*)(channel.data), channel.cols, channel.rows, channel.step, QImage::Format_RGB888);
	ui.label_pic->setPixmap(QPixmap::fromImage(Qtemp));
	ui.label_pic->resize(Qtemp.size());
	ui.label_pic->show();
	//cv::imshow("opencv test", channel);
	//cv::waitKey(10);
	OutputDebugString(L"������Ϣ-----��ȡ�ɹ�%d\n");
}


void OpencvShow::on_btn_show()
{
	OutputDebugString(L"������Ϣ-----on_btn_show()ִ�п�ʼ\n");

	clientID = simxStart("127.0.0.1", 19997, true, true, 5000, 5);
	simxStartSimulation(clientID, simx_opmode_oneshot);
	simxGetObjectHandle(clientID, "Vision_sensor", &camera, simx_opmode_blocking);
	timer->start(33);// Start timing, Signal out when timeout
	OutputDebugString(L"������Ϣ-----on_btn_show()ִ�����\n");

	//simxInt resolution[2];
	//simxUChar * image = 0;
}


void OpencvShow::on_btn_close()
{
	simxStopSimulation(clientID, simx_opmode_oneshot);
	simxFinish(clientID);
	timer->stop();

}
