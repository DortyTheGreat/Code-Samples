// link "liburlmon.a"


//#include "stdafx.h"
#include <windows.h>
#include <urlmon.h>
#include <iostream>

#pragma lib "urlmon.lib"

using namespace std;

int main()
{
    string path = "http://dorty.gosunov.ru/HeDoG.txt";
    cout << "Path = " <<path;
    URLDownloadToFile(0, path.c_str(), "output.txt", 0, 0);
    return 0;
};
