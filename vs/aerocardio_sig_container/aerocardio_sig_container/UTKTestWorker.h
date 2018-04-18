#pragma once
#include "UTKModel.h"
#include <Windows.h>

class UTKTestWorker {
public:
	void startWork();
	void stopWork();
	void(*callback)(UTKModel*);

private:
	HANDLE workThrd;
	bool isRunning;
	static unsigned int __stdcall work(LPVOID); //输入参数为UTKTestWorker 这是一个静态的入口，不要包含状态
};