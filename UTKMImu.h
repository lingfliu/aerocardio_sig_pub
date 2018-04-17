#ifndef _UTK_MIMU_
#define _UTK_MIMU_

const int UTK_IMU_TYPE_6 = 6; //6轴加速度计

class UTKMImu {
    /*data in
    ax1 ay1 az1 gx1 gy1 gz1    ax2 ay2 az2 gx2 gy2 gz2 ...
    */
    int* data; 
    
    int dateLen;
    long startTime;//起始时间,以毫秒计，基准为上位机的时钟
    long stopTime;//终止时间,以毫秒计，基准为上位机的时钟
    int sps;
    int type = UTK_IMU_TYPE_6;
}

#endif