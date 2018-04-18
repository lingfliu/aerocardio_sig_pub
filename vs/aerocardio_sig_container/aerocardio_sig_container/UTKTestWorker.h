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
	static unsigned int __stdcall work(LPVOID); //�������ΪUTKTestWorker ����һ����̬����ڣ���Ҫ����״̬
};