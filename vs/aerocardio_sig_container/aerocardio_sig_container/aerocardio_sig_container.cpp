// aerocardio_sig_container.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "aerocardio_sig_libwin32.h"
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include "UTKModel.h"
#include "UTKTestWorker.h"

using std::cout;
using std::endl;

unsigned int __stdcall TestThreadTask(LPVOID);

//fecomm callback declaration
void onDeviceConnected(UTKMDevice* device);
void onDeviceDisonnected(UTKMDevice* device);
void onBytes2Device(char* bytes, int byteLen);
void onERIRawReceived(UTKMERI *eri);
void onEcgFilteredReceived(UTKMEcg *ecg);
void onEcgMarkReceived(UTKMEcgMark *mark);

//instances
UTKFeComm *feComm;

//TODO: test model, remove later
UTKMModel *model;

int main()
{

	feComm = getFeComm();
	feComm->onDeviceConnected = onDeviceConnected;
	feComm->onDeviceDisonnected = onDeviceDisonnected;
	feComm->onERIRawReceived = onERIRawReceived;
	feComm->onEcgFilteredReceived = onEcgFilteredReceived;
	feComm->onEcgMarkReceived = onEcgMarkReceived;
	feComm->onBytes2Device = onBytes2Device;

	feComm->startWork();

	int byteLen = 100;
	unsigned char* bytes = (unsigned char*)malloc(sizeof(unsigned char)*byteLen);
	feComm->putBytes(bytes, byteLen);
	model = getUTKMModelTest()->getInstance();

	while (true);
    return 0;
}

/*callbacks from fecomm*/
void onDeviceConnected(UTKMDevice* device) {

}

void onDeviceDisonnected(UTKMDevice* device) {

}

//发往设备的字节流
void onBytes2Device(char* bytes, int byteLen) {
} 

void onERIRawReceived(UTKMERI *eri) {
}

void onEcgFilteredReceived(UTKMEcg *ecg) {
	cout << "received ecg filtered" << endl;
}

//经过卡尔曼滤波的加速度（暂不提供）
void onImuFilteredReceived(UTKMImu *imu) {
}

void onEcgMarkReceived(UTKMEcgMark *mark) {
	if (mark->typeGroup == 1) {
		//状态标记，暂不处理
	}
	else if (mark->typeGroup == 2) {
		switch (mark->type) {
		case 1:
			cout << "心率=" << mark->val<<endl;
			break;
		case 2:
			cout << "呼吸率=" << mark->val<<endl;
			break;
		}
	}
	delete mark;
}

unsigned int __stdcall TestThreadTask(LPVOID p) {
	Sleep(2000);
	return 0;
}

