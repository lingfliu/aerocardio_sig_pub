// aerocardio_sig_container.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "aerocardio_sig_libwin32.h"
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include "UTKModel.h"
#include "UTKTestWorker.h"

using std::cout;
using std::endl;

unsigned int __stdcall TestThreadTask(LPVOID);
void callback(UTKModel*);

int main()
{
	HANDLE thrd;
	unsigned int thrdLd = 1;
	int *data = (int*) malloc(sizeof(int) * 200);
	for (int m = 0; m < 200; m++) {
		data[m] = m;
	}
	UTKModel *model = new UTKModel(data, 200);
	delete model;
	cout << "model is now = " << model << endl;
	UTKTestWorker *worker = new UTKTestWorker();
	worker->callback = callback;
	worker->startWork();

	thrd = (HANDLE)_beginthreadex(NULL, 0, TestThreadTask, (LPVOID*) worker, 0, &thrdLd);

	cout<<initFeComm()<<endl;
	WaitForSingleObject(thrd, INFINITE);
	
	while (true);
    return 0;
}

void callback(UTKModel* model) {
	cout << "callback model = " << model->getDataAt(10) << endl;
}
unsigned int __stdcall TestThreadTask(LPVOID p) {
	/*
	UTKModel *model = (UTKModel*)p;
	int cnt = 0;
	while (true)
	{
		Sleep(10000);
		cout <<"is running " << cnt++ << model->getDataAt(10) << endl;
	}
	*/
	Sleep(2000);
	UTKTestWorker *worker = (UTKTestWorker*)p;
	worker->stopWork();
	return 0;
}

