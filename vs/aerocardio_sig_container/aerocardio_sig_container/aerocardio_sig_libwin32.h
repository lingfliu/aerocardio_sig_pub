#pragma once

#define _DLL_ __declspec(dllexport) 
class _DLL_ UTKMImu {
public:
	static const int TYPE_IMU_3 = 1;

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
	static const int TYPE_ECG_3 = 3;
	static const int TYPE_ERI_4 = 4;
	unsigned char id[8];

	int* data;
	int dataLen;
	int type;
	__int64 startTime;
	__int64 stopTime;
	int sps;

	UTKMEcg();
	~UTKMEcg();
	float ** deplexData(int streamLen, int chnNum);
	int* multiplexData(float** datum, int streamLen, int chnNum);
};


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

	//for stream data
	int stamp;
	__int64 prevStartTime;
	bool isStreamInited;

	__int64 lastTimeFeMessage;
};

class _DLL_ UTKMERI {
public:
	static const int TYPE_ECG_3 = 3; //3 ecg 24 bit
	static const int TYPE_ERI_4 = 4; //3 ecg + 1 resp + 3 axis imu

	unsigned char id[8];

	int *data;
	int dataLen;
	int type;
	__int64 startTime;
	__int64 stopTime;

	UTKMEcg* extractEcg();
	UTKMImu* extractImu();
};


_DLL_ int initFeComm();
_DLL_ void regCbOnDeviceConnected(void(*onDeviceConnected)(UTKMDevice*));
_DLL_ void regCbOnDeviceDisconnected(void(*onDeviceDisonnected)(UTKMDevice*));
_DLL_ void regCbOnByte2Device(void(*onBytes2Device)(unsigned char*, int)); //发往设备的字节流
_DLL_ void regCbOnERIRawReceived(void(*onERIRawReceived)(UTKMERI *)); //原始eri数据
_DLL_ void regCbOnEcgRawReceived(void(*onEcgRawReceived)(UTKMEcg *)); //原始ecg数据
_DLL_ void regCbOnEcgFilteredReceived(void(*onEcgFilteredReceived)(UTKMEcg *)); //滤波后ecg数据
_DLL_ void regCbOnImuFilteredReceived(void(*onImuFilteredReceived)(UTKMImu *)); //采集到的IMU数据
_DLL_ void regCbOnEcgMarkReceived(void(*onEcgMarkReceived)(UTKMEcgMark *)); //呼吸，心率，电量

_DLL_ int setDeviceModel(int model);
_DLL_ int startWork();
_DLL_ void stopWork();
_DLL_ void reset();
_DLL_ void putBytes(unsigned char* bytes, int byteLen);
_DLL_ UTKMDevice* getdevice();