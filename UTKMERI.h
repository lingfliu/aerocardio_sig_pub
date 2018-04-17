#ifndef _UTK_MERI_
#define _UTK_MERI_

class UTKMERI{
    public:
    long startTime;
    long stopTime;
    int* data;
    int dataLen;

    UTKMEcg* extractEcg(); //提取心电与呼吸复合信号
    UTKMImu* extractImu(); //提取IMU数据
}

#endif