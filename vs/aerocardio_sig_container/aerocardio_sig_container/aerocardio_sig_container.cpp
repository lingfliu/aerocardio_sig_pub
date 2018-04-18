// aerocardio_sig_container.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "aerocardio_sig_libwin32.h"
using std::cout;
using std::endl;
int main()
{
	cout<<initFeComm()<<endl;
    return 0;
}

