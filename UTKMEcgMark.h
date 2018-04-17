#ifndef _UTK_MECGMARK_
#define _UTK_MECGMARK_

const int UTK_ECGMARK_GROUP_STATUS  = 1; //设备状态标记组，暂时用不上
const int UTK_ECGMARK_GROUP_PHYSIO = 2; //生理标记组

const int UTK_ECGMARK_PHYSIO_HR = 1; //心律
const int UTK_ECGMARK_PHYSIO_BR = 2; //呼吸率

class UTKMEcgMark {
    long startTime; //标记生成的时间点，以上位机时钟为基准
    long stopTime; //目前该值和startTime相等
    int type;
    int typeGroup;
    int val; //当typeGroup=2，type=1/2时，该值为心律／呼吸率
};

#endif