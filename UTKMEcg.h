#ifndef _UTK_MECG_
#define _UTK_MECG_

const int UTK_ECG_TYPE_3 = 3; //3导500Hz心电
cosnt int UTK_ECG_TYPE_5 = 5;  //3导250Hz心电+1路呼吸

class UTKMEcg {
    public:
    int* data;
    int dataLen;
    long startTime; //起始时间,以毫秒计，基准为上位机的时钟
    long stopTime; //终止时间，以毫秒计，基准为上位机的时钟
}

#endif