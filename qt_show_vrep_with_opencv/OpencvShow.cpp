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


OpencvShow::OpencvShow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.btn_show, SIGNAL(clicked()), this, SLOT(on_btn_show()));
}

void OpencvShow::on_btn_show()
{
	OutputDebugString(L"������Ϣ-----�������\n");

	int clientID = simxStart("127.0.0.1", 19997, true, true, 5000, 5);


	if (clientID != -1)
	{
		printf("success");
	}
	else
	{
		printf("error");
	}
	simxStartSimulation(clientID, simx_opmode_oneshot);
	simxInt camera;
	simxGetObjectHandle(clientID, "Vision_sensor", &camera, simx_opmode_blocking);
	simxInt resolution[2];
	simxUChar * image = 0;

	for (int time = 0; time < 10000; time++) {
		int retval = simxGetVisionSensorImage(clientID, camera, resolution, &image, 0, simx_opmode_oneshot);
		if (retval != simx_return_ok) {
			OutputDebugString(L"������Ϣ-----��ȡʧ��\n");

			continue;
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
		cv::waitKey(10);
		OutputDebugString(L"������Ϣ-----��ȡ�ɹ�%d\n");

	}
	simxStopSimulation(clientID, simx_opmode_oneshot);
	simxFinish(clientID);
}


