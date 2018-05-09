// aerocardio_sig_container.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "aerocardio_sig_libwin32.h"
#include <Windows.h>
#include <process.h>
#include <sys\timeb.h>

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;

//fecomm callback declaration
void onDeviceConnected(UTKMDevice* device);
void onDeviceDisonnected(UTKMDevice* device);
void onBytes2Device(unsigned char* bytes, int byteLen);
void onERIRawReceived(UTKMERI *eri);
void onEcgFilteredReceived(UTKMEcg *ecg);
void onEcgRawReceived(UTKMEcg *ecg);
void onEcgMarkReceived(UTKMEcgMark *mark);

__int64 currentTimeInMilli();

static unsigned int __stdcall msg_mock(LPVOID p);
static unsigned int mockThrdId = 1001;
static unsigned int __stdcall stream_file_demo(LPVOID p);

int main()
{
	initFeComm();
	int res = setDeviceModel(5);
	startWork();
	regCbOnEcgRawReceived(onEcgRawReceived);
	regCbOnEcgFilteredReceived(onEcgFilteredReceived);
	regCbOnEcgMarkReceived(onEcgMarkReceived);
	regCbOnByte2Device(onBytes2Device);

	//HANDLE thrdMock = (HANDLE) _beginthreadex(NULL, 0, msg_mock, NULL, 0, &mockThrdId);
	HANDLE thrdMock = (HANDLE)_beginthreadex(NULL, 0, stream_file_demo, NULL, 0, &mockThrdId);


	while (true);
    return 0;
}

/*callbacks from fecomm*/
void onDeviceConnected(UTKMDevice* device) {

}

void onDeviceDisonnected(UTKMDevice* device) {

}

//发往设备的字节流
void onBytes2Device(unsigned char* bytes, int byteLen) {
	cout << "console: send bytes to device len = " << byteLen << endl;
} 

void onERIRawReceived(UTKMERI *eri) {
	//这里请直接删除eri
	delete eri;
}

void onEcgRawReceived(UTKMEcg *ecg) {
	//cout << "console: received raw ecg, time = " << ecg->startTime << endl;
	//这里暂时不要delete ecg，此处的引用会在内部被使用
}

void onEcgFilteredReceived(UTKMEcg *ecg) {
	//cout << "console: received ecg filtered time = " << ecg->startTime << endl;
	delete ecg;
}

//加速度原始数据
void onImuFilteredReceived(UTKMImu *imu) {
	//这里请直接删除imu
	delete imu;
}

void onEcgMarkReceived(UTKMEcgMark *mark) {
	if (mark->typeGroup == 1) {
		if (mark->type == 1) {
			//电压状态
			cout << "console: received power mark, value = " << mark->val << endl;
		}
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
	//这里请直接删除mark
	delete mark;
}


/*
 * 从test_torso.dat读取数据流，解析，滤波，并输出心率与呼吸率估测值
 */
unsigned int __stdcall stream_file_demo(LPVOID p) {
	ifstream fid("test_torso.dat", ios::binary);
	if (!fid) {
		cout << "failed to read file." << endl;
		return 0;
	}
	char buff[139];
	int len = 139;
	while (true) {
		Sleep(20);
		fid.read(buff, len);
		if (fid) {
			len = 139;
			putBytes((unsigned char*)buff, len);
		}
		else {
			len = fid.gcount();
			if (len > 0) {
				putBytes((unsigned char*)buff, len);
			}
			break;
		}
	}
	cout << "finished reading file" << endl;

	fid.close();

	return 0;
}

unsigned int __stdcall msg_mock(LPVOID p) {

	unsigned char bytes[512];
	bytes[0] = 0x00;
	bytes[1] = 0xAA;
	bytes[2] = 0x00;
	bytes[3] = 0xcc;
	bytes[4] = 0x11;
	bytes[5] = 0x11;

	unsigned int stamp = 0;
	int byteLen = 0;
	unsigned char type_pulse = 231;
	unsigned char type_eri4 = 5;
	unsigned char type_ecg3 = 1;
	unsigned char type_status = 100;

	__int64 timerPulse = currentTimeInMilli();
	__int64 timerERI = timerPulse;
	__int64 timerECG = timerPulse;
	__int64 timerStatus = timerPulse;

	unsigned long long cnt = 0;
	while (true) {
		Sleep(40);

		//模拟采样数据
		byteLen = 9 + 120 + 4 + 6; //250 sps eri
		bytes[129] = 0x55;
		bytes[130] = 0xaa;
		bytes[131] = 0xaa;
		bytes[132] = 0x55;

		bytes[6] = type_eri4;

		bytes[8] = (stamp & 0xff);
		bytes[9] = (stamp >> 8) & 0xff;
		putBytes(bytes, byteLen);

		//模拟心跳包
		__int64 now = currentTimeInMilli();
		if (now - timerPulse > 800) {
			byteLen = 10;
			bytes[6] = type_pulse;
			putBytes(bytes, byteLen);
			timerPulse = now;
		}
		//模拟电量数据
		if (now - timerStatus > 5000) {
			byteLen = 7 + 2 + 4;
			bytes[6] = type_status;
			bytes[7] = 0x01;
			bytes[8] = 0x00;
			putBytes(bytes, byteLen);
			timerStatus = now;
		}
	}
}
__int64 currentTimeInMilli() {
	timeb t;
	ftime(&t);
	return t.time * 1000 + t.millitm;
}