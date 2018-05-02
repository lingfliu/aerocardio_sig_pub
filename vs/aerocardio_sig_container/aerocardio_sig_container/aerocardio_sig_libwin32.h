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
	void(*onBytes2Device)(unsigned char* bytes, int byteLen); //�����豸���ֽ���
	void(*onERIRawReceived)(UTKMERI *eri); //ԭʼeri����
	void(*onEcgRawReceived)(UTKMEcg *ecg); //ԭʼecg����
	void(*onEcgFilteredReceived)(UTKMEcg *ecg); //�˲���ecg����
	void(*onImuFilteredReceived)(UTKMImu *imu); //�ɼ�����IMU����
	void(*onEcgMarkReceived)(UTKMEcgMark *mark); //���������ʣ�����

	UTKMDevice *device; //�豸��Ϣ���ͺţ������ʣ����ݰ���С
	int startWork();
	void stopWork();
	void reset();

	int setDeviceModel(int model);
	void putBytes(unsigned char* bytes, int byteLen);

	~UTKFeComm();
	UTKFeComm();

};