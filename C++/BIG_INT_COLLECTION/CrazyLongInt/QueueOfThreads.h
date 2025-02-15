/*
Queue.h

This class implements the queue of threads. The constructor gets the number of cores from MyHardwareInfo and sets the
max number of threads to either that value or the default - whichever is higher.
A LongIntWrapper object can be added to the queue. If the number of running threads is less than the max permitted
it will start a thread that calls the 'startProcess' method of the LongIntWrapper object.
It also allows threads to signal that they are waiting, which will reduce the count of running threads and to then
signal that they have resumed waiting.
The 'iHaveFinished' method tells the queue the thread is about to finish and the counts are updated, along with the
specified thread being removed from the list of threads.
There are logging methods in place, both for logging with locks and without.

The class uses a condition_variable to allow threads to wait on a specific condition.
waitForThread method gives exactly this, waiting until another thread has finished before resuming.

ToDo:
Currently this class is tied to LongIntWrapper. Once all is working properly make it generic.
I tried to make this class generic from the start, but was getting errors and didn't know if it was the
generics or the threading, so I tied it to LongIntWrapper to remove that from the equation for now.
*/


#pragma once
#include <mutex>
#include <queue>
#include <vector>
#include <condition_variable>
#include "ReceiveUpdateClass.h"

#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


#include "MyHardwareInfo.h"
#ifndef _WIN32
#include <iostream>
#endif


using std::vector;
using std::mutex;
using std::unique_lock;
using std::condition_variable;


#define UINT unsigned int
template<class T>
class QueueOfThreads : ReceiveUpdateClass<T>
{
public:
	QueueOfThreads();
	~QueueOfThreads();

private:
	// Attributes
	UINT threadsRunning;
	UINT threadsWaiting;
	UINT maxThreads;
	UINT deviceCores;
	static const UINT minThreads = 4; // 4 seems as good a number as any.
	mutex myMutex;
	vector<T*> queueOfWaitingThreads;
	vector<int> queueOfRunningThreads;
	condition_variable myConditionVariable;
	UINT threadID;

public:
	// Methods
	void decreaseCount(UINT id);
	bool addToQueue(T*);
	void startAThread();

	UINT numOfThreads();
	void setNumThreads(UINT);
	UINT getDeviceCores();

	// Tell the queue that the current thread has finished
	void iHaveFinished(UINT id);

	// Tell the queue that the current thread is waiting and so remove it from the count of running threads
	void iAmWaiting();
	// Tell the queue that the current thread is ready to start running again
	void iHaveStoppedWaiting();

	// Wait for a thread to finish
	void waitForThread(T*);


	void logwithoutlock(std::string);
	void logwithlock(std::string);



};

// A workaround for the requirement that the declaration and definition of template methods must be in the same file
#include "QueueOfThreads.hpp"
