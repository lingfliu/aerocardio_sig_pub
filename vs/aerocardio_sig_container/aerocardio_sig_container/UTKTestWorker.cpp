#include "stdafx.h"
#include "UTKTestWorker.h"
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

void UTKTestWorker::startWork() {
	isRunning = true;
	unsigned int thrdLd = 1;
	workThrd = (HANDLE)_beginthreadex(NULL, 0, work, (LPVOID*)this, 0, &thrdLd);
}

void UTKTestWorker::stopWork() {
	isRunning = false;
	workThrd = NULL;
}

unsigned int __stdcall UTKTestWorker::work(LPVOID p) {
	UTKTestWorker *worker = (UTKTestWorker*) p;

	int *data = (int*)malloc(sizeof(int) * 200);
	for (int m = 0; m < 200; m++) {
		data[m] = m;
	}
	UTKModel *model = new UTKModel(data, 200);

	while (true){
		if (!worker->isRunning) {
			break;
		}
		Sleep(1);
		int *data = (int*)malloc(sizeof(int) * 200);
		for (int m = 0; m < 200; m++) {
			data[m] = m;
		}
		UTKModel *model = new UTKModel(data, 200);

		if (worker->callback != NULL) {
			worker->callback(model);
		}
		delete model;
	}
	cout << "work stopped" << endl;

	delete model;
	
	return 0;
}