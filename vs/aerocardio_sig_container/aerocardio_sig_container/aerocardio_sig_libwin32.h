#pragma once

#pragma once

#define _DLL_ __declspec(dllexport) 

class _DLL_ UTKMModel {
public:
	int *data;
	int dataLen;
	UTKMModel();
	~UTKMModel();
	static UTKMModel* getInstance();
};

class _DLL_ UTKMImu {
public:
	unsigned char id[8];

	int *data;
	int dataLen;
	int type;
	__int64 startTime;
	__int64 stopTime;
	int sps;

	UTKMImu();
	~UTKMImu();
	void setData(int *data, int dataLen);
};

class _DLL_ UTKMEcg {
public:
	unsigned char id[8];

	int* data;
	int dataLen;
	int type;
	__int64 startTime;
	__int64 stopTime;

	int sps;

	UTKMEcg();
	~UTKMEcg();
};

class _DLL_ UTKMERI {
public:
	unsigned char id[8];

	int *data;
	int dataLen;
	int type;
	__int64 startTime;
	__int64 stopTime;

	UTKMEcg* extractEcg();
	UTKMImu* extractImu();
};

static int const ECGMARK_TYPE_GROUP_STATUS = 1;

static int const ECGMARK_STATUS_POWER = 1;

static int const ECGMARK_PHYSIO_HR = 1;
static int const ECGMARK_PHYSIO_BR = 2;
static int const ECGMARK_PHYSIO_NOISE = 3;

class _DLL_ UTKMEcgMark {
public:
	unsigned char id[8];

	__int64 startTime;
	__int64 stopTime;
	int type;
	int typeGroup;
	int val;
};


class _DLL_ UTKMDevice {
public:
	static int const STATE_DISCONNECTED = 1;
	static int const STATE_CONNECTED = 2;

	static const int MODEL_ECG3 = 3;//version 2.0, 3-chn, 24 bit resolution
	static const int MODEL_ERI4 = 5;//version 2.6, 3 chn ECG + 1 chn RESP (24bit) + 6-Axis IMU


	int model;

	unsigned char id[8];
	int spsEcg;
	int streamLenEcg;
	int resolutionEcg;
	int lenEcg;

	int spsImu;
	int streamLenImu;
	int resolutionImu;
	int lenImu;

	int state;
};

class _DLL_ UTKFeComm {
public:
	//callbacks
	void(*onDeviceConnected)(UTKMDevice* device);
	void(*onDeviceDisonnected)(UTKMDevice* device);
	void(*onBytes2Device)(unsigned char* bytes, int byteLen); //发往设备的字节流
	void(*onERIRawReceived)(UTKMERI *eri); //原始eri数据
	void(*onEcgRawReceived)(UTKMEcg *ecg); //原始ecg数据
	void(*onEcgFilteredReceived)(UTKMEcg *ecg); //滤波后ecg数据
	void(*onImuFilteredReceived)(UTKMImu *imu); //采集到的IMU数据
	void(*onEcgMarkReceived)(UTKMEcgMark *mark); //呼吸，心率，电量

	UTKMDevice *device; //设备信息：型号，采样率，数据包大小
	int startWork();
	void stopWork();
	void reset();

	int setDeviceModel(int model);
	void putBytes(unsigned char* bytes, int byteLen);

	~UTKFeComm();
	UTKFeComm();

};