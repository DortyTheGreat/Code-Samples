#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

string StartLoggingText = "DortyLogs Has started working, logs made at   ";



void StartLogging(string FileName){
    ofstream fout(FileName.c_str());


    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);




    fout << StartLoggingText << std::ctime(&start_time);



}

void LogString(string FileName, string Data){
    ofstream fout(FileName.c_str(),std::ofstream::app);
    fout << Data << endl;
}

