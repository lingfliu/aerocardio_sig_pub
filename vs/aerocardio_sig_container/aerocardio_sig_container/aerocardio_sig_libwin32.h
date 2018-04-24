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
	int *data;
	int dataLen;
	int type;
	long startTime;
	long stopTime;
	UTKMImu();
	~UTKMImu();
	void setData(int *data, int dataLen);
}; 

class _DLL_ UTKMEcg {
public:
	int* data;
	int dataLen;
	int type;
	long startTime;
	long stopTime;
	int sps;

	~UTKMEcg();
	float ** deplexData();
	void multiplexData(float** datum, int dataLen, int ecgNum);
};

class _DLL_ UTKMERI{
public:
	int *data;
	int dataLen;
	int type;
	long startTime;
	long stopTime;

	UTKMEcg* extractEcg();
	UTKMImu* extractImu();
};

class _DLL_ UTKMEcgMark {
public:
	long startTime;
	long stopTime;
	int type;
	int typeGroup;
	int val;
};

class _DLL_ UTKMDevice {
public:
	int model;
	int sps;
	int streamLen;
	int state;
};

class _DLL_ UTKFeComm {
public:
	void(*onDeviceConnected)(UTKMDevice* device);
	void(*onDeviceDisonnected)(UTKMDevice* device);
	void(*onBytes2Device)(char* bytes, int byteLen); //发往设备的字节流
	void(*onERIRawReceived)(UTKMERI *eri);
	void(*onEcgFilteredReceived)(UTKMEcg *ecg);
	void(*onImuFilteredReceived)(UTKMImu *imu); //经过卡尔曼滤波的加速度（暂时不提供）
	void(*onEcgMarkReceived)(UTKMEcgMark *mark);

	UTKMDevice *device; //设备信息：型号，采样率，数据包大小
	void startWork();
	void stopWork();
	void reset();
	void putBytes(unsigned char* bytes, int byteLen);
};

_DLL_ UTKFeComm* getFeComm();

_DLL_ UTKMModel* getUTKMModelTest();