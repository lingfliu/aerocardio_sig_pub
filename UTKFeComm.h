#ifndef _UTK_FECOMM_
#define _UTK_FECOMM_

class UTKMEcg;
class UTKMEcgMark;
class UTKMImu;

class UTKFeComm {
    public:

    int getEcgSps(); //ecg的采样率
    int getEcgStreamLen(); //ecg的数据长度
    
    void (*onEcgRawReceived)(UTKMEcg*); 
    void (*onEcgFilteredReceived)(UTKMEcg*);
    void (*onEcgMarkOutput)(UTKMEcgMark*);

    int getImuSps(); //IMU的采样率
    int getImuStreamLen(); //IMU的数据长度
    void (*onImuRawReceived)(UTKMImu*);

    void reset(); //重置
    void startWork(); //启动
    void stopWork(); //停止（同时重置）

    void (*onBytesOut)(char* bytes, int byteLen);//这个回调的字节流交由蓝牙返回给设备用于底层字节流的交互
};

#endif