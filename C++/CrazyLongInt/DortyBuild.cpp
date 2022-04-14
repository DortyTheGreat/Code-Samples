/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: �����#9030 
---Original---Code---



#include <cstdlib>
#include <iostream>
#include "MyHardwareInfo.h"
#include "LongInteger.h"

#include "LongInteger.cpp"
#include "../DortyLibs/DortyBuild.h"


 using namespace std;

int main(int argc, char** argv) {


    AppBuild();
    string a;
    ifstream fin("input.txt");
	ofstream fout("output.txt");



    fin >> a;
    LongInteger value1(a);

    for(int i = 0;i<10;i++){
        LongInteger::sqrt(value1);
    }

    fout << LongInteger::sqrt(value1).toDecimal() << endl;
    return 0;

    LongInteger value2(10);
    LongInteger value3("10");
    LongInteger value4(value3);
    value1 = value2 * value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 / value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 + value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 - value3;
    cout << value1.toDecimal() << endl;
    value1 = value2;
    value1.powerCalc(value3);
    cout << value1.toDecimal() << endl;

    value1 = 100000;
    cout << value1.toDecimal() << endl;
    string value = "100000000000000000000";
    value2 = value;
    cout << value2.toDecimal() << endl;
    value3 = value2 * value2;
    value3 *= value2;
    value3 *= value2;
    value3 *= value2;
    cout << value3.toDecimal() << endl;
    cout << value3.getSize() << endl;

    LongInteger::KARATSUBACUTOFF = 20;
    LongInteger::KARATSUBATHREADING = 50;
    for( int i = 0; i < 14; i++) {
        value3 *= value3;
//        cout << value3.toDecimal() << endl;
        cout << value3.getSize() << endl;
    }
    return 0;
}

*/


#include <cstdlib>
#include <iostream>
/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

/*
* LongInteger.h
*
* Header for LongInteger class. Can handle positive integers up to 4 billion digits in length.
* It holds the number as a byte array and indexes it using an uint (hence the size limit)
* Addition, subtraction, multiplication and division and powers are handled.
* Standard operators - +,-,*,/,+=,-=,/=,*=,<,>,<=,>=,!=,== are handled
* The = operator is overriden to provide copy by value instead of the default copy by reference
* It is also overloaded, so that strings and ints can be assigned to a LongInteger
*
* The karatsuba algorithm is used to multiply large numbers. It is more complex than long multiplication,
* but the number of steps needed doesn't increase as rapidly as the number length increases.
* The karatsuba algorithm is only accessed via the multiplyNumber method
*
* ToomCook3 algorithm has been added for multiplying even larger numbers. The implementation looks rather complex, so
* there may well be inefficiencies. Performance is odd, which convinces me all is not correct
*
* Burnikel-Ziegler algorithm for division has been implemented. It ended up with much more code than expected
* and also handles scenarios that aren't mentioned at all in Burnikel and Ziegler's paper, so that isn't a good sign.
* It works and divides numbers faster than the division algorithm I implemented for large numbers, where the divisor
* is at least half the size of the value being divided.
*
*
* The compiler needs to support C++14 to get this code to work.
* Visual Studio 2015 Community Edition supports this without any amendments needed.
*
* I got NetBeans to compile this code by going into
* Project Properties - C++ Compiler - Additional options - and added '-std=c++14 -pthread'. The -pthread is to
* add multithreading support otherwise NetBeans gets very confused.
*
* Managed to get Eclipse to compile the code as well, although I cannot get the IDE to recognise C++14 code
* It insists there are errors, but hit compile and it builds fine. It will also debug and step through the code
* without issues, but still with warnings about unrecognised code all over the place.
*
* Unique Pointers are used because the memory management was getting out of hand and was becoming a real mess.
* Where it is manageable I've kept using simple points to reduce overheads.
*
*/

#pragma once

#ifndef _LONGINTEGER_H
#define _LONGINTEGER_H

#include <vector>
#include <memory>
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
#pragma once

// Interface class to define common messages the subclasses can receive

template<class T>
class ReceiveUpdateClass
{
public:
	// If I make the constructor virtual Visual Studio refuses to compile. Dunno why. GCC has no issues.
	ReceiveUpdateClass();
	// Virtual destructor needed so I can assign a subclass to a ReceiveUpdateClass pointer and not get memory leaks
	// if delete is called on that pointer
	virtual ~ReceiveUpdateClass();

	virtual void iHaveFinished(unsigned int) = 0;
	virtual void iAmWaiting() = 0;
	virtual void iHaveStoppedWaiting() = 0;
	
};

template <class T>
ReceiveUpdateClass<T>::ReceiveUpdateClass()
{
}

template <class T>
ReceiveUpdateClass<T>::~ReceiveUpdateClass()
{
}


#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

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
/*
Implementation of the QueueOfThreads template
Managed to work out how to move it into a separate file
The .h file includes this file at the end. All seems to work just fine.
*/

#include <thread>
#include <fstream>

template <class T>
QueueOfThreads<T>::QueueOfThreads() {
	threadsRunning = 0;
	threadsWaiting = 0;
	threadID = 0;
	//	deviceCores = std::thread::hardware_concurrency();

	deviceCores = 4;
	if (deviceCores < minThreads) {
		maxThreads = minThreads; // Default value
	}
	else {
		maxThreads = deviceCores;
	}

}

template <class T>
QueueOfThreads<T>::~QueueOfThreads() {
	// Can't exit whilst threads are running.
	// Set the shutting down flag (all should have a reference to that - use an interface)
	// and wait for them to finish

}

template <class T>
void QueueOfThreads<T>::decreaseCount(UINT id) {
	try {
		unique_lock<mutex> lock(myMutex);
		// Find out which thread has finished and remove it from the list
		UINT index = 0;
		bool bFound = false;

		while (!bFound && index < queueOfRunningThreads.size()) {
			if (queueOfRunningThreads[index] == id) {
				bFound = true;
			}
			else {
				index++;
			}
		}

		if (!bFound) {
			abort();
		}

		queueOfRunningThreads.erase(queueOfRunningThreads.begin() + index);

		threadsRunning--;
		lock.unlock();
		myConditionVariable.notify_all();

	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}

}

template <class T>
bool QueueOfThreads<T>::addToQueue(T* newLongInt) {
	try {

		unique_lock<mutex> lock(myMutex);

		newLongInt->setID(threadID);
		queueOfWaitingThreads.push_back(newLongInt);

		threadID++;
		threadsWaiting++;
		newLongInt->setCallback(this);

		// I was using a lambda and it was working fine, but this format of thread starting
		// matches up to the other one.
		// Starting a thread to start a thread may seem weird, but this functionality is just a placeholder
		std::thread t1(&QueueOfThreads<T>::startAThread, this);

		t1.detach();
		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}
	return true;
}

template <class T>
void QueueOfThreads<T>::startAThread() {
	if (threadsWaiting == 0) {
		return;
	}
	try {
		unique_lock<std::mutex> lock(myMutex);
		// The wait will unlock and then try to reacquire the lock when it wakes up
		myConditionVariable.wait(lock, [this]() {
			return threadsRunning < maxThreads; });


		// Insert code to start a thread
		if (queueOfWaitingThreads.size() == 0) {
			abort();
		}


		T* tempLIW = queueOfWaitingThreads[0];
		queueOfWaitingThreads.erase(queueOfWaitingThreads.begin());
		queueOfRunningThreads.push_back(tempLIW->getID());
		threadsRunning++;
		threadsWaiting--;


		//	CString strOutput;
		//	strOutput.Format(L"Thread ID %d - Starting \n", tempLIW->getID());
		//	logwithoutlock(strOutput);


		// This format of call seems to have fixed the issues with access violation. Let's hope it
		// keeps on working.
		std::thread t1(&T::startProcess, tempLIW);

		t1.detach();

		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
}

template <class T>
UINT QueueOfThreads<T>::numOfThreads() {
	// For testing
	unique_lock<mutex> lock(myMutex);
	return threadsRunning + threadsWaiting;
	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::iHaveFinished(UINT id) {
	decreaseCount(id);
#ifdef __linux__
	// Linux test code
	std::cout << "Thread " << id << " finished. Threads waiting&running " << threadsWaiting << "," << threadsRunning << std::endl;
#endif
}

template <class T>
void QueueOfThreads<T>::iAmWaiting() {
	if (threadsRunning == 0) abort(); // Test code

									  // The current thread is waiting on something, so let the queue know that other threads can be started
	unique_lock<mutex> lock(myMutex);

	threadsRunning--;
	threadsWaiting++;

	// Although the lock will release when it goes out of scope, I need to unlock it before calling notify
	lock.unlock();
	myConditionVariable.notify_all();

}

template <class T>
void QueueOfThreads<T>::iHaveStoppedWaiting() {
	if (threadsWaiting == 0) abort(); // Test code

	unique_lock<mutex> lock(myMutex);
	myConditionVariable.wait(lock, [this]() {
		return threadsRunning < maxThreads; });

	threadsRunning++;
	threadsWaiting--;

	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::waitForThread(T* pLIW) {
	unique_lock<mutex> lock(myMutex);

	myConditionVariable.wait(lock, [pLIW]() {
		return pLIW->bFinished; });

	lock.unlock();
	myConditionVariable.notify_all();

}


template <class T>
void QueueOfThreads<T>::logwithoutlock(std::string logString) {
	// Called if a lock has already been established

	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
}



template <class T>
void QueueOfThreads<T>::logwithlock(std::string logString) {
	unique_lock<mutex> lock(myMutex);
	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
	lock.unlock();
	myConditionVariable.notify_all();
}



template <class T>
void QueueOfThreads<T>::setNumThreads(UINT numThreads) {
	maxThreads = numThreads;
}

template <class T>
UINT QueueOfThreads<T>::getDeviceCores() {
	return deviceCores;
}


/*
GeneralIntWrapper.h

This class is a wrapper to LongInteger although it can also wrap other items. It allows LongIntegers to be sent
to QueueOfThreads and then collects the results of processing to be picked up by the caller.
It has been created to separate LongInteger and QueueOfThreads

At the moment it just calls the karatsuba algorithm. Will need to be amended to allow for calling any mr.
*/

#pragma once

#ifndef _WIN32
typedef unsigned int UINT;
#endif

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
#pragma once

// Interface class to define common messages the subclasses can receive

template<class T>
class ReceiveUpdateClass
{
public:
	// If I make the constructor virtual Visual Studio refuses to compile. Dunno why. GCC has no issues.
	ReceiveUpdateClass();
	// Virtual destructor needed so I can assign a subclass to a ReceiveUpdateClass pointer and not get memory leaks
	// if delete is called on that pointer
	virtual ~ReceiveUpdateClass();

	virtual void iHaveFinished(unsigned int) = 0;
	virtual void iAmWaiting() = 0;
	virtual void iHaveStoppedWaiting() = 0;
	
};

template <class T>
ReceiveUpdateClass<T>::ReceiveUpdateClass()
{
}

template <class T>
ReceiveUpdateClass<T>::~ReceiveUpdateClass()
{
}


#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

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
/*
Implementation of the QueueOfThreads template
Managed to work out how to move it into a separate file
The .h file includes this file at the end. All seems to work just fine.
*/

#include <thread>
#include <fstream>

template <class T>
QueueOfThreads<T>::QueueOfThreads() {
	threadsRunning = 0;
	threadsWaiting = 0;
	threadID = 0;
	//	deviceCores = std::thread::hardware_concurrency();

	deviceCores = 4;
	if (deviceCores < minThreads) {
		maxThreads = minThreads; // Default value
	}
	else {
		maxThreads = deviceCores;
	}

}

template <class T>
QueueOfThreads<T>::~QueueOfThreads() {
	// Can't exit whilst threads are running.
	// Set the shutting down flag (all should have a reference to that - use an interface)
	// and wait for them to finish

}

template <class T>
void QueueOfThreads<T>::decreaseCount(UINT id) {
	try {
		unique_lock<mutex> lock(myMutex);
		// Find out which thread has finished and remove it from the list
		UINT index = 0;
		bool bFound = false;

		while (!bFound && index < queueOfRunningThreads.size()) {
			if (queueOfRunningThreads[index] == id) {
				bFound = true;
			}
			else {
				index++;
			}
		}

		if (!bFound) {
			abort();
		}

		queueOfRunningThreads.erase(queueOfRunningThreads.begin() + index);

		threadsRunning--;
		lock.unlock();
		myConditionVariable.notify_all();

	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}

}

template <class T>
bool QueueOfThreads<T>::addToQueue(T* newLongInt) {
	try {

		unique_lock<mutex> lock(myMutex);

		newLongInt->setID(threadID);
		queueOfWaitingThreads.push_back(newLongInt);

		threadID++;
		threadsWaiting++;
		newLongInt->setCallback(this);

		// I was using a lambda and it was working fine, but this format of thread starting
		// matches up to the other one.
		// Starting a thread to start a thread may seem weird, but this functionality is just a placeholder
		std::thread t1(&QueueOfThreads<T>::startAThread, this);

		t1.detach();
		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}
	return true;
}

template <class T>
void QueueOfThreads<T>::startAThread() {
	if (threadsWaiting == 0) {
		return;
	}
	try {
		unique_lock<std::mutex> lock(myMutex);
		// The wait will unlock and then try to reacquire the lock when it wakes up
		myConditionVariable.wait(lock, [this]() {
			return threadsRunning < maxThreads; });


		// Insert code to start a thread
		if (queueOfWaitingThreads.size() == 0) {
			abort();
		}


		T* tempLIW = queueOfWaitingThreads[0];
		queueOfWaitingThreads.erase(queueOfWaitingThreads.begin());
		queueOfRunningThreads.push_back(tempLIW->getID());
		threadsRunning++;
		threadsWaiting--;


		//	CString strOutput;
		//	strOutput.Format(L"Thread ID %d - Starting \n", tempLIW->getID());
		//	logwithoutlock(strOutput);


		// This format of call seems to have fixed the issues with access violation. Let's hope it
		// keeps on working.
		std::thread t1(&T::startProcess, tempLIW);

		t1.detach();

		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
}

template <class T>
UINT QueueOfThreads<T>::numOfThreads() {
	// For testing
	unique_lock<mutex> lock(myMutex);
	return threadsRunning + threadsWaiting;
	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::iHaveFinished(UINT id) {
	decreaseCount(id);
#ifdef __linux__
	// Linux test code
	std::cout << "Thread " << id << " finished. Threads waiting&running " << threadsWaiting << "," << threadsRunning << std::endl;
#endif
}

template <class T>
void QueueOfThreads<T>::iAmWaiting() {
	if (threadsRunning == 0) abort(); // Test code

									  // The current thread is waiting on something, so let the queue know that other threads can be started
	unique_lock<mutex> lock(myMutex);

	threadsRunning--;
	threadsWaiting++;

	// Although the lock will release when it goes out of scope, I need to unlock it before calling notify
	lock.unlock();
	myConditionVariable.notify_all();

}

template <class T>
void QueueOfThreads<T>::iHaveStoppedWaiting() {
	if (threadsWaiting == 0) abort(); // Test code

	unique_lock<mutex> lock(myMutex);
	myConditionVariable.wait(lock, [this]() {
		return threadsRunning < maxThreads; });

	threadsRunning++;
	threadsWaiting--;

	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::waitForThread(T* pLIW) {
	unique_lock<mutex> lock(myMutex);

	myConditionVariable.wait(lock, [pLIW]() {
		return pLIW->bFinished; });

	lock.unlock();
	myConditionVariable.notify_all();

}


template <class T>
void QueueOfThreads<T>::logwithoutlock(std::string logString) {
	// Called if a lock has already been established

	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
}



template <class T>
void QueueOfThreads<T>::logwithlock(std::string logString) {
	unique_lock<mutex> lock(myMutex);
	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
	lock.unlock();
	myConditionVariable.notify_all();
}



template <class T>
void QueueOfThreads<T>::setNumThreads(UINT numThreads) {
	maxThreads = numThreads;
}

template <class T>
UINT QueueOfThreads<T>::getDeviceCores() {
	return deviceCores;
}





template<class T> class GeneralIntWrapper
{
public:
	GeneralIntWrapper();
	~GeneralIntWrapper();

	typedef T* (*Tfunction)(const T&, const T&, bool);

private:
	UINT id;
	T* param1;
	T* param2;
	T* pResult;
	ReceiveUpdateClass<GeneralIntWrapper<T>> *callbackObject;
	Tfunction startMethod;
	static QueueOfThreads<GeneralIntWrapper<T>> qot;

public:
	bool bRunning;
	bool bFinished;
	int startProcess();
	void setCallback(ReceiveUpdateClass<GeneralIntWrapper<T>>*);
	void setStartMethod(Tfunction newMethod);
	void setID(UINT);
	UINT getID();
	static QueueOfThreads<GeneralIntWrapper<T>>* getQOT();

	T* getResult();
	void setParams(const T& rParam1, const T& rParam2);
};


template <class T>
GeneralIntWrapper<T>::GeneralIntWrapper()
{
	param1 = nullptr;
	param2 = nullptr;
	pResult = nullptr;
	bRunning = false;
	bFinished = false;
}

template <class T>
GeneralIntWrapper<T>::~GeneralIntWrapper()
{
	delete param1;
	delete param2;
}

template <class T>
QueueOfThreads<GeneralIntWrapper<T>> GeneralIntWrapper<T>::qot;

template <class T>
QueueOfThreads<GeneralIntWrapper<T>>* GeneralIntWrapper<T>::getQOT()
{
	return &qot;
}

template <class T>
int GeneralIntWrapper<T>::startProcess()
{
	bRunning = true;

	// This will call any method that takes 2 parameters of type T and a 3rd parameter of bool
	pResult = startMethod(*(param1), *(param2), true);

	bRunning = false;
	// Need a way this can inform QueueOfThreads that it has finished.
	bFinished = true;
	callbackObject->iHaveFinished(id);
	return 0;
}

template <class T>
void GeneralIntWrapper<T>::setCallback(ReceiveUpdateClass<GeneralIntWrapper<T>>* newcallbackObject)
{
	callbackObject = newcallbackObject;
}

template <class T>
void GeneralIntWrapper<T>::setStartMethod(Tfunction newMethod)
{
	startMethod = newMethod;
}

template <class T>
void GeneralIntWrapper<T>::setID(UINT newID)
{
	id = newID;
}

template <class T>
UINT GeneralIntWrapper<T>::getID()
{
	return id;
}

template <class T>
T* GeneralIntWrapper<T>::getResult()
{
	return pResult;
}

template <class T>
void GeneralIntWrapper<T>::setParams(const T& rParam1, const T& rParam2)
{
	// Copy the parameters. This requires that the assignment operator is overloaded to be a deep copy (should be)
	param1 = new T;
	param2 = new T;

	*param1 = rParam1;
	*param2 = rParam2;
}


#ifndef _WIN32
/* Linux includes. Should cover all non-Windows platforms (and Windows, but Windows code was built using Microsoft-specific
   classes, such as CString), but only tested on Ubuntu 16 so far.
   For my reference - the preprocessor definitions for different platforms
   __linux__       Defined on Linux
   __sun           Defined on Solaris
   __FreeBSD__     Defined on FreeBSD
   __NetBSD__      Defined on NetBSD
   __OpenBSD__     Defined on OpenBSD
   __APPLE__       Defined on Mac OS X
   __hpux          Defined on HP-UX
   __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
   __sgi           Defined on Irix
   _AIX            Defined on AIX
   _WIN32          Defined on Windows

   I believe that __linux and linux work on the Linux platform as well.
*/
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <algorithm>
///typedef unsigned char byte; // Didn't realise byte and UINT were Microsoft specific definitions. Added them here for Linux
///typedef unsigned int UINT;
///typedef unsigned long ULONG;
///typedef unsigned long long ULONGLONG;



using std::stringstream;
using std::string;
using std::ifstream;
using std::ios;
#endif

// This definition is to add compatibility with C++11. The code is intended for C++14, but it turns out
// the template below is all that is needed to run under the C++11 standard
#if __cplusplus == 201103L
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&& ... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif

using std::vector;
using std::unique_ptr;
#if __cplusplus != 201103L
using std::make_unique;
#endif
using std::move;

// The class is named below with no implementation so as to avoid a Catch-22 situation with the typedefs
// The typedefs need to be defined using class LongInteger, but class LongInteger needs the typedefs
// So this definition says "I'm going to use a class called LongInteger and I'll fill in the details later on"
class LongInteger;
typedef GeneralIntWrapper<LongInteger> LongIntWrapper; // A shorthand to make it easier to type
typedef unique_ptr<LongInteger> LongIntegerUP; // Ditto
// This for passing a pointer to a function that takes 2 const LongInteger parameters and a bool and returns a pointer to a LongInteger
// The function pointer is referred to as 'Lifunction' in the code
typedef LongInteger* (*LIfunction)(const LongInteger&, const LongInteger&, bool);

// Forward declaration. For some reason I only need to forward declare this one and everything works
bool operator<(int lhs, const LongInteger& rhs);
bool operator<(UINT lhs, const LongInteger& rhs);


#define byte unsigned char
#define ULONG unsigned long
#define ULONGLONG unsigned long long
class LongInteger {
public:
	// Have these listed here (public and at the top of the class) whilst still working on them

	// Still in testing. Performance is weird in release build (improves dramatically at multiples of 350 and then drops
	// rapidly until the next multiple is hit), but works as expected in debug build. Haven't worked out why.
	static LongInteger* ToomCook3(const LongInteger&, const LongInteger&, bool bBackgroundThread = false);

	// This is under development. The code is rather messy as I'm struggling to follow the paper due to the heavy usage of maths
	// terminology I'm unfamiliar with.
	// So far it shows that it is a lot quicker than long division if the divisor is at least half the size (number of digits)
	// of the value. Otherwise it is a lot slower. So working on a framework to adjust the size of the divisor and then
	// adjust the results. Despite being a lot more work it is still quicker. Needs quite a bit of testing
	// to work out the optimal values.
	static void BurnikelZiegler(const LongInteger&, const LongInteger&, LongIntegerUP&, LongIntegerUP&);
	// This is the framework that does the adjustments prior to calling the BurnikelZiegler method
	static bool DivAndMod(const LongInteger&, const LongInteger&, LongIntegerUP&, LongIntegerUP&);
	static bool DivAndMod(const LongInteger&, const LongInteger&, LongInteger&, LongInteger&);


	static LongInteger sqrt(const LongInteger&);
	static LongInteger sqr(const LongInteger&);
	static LongInteger pow(const LongInteger&, const LongInteger&);
	static LongInteger factorial(const LongInteger&);
	static LongInteger log(const LongInteger&);
	static LongInteger log(const LongInteger&, const LongInteger&);
	static LongInteger ln(const LongInteger&);

private:
	// This is the front end to the Karatsuba algorithm which also tidies up any memory allocated
	static LongInteger multiplyChooser(const LongInteger&, const LongInteger&);
	// Restoring division seems to work fine. Some more testing needed to see what the performance is
	static void RestoringDivision(LongInteger&, LongInteger&, LongInteger*, LongInteger*);

	static bool TriedToReadE;

	static LongInteger ReadEFromFile(std::string path);


public: // Make this public during development
		// This is the recursive part of the karatsuba algorithm
	static LongInteger* karatsuba(const LongInteger&, const LongInteger&, bool bBackgroundThread = false);

	// Constants
public:
	static const UINT BASEVAL = 256; // The effective base of the numbers (each digit is 1 byte)
	static const UINT BASEVALBITS = 8; // Size of each digit in bits
	static const UINT BASEVALBITSSHIFT = 3; // If dividing/multiplying by basevalbits, using shifts
	static const byte BASEMAX = 255; // Highest value that can be stored in each digit
	static const UINT ABSMAXSIZE = 4294967295; // Largest number of values that can be stored (index is by uint, so 2^32-1)

	static const UINT MINSIZE = 50;
	static const UINT TINYSIZESTEP = 50;
	static const UINT SMALLSIZESTEP = 1000;
	static const UINT SIZESTEP = 10000; // Internal byte array is increased or decreased in block of this size
										//	static const UINT KARATSUBACUTOFF = 50; // Karatsuba cutoff size. Numbers below this size will use long multiplication
										//	static const UINT TOOMCOOK3CUTOFF = 150; // Testing shows this is the optimal value. Update - 150 is the best in debug builds. In release builds it is not. In release it is all over the place.
										//	static const UINT BURKINELZIEGLERCUTOFF = 50; // 50 seems to work well for the recursion point

										// Making these non-const so I can test different values
	static UINT KARATSUBACUTOFF;
	static UINT TOOMCOOK3CUTOFF;
	static UINT BURKINELZIEGLERCUTOFF;
	// Threading values are now calculated dynamically (after accidentally triggering 20,000 threads) and so are non-const
	static UINT KARATSUBATHREADING;
	static UINT TOOMCOOK3THREADING;

	static LongInteger E; // These aren't const as there will be an attempt to read in a value from file, else use the default.
	static UINT SIZEOFE; // Number of bytes that e has been shifted left by for the value above.

public:
	// For testing only
	void assignByteArray(byte*, UINT);

	// Constructors
	LongInteger();
	LongInteger(const int);
	LongInteger(const UINT);
	LongInteger(const ULONG);
	LongInteger(const ULONGLONG);
	LongInteger(const LongInteger&);
	LongInteger(const double);
	LongInteger(const long double);
	LongInteger(LongInteger*);

	// Add in wstring option as well once this is compiling
	LongInteger(const std::string&);

	~LongInteger();

	// Useful functions
	const UINT getSize() const;

	bool assignNumber(int);
	bool assignNumber(UINT);
	bool assignNumber(ULONG);
	bool assignNumber(ULONGLONG);
	bool assignNumber(double);
	bool assignNumber(long double);

	bool assignNumber(const std::string&);


	byte getDigit(UINT) const;
	bool setDigit(UINT, byte);
	// Split the current LongInt. Send in 2 LongInts to hold the result. Returns false if it fails
	bool split(LongInteger*, LongInteger*, UINT) const;
	// Split 'this' into 3 parts of UINT size and return as an array of LongIntegers
	UINT toomsplit(LongInteger**, UINT) const;



	std::string toDecimal();
	std::string toDecimal() const;
	std::string toHexString() const; // Useful for testing
	std::string toArrayNumbers(); // Also useful for testing

	explicit operator int() const; // Convert to int. Make it explicit to avoid auto casting which will cause confusion
	explicit operator UINT() const;

	// Arithmetic functions
	bool addNumber(int);
	bool addNumber(const LongInteger&);
	bool subtractNumber(int);
	bool subtractNumber(const LongInteger&);
	bool multiplyNumber(int);
	bool multiplyNumber(const LongInteger&);
	bool divideNumber(int);
	bool divideNumber(const LongInteger&);
	bool powerCalc(LongInteger&, const LongInteger&);
	bool powerCalc(const LongInteger&);
	bool powerCalc(int);

	bool arrowCalc(UINT, int);
	bool modulus(const LongInteger&);
	bool factorial();

	// Arithmetic operators
	LongInteger operator+(const LongInteger&) const; // Addition
	LongInteger operator+() const; // Unary plus
	LongInteger operator-(const LongInteger&) const;
	LongInteger operator-() const; // Unary negate
	LongInteger operator*(const LongInteger&) const;
	LongInteger operator/(const LongInteger&) const;
	LongInteger operator%(const LongInteger&) const;

	LongInteger operator+(int) const; // Addition
	LongInteger operator-(int) const;
	LongInteger operator*(int) const;
	LongInteger operator/(int) const;
	LongInteger operator%(int) const;

	LongInteger& operator=(const LongInteger&);
	LongInteger& operator++(); // Prefix increment
	LongInteger operator++(int); // Postfix increment (the int is unused - a placeholder in the syntax)
	LongInteger& operator+=(const LongInteger&); // Adding a LongInteger
	LongInteger& operator+=(int); // Adding an int
	LongInteger& operator--(); // Prefix decrement
	LongInteger operator--(int); // Postfix decrement
	LongInteger& operator-=(const LongInteger&);
	LongInteger& operator-=(int);
	LongInteger& operator*=(const LongInteger&);
	LongInteger& operator*=(int);
	LongInteger& operator/=(const LongInteger&);
	LongInteger& operator/=(int);
	LongInteger& operator%=(const LongInteger&);
	LongInteger& operator%=(int);

	// Bitwise operators
	bool bitwiseand(const LongInteger&);
	LongInteger operator&(const LongInteger&);
	LongInteger operator&(int);
	LongInteger& operator&=(const LongInteger&);
	LongInteger& operator&=(int);

	bool bitwiseor(const LongInteger&);
	LongInteger operator|(const LongInteger&);
	LongInteger operator|(int);
	LongInteger& operator|=(const LongInteger&);
	LongInteger& operator|=(int);

	bool bitwisenot();
	LongInteger operator~() const;

	bool bitwisexor(const LongInteger&);
	LongInteger operator^(const LongInteger&);
	LongInteger operator^(int);
	LongInteger& operator^=(const LongInteger&);
	LongInteger& operator^=(int);

	bool bitshiftright(const LongInteger&);
	bool bitshiftleft(const LongInteger&);
	bool bitshiftright(UINT);
	bool bitshiftleft(UINT);
	LongInteger operator >> (const LongInteger&);
	LongInteger operator >> (UINT);
	LongInteger& operator>>=(const LongInteger&);
	LongInteger& operator>>=(UINT);
	LongInteger operator<<(const LongInteger&);
	LongInteger operator<<(UINT);
	LongInteger& operator<<=(const LongInteger&);
	LongInteger& operator<<=(UINT);

	static LongInteger abs(const LongInteger&);

	bool equalsZero() const;
	bool isProcessing();
	// Commenting these 2 calls out as I need a better way of waiting on completion
	// This was a hack to get the program working properly in Windows
	void setProcessing(bool);
	//    void setProcessing(bool, CWinThread* = nullptr);
	//    HANDLE getProcessingHandle();
	bool isShuttingDown();
	void setShuttingDown(bool);

	inline bool overflow() const {
		return bOverflow;
	}

	bool writeToFile(std::string&);
	bool readFromFile(std::string&);


private:
	byte* digits = nullptr;
	bool bPositive = true;
	UINT maxSize = 0;
	UINT size = 0;
	bool bOverflow = false;
	bool static bShuttingDown;
	bool bProcessing;
	// Commented out at the moment. Not just because it is Windows specific, but
	// because I need a more secure way of waiting on completion
	//    CWinThread *thrProcessingRef = nullptr;

	void init();
	void reset(); // Reset the internal array
	void copy(const LongInteger&);
	void addInternal(byte*, UINT, UINT, UINT);
	void checkSize();
	void recalcMaxSize();
	void recalcMaxSizeAndClear();
	bool increaseSize();
	bool decreaseSize();
	bool increment(); // Helper function for ++
	bool decrement(); // Helper function for --

					  // Helper methods
	bool arrowCalc(const LongInteger&, UINT, LongInteger&);
	bool powerCalcHelper(const LongInteger&, LongInteger&);
	bool divHelper(int);
	bool divByByte(byte);
	bool multHelper(int);
	bool multHelper2(UINT);
	UINT UINTpower(UINT, UINT) const;

	// Helper methods for Burnikel-Ziegler division
	static LongIntegerUP merge(vector<LongIntegerUP>& vList, UINT uNumParts, UINT uSizeParts);
	static vector<LongIntegerUP> DivThreeHalvesByTwo(LongIntegerUP& a1, LongIntegerUP& a2, LongIntegerUP& a3, LongIntegerUP& b1, LongIntegerUP& b2, UINT uNumDigits);
	static vector<LongIntegerUP> DivTwoDigitsByOne(LongIntegerUP& AHigh, LongIntegerUP& ALow, LongIntegerUP& B, UINT uNumDigits);
	// A generic splitting function. Split the input LongInteger into UINT parts of UINT length and return as an array of LongIntegers
	static vector<LongIntegerUP> split(LongIntegerUP&, UINT, UINT);

	LongInteger* pSharedLongInt;

public:
	bool multiplyInternal(const LongInteger&);

	// comparison operators
public:
	inline bool isPositive() const { return bPositive; }

	inline bool operator<(const LongInteger& rhs) const {
		if (bOverflow || rhs.bOverflow) {
			return false;
		}

		if (bPositive != rhs.bPositive) {
			// If this is + and rhs is -, then return -, else return +. So return opposite of bPositive flag
			return !bPositive;
		}

		if (size < rhs.size) {
			return true;
		}
		if (size > rhs.size) {
			return false;
		}

		bool bLessThan = false;
		bool bLoop = true;
		bool bEquals = false;
		// Some amendments as the index is now a UINT and thus we can't go negative
		if (size > 0) {
			UINT index = size - 1;
			while (index > 0 && bLoop) {
				if (digits[index] < rhs.digits[index]) {
					bLessThan = true;
					bLoop = false;
				}
				else if (digits[index] > rhs.digits[index]) {
					bLoop = false;
				}
				--index;
			}
		}
		// Scenario for index = 0 and we haven't finished checking
		if (bLoop) {
			if (digits[0] < rhs.digits[0]) {
				bLessThan = true;
			}
			else if (digits[0] == rhs.digits[0])
			{
				// Added extra test as this was going wrong comparing negative numbers that were equal and returning true
				bEquals = true;
			}
		}

		if (bEquals) {
			return false;
		}
		else {
			return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
		}
	}

	inline bool operator>(const LongInteger& rhs) const {
		return rhs < (*this);
	}

	inline bool operator<=(const LongInteger& rhs) const {
		return !((*this) > rhs);
	}

	inline bool operator<=(int rhs) const {
		return !((*this) > rhs);
	}

	inline bool operator>=(const LongInteger& rhs) const {
		return !((*this) < rhs);
	}

	inline bool operator>=(int rhs) const {
		return !((*this) < rhs);
	}

	inline bool operator==(const LongInteger& rhs) const {
		if (bOverflow || rhs.bOverflow) {
			return false;
		}
		if (size != rhs.size) {
			return false;
		}
		if (bPositive != rhs.bPositive) {
			return false;
		}
		bool bEqual = true;
		// Amendments for using UINT as index instead of int. Can no longer check for less than zero
		// so we have to do this in 2 bits
		if (size > 0) {
			UINT iLoop = size - 1;
			while (iLoop > 0 && bEqual) {
				if (digits[iLoop] != rhs.digits[iLoop])
					bEqual = false;
				--iLoop;
			}
		}
		// Extra bit for the zeroth digit
		if (bEqual) {
			if (digits[0] != rhs.digits[0])
				bEqual = false;
		}
		return bEqual;
	}

	inline bool operator==(int rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1 && bPositive);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(int)) {
			return false;
		}

		bool bEquals = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt += (digits[i] << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == std::abs(rhs))
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator==(UINT rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(UINT)) {
			return false;
		}

		bool bEquals = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt += (digits[i] << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == rhs)
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator==(ULONGLONG rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(ULONGLONG)) {
			return false;
		}

		bool bEquals = false;
		ULONGLONG thisAsInt = digits[0];
		ULONGLONG temp;

		for (UINT i = 1; i < size; i++)
		{
			temp = digits[i];
			thisAsInt += (temp << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == rhs)
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator!=(const LongInteger& rhs) {
		return !((*this) == rhs);
	}

	inline bool operator!=(int rhs) {
		return !((*this) == rhs);
	}

	inline bool operator!=(UINT rhs) {
		return !((*this) == rhs);
	}

	// Add int versions of the comparison operators to avoid the overhead of converting ints to LongIntegers for comparisons.
	inline bool operator<(int rhs) const {
		if (bOverflow) {
			return false;
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			// If this is + and rhs is -, then return -, else return +. So return opposite of bPositive flag
			return !bPositive;
		}
		// Comparison with zero. If both are zero
		if (rhs == 0) {
			if (equalsZero()) {
				return false;
			}
			else {
				return !bPositive;
			}
		}
		else {
			if (equalsZero()) {
				return (rhs > 0);
			}
		}

		if (size > sizeof(int)) {
			return false ^ !bPositive;
		}

		bool bLessThan = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt *= digits[i];
		}

		if (thisAsInt < (UINT)std::abs(rhs))
		{
			bLessThan = true;
		}
		else if (thisAsInt == (UINT)std::abs(rhs))
		{
			return false; // The return value for equal negative numbers was going wrong
		}
		return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
	}

	inline bool operator<(UINT rhs) const {
		if (bOverflow) {
			return false;
		}

		if (!bPositive) {
			// UINTs can only be positive, so if this is negative it is definately less than the UINT
			return true;
		}
		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(int)) {
			return false ^ !bPositive;
		}

		bool bLessThan = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt *= digits[i];
		}

		if (thisAsInt < rhs)
		{
			bLessThan = true;
		}
		return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
	}

	inline bool operator>(int rhs) const
	{
		return rhs < (*this);
	}

	inline bool operator>(UINT rhs) const
	{
		return rhs < (*this);
	}
};


inline bool operator==(int lhs, const LongInteger& rhs) {
	return rhs == lhs;
}

inline bool operator==(UINT lhs, const LongInteger& rhs) {
	return rhs == lhs;
}

inline bool operator!=(int lhs, const LongInteger& rhs) {
	return !(rhs == lhs);
}

inline bool operator!=(UINT lhs, const LongInteger& rhs) {
	return !(rhs == lhs);
}

inline bool operator<(UINT lhs, const LongInteger& rhs) {
	if (rhs.overflow()) {
		return false;
	}

	bool bPositive = rhs.isPositive();

	if (!bPositive) {
		// If rhs is negative it is definately less than lhs as UINTs can't be negative
		return false;
	}
	if (rhs.equalsZero()) {
		if (lhs == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (lhs == 0) {
			return false;
		}
	}

	if (rhs.getSize() > sizeof(int)) {
		return true ^ !bPositive;
	}

	bool bLessThan = false;
	UINT thisAsInt = rhs.getDigit(rhs.getSize() - 1);

	if (rhs.getSize() > 1)
	{
		for (UINT i = rhs.getSize() - 1; i > 0; i--)
		{
			thisAsInt *= LongInteger::BASEVAL;
			thisAsInt += (rhs.getDigit(i - 1));
		}
	}

	if (lhs < thisAsInt)
	{
		bLessThan = true;
	}
	return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
}

inline bool operator<(int lhs, const LongInteger& rhs) {
	if (rhs.overflow()) {
		return false;
	}

	bool bPositive = rhs.isPositive();

	if ((bPositive && lhs < 0) || (!bPositive && lhs >= 0)) {
		// If this is + and rhs is -, then return -, else return +. So return bPositive flag
		return bPositive;
	}
	if (rhs.equalsZero()) {
		if (lhs == 0) {
			return false;
		}
		else {
			return (lhs < 0);
		}
	}
	else {
		if (lhs == 0) {
			return bPositive;
		}
	}

	if (rhs.getSize() > sizeof(int)) {
		return true ^ !bPositive;
	}

	bool bLessThan = false;
	UINT thisAsInt = rhs.getDigit(rhs.getSize() - 1);

	if (rhs.getSize() > 1)
	{
		for (UINT i = rhs.getSize() - 1; i > 0; i--)
		{
			thisAsInt *= LongInteger::BASEVAL;
			thisAsInt += (rhs.getDigit(i - 1));
		}
	}

	if ((UINT)std::abs(lhs) < thisAsInt)
	{
		bLessThan = true;
	}
	else if ((UINT)std::abs(lhs) == thisAsInt)
	{
		return false;
	}
	return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
}


inline bool operator>(int lhs, const LongInteger& rhs) {
	return rhs < lhs;
}

inline bool operator>(UINT lhs, const LongInteger& rhs) {
	return rhs < lhs;
}

inline bool operator>=(int lhs, const LongInteger& rhs) {
	return !(lhs < rhs);
}

inline bool operator>=(UINT lhs, const LongInteger& rhs) {
	return !(lhs < rhs);
}

inline bool operator<=(int lhs, const LongInteger& rhs) {
	return !(lhs > rhs);
}

inline bool operator<=(UINT lhs, const LongInteger& rhs) {
	return !(lhs > rhs);
}

inline LongInteger operator+(int lhs, const LongInteger& rhs) {
	return rhs + lhs;
}

inline LongInteger operator+(UINT lhs, const LongInteger& rhs) {
	return rhs + lhs;
}

inline LongInteger operator-(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value - rhs;
}

inline LongInteger operator-(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value - rhs;
}

inline LongInteger operator*(int lhs, const LongInteger& rhs) {
	return rhs * lhs;
}

inline LongInteger operator*(UINT lhs, const LongInteger& rhs) {
	return rhs * lhs;
}

inline LongInteger operator/(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value / rhs;
}

inline LongInteger operator/(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value / rhs;
}

inline LongInteger operator&(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value & rhs;
}

inline LongInteger operator&(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value & rhs;
}

inline LongInteger operator|(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value | rhs;
}

inline LongInteger operator|(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value | rhs;
}

inline LongInteger operator^(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value ^ rhs;
}

inline LongInteger operator^(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value ^ rhs;
}

inline LongInteger operator >> (int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value >> rhs;
}

inline LongInteger operator >> (UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value >> rhs;
}

#endif


﻿#ifdef _WIN32

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

///#include <afxwin.h>         // MFC core and standard components
///#include <afxext.h>         // MFC extensions


///#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
///#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
///#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

///#include <afxcontrolbars.h>     // MFC support for ribbons and control bars









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



#endif
/*
* LongInteger.h
*
* Header for LongInteger class. Can handle positive integers up to 4 billion digits in length.
* It holds the number as a byte array and indexes it using an uint (hence the size limit)
* Addition, subtraction, multiplication and division and powers are handled.
* Standard operators - +,-,*,/,+=,-=,/=,*=,<,>,<=,>=,!=,== are handled
* The = operator is overriden to provide copy by value instead of the default copy by reference
* It is also overloaded, so that strings and ints can be assigned to a LongInteger
*
* The karatsuba algorithm is used to multiply large numbers. It is more complex than long multiplication,
* but the number of steps needed doesn't increase as rapidly as the number length increases.
* The karatsuba algorithm is only accessed via the multiplyNumber method
*
* ToomCook3 algorithm has been added for multiplying even larger numbers. The implementation looks rather complex, so
* there may well be inefficiencies. Performance is odd, which convinces me all is not correct
*
* Burnikel-Ziegler algorithm for division has been implemented. It ended up with much more code than expected
* and also handles scenarios that aren't mentioned at all in Burnikel and Ziegler's paper, so that isn't a good sign.
* It works and divides numbers faster than the division algorithm I implemented for large numbers, where the divisor
* is at least half the size of the value being divided.
*
*
* The compiler needs to support C++14 to get this code to work.
* Visual Studio 2015 Community Edition supports this without any amendments needed.
*
* I got NetBeans to compile this code by going into
* Project Properties - C++ Compiler - Additional options - and added '-std=c++14 -pthread'. The -pthread is to
* add multithreading support otherwise NetBeans gets very confused.
*
* Managed to get Eclipse to compile the code as well, although I cannot get the IDE to recognise C++14 code
* It insists there are errors, but hit compile and it builds fine. It will also debug and step through the code
* without issues, but still with warnings about unrecognised code all over the place.
*
* Unique Pointers are used because the memory management was getting out of hand and was becoming a real mess.
* Where it is manageable I've kept using simple points to reduce overheads.
*
*/

#pragma once

#ifndef _LONGINTEGER_H
#define _LONGINTEGER_H

#include <vector>
#include <memory>
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
#pragma once

// Interface class to define common messages the subclasses can receive

template<class T>
class ReceiveUpdateClass
{
public:
	// If I make the constructor virtual Visual Studio refuses to compile. Dunno why. GCC has no issues.
	ReceiveUpdateClass();
	// Virtual destructor needed so I can assign a subclass to a ReceiveUpdateClass pointer and not get memory leaks
	// if delete is called on that pointer
	virtual ~ReceiveUpdateClass();

	virtual void iHaveFinished(unsigned int) = 0;
	virtual void iAmWaiting() = 0;
	virtual void iHaveStoppedWaiting() = 0;
	
};

template <class T>
ReceiveUpdateClass<T>::ReceiveUpdateClass()
{
}

template <class T>
ReceiveUpdateClass<T>::~ReceiveUpdateClass()
{
}


#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

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
/*
Implementation of the QueueOfThreads template
Managed to work out how to move it into a separate file
The .h file includes this file at the end. All seems to work just fine.
*/

#include <thread>
#include <fstream>

template <class T>
QueueOfThreads<T>::QueueOfThreads() {
	threadsRunning = 0;
	threadsWaiting = 0;
	threadID = 0;
	//	deviceCores = std::thread::hardware_concurrency();

	deviceCores = 4;
	if (deviceCores < minThreads) {
		maxThreads = minThreads; // Default value
	}
	else {
		maxThreads = deviceCores;
	}

}

template <class T>
QueueOfThreads<T>::~QueueOfThreads() {
	// Can't exit whilst threads are running.
	// Set the shutting down flag (all should have a reference to that - use an interface)
	// and wait for them to finish

}

template <class T>
void QueueOfThreads<T>::decreaseCount(UINT id) {
	try {
		unique_lock<mutex> lock(myMutex);
		// Find out which thread has finished and remove it from the list
		UINT index = 0;
		bool bFound = false;

		while (!bFound && index < queueOfRunningThreads.size()) {
			if (queueOfRunningThreads[index] == id) {
				bFound = true;
			}
			else {
				index++;
			}
		}

		if (!bFound) {
			abort();
		}

		queueOfRunningThreads.erase(queueOfRunningThreads.begin() + index);

		threadsRunning--;
		lock.unlock();
		myConditionVariable.notify_all();

	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}

}

template <class T>
bool QueueOfThreads<T>::addToQueue(T* newLongInt) {
	try {

		unique_lock<mutex> lock(myMutex);

		newLongInt->setID(threadID);
		queueOfWaitingThreads.push_back(newLongInt);

		threadID++;
		threadsWaiting++;
		newLongInt->setCallback(this);

		// I was using a lambda and it was working fine, but this format of thread starting
		// matches up to the other one.
		// Starting a thread to start a thread may seem weird, but this functionality is just a placeholder
		std::thread t1(&QueueOfThreads<T>::startAThread, this);

		t1.detach();
		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}
	return true;
}

template <class T>
void QueueOfThreads<T>::startAThread() {
	if (threadsWaiting == 0) {
		return;
	}
	try {
		unique_lock<std::mutex> lock(myMutex);
		// The wait will unlock and then try to reacquire the lock when it wakes up
		myConditionVariable.wait(lock, [this]() {
			return threadsRunning < maxThreads; });


		// Insert code to start a thread
		if (queueOfWaitingThreads.size() == 0) {
			abort();
		}


		T* tempLIW = queueOfWaitingThreads[0];
		queueOfWaitingThreads.erase(queueOfWaitingThreads.begin());
		queueOfRunningThreads.push_back(tempLIW->getID());
		threadsRunning++;
		threadsWaiting--;


		//	CString strOutput;
		//	strOutput.Format(L"Thread ID %d - Starting \n", tempLIW->getID());
		//	logwithoutlock(strOutput);


		// This format of call seems to have fixed the issues with access violation. Let's hope it
		// keeps on working.
		std::thread t1(&T::startProcess, tempLIW);

		t1.detach();

		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
}

template <class T>
UINT QueueOfThreads<T>::numOfThreads() {
	// For testing
	unique_lock<mutex> lock(myMutex);
	return threadsRunning + threadsWaiting;
	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::iHaveFinished(UINT id) {
	decreaseCount(id);
#ifdef __linux__
	// Linux test code
	std::cout << "Thread " << id << " finished. Threads waiting&running " << threadsWaiting << "," << threadsRunning << std::endl;
#endif
}

template <class T>
void QueueOfThreads<T>::iAmWaiting() {
	if (threadsRunning == 0) abort(); // Test code

									  // The current thread is waiting on something, so let the queue know that other threads can be started
	unique_lock<mutex> lock(myMutex);

	threadsRunning--;
	threadsWaiting++;

	// Although the lock will release when it goes out of scope, I need to unlock it before calling notify
	lock.unlock();
	myConditionVariable.notify_all();

}

template <class T>
void QueueOfThreads<T>::iHaveStoppedWaiting() {
	if (threadsWaiting == 0) abort(); // Test code

	unique_lock<mutex> lock(myMutex);
	myConditionVariable.wait(lock, [this]() {
		return threadsRunning < maxThreads; });

	threadsRunning++;
	threadsWaiting--;

	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::waitForThread(T* pLIW) {
	unique_lock<mutex> lock(myMutex);

	myConditionVariable.wait(lock, [pLIW]() {
		return pLIW->bFinished; });

	lock.unlock();
	myConditionVariable.notify_all();

}


template <class T>
void QueueOfThreads<T>::logwithoutlock(std::string logString) {
	// Called if a lock has already been established

	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
}



template <class T>
void QueueOfThreads<T>::logwithlock(std::string logString) {
	unique_lock<mutex> lock(myMutex);
	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
	lock.unlock();
	myConditionVariable.notify_all();
}



template <class T>
void QueueOfThreads<T>::setNumThreads(UINT numThreads) {
	maxThreads = numThreads;
}

template <class T>
UINT QueueOfThreads<T>::getDeviceCores() {
	return deviceCores;
}


/*
GeneralIntWrapper.h

This class is a wrapper to LongInteger although it can also wrap other items. It allows LongIntegers to be sent
to QueueOfThreads and then collects the results of processing to be picked up by the caller.
It has been created to separate LongInteger and QueueOfThreads

At the moment it just calls the karatsuba algorithm. Will need to be amended to allow for calling any mr.
*/

#pragma once

#ifndef _WIN32
typedef unsigned int UINT;
#endif

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
#pragma once

// Interface class to define common messages the subclasses can receive

template<class T>
class ReceiveUpdateClass
{
public:
	// If I make the constructor virtual Visual Studio refuses to compile. Dunno why. GCC has no issues.
	ReceiveUpdateClass();
	// Virtual destructor needed so I can assign a subclass to a ReceiveUpdateClass pointer and not get memory leaks
	// if delete is called on that pointer
	virtual ~ReceiveUpdateClass();

	virtual void iHaveFinished(unsigned int) = 0;
	virtual void iAmWaiting() = 0;
	virtual void iHaveStoppedWaiting() = 0;
	
};

template <class T>
ReceiveUpdateClass<T>::ReceiveUpdateClass()
{
}

template <class T>
ReceiveUpdateClass<T>::~ReceiveUpdateClass()
{
}


#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

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
/*
Implementation of the QueueOfThreads template
Managed to work out how to move it into a separate file
The .h file includes this file at the end. All seems to work just fine.
*/

#include <thread>
#include <fstream>

template <class T>
QueueOfThreads<T>::QueueOfThreads() {
	threadsRunning = 0;
	threadsWaiting = 0;
	threadID = 0;
	//	deviceCores = std::thread::hardware_concurrency();

	deviceCores = 4;
	if (deviceCores < minThreads) {
		maxThreads = minThreads; // Default value
	}
	else {
		maxThreads = deviceCores;
	}

}

template <class T>
QueueOfThreads<T>::~QueueOfThreads() {
	// Can't exit whilst threads are running.
	// Set the shutting down flag (all should have a reference to that - use an interface)
	// and wait for them to finish

}

template <class T>
void QueueOfThreads<T>::decreaseCount(UINT id) {
	try {
		unique_lock<mutex> lock(myMutex);
		// Find out which thread has finished and remove it from the list
		UINT index = 0;
		bool bFound = false;

		while (!bFound && index < queueOfRunningThreads.size()) {
			if (queueOfRunningThreads[index] == id) {
				bFound = true;
			}
			else {
				index++;
			}
		}

		if (!bFound) {
			abort();
		}

		queueOfRunningThreads.erase(queueOfRunningThreads.begin() + index);

		threadsRunning--;
		lock.unlock();
		myConditionVariable.notify_all();

	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}

}

template <class T>
bool QueueOfThreads<T>::addToQueue(T* newLongInt) {
	try {

		unique_lock<mutex> lock(myMutex);

		newLongInt->setID(threadID);
		queueOfWaitingThreads.push_back(newLongInt);

		threadID++;
		threadsWaiting++;
		newLongInt->setCallback(this);

		// I was using a lambda and it was working fine, but this format of thread starting
		// matches up to the other one.
		// Starting a thread to start a thread may seem weird, but this functionality is just a placeholder
		std::thread t1(&QueueOfThreads<T>::startAThread, this);

		t1.detach();
		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}
	return true;
}

template <class T>
void QueueOfThreads<T>::startAThread() {
	if (threadsWaiting == 0) {
		return;
	}
	try {
		unique_lock<std::mutex> lock(myMutex);
		// The wait will unlock and then try to reacquire the lock when it wakes up
		myConditionVariable.wait(lock, [this]() {
			return threadsRunning < maxThreads; });


		// Insert code to start a thread
		if (queueOfWaitingThreads.size() == 0) {
			abort();
		}


		T* tempLIW = queueOfWaitingThreads[0];
		queueOfWaitingThreads.erase(queueOfWaitingThreads.begin());
		queueOfRunningThreads.push_back(tempLIW->getID());
		threadsRunning++;
		threadsWaiting--;


		//	CString strOutput;
		//	strOutput.Format(L"Thread ID %d - Starting \n", tempLIW->getID());
		//	logwithoutlock(strOutput);


		// This format of call seems to have fixed the issues with access violation. Let's hope it
		// keeps on working.
		std::thread t1(&T::startProcess, tempLIW);

		t1.detach();

		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
}

template <class T>
UINT QueueOfThreads<T>::numOfThreads() {
	// For testing
	unique_lock<mutex> lock(myMutex);
	return threadsRunning + threadsWaiting;
	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::iHaveFinished(UINT id) {
	decreaseCount(id);
#ifdef __linux__
	// Linux test code
	std::cout << "Thread " << id << " finished. Threads waiting&running " << threadsWaiting << "," << threadsRunning << std::endl;
#endif
}

template <class T>
void QueueOfThreads<T>::iAmWaiting() {
	if (threadsRunning == 0) abort(); // Test code

									  // The current thread is waiting on something, so let the queue know that other threads can be started
	unique_lock<mutex> lock(myMutex);

	threadsRunning--;
	threadsWaiting++;

	// Although the lock will release when it goes out of scope, I need to unlock it before calling notify
	lock.unlock();
	myConditionVariable.notify_all();

}

template <class T>
void QueueOfThreads<T>::iHaveStoppedWaiting() {
	if (threadsWaiting == 0) abort(); // Test code

	unique_lock<mutex> lock(myMutex);
	myConditionVariable.wait(lock, [this]() {
		return threadsRunning < maxThreads; });

	threadsRunning++;
	threadsWaiting--;

	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::waitForThread(T* pLIW) {
	unique_lock<mutex> lock(myMutex);

	myConditionVariable.wait(lock, [pLIW]() {
		return pLIW->bFinished; });

	lock.unlock();
	myConditionVariable.notify_all();

}


template <class T>
void QueueOfThreads<T>::logwithoutlock(std::string logString) {
	// Called if a lock has already been established

	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
}



template <class T>
void QueueOfThreads<T>::logwithlock(std::string logString) {
	unique_lock<mutex> lock(myMutex);
	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
	lock.unlock();
	myConditionVariable.notify_all();
}



template <class T>
void QueueOfThreads<T>::setNumThreads(UINT numThreads) {
	maxThreads = numThreads;
}

template <class T>
UINT QueueOfThreads<T>::getDeviceCores() {
	return deviceCores;
}





template<class T> class GeneralIntWrapper
{
public:
	GeneralIntWrapper();
	~GeneralIntWrapper();

	typedef T* (*Tfunction)(const T&, const T&, bool);

private:
	UINT id;
	T* param1;
	T* param2;
	T* pResult;
	ReceiveUpdateClass<GeneralIntWrapper<T>> *callbackObject;
	Tfunction startMethod;
	static QueueOfThreads<GeneralIntWrapper<T>> qot;

public:
	bool bRunning;
	bool bFinished;
	int startProcess();
	void setCallback(ReceiveUpdateClass<GeneralIntWrapper<T>>*);
	void setStartMethod(Tfunction newMethod);
	void setID(UINT);
	UINT getID();
	static QueueOfThreads<GeneralIntWrapper<T>>* getQOT();

	T* getResult();
	void setParams(const T& rParam1, const T& rParam2);
};


template <class T>
GeneralIntWrapper<T>::GeneralIntWrapper()
{
	param1 = nullptr;
	param2 = nullptr;
	pResult = nullptr;
	bRunning = false;
	bFinished = false;
}

template <class T>
GeneralIntWrapper<T>::~GeneralIntWrapper()
{
	delete param1;
	delete param2;
}

template <class T>
QueueOfThreads<GeneralIntWrapper<T>> GeneralIntWrapper<T>::qot;

template <class T>
QueueOfThreads<GeneralIntWrapper<T>>* GeneralIntWrapper<T>::getQOT()
{
	return &qot;
}

template <class T>
int GeneralIntWrapper<T>::startProcess()
{
	bRunning = true;

	// This will call any method that takes 2 parameters of type T and a 3rd parameter of bool
	pResult = startMethod(*(param1), *(param2), true);

	bRunning = false;
	// Need a way this can inform QueueOfThreads that it has finished.
	bFinished = true;
	callbackObject->iHaveFinished(id);
	return 0;
}

template <class T>
void GeneralIntWrapper<T>::setCallback(ReceiveUpdateClass<GeneralIntWrapper<T>>* newcallbackObject)
{
	callbackObject = newcallbackObject;
}

template <class T>
void GeneralIntWrapper<T>::setStartMethod(Tfunction newMethod)
{
	startMethod = newMethod;
}

template <class T>
void GeneralIntWrapper<T>::setID(UINT newID)
{
	id = newID;
}

template <class T>
UINT GeneralIntWrapper<T>::getID()
{
	return id;
}

template <class T>
T* GeneralIntWrapper<T>::getResult()
{
	return pResult;
}

template <class T>
void GeneralIntWrapper<T>::setParams(const T& rParam1, const T& rParam2)
{
	// Copy the parameters. This requires that the assignment operator is overloaded to be a deep copy (should be)
	param1 = new T;
	param2 = new T;

	*param1 = rParam1;
	*param2 = rParam2;
}


#ifndef _WIN32
/* Linux includes. Should cover all non-Windows platforms (and Windows, but Windows code was built using Microsoft-specific
   classes, such as CString), but only tested on Ubuntu 16 so far.
   For my reference - the preprocessor definitions for different platforms
   __linux__       Defined on Linux
   __sun           Defined on Solaris
   __FreeBSD__     Defined on FreeBSD
   __NetBSD__      Defined on NetBSD
   __OpenBSD__     Defined on OpenBSD
   __APPLE__       Defined on Mac OS X
   __hpux          Defined on HP-UX
   __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
   __sgi           Defined on Irix
   _AIX            Defined on AIX
   _WIN32          Defined on Windows

   I believe that __linux and linux work on the Linux platform as well.
*/
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <algorithm>
///typedef unsigned char byte; // Didn't realise byte and UINT were Microsoft specific definitions. Added them here for Linux
///typedef unsigned int UINT;
///typedef unsigned long ULONG;
///typedef unsigned long long ULONGLONG;



using std::stringstream;
using std::string;
using std::ifstream;
using std::ios;
#endif

// This definition is to add compatibility with C++11. The code is intended for C++14, but it turns out
// the template below is all that is needed to run under the C++11 standard
#if __cplusplus == 201103L
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&& ... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif

using std::vector;
using std::unique_ptr;
#if __cplusplus != 201103L
using std::make_unique;
#endif
using std::move;

// The class is named below with no implementation so as to avoid a Catch-22 situation with the typedefs
// The typedefs need to be defined using class LongInteger, but class LongInteger needs the typedefs
// So this definition says "I'm going to use a class called LongInteger and I'll fill in the details later on"
class LongInteger;
typedef GeneralIntWrapper<LongInteger> LongIntWrapper; // A shorthand to make it easier to type
typedef unique_ptr<LongInteger> LongIntegerUP; // Ditto
// This for passing a pointer to a function that takes 2 const LongInteger parameters and a bool and returns a pointer to a LongInteger
// The function pointer is referred to as 'Lifunction' in the code
typedef LongInteger* (*LIfunction)(const LongInteger&, const LongInteger&, bool);

// Forward declaration. For some reason I only need to forward declare this one and everything works
bool operator<(int lhs, const LongInteger& rhs);
bool operator<(UINT lhs, const LongInteger& rhs);


#define byte unsigned char
#define ULONG unsigned long
#define ULONGLONG unsigned long long
class LongInteger {
public:
	// Have these listed here (public and at the top of the class) whilst still working on them

	// Still in testing. Performance is weird in release build (improves dramatically at multiples of 350 and then drops
	// rapidly until the next multiple is hit), but works as expected in debug build. Haven't worked out why.
	static LongInteger* ToomCook3(const LongInteger&, const LongInteger&, bool bBackgroundThread = false);

	// This is under development. The code is rather messy as I'm struggling to follow the paper due to the heavy usage of maths
	// terminology I'm unfamiliar with.
	// So far it shows that it is a lot quicker than long division if the divisor is at least half the size (number of digits)
	// of the value. Otherwise it is a lot slower. So working on a framework to adjust the size of the divisor and then
	// adjust the results. Despite being a lot more work it is still quicker. Needs quite a bit of testing
	// to work out the optimal values.
	static void BurnikelZiegler(const LongInteger&, const LongInteger&, LongIntegerUP&, LongIntegerUP&);
	// This is the framework that does the adjustments prior to calling the BurnikelZiegler method
	static bool DivAndMod(const LongInteger&, const LongInteger&, LongIntegerUP&, LongIntegerUP&);
	static bool DivAndMod(const LongInteger&, const LongInteger&, LongInteger&, LongInteger&);


	static LongInteger sqrt(const LongInteger&);
	static LongInteger sqr(const LongInteger&);
	static LongInteger pow(const LongInteger&, const LongInteger&);
	static LongInteger factorial(const LongInteger&);
	static LongInteger log(const LongInteger&);
	static LongInteger log(const LongInteger&, const LongInteger&);
	static LongInteger ln(const LongInteger&);

private:
	// This is the front end to the Karatsuba algorithm which also tidies up any memory allocated
	static LongInteger multiplyChooser(const LongInteger&, const LongInteger&);
	// Restoring division seems to work fine. Some more testing needed to see what the performance is
	static void RestoringDivision(LongInteger&, LongInteger&, LongInteger*, LongInteger*);

	static bool TriedToReadE;

	static LongInteger ReadEFromFile(std::string path);


public: // Make this public during development
		// This is the recursive part of the karatsuba algorithm
	static LongInteger* karatsuba(const LongInteger&, const LongInteger&, bool bBackgroundThread = false);

	// Constants
public:
	static const UINT BASEVAL = 256; // The effective base of the numbers (each digit is 1 byte)
	static const UINT BASEVALBITS = 8; // Size of each digit in bits
	static const UINT BASEVALBITSSHIFT = 3; // If dividing/multiplying by basevalbits, using shifts
	static const byte BASEMAX = 255; // Highest value that can be stored in each digit
	static const UINT ABSMAXSIZE = 4294967295; // Largest number of values that can be stored (index is by uint, so 2^32-1)

	static const UINT MINSIZE = 50;
	static const UINT TINYSIZESTEP = 50;
	static const UINT SMALLSIZESTEP = 1000;
	static const UINT SIZESTEP = 10000; // Internal byte array is increased or decreased in block of this size
										//	static const UINT KARATSUBACUTOFF = 50; // Karatsuba cutoff size. Numbers below this size will use long multiplication
										//	static const UINT TOOMCOOK3CUTOFF = 150; // Testing shows this is the optimal value. Update - 150 is the best in debug builds. In release builds it is not. In release it is all over the place.
										//	static const UINT BURKINELZIEGLERCUTOFF = 50; // 50 seems to work well for the recursion point

										// Making these non-const so I can test different values
	static UINT KARATSUBACUTOFF;
	static UINT TOOMCOOK3CUTOFF;
	static UINT BURKINELZIEGLERCUTOFF;
	// Threading values are now calculated dynamically (after accidentally triggering 20,000 threads) and so are non-const
	static UINT KARATSUBATHREADING;
	static UINT TOOMCOOK3THREADING;

	static LongInteger E; // These aren't const as there will be an attempt to read in a value from file, else use the default.
	static UINT SIZEOFE; // Number of bytes that e has been shifted left by for the value above.

public:
	// For testing only
	void assignByteArray(byte*, UINT);

	// Constructors
	LongInteger();
	LongInteger(const int);
	LongInteger(const UINT);
	LongInteger(const ULONG);
	LongInteger(const ULONGLONG);
	LongInteger(const LongInteger&);
	LongInteger(const double);
	LongInteger(const long double);
	LongInteger(LongInteger*);

	// Add in wstring option as well once this is compiling
	LongInteger(const std::string&);

	~LongInteger();

	// Useful functions
	const UINT getSize() const;

	bool assignNumber(int);
	bool assignNumber(UINT);
	bool assignNumber(ULONG);
	bool assignNumber(ULONGLONG);
	bool assignNumber(double);
	bool assignNumber(long double);

	bool assignNumber(const std::string&);


	byte getDigit(UINT) const;
	bool setDigit(UINT, byte);
	// Split the current LongInt. Send in 2 LongInts to hold the result. Returns false if it fails
	bool split(LongInteger*, LongInteger*, UINT) const;
	// Split 'this' into 3 parts of UINT size and return as an array of LongIntegers
	UINT toomsplit(LongInteger**, UINT) const;



	std::string toDecimal();
	std::string toDecimal() const;
	std::string toHexString() const; // Useful for testing
	std::string toArrayNumbers(); // Also useful for testing

	explicit operator int() const; // Convert to int. Make it explicit to avoid auto casting which will cause confusion
	explicit operator UINT() const;

	// Arithmetic functions
	bool addNumber(int);
	bool addNumber(const LongInteger&);
	bool subtractNumber(int);
	bool subtractNumber(const LongInteger&);
	bool multiplyNumber(int);
	bool multiplyNumber(const LongInteger&);
	bool divideNumber(int);
	bool divideNumber(const LongInteger&);
	bool powerCalc(LongInteger&, const LongInteger&);
	bool powerCalc(const LongInteger&);
	bool powerCalc(int);

	bool arrowCalc(UINT, int);
	bool modulus(const LongInteger&);
	bool factorial();

	// Arithmetic operators
	LongInteger operator+(const LongInteger&) const; // Addition
	LongInteger operator+() const; // Unary plus
	LongInteger operator-(const LongInteger&) const;
	LongInteger operator-() const; // Unary negate
	LongInteger operator*(const LongInteger&) const;
	LongInteger operator/(const LongInteger&) const;
	LongInteger operator%(const LongInteger&) const;

	LongInteger operator+(int) const; // Addition
	LongInteger operator-(int) const;
	LongInteger operator*(int) const;
	LongInteger operator/(int) const;
	LongInteger operator%(int) const;

	LongInteger& operator=(const LongInteger&);
	LongInteger& operator++(); // Prefix increment
	LongInteger operator++(int); // Postfix increment (the int is unused - a placeholder in the syntax)
	LongInteger& operator+=(const LongInteger&); // Adding a LongInteger
	LongInteger& operator+=(int); // Adding an int
	LongInteger& operator--(); // Prefix decrement
	LongInteger operator--(int); // Postfix decrement
	LongInteger& operator-=(const LongInteger&);
	LongInteger& operator-=(int);
	LongInteger& operator*=(const LongInteger&);
	LongInteger& operator*=(int);
	LongInteger& operator/=(const LongInteger&);
	LongInteger& operator/=(int);
	LongInteger& operator%=(const LongInteger&);
	LongInteger& operator%=(int);

	// Bitwise operators
	bool bitwiseand(const LongInteger&);
	LongInteger operator&(const LongInteger&);
	LongInteger operator&(int);
	LongInteger& operator&=(const LongInteger&);
	LongInteger& operator&=(int);

	bool bitwiseor(const LongInteger&);
	LongInteger operator|(const LongInteger&);
	LongInteger operator|(int);
	LongInteger& operator|=(const LongInteger&);
	LongInteger& operator|=(int);

	bool bitwisenot();
	LongInteger operator~() const;

	bool bitwisexor(const LongInteger&);
	LongInteger operator^(const LongInteger&);
	LongInteger operator^(int);
	LongInteger& operator^=(const LongInteger&);
	LongInteger& operator^=(int);

	bool bitshiftright(const LongInteger&);
	bool bitshiftleft(const LongInteger&);
	bool bitshiftright(UINT);
	bool bitshiftleft(UINT);
	LongInteger operator >> (const LongInteger&);
	LongInteger operator >> (UINT);
	LongInteger& operator>>=(const LongInteger&);
	LongInteger& operator>>=(UINT);
	LongInteger operator<<(const LongInteger&);
	LongInteger operator<<(UINT);
	LongInteger& operator<<=(const LongInteger&);
	LongInteger& operator<<=(UINT);

	static LongInteger abs(const LongInteger&);

	bool equalsZero() const;
	bool isProcessing();
	// Commenting these 2 calls out as I need a better way of waiting on completion
	// This was a hack to get the program working properly in Windows
	void setProcessing(bool);
	//    void setProcessing(bool, CWinThread* = nullptr);
	//    HANDLE getProcessingHandle();
	bool isShuttingDown();
	void setShuttingDown(bool);

	inline bool overflow() const {
		return bOverflow;
	}

	bool writeToFile(std::string&);
	bool readFromFile(std::string&);


private:
	byte* digits = nullptr;
	bool bPositive = true;
	UINT maxSize = 0;
	UINT size = 0;
	bool bOverflow = false;
	bool static bShuttingDown;
	bool bProcessing;
	// Commented out at the moment. Not just because it is Windows specific, but
	// because I need a more secure way of waiting on completion
	//    CWinThread *thrProcessingRef = nullptr;

	void init();
	void reset(); // Reset the internal array
	void copy(const LongInteger&);
	void addInternal(byte*, UINT, UINT, UINT);
	void checkSize();
	void recalcMaxSize();
	void recalcMaxSizeAndClear();
	bool increaseSize();
	bool decreaseSize();
	bool increment(); // Helper function for ++
	bool decrement(); // Helper function for --

					  // Helper methods
	bool arrowCalc(const LongInteger&, UINT, LongInteger&);
	bool powerCalcHelper(const LongInteger&, LongInteger&);
	bool divHelper(int);
	bool divByByte(byte);
	bool multHelper(int);
	bool multHelper2(UINT);
	UINT UINTpower(UINT, UINT) const;

	// Helper methods for Burnikel-Ziegler division
	static LongIntegerUP merge(vector<LongIntegerUP>& vList, UINT uNumParts, UINT uSizeParts);
	static vector<LongIntegerUP> DivThreeHalvesByTwo(LongIntegerUP& a1, LongIntegerUP& a2, LongIntegerUP& a3, LongIntegerUP& b1, LongIntegerUP& b2, UINT uNumDigits);
	static vector<LongIntegerUP> DivTwoDigitsByOne(LongIntegerUP& AHigh, LongIntegerUP& ALow, LongIntegerUP& B, UINT uNumDigits);
	// A generic splitting function. Split the input LongInteger into UINT parts of UINT length and return as an array of LongIntegers
	static vector<LongIntegerUP> split(LongIntegerUP&, UINT, UINT);

	LongInteger* pSharedLongInt;

public:
	bool multiplyInternal(const LongInteger&);

	// comparison operators
public:
	inline bool isPositive() const { return bPositive; }

	inline bool operator<(const LongInteger& rhs) const {
		if (bOverflow || rhs.bOverflow) {
			return false;
		}

		if (bPositive != rhs.bPositive) {
			// If this is + and rhs is -, then return -, else return +. So return opposite of bPositive flag
			return !bPositive;
		}

		if (size < rhs.size) {
			return true;
		}
		if (size > rhs.size) {
			return false;
		}

		bool bLessThan = false;
		bool bLoop = true;
		bool bEquals = false;
		// Some amendments as the index is now a UINT and thus we can't go negative
		if (size > 0) {
			UINT index = size - 1;
			while (index > 0 && bLoop) {
				if (digits[index] < rhs.digits[index]) {
					bLessThan = true;
					bLoop = false;
				}
				else if (digits[index] > rhs.digits[index]) {
					bLoop = false;
				}
				--index;
			}
		}
		// Scenario for index = 0 and we haven't finished checking
		if (bLoop) {
			if (digits[0] < rhs.digits[0]) {
				bLessThan = true;
			}
			else if (digits[0] == rhs.digits[0])
			{
				// Added extra test as this was going wrong comparing negative numbers that were equal and returning true
				bEquals = true;
			}
		}

		if (bEquals) {
			return false;
		}
		else {
			return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
		}
	}

	inline bool operator>(const LongInteger& rhs) const {
		return rhs < (*this);
	}

	inline bool operator<=(const LongInteger& rhs) const {
		return !((*this) > rhs);
	}

	inline bool operator<=(int rhs) const {
		return !((*this) > rhs);
	}

	inline bool operator>=(const LongInteger& rhs) const {
		return !((*this) < rhs);
	}

	inline bool operator>=(int rhs) const {
		return !((*this) < rhs);
	}

	inline bool operator==(const LongInteger& rhs) const {
		if (bOverflow || rhs.bOverflow) {
			return false;
		}
		if (size != rhs.size) {
			return false;
		}
		if (bPositive != rhs.bPositive) {
			return false;
		}
		bool bEqual = true;
		// Amendments for using UINT as index instead of int. Can no longer check for less than zero
		// so we have to do this in 2 bits
		if (size > 0) {
			UINT iLoop = size - 1;
			while (iLoop > 0 && bEqual) {
				if (digits[iLoop] != rhs.digits[iLoop])
					bEqual = false;
				--iLoop;
			}
		}
		// Extra bit for the zeroth digit
		if (bEqual) {
			if (digits[0] != rhs.digits[0])
				bEqual = false;
		}
		return bEqual;
	}

	inline bool operator==(int rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1 && bPositive);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(int)) {
			return false;
		}

		bool bEquals = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt += (digits[i] << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == std::abs(rhs))
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator==(UINT rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(UINT)) {
			return false;
		}

		bool bEquals = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt += (digits[i] << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == rhs)
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator==(ULONGLONG rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(ULONGLONG)) {
			return false;
		}

		bool bEquals = false;
		ULONGLONG thisAsInt = digits[0];
		ULONGLONG temp;

		for (UINT i = 1; i < size; i++)
		{
			temp = digits[i];
			thisAsInt += (temp << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == rhs)
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator!=(const LongInteger& rhs) {
		return !((*this) == rhs);
	}

	inline bool operator!=(int rhs) {
		return !((*this) == rhs);
	}

	inline bool operator!=(UINT rhs) {
		return !((*this) == rhs);
	}

	// Add int versions of the comparison operators to avoid the overhead of converting ints to LongIntegers for comparisons.
	inline bool operator<(int rhs) const {
		if (bOverflow) {
			return false;
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			// If this is + and rhs is -, then return -, else return +. So return opposite of bPositive flag
			return !bPositive;
		}
		// Comparison with zero. If both are zero
		if (rhs == 0) {
			if (equalsZero()) {
				return false;
			}
			else {
				return !bPositive;
			}
		}
		else {
			if (equalsZero()) {
				return (rhs > 0);
			}
		}

		if (size > sizeof(int)) {
			return false ^ !bPositive;
		}

		bool bLessThan = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt *= digits[i];
		}

		if (thisAsInt < (UINT)std::abs(rhs))
		{
			bLessThan = true;
		}
		else if (thisAsInt == (UINT)std::abs(rhs))
		{
			return false; // The return value for equal negative numbers was going wrong
		}
		return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
	}

	inline bool operator<(UINT rhs) const {
		if (bOverflow) {
			return false;
		}

		if (!bPositive) {
			// UINTs can only be positive, so if this is negative it is definately less than the UINT
			return true;
		}
		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(int)) {
			return false ^ !bPositive;
		}

		bool bLessThan = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt *= digits[i];
		}

		if (thisAsInt < rhs)
		{
			bLessThan = true;
		}
		return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
	}

	inline bool operator>(int rhs) const
	{
		return rhs < (*this);
	}

	inline bool operator>(UINT rhs) const
	{
		return rhs < (*this);
	}
};


inline bool operator==(int lhs, const LongInteger& rhs) {
	return rhs == lhs;
}

inline bool operator==(UINT lhs, const LongInteger& rhs) {
	return rhs == lhs;
}

inline bool operator!=(int lhs, const LongInteger& rhs) {
	return !(rhs == lhs);
}

inline bool operator!=(UINT lhs, const LongInteger& rhs) {
	return !(rhs == lhs);
}

inline bool operator<(UINT lhs, const LongInteger& rhs) {
	if (rhs.overflow()) {
		return false;
	}

	bool bPositive = rhs.isPositive();

	if (!bPositive) {
		// If rhs is negative it is definately less than lhs as UINTs can't be negative
		return false;
	}
	if (rhs.equalsZero()) {
		if (lhs == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (lhs == 0) {
			return false;
		}
	}

	if (rhs.getSize() > sizeof(int)) {
		return true ^ !bPositive;
	}

	bool bLessThan = false;
	UINT thisAsInt = rhs.getDigit(rhs.getSize() - 1);

	if (rhs.getSize() > 1)
	{
		for (UINT i = rhs.getSize() - 1; i > 0; i--)
		{
			thisAsInt *= LongInteger::BASEVAL;
			thisAsInt += (rhs.getDigit(i - 1));
		}
	}

	if (lhs < thisAsInt)
	{
		bLessThan = true;
	}
	return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
}

inline bool operator<(int lhs, const LongInteger& rhs) {
	if (rhs.overflow()) {
		return false;
	}

	bool bPositive = rhs.isPositive();

	if ((bPositive && lhs < 0) || (!bPositive && lhs >= 0)) {
		// If this is + and rhs is -, then return -, else return +. So return bPositive flag
		return bPositive;
	}
	if (rhs.equalsZero()) {
		if (lhs == 0) {
			return false;
		}
		else {
			return (lhs < 0);
		}
	}
	else {
		if (lhs == 0) {
			return bPositive;
		}
	}

	if (rhs.getSize() > sizeof(int)) {
		return true ^ !bPositive;
	}

	bool bLessThan = false;
	UINT thisAsInt = rhs.getDigit(rhs.getSize() - 1);

	if (rhs.getSize() > 1)
	{
		for (UINT i = rhs.getSize() - 1; i > 0; i--)
		{
			thisAsInt *= LongInteger::BASEVAL;
			thisAsInt += (rhs.getDigit(i - 1));
		}
	}

	if ((UINT)std::abs(lhs) < thisAsInt)
	{
		bLessThan = true;
	}
	else if ((UINT)std::abs(lhs) == thisAsInt)
	{
		return false;
	}
	return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
}


inline bool operator>(int lhs, const LongInteger& rhs) {
	return rhs < lhs;
}

inline bool operator>(UINT lhs, const LongInteger& rhs) {
	return rhs < lhs;
}

inline bool operator>=(int lhs, const LongInteger& rhs) {
	return !(lhs < rhs);
}

inline bool operator>=(UINT lhs, const LongInteger& rhs) {
	return !(lhs < rhs);
}

inline bool operator<=(int lhs, const LongInteger& rhs) {
	return !(lhs > rhs);
}

inline bool operator<=(UINT lhs, const LongInteger& rhs) {
	return !(lhs > rhs);
}

inline LongInteger operator+(int lhs, const LongInteger& rhs) {
	return rhs + lhs;
}

inline LongInteger operator+(UINT lhs, const LongInteger& rhs) {
	return rhs + lhs;
}

inline LongInteger operator-(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value - rhs;
}

inline LongInteger operator-(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value - rhs;
}

inline LongInteger operator*(int lhs, const LongInteger& rhs) {
	return rhs * lhs;
}

inline LongInteger operator*(UINT lhs, const LongInteger& rhs) {
	return rhs * lhs;
}

inline LongInteger operator/(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value / rhs;
}

inline LongInteger operator/(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value / rhs;
}

inline LongInteger operator&(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value & rhs;
}

inline LongInteger operator&(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value & rhs;
}

inline LongInteger operator|(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value | rhs;
}

inline LongInteger operator|(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value | rhs;
}

inline LongInteger operator^(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value ^ rhs;
}

inline LongInteger operator^(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value ^ rhs;
}

inline LongInteger operator >> (int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value >> rhs;
}

inline LongInteger operator >> (UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value >> rhs;
}

#endif

#pragma once

// Based on the class created by Roman Pasechnik. Modified to use my LongInteger class instead of ints


#ifndef _PRIMESWING_H_
#define _PRIMESWING_H_

#ifndef _PRIMESIEVE_H_
#pragma once

#ifndef _PRIMESIEVE_H_
#define _PRIMESIEVE_H_

#pragma once


#ifndef _UTILITYFUNCTIONS_H_
#define _UTILITYFUNCTIONS_H_

//////////////////////////////////////////////////////////////////////////

#ifndef _UTILITYTYPES_H_
#pragma once

#ifndef _UTILITYTYPES_H_
#define _UTILITYTYPES_H_

// Based on the code of Roman Pasechnik. Modified to work with my LongInteger class

#include <vector>
#include <set>
#include <map>
#include <queue>

class LongInteger; // Forward definition to avoid circular includes. Will generitisate this once I understand what is happening

/** Vector of integers */
typedef std::vector<int> IntVec;

/** Vector of booleans */
typedef std::vector<bool> BoolVec;

/** Set of big integers */
typedef std::multiset<LongInteger> LongIntSet; // Multiset needed as it can contain duplicate values. std::set doesn't allow duplicates

/** Vector of LongIntegers */
typedef std::vector<LongInteger> LongIntVec;

// Attempting to add replacement types that can handle more than 4 billion entries
// A map can handle 8^8 entries, which is a start, although I would like to go to something that could potentially hold 2^32^8 entries
// even though 8^8 entries would exceed the RAM capacity on any normal machine
/** Map of LongIntegers */
typedef std::map<LongInteger, LongInteger> LongIntMap;

typedef std::queue<LongInteger> LongIntQueue;

#endif

/*
* LongInteger.h
*
* Header for LongInteger class. Can handle positive integers up to 4 billion digits in length.
* It holds the number as a byte array and indexes it using an uint (hence the size limit)
* Addition, subtraction, multiplication and division and powers are handled.
* Standard operators - +,-,*,/,+=,-=,/=,*=,<,>,<=,>=,!=,== are handled
* The = operator is overriden to provide copy by value instead of the default copy by reference
* It is also overloaded, so that strings and ints can be assigned to a LongInteger
*
* The karatsuba algorithm is used to multiply large numbers. It is more complex than long multiplication,
* but the number of steps needed doesn't increase as rapidly as the number length increases.
* The karatsuba algorithm is only accessed via the multiplyNumber method
*
* ToomCook3 algorithm has been added for multiplying even larger numbers. The implementation looks rather complex, so
* there may well be inefficiencies. Performance is odd, which convinces me all is not correct
*
* Burnikel-Ziegler algorithm for division has been implemented. It ended up with much more code than expected
* and also handles scenarios that aren't mentioned at all in Burnikel and Ziegler's paper, so that isn't a good sign.
* It works and divides numbers faster than the division algorithm I implemented for large numbers, where the divisor
* is at least half the size of the value being divided.
*
*
* The compiler needs to support C++14 to get this code to work.
* Visual Studio 2015 Community Edition supports this without any amendments needed.
*
* I got NetBeans to compile this code by going into
* Project Properties - C++ Compiler - Additional options - and added '-std=c++14 -pthread'. The -pthread is to
* add multithreading support otherwise NetBeans gets very confused.
*
* Managed to get Eclipse to compile the code as well, although I cannot get the IDE to recognise C++14 code
* It insists there are errors, but hit compile and it builds fine. It will also debug and step through the code
* without issues, but still with warnings about unrecognised code all over the place.
*
* Unique Pointers are used because the memory management was getting out of hand and was becoming a real mess.
* Where it is manageable I've kept using simple points to reduce overheads.
*
*/

#pragma once

#ifndef _LONGINTEGER_H
#define _LONGINTEGER_H

#include <vector>
#include <memory>
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
#pragma once

// Interface class to define common messages the subclasses can receive

template<class T>
class ReceiveUpdateClass
{
public:
	// If I make the constructor virtual Visual Studio refuses to compile. Dunno why. GCC has no issues.
	ReceiveUpdateClass();
	// Virtual destructor needed so I can assign a subclass to a ReceiveUpdateClass pointer and not get memory leaks
	// if delete is called on that pointer
	virtual ~ReceiveUpdateClass();

	virtual void iHaveFinished(unsigned int) = 0;
	virtual void iAmWaiting() = 0;
	virtual void iHaveStoppedWaiting() = 0;
	
};

template <class T>
ReceiveUpdateClass<T>::ReceiveUpdateClass()
{
}

template <class T>
ReceiveUpdateClass<T>::~ReceiveUpdateClass()
{
}


#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

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
/*
Implementation of the QueueOfThreads template
Managed to work out how to move it into a separate file
The .h file includes this file at the end. All seems to work just fine.
*/

#include <thread>
#include <fstream>

template <class T>
QueueOfThreads<T>::QueueOfThreads() {
	threadsRunning = 0;
	threadsWaiting = 0;
	threadID = 0;
	//	deviceCores = std::thread::hardware_concurrency();

	deviceCores = 4;
	if (deviceCores < minThreads) {
		maxThreads = minThreads; // Default value
	}
	else {
		maxThreads = deviceCores;
	}

}

template <class T>
QueueOfThreads<T>::~QueueOfThreads() {
	// Can't exit whilst threads are running.
	// Set the shutting down flag (all should have a reference to that - use an interface)
	// and wait for them to finish

}

template <class T>
void QueueOfThreads<T>::decreaseCount(UINT id) {
	try {
		unique_lock<mutex> lock(myMutex);
		// Find out which thread has finished and remove it from the list
		UINT index = 0;
		bool bFound = false;

		while (!bFound && index < queueOfRunningThreads.size()) {
			if (queueOfRunningThreads[index] == id) {
				bFound = true;
			}
			else {
				index++;
			}
		}

		if (!bFound) {
			abort();
		}

		queueOfRunningThreads.erase(queueOfRunningThreads.begin() + index);

		threadsRunning--;
		lock.unlock();
		myConditionVariable.notify_all();

	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}

}

template <class T>
bool QueueOfThreads<T>::addToQueue(T* newLongInt) {
	try {

		unique_lock<mutex> lock(myMutex);

		newLongInt->setID(threadID);
		queueOfWaitingThreads.push_back(newLongInt);

		threadID++;
		threadsWaiting++;
		newLongInt->setCallback(this);

		// I was using a lambda and it was working fine, but this format of thread starting
		// matches up to the other one.
		// Starting a thread to start a thread may seem weird, but this functionality is just a placeholder
		std::thread t1(&QueueOfThreads<T>::startAThread, this);

		t1.detach();
		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}
	return true;
}

template <class T>
void QueueOfThreads<T>::startAThread() {
	if (threadsWaiting == 0) {
		return;
	}
	try {
		unique_lock<std::mutex> lock(myMutex);
		// The wait will unlock and then try to reacquire the lock when it wakes up
		myConditionVariable.wait(lock, [this]() {
			return threadsRunning < maxThreads; });


		// Insert code to start a thread
		if (queueOfWaitingThreads.size() == 0) {
			abort();
		}


		T* tempLIW = queueOfWaitingThreads[0];
		queueOfWaitingThreads.erase(queueOfWaitingThreads.begin());
		queueOfRunningThreads.push_back(tempLIW->getID());
		threadsRunning++;
		threadsWaiting--;


		//	CString strOutput;
		//	strOutput.Format(L"Thread ID %d - Starting \n", tempLIW->getID());
		//	logwithoutlock(strOutput);


		// This format of call seems to have fixed the issues with access violation. Let's hope it
		// keeps on working.
		std::thread t1(&T::startProcess, tempLIW);

		t1.detach();

		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
}

template <class T>
UINT QueueOfThreads<T>::numOfThreads() {
	// For testing
	unique_lock<mutex> lock(myMutex);
	return threadsRunning + threadsWaiting;
	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::iHaveFinished(UINT id) {
	decreaseCount(id);
#ifdef __linux__
	// Linux test code
	std::cout << "Thread " << id << " finished. Threads waiting&running " << threadsWaiting << "," << threadsRunning << std::endl;
#endif
}

template <class T>
void QueueOfThreads<T>::iAmWaiting() {
	if (threadsRunning == 0) abort(); // Test code

									  // The current thread is waiting on something, so let the queue know that other threads can be started
	unique_lock<mutex> lock(myMutex);

	threadsRunning--;
	threadsWaiting++;

	// Although the lock will release when it goes out of scope, I need to unlock it before calling notify
	lock.unlock();
	myConditionVariable.notify_all();

}

template <class T>
void QueueOfThreads<T>::iHaveStoppedWaiting() {
	if (threadsWaiting == 0) abort(); // Test code

	unique_lock<mutex> lock(myMutex);
	myConditionVariable.wait(lock, [this]() {
		return threadsRunning < maxThreads; });

	threadsRunning++;
	threadsWaiting--;

	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::waitForThread(T* pLIW) {
	unique_lock<mutex> lock(myMutex);

	myConditionVariable.wait(lock, [pLIW]() {
		return pLIW->bFinished; });

	lock.unlock();
	myConditionVariable.notify_all();

}


template <class T>
void QueueOfThreads<T>::logwithoutlock(std::string logString) {
	// Called if a lock has already been established

	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
}



template <class T>
void QueueOfThreads<T>::logwithlock(std::string logString) {
	unique_lock<mutex> lock(myMutex);
	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
	lock.unlock();
	myConditionVariable.notify_all();
}



template <class T>
void QueueOfThreads<T>::setNumThreads(UINT numThreads) {
	maxThreads = numThreads;
}

template <class T>
UINT QueueOfThreads<T>::getDeviceCores() {
	return deviceCores;
}


/*
GeneralIntWrapper.h

This class is a wrapper to LongInteger although it can also wrap other items. It allows LongIntegers to be sent
to QueueOfThreads and then collects the results of processing to be picked up by the caller.
It has been created to separate LongInteger and QueueOfThreads

At the moment it just calls the karatsuba algorithm. Will need to be amended to allow for calling any mr.
*/

#pragma once

#ifndef _WIN32
typedef unsigned int UINT;
#endif

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
#pragma once

// Interface class to define common messages the subclasses can receive

template<class T>
class ReceiveUpdateClass
{
public:
	// If I make the constructor virtual Visual Studio refuses to compile. Dunno why. GCC has no issues.
	ReceiveUpdateClass();
	// Virtual destructor needed so I can assign a subclass to a ReceiveUpdateClass pointer and not get memory leaks
	// if delete is called on that pointer
	virtual ~ReceiveUpdateClass();

	virtual void iHaveFinished(unsigned int) = 0;
	virtual void iAmWaiting() = 0;
	virtual void iHaveStoppedWaiting() = 0;
	
};

template <class T>
ReceiveUpdateClass<T>::ReceiveUpdateClass()
{
}

template <class T>
ReceiveUpdateClass<T>::~ReceiveUpdateClass()
{
}


#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

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
/*
Implementation of the QueueOfThreads template
Managed to work out how to move it into a separate file
The .h file includes this file at the end. All seems to work just fine.
*/

#include <thread>
#include <fstream>

template <class T>
QueueOfThreads<T>::QueueOfThreads() {
	threadsRunning = 0;
	threadsWaiting = 0;
	threadID = 0;
	//	deviceCores = std::thread::hardware_concurrency();

	deviceCores = 4;
	if (deviceCores < minThreads) {
		maxThreads = minThreads; // Default value
	}
	else {
		maxThreads = deviceCores;
	}

}

template <class T>
QueueOfThreads<T>::~QueueOfThreads() {
	// Can't exit whilst threads are running.
	// Set the shutting down flag (all should have a reference to that - use an interface)
	// and wait for them to finish

}

template <class T>
void QueueOfThreads<T>::decreaseCount(UINT id) {
	try {
		unique_lock<mutex> lock(myMutex);
		// Find out which thread has finished and remove it from the list
		UINT index = 0;
		bool bFound = false;

		while (!bFound && index < queueOfRunningThreads.size()) {
			if (queueOfRunningThreads[index] == id) {
				bFound = true;
			}
			else {
				index++;
			}
		}

		if (!bFound) {
			abort();
		}

		queueOfRunningThreads.erase(queueOfRunningThreads.begin() + index);

		threadsRunning--;
		lock.unlock();
		myConditionVariable.notify_all();

	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}

}

template <class T>
bool QueueOfThreads<T>::addToQueue(T* newLongInt) {
	try {

		unique_lock<mutex> lock(myMutex);

		newLongInt->setID(threadID);
		queueOfWaitingThreads.push_back(newLongInt);

		threadID++;
		threadsWaiting++;
		newLongInt->setCallback(this);

		// I was using a lambda and it was working fine, but this format of thread starting
		// matches up to the other one.
		// Starting a thread to start a thread may seem weird, but this functionality is just a placeholder
		std::thread t1(&QueueOfThreads<T>::startAThread, this);

		t1.detach();
		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}
	return true;
}

template <class T>
void QueueOfThreads<T>::startAThread() {
	if (threadsWaiting == 0) {
		return;
	}
	try {
		unique_lock<std::mutex> lock(myMutex);
		// The wait will unlock and then try to reacquire the lock when it wakes up
		myConditionVariable.wait(lock, [this]() {
			return threadsRunning < maxThreads; });


		// Insert code to start a thread
		if (queueOfWaitingThreads.size() == 0) {
			abort();
		}


		T* tempLIW = queueOfWaitingThreads[0];
		queueOfWaitingThreads.erase(queueOfWaitingThreads.begin());
		queueOfRunningThreads.push_back(tempLIW->getID());
		threadsRunning++;
		threadsWaiting--;


		//	CString strOutput;
		//	strOutput.Format(L"Thread ID %d - Starting \n", tempLIW->getID());
		//	logwithoutlock(strOutput);


		// This format of call seems to have fixed the issues with access violation. Let's hope it
		// keeps on working.
		std::thread t1(&T::startProcess, tempLIW);

		t1.detach();

		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
}

template <class T>
UINT QueueOfThreads<T>::numOfThreads() {
	// For testing
	unique_lock<mutex> lock(myMutex);
	return threadsRunning + threadsWaiting;
	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::iHaveFinished(UINT id) {
	decreaseCount(id);
#ifdef __linux__
	// Linux test code
	std::cout << "Thread " << id << " finished. Threads waiting&running " << threadsWaiting << "," << threadsRunning << std::endl;
#endif
}

template <class T>
void QueueOfThreads<T>::iAmWaiting() {
	if (threadsRunning == 0) abort(); // Test code

									  // The current thread is waiting on something, so let the queue know that other threads can be started
	unique_lock<mutex> lock(myMutex);

	threadsRunning--;
	threadsWaiting++;

	// Although the lock will release when it goes out of scope, I need to unlock it before calling notify
	lock.unlock();
	myConditionVariable.notify_all();

}

template <class T>
void QueueOfThreads<T>::iHaveStoppedWaiting() {
	if (threadsWaiting == 0) abort(); // Test code

	unique_lock<mutex> lock(myMutex);
	myConditionVariable.wait(lock, [this]() {
		return threadsRunning < maxThreads; });

	threadsRunning++;
	threadsWaiting--;

	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::waitForThread(T* pLIW) {
	unique_lock<mutex> lock(myMutex);

	myConditionVariable.wait(lock, [pLIW]() {
		return pLIW->bFinished; });

	lock.unlock();
	myConditionVariable.notify_all();

}


template <class T>
void QueueOfThreads<T>::logwithoutlock(std::string logString) {
	// Called if a lock has already been established

	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
}



template <class T>
void QueueOfThreads<T>::logwithlock(std::string logString) {
	unique_lock<mutex> lock(myMutex);
	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
	lock.unlock();
	myConditionVariable.notify_all();
}



template <class T>
void QueueOfThreads<T>::setNumThreads(UINT numThreads) {
	maxThreads = numThreads;
}

template <class T>
UINT QueueOfThreads<T>::getDeviceCores() {
	return deviceCores;
}





template<class T> class GeneralIntWrapper
{
public:
	GeneralIntWrapper();
	~GeneralIntWrapper();

	typedef T* (*Tfunction)(const T&, const T&, bool);

private:
	UINT id;
	T* param1;
	T* param2;
	T* pResult;
	ReceiveUpdateClass<GeneralIntWrapper<T>> *callbackObject;
	Tfunction startMethod;
	static QueueOfThreads<GeneralIntWrapper<T>> qot;

public:
	bool bRunning;
	bool bFinished;
	int startProcess();
	void setCallback(ReceiveUpdateClass<GeneralIntWrapper<T>>*);
	void setStartMethod(Tfunction newMethod);
	void setID(UINT);
	UINT getID();
	static QueueOfThreads<GeneralIntWrapper<T>>* getQOT();

	T* getResult();
	void setParams(const T& rParam1, const T& rParam2);
};


template <class T>
GeneralIntWrapper<T>::GeneralIntWrapper()
{
	param1 = nullptr;
	param2 = nullptr;
	pResult = nullptr;
	bRunning = false;
	bFinished = false;
}

template <class T>
GeneralIntWrapper<T>::~GeneralIntWrapper()
{
	delete param1;
	delete param2;
}

template <class T>
QueueOfThreads<GeneralIntWrapper<T>> GeneralIntWrapper<T>::qot;

template <class T>
QueueOfThreads<GeneralIntWrapper<T>>* GeneralIntWrapper<T>::getQOT()
{
	return &qot;
}

template <class T>
int GeneralIntWrapper<T>::startProcess()
{
	bRunning = true;

	// This will call any method that takes 2 parameters of type T and a 3rd parameter of bool
	pResult = startMethod(*(param1), *(param2), true);

	bRunning = false;
	// Need a way this can inform QueueOfThreads that it has finished.
	bFinished = true;
	callbackObject->iHaveFinished(id);
	return 0;
}

template <class T>
void GeneralIntWrapper<T>::setCallback(ReceiveUpdateClass<GeneralIntWrapper<T>>* newcallbackObject)
{
	callbackObject = newcallbackObject;
}

template <class T>
void GeneralIntWrapper<T>::setStartMethod(Tfunction newMethod)
{
	startMethod = newMethod;
}

template <class T>
void GeneralIntWrapper<T>::setID(UINT newID)
{
	id = newID;
}

template <class T>
UINT GeneralIntWrapper<T>::getID()
{
	return id;
}

template <class T>
T* GeneralIntWrapper<T>::getResult()
{
	return pResult;
}

template <class T>
void GeneralIntWrapper<T>::setParams(const T& rParam1, const T& rParam2)
{
	// Copy the parameters. This requires that the assignment operator is overloaded to be a deep copy (should be)
	param1 = new T;
	param2 = new T;

	*param1 = rParam1;
	*param2 = rParam2;
}


#ifndef _WIN32
/* Linux includes. Should cover all non-Windows platforms (and Windows, but Windows code was built using Microsoft-specific
   classes, such as CString), but only tested on Ubuntu 16 so far.
   For my reference - the preprocessor definitions for different platforms
   __linux__       Defined on Linux
   __sun           Defined on Solaris
   __FreeBSD__     Defined on FreeBSD
   __NetBSD__      Defined on NetBSD
   __OpenBSD__     Defined on OpenBSD
   __APPLE__       Defined on Mac OS X
   __hpux          Defined on HP-UX
   __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
   __sgi           Defined on Irix
   _AIX            Defined on AIX
   _WIN32          Defined on Windows

   I believe that __linux and linux work on the Linux platform as well.
*/
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <algorithm>
///typedef unsigned char byte; // Didn't realise byte and UINT were Microsoft specific definitions. Added them here for Linux
///typedef unsigned int UINT;
///typedef unsigned long ULONG;
///typedef unsigned long long ULONGLONG;



using std::stringstream;
using std::string;
using std::ifstream;
using std::ios;
#endif

// This definition is to add compatibility with C++11. The code is intended for C++14, but it turns out
// the template below is all that is needed to run under the C++11 standard
#if __cplusplus == 201103L
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&& ... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif

using std::vector;
using std::unique_ptr;
#if __cplusplus != 201103L
using std::make_unique;
#endif
using std::move;

// The class is named below with no implementation so as to avoid a Catch-22 situation with the typedefs
// The typedefs need to be defined using class LongInteger, but class LongInteger needs the typedefs
// So this definition says "I'm going to use a class called LongInteger and I'll fill in the details later on"
class LongInteger;
typedef GeneralIntWrapper<LongInteger> LongIntWrapper; // A shorthand to make it easier to type
typedef unique_ptr<LongInteger> LongIntegerUP; // Ditto
// This for passing a pointer to a function that takes 2 const LongInteger parameters and a bool and returns a pointer to a LongInteger
// The function pointer is referred to as 'Lifunction' in the code
typedef LongInteger* (*LIfunction)(const LongInteger&, const LongInteger&, bool);

// Forward declaration. For some reason I only need to forward declare this one and everything works
bool operator<(int lhs, const LongInteger& rhs);
bool operator<(UINT lhs, const LongInteger& rhs);


#define byte unsigned char
#define ULONG unsigned long
#define ULONGLONG unsigned long long
class LongInteger {
public:
	// Have these listed here (public and at the top of the class) whilst still working on them

	// Still in testing. Performance is weird in release build (improves dramatically at multiples of 350 and then drops
	// rapidly until the next multiple is hit), but works as expected in debug build. Haven't worked out why.
	static LongInteger* ToomCook3(const LongInteger&, const LongInteger&, bool bBackgroundThread = false);

	// This is under development. The code is rather messy as I'm struggling to follow the paper due to the heavy usage of maths
	// terminology I'm unfamiliar with.
	// So far it shows that it is a lot quicker than long division if the divisor is at least half the size (number of digits)
	// of the value. Otherwise it is a lot slower. So working on a framework to adjust the size of the divisor and then
	// adjust the results. Despite being a lot more work it is still quicker. Needs quite a bit of testing
	// to work out the optimal values.
	static void BurnikelZiegler(const LongInteger&, const LongInteger&, LongIntegerUP&, LongIntegerUP&);
	// This is the framework that does the adjustments prior to calling the BurnikelZiegler method
	static bool DivAndMod(const LongInteger&, const LongInteger&, LongIntegerUP&, LongIntegerUP&);
	static bool DivAndMod(const LongInteger&, const LongInteger&, LongInteger&, LongInteger&);


	static LongInteger sqrt(const LongInteger&);
	static LongInteger sqr(const LongInteger&);
	static LongInteger pow(const LongInteger&, const LongInteger&);
	static LongInteger factorial(const LongInteger&);
	static LongInteger log(const LongInteger&);
	static LongInteger log(const LongInteger&, const LongInteger&);
	static LongInteger ln(const LongInteger&);

private:
	// This is the front end to the Karatsuba algorithm which also tidies up any memory allocated
	static LongInteger multiplyChooser(const LongInteger&, const LongInteger&);
	// Restoring division seems to work fine. Some more testing needed to see what the performance is
	static void RestoringDivision(LongInteger&, LongInteger&, LongInteger*, LongInteger*);

	static bool TriedToReadE;

	static LongInteger ReadEFromFile(std::string path);


public: // Make this public during development
		// This is the recursive part of the karatsuba algorithm
	static LongInteger* karatsuba(const LongInteger&, const LongInteger&, bool bBackgroundThread = false);

	// Constants
public:
	static const UINT BASEVAL = 256; // The effective base of the numbers (each digit is 1 byte)
	static const UINT BASEVALBITS = 8; // Size of each digit in bits
	static const UINT BASEVALBITSSHIFT = 3; // If dividing/multiplying by basevalbits, using shifts
	static const byte BASEMAX = 255; // Highest value that can be stored in each digit
	static const UINT ABSMAXSIZE = 4294967295; // Largest number of values that can be stored (index is by uint, so 2^32-1)

	static const UINT MINSIZE = 50;
	static const UINT TINYSIZESTEP = 50;
	static const UINT SMALLSIZESTEP = 1000;
	static const UINT SIZESTEP = 10000; // Internal byte array is increased or decreased in block of this size
										//	static const UINT KARATSUBACUTOFF = 50; // Karatsuba cutoff size. Numbers below this size will use long multiplication
										//	static const UINT TOOMCOOK3CUTOFF = 150; // Testing shows this is the optimal value. Update - 150 is the best in debug builds. In release builds it is not. In release it is all over the place.
										//	static const UINT BURKINELZIEGLERCUTOFF = 50; // 50 seems to work well for the recursion point

										// Making these non-const so I can test different values
	static UINT KARATSUBACUTOFF;
	static UINT TOOMCOOK3CUTOFF;
	static UINT BURKINELZIEGLERCUTOFF;
	// Threading values are now calculated dynamically (after accidentally triggering 20,000 threads) and so are non-const
	static UINT KARATSUBATHREADING;
	static UINT TOOMCOOK3THREADING;

	static LongInteger E; // These aren't const as there will be an attempt to read in a value from file, else use the default.
	static UINT SIZEOFE; // Number of bytes that e has been shifted left by for the value above.

public:
	// For testing only
	void assignByteArray(byte*, UINT);

	// Constructors
	LongInteger();
	LongInteger(const int);
	LongInteger(const UINT);
	LongInteger(const ULONG);
	LongInteger(const ULONGLONG);
	LongInteger(const LongInteger&);
	LongInteger(const double);
	LongInteger(const long double);
	LongInteger(LongInteger*);

	// Add in wstring option as well once this is compiling
	LongInteger(const std::string&);

	~LongInteger();

	// Useful functions
	const UINT getSize() const;

	bool assignNumber(int);
	bool assignNumber(UINT);
	bool assignNumber(ULONG);
	bool assignNumber(ULONGLONG);
	bool assignNumber(double);
	bool assignNumber(long double);

	bool assignNumber(const std::string&);


	byte getDigit(UINT) const;
	bool setDigit(UINT, byte);
	// Split the current LongInt. Send in 2 LongInts to hold the result. Returns false if it fails
	bool split(LongInteger*, LongInteger*, UINT) const;
	// Split 'this' into 3 parts of UINT size and return as an array of LongIntegers
	UINT toomsplit(LongInteger**, UINT) const;



	std::string toDecimal();
	std::string toDecimal() const;
	std::string toHexString() const; // Useful for testing
	std::string toArrayNumbers(); // Also useful for testing

	explicit operator int() const; // Convert to int. Make it explicit to avoid auto casting which will cause confusion
	explicit operator UINT() const;

	// Arithmetic functions
	bool addNumber(int);
	bool addNumber(const LongInteger&);
	bool subtractNumber(int);
	bool subtractNumber(const LongInteger&);
	bool multiplyNumber(int);
	bool multiplyNumber(const LongInteger&);
	bool divideNumber(int);
	bool divideNumber(const LongInteger&);
	bool powerCalc(LongInteger&, const LongInteger&);
	bool powerCalc(const LongInteger&);
	bool powerCalc(int);

	bool arrowCalc(UINT, int);
	bool modulus(const LongInteger&);
	bool factorial();

	// Arithmetic operators
	LongInteger operator+(const LongInteger&) const; // Addition
	LongInteger operator+() const; // Unary plus
	LongInteger operator-(const LongInteger&) const;
	LongInteger operator-() const; // Unary negate
	LongInteger operator*(const LongInteger&) const;
	LongInteger operator/(const LongInteger&) const;
	LongInteger operator%(const LongInteger&) const;

	LongInteger operator+(int) const; // Addition
	LongInteger operator-(int) const;
	LongInteger operator*(int) const;
	LongInteger operator/(int) const;
	LongInteger operator%(int) const;

	LongInteger& operator=(const LongInteger&);
	LongInteger& operator++(); // Prefix increment
	LongInteger operator++(int); // Postfix increment (the int is unused - a placeholder in the syntax)
	LongInteger& operator+=(const LongInteger&); // Adding a LongInteger
	LongInteger& operator+=(int); // Adding an int
	LongInteger& operator--(); // Prefix decrement
	LongInteger operator--(int); // Postfix decrement
	LongInteger& operator-=(const LongInteger&);
	LongInteger& operator-=(int);
	LongInteger& operator*=(const LongInteger&);
	LongInteger& operator*=(int);
	LongInteger& operator/=(const LongInteger&);
	LongInteger& operator/=(int);
	LongInteger& operator%=(const LongInteger&);
	LongInteger& operator%=(int);

	// Bitwise operators
	bool bitwiseand(const LongInteger&);
	LongInteger operator&(const LongInteger&);
	LongInteger operator&(int);
	LongInteger& operator&=(const LongInteger&);
	LongInteger& operator&=(int);

	bool bitwiseor(const LongInteger&);
	LongInteger operator|(const LongInteger&);
	LongInteger operator|(int);
	LongInteger& operator|=(const LongInteger&);
	LongInteger& operator|=(int);

	bool bitwisenot();
	LongInteger operator~() const;

	bool bitwisexor(const LongInteger&);
	LongInteger operator^(const LongInteger&);
	LongInteger operator^(int);
	LongInteger& operator^=(const LongInteger&);
	LongInteger& operator^=(int);

	bool bitshiftright(const LongInteger&);
	bool bitshiftleft(const LongInteger&);
	bool bitshiftright(UINT);
	bool bitshiftleft(UINT);
	LongInteger operator >> (const LongInteger&);
	LongInteger operator >> (UINT);
	LongInteger& operator>>=(const LongInteger&);
	LongInteger& operator>>=(UINT);
	LongInteger operator<<(const LongInteger&);
	LongInteger operator<<(UINT);
	LongInteger& operator<<=(const LongInteger&);
	LongInteger& operator<<=(UINT);

	static LongInteger abs(const LongInteger&);

	bool equalsZero() const;
	bool isProcessing();
	// Commenting these 2 calls out as I need a better way of waiting on completion
	// This was a hack to get the program working properly in Windows
	void setProcessing(bool);
	//    void setProcessing(bool, CWinThread* = nullptr);
	//    HANDLE getProcessingHandle();
	bool isShuttingDown();
	void setShuttingDown(bool);

	inline bool overflow() const {
		return bOverflow;
	}

	bool writeToFile(std::string&);
	bool readFromFile(std::string&);


private:
	byte* digits = nullptr;
	bool bPositive = true;
	UINT maxSize = 0;
	UINT size = 0;
	bool bOverflow = false;
	bool static bShuttingDown;
	bool bProcessing;
	// Commented out at the moment. Not just because it is Windows specific, but
	// because I need a more secure way of waiting on completion
	//    CWinThread *thrProcessingRef = nullptr;

	void init();
	void reset(); // Reset the internal array
	void copy(const LongInteger&);
	void addInternal(byte*, UINT, UINT, UINT);
	void checkSize();
	void recalcMaxSize();
	void recalcMaxSizeAndClear();
	bool increaseSize();
	bool decreaseSize();
	bool increment(); // Helper function for ++
	bool decrement(); // Helper function for --

					  // Helper methods
	bool arrowCalc(const LongInteger&, UINT, LongInteger&);
	bool powerCalcHelper(const LongInteger&, LongInteger&);
	bool divHelper(int);
	bool divByByte(byte);
	bool multHelper(int);
	bool multHelper2(UINT);
	UINT UINTpower(UINT, UINT) const;

	// Helper methods for Burnikel-Ziegler division
	static LongIntegerUP merge(vector<LongIntegerUP>& vList, UINT uNumParts, UINT uSizeParts);
	static vector<LongIntegerUP> DivThreeHalvesByTwo(LongIntegerUP& a1, LongIntegerUP& a2, LongIntegerUP& a3, LongIntegerUP& b1, LongIntegerUP& b2, UINT uNumDigits);
	static vector<LongIntegerUP> DivTwoDigitsByOne(LongIntegerUP& AHigh, LongIntegerUP& ALow, LongIntegerUP& B, UINT uNumDigits);
	// A generic splitting function. Split the input LongInteger into UINT parts of UINT length and return as an array of LongIntegers
	static vector<LongIntegerUP> split(LongIntegerUP&, UINT, UINT);

	LongInteger* pSharedLongInt;

public:
	bool multiplyInternal(const LongInteger&);

	// comparison operators
public:
	inline bool isPositive() const { return bPositive; }

	inline bool operator<(const LongInteger& rhs) const {
		if (bOverflow || rhs.bOverflow) {
			return false;
		}

		if (bPositive != rhs.bPositive) {
			// If this is + and rhs is -, then return -, else return +. So return opposite of bPositive flag
			return !bPositive;
		}

		if (size < rhs.size) {
			return true;
		}
		if (size > rhs.size) {
			return false;
		}

		bool bLessThan = false;
		bool bLoop = true;
		bool bEquals = false;
		// Some amendments as the index is now a UINT and thus we can't go negative
		if (size > 0) {
			UINT index = size - 1;
			while (index > 0 && bLoop) {
				if (digits[index] < rhs.digits[index]) {
					bLessThan = true;
					bLoop = false;
				}
				else if (digits[index] > rhs.digits[index]) {
					bLoop = false;
				}
				--index;
			}
		}
		// Scenario for index = 0 and we haven't finished checking
		if (bLoop) {
			if (digits[0] < rhs.digits[0]) {
				bLessThan = true;
			}
			else if (digits[0] == rhs.digits[0])
			{
				// Added extra test as this was going wrong comparing negative numbers that were equal and returning true
				bEquals = true;
			}
		}

		if (bEquals) {
			return false;
		}
		else {
			return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
		}
	}

	inline bool operator>(const LongInteger& rhs) const {
		return rhs < (*this);
	}

	inline bool operator<=(const LongInteger& rhs) const {
		return !((*this) > rhs);
	}

	inline bool operator<=(int rhs) const {
		return !((*this) > rhs);
	}

	inline bool operator>=(const LongInteger& rhs) const {
		return !((*this) < rhs);
	}

	inline bool operator>=(int rhs) const {
		return !((*this) < rhs);
	}

	inline bool operator==(const LongInteger& rhs) const {
		if (bOverflow || rhs.bOverflow) {
			return false;
		}
		if (size != rhs.size) {
			return false;
		}
		if (bPositive != rhs.bPositive) {
			return false;
		}
		bool bEqual = true;
		// Amendments for using UINT as index instead of int. Can no longer check for less than zero
		// so we have to do this in 2 bits
		if (size > 0) {
			UINT iLoop = size - 1;
			while (iLoop > 0 && bEqual) {
				if (digits[iLoop] != rhs.digits[iLoop])
					bEqual = false;
				--iLoop;
			}
		}
		// Extra bit for the zeroth digit
		if (bEqual) {
			if (digits[0] != rhs.digits[0])
				bEqual = false;
		}
		return bEqual;
	}

	inline bool operator==(int rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1 && bPositive);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(int)) {
			return false;
		}

		bool bEquals = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt += (digits[i] << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == std::abs(rhs))
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator==(UINT rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(UINT)) {
			return false;
		}

		bool bEquals = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt += (digits[i] << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == rhs)
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator==(ULONGLONG rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(ULONGLONG)) {
			return false;
		}

		bool bEquals = false;
		ULONGLONG thisAsInt = digits[0];
		ULONGLONG temp;

		for (UINT i = 1; i < size; i++)
		{
			temp = digits[i];
			thisAsInt += (temp << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == rhs)
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator!=(const LongInteger& rhs) {
		return !((*this) == rhs);
	}

	inline bool operator!=(int rhs) {
		return !((*this) == rhs);
	}

	inline bool operator!=(UINT rhs) {
		return !((*this) == rhs);
	}

	// Add int versions of the comparison operators to avoid the overhead of converting ints to LongIntegers for comparisons.
	inline bool operator<(int rhs) const {
		if (bOverflow) {
			return false;
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			// If this is + and rhs is -, then return -, else return +. So return opposite of bPositive flag
			return !bPositive;
		}
		// Comparison with zero. If both are zero
		if (rhs == 0) {
			if (equalsZero()) {
				return false;
			}
			else {
				return !bPositive;
			}
		}
		else {
			if (equalsZero()) {
				return (rhs > 0);
			}
		}

		if (size > sizeof(int)) {
			return false ^ !bPositive;
		}

		bool bLessThan = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt *= digits[i];
		}

		if (thisAsInt < (UINT)std::abs(rhs))
		{
			bLessThan = true;
		}
		else if (thisAsInt == (UINT)std::abs(rhs))
		{
			return false; // The return value for equal negative numbers was going wrong
		}
		return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
	}

	inline bool operator<(UINT rhs) const {
		if (bOverflow) {
			return false;
		}

		if (!bPositive) {
			// UINTs can only be positive, so if this is negative it is definately less than the UINT
			return true;
		}
		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(int)) {
			return false ^ !bPositive;
		}

		bool bLessThan = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt *= digits[i];
		}

		if (thisAsInt < rhs)
		{
			bLessThan = true;
		}
		return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
	}

	inline bool operator>(int rhs) const
	{
		return rhs < (*this);
	}

	inline bool operator>(UINT rhs) const
	{
		return rhs < (*this);
	}
};


inline bool operator==(int lhs, const LongInteger& rhs) {
	return rhs == lhs;
}

inline bool operator==(UINT lhs, const LongInteger& rhs) {
	return rhs == lhs;
}

inline bool operator!=(int lhs, const LongInteger& rhs) {
	return !(rhs == lhs);
}

inline bool operator!=(UINT lhs, const LongInteger& rhs) {
	return !(rhs == lhs);
}

inline bool operator<(UINT lhs, const LongInteger& rhs) {
	if (rhs.overflow()) {
		return false;
	}

	bool bPositive = rhs.isPositive();

	if (!bPositive) {
		// If rhs is negative it is definately less than lhs as UINTs can't be negative
		return false;
	}
	if (rhs.equalsZero()) {
		if (lhs == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (lhs == 0) {
			return false;
		}
	}

	if (rhs.getSize() > sizeof(int)) {
		return true ^ !bPositive;
	}

	bool bLessThan = false;
	UINT thisAsInt = rhs.getDigit(rhs.getSize() - 1);

	if (rhs.getSize() > 1)
	{
		for (UINT i = rhs.getSize() - 1; i > 0; i--)
		{
			thisAsInt *= LongInteger::BASEVAL;
			thisAsInt += (rhs.getDigit(i - 1));
		}
	}

	if (lhs < thisAsInt)
	{
		bLessThan = true;
	}
	return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
}

inline bool operator<(int lhs, const LongInteger& rhs) {
	if (rhs.overflow()) {
		return false;
	}

	bool bPositive = rhs.isPositive();

	if ((bPositive && lhs < 0) || (!bPositive && lhs >= 0)) {
		// If this is + and rhs is -, then return -, else return +. So return bPositive flag
		return bPositive;
	}
	if (rhs.equalsZero()) {
		if (lhs == 0) {
			return false;
		}
		else {
			return (lhs < 0);
		}
	}
	else {
		if (lhs == 0) {
			return bPositive;
		}
	}

	if (rhs.getSize() > sizeof(int)) {
		return true ^ !bPositive;
	}

	bool bLessThan = false;
	UINT thisAsInt = rhs.getDigit(rhs.getSize() - 1);

	if (rhs.getSize() > 1)
	{
		for (UINT i = rhs.getSize() - 1; i > 0; i--)
		{
			thisAsInt *= LongInteger::BASEVAL;
			thisAsInt += (rhs.getDigit(i - 1));
		}
	}

	if ((UINT)std::abs(lhs) < thisAsInt)
	{
		bLessThan = true;
	}
	else if ((UINT)std::abs(lhs) == thisAsInt)
	{
		return false;
	}
	return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
}


inline bool operator>(int lhs, const LongInteger& rhs) {
	return rhs < lhs;
}

inline bool operator>(UINT lhs, const LongInteger& rhs) {
	return rhs < lhs;
}

inline bool operator>=(int lhs, const LongInteger& rhs) {
	return !(lhs < rhs);
}

inline bool operator>=(UINT lhs, const LongInteger& rhs) {
	return !(lhs < rhs);
}

inline bool operator<=(int lhs, const LongInteger& rhs) {
	return !(lhs > rhs);
}

inline bool operator<=(UINT lhs, const LongInteger& rhs) {
	return !(lhs > rhs);
}

inline LongInteger operator+(int lhs, const LongInteger& rhs) {
	return rhs + lhs;
}

inline LongInteger operator+(UINT lhs, const LongInteger& rhs) {
	return rhs + lhs;
}

inline LongInteger operator-(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value - rhs;
}

inline LongInteger operator-(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value - rhs;
}

inline LongInteger operator*(int lhs, const LongInteger& rhs) {
	return rhs * lhs;
}

inline LongInteger operator*(UINT lhs, const LongInteger& rhs) {
	return rhs * lhs;
}

inline LongInteger operator/(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value / rhs;
}

inline LongInteger operator/(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value / rhs;
}

inline LongInteger operator&(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value & rhs;
}

inline LongInteger operator&(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value & rhs;
}

inline LongInteger operator|(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value | rhs;
}

inline LongInteger operator|(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value | rhs;
}

inline LongInteger operator^(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value ^ rhs;
}

inline LongInteger operator^(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value ^ rhs;
}

inline LongInteger operator >> (int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value >> rhs;
}

inline LongInteger operator >> (UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value >> rhs;
}

#endif


#endif

//////////////////////////////////////////////////////////////////////////

// Based on the code of Roman Pasechnik. The logic has had no changes. I have simply adapted it to work with my LongInteger class
//
// Using a set of LongIntegers instead of a set of ints seems to have worked just fine without any further changes.
//
// The original comments have been left in the code

class UtilityFunctions
{
public:
	static const int bitCount[];

	static LongInteger BitCount(const LongInteger &lin);

	/* Sorting numbers keeps the resulting products more nearly equal in size
	* than would the simpler approach.
	* Nearly equal products are more efficient for the current multiply implementation.
	* Such sorting is more efficient than repeated N?1 multiplies since it forms big multiplies,
	* allowing Karatsuba and higher algorithms to be used. And even below the Karatsuba threshold
	* a big block of work can be more efficient for the base case algorithm. */
	// WD - Above comment is from Roman Pasachnik. I've implemented Karatsuba and ToomCook3 and multithreading for
	// the multiplication. Using multiset seems to give quite good performance, at least relative to the time
	// taken for multiplication. Once the set gets big enough for the updates to be noticeable the set is so
	// big that the multiplication - even with optimisations - is substantial. Nonetheless I'll look at quicker
	// alternatives. Maybe a FIFO queue?
	template<typename _InputIterator>
	static LongInteger SequenceProduct(const _InputIterator& _begin,
		const _InputIterator& _end)
	{
		// First copy collection to sorted container
		LongIntSet sorted;
		for (_InputIterator it = _begin; it != _end; ++it) {
			sorted.insert(*it);
		}

		// Start from smaller numbers
		// Get first and second smallest numbers
		LongIntSet::iterator itFirst = sorted.begin();
		if (itFirst == sorted.end())
			return 0;

		LongIntSet::iterator itSecond = itFirst;
		++itSecond;

		while (itSecond != sorted.end())
		{
			// Multiply them
			LongInteger prod = (*itFirst) * (*itSecond);

			// Remove them from container
			sorted.erase(itFirst);
			sorted.erase(itSecond);

			// Put their product in container
			sorted.insert(prod);

			// And repeat all this stuff
			itFirst = sorted.begin();
			itSecond = itFirst;
			++itSecond;
		}

		// After all of this we have single element in sorted
		// container -- product of all elements of sequence.
		return *itFirst;


		// This implementation may be optimized further, I guess.
		// Maybe using of std::set is not a best choice.
	}

	// The above SequenceProduct method doesn't work if the iterators are part of a Map instead of a Set.
	// The dereference operator doesn't give the value and you need to access the ->second property.
	template<typename _InputIterator>
	static LongInteger SequenceProduct2(const _InputIterator& _begin,
		const _InputIterator& _end)
	{
		// First copy collection to sorted container
		LongIntSet sorted;
		for (auto it = _begin; it != _end; ++it) {
			if (it->second.equalsZero())
				continue;
			sorted.insert(it->second);
		}

		// Start from smaller numbers
		// Get first and second smallest numbers
		LongIntSet::iterator itFirst = sorted.begin();
		if (itFirst == sorted.end())
			return 0;

		LongIntSet::iterator itSecond = itFirst;
		++itSecond;

		while (itSecond != sorted.end())
		{
			// Multiply them
			LongInteger prod = (*itFirst) * (*itSecond);

			// Remove them from container
			sorted.erase(itFirst);
			sorted.erase(itSecond);

			// Put their product in container
			sorted.insert(prod);

			// And repeat all this stuff
			itFirst = sorted.begin();
			itSecond = itFirst;
			++itSecond;
		}

		// After all of this we have single element in sorted
		// container -- product of all elements of sequence.
		return *itFirst;
	}


};

#endif


#ifdef _WIN32

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

///#include <afxwin.h>         // MFC core and standard components
///#include <afxext.h>         // MFC extensions


///#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
///#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
///#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

///#include <afxcontrolbars.h>     // MFC support for ribbons and control bars









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



#endif
/*
* LongInteger.h
*
* Header for LongInteger class. Can handle positive integers up to 4 billion digits in length.
* It holds the number as a byte array and indexes it using an uint (hence the size limit)
* Addition, subtraction, multiplication and division and powers are handled.
* Standard operators - +,-,*,/,+=,-=,/=,*=,<,>,<=,>=,!=,== are handled
* The = operator is overriden to provide copy by value instead of the default copy by reference
* It is also overloaded, so that strings and ints can be assigned to a LongInteger
*
* The karatsuba algorithm is used to multiply large numbers. It is more complex than long multiplication,
* but the number of steps needed doesn't increase as rapidly as the number length increases.
* The karatsuba algorithm is only accessed via the multiplyNumber method
*
* ToomCook3 algorithm has been added for multiplying even larger numbers. The implementation looks rather complex, so
* there may well be inefficiencies. Performance is odd, which convinces me all is not correct
*
* Burnikel-Ziegler algorithm for division has been implemented. It ended up with much more code than expected
* and also handles scenarios that aren't mentioned at all in Burnikel and Ziegler's paper, so that isn't a good sign.
* It works and divides numbers faster than the division algorithm I implemented for large numbers, where the divisor
* is at least half the size of the value being divided.
*
*
* The compiler needs to support C++14 to get this code to work.
* Visual Studio 2015 Community Edition supports this without any amendments needed.
*
* I got NetBeans to compile this code by going into
* Project Properties - C++ Compiler - Additional options - and added '-std=c++14 -pthread'. The -pthread is to
* add multithreading support otherwise NetBeans gets very confused.
*
* Managed to get Eclipse to compile the code as well, although I cannot get the IDE to recognise C++14 code
* It insists there are errors, but hit compile and it builds fine. It will also debug and step through the code
* without issues, but still with warnings about unrecognised code all over the place.
*
* Unique Pointers are used because the memory management was getting out of hand and was becoming a real mess.
* Where it is manageable I've kept using simple points to reduce overheads.
*
*/

#pragma once

#ifndef _LONGINTEGER_H
#define _LONGINTEGER_H

#include <vector>
#include <memory>
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
#pragma once

// Interface class to define common messages the subclasses can receive

template<class T>
class ReceiveUpdateClass
{
public:
	// If I make the constructor virtual Visual Studio refuses to compile. Dunno why. GCC has no issues.
	ReceiveUpdateClass();
	// Virtual destructor needed so I can assign a subclass to a ReceiveUpdateClass pointer and not get memory leaks
	// if delete is called on that pointer
	virtual ~ReceiveUpdateClass();

	virtual void iHaveFinished(unsigned int) = 0;
	virtual void iAmWaiting() = 0;
	virtual void iHaveStoppedWaiting() = 0;
	
};

template <class T>
ReceiveUpdateClass<T>::ReceiveUpdateClass()
{
}

template <class T>
ReceiveUpdateClass<T>::~ReceiveUpdateClass()
{
}


#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

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
/*
Implementation of the QueueOfThreads template
Managed to work out how to move it into a separate file
The .h file includes this file at the end. All seems to work just fine.
*/

#include <thread>
#include <fstream>

template <class T>
QueueOfThreads<T>::QueueOfThreads() {
	threadsRunning = 0;
	threadsWaiting = 0;
	threadID = 0;
	//	deviceCores = std::thread::hardware_concurrency();

	deviceCores = 4;
	if (deviceCores < minThreads) {
		maxThreads = minThreads; // Default value
	}
	else {
		maxThreads = deviceCores;
	}

}

template <class T>
QueueOfThreads<T>::~QueueOfThreads() {
	// Can't exit whilst threads are running.
	// Set the shutting down flag (all should have a reference to that - use an interface)
	// and wait for them to finish

}

template <class T>
void QueueOfThreads<T>::decreaseCount(UINT id) {
	try {
		unique_lock<mutex> lock(myMutex);
		// Find out which thread has finished and remove it from the list
		UINT index = 0;
		bool bFound = false;

		while (!bFound && index < queueOfRunningThreads.size()) {
			if (queueOfRunningThreads[index] == id) {
				bFound = true;
			}
			else {
				index++;
			}
		}

		if (!bFound) {
			abort();
		}

		queueOfRunningThreads.erase(queueOfRunningThreads.begin() + index);

		threadsRunning--;
		lock.unlock();
		myConditionVariable.notify_all();

	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}

}

template <class T>
bool QueueOfThreads<T>::addToQueue(T* newLongInt) {
	try {

		unique_lock<mutex> lock(myMutex);

		newLongInt->setID(threadID);
		queueOfWaitingThreads.push_back(newLongInt);

		threadID++;
		threadsWaiting++;
		newLongInt->setCallback(this);

		// I was using a lambda and it was working fine, but this format of thread starting
		// matches up to the other one.
		// Starting a thread to start a thread may seem weird, but this functionality is just a placeholder
		std::thread t1(&QueueOfThreads<T>::startAThread, this);

		t1.detach();
		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}
	return true;
}

template <class T>
void QueueOfThreads<T>::startAThread() {
	if (threadsWaiting == 0) {
		return;
	}
	try {
		unique_lock<std::mutex> lock(myMutex);
		// The wait will unlock and then try to reacquire the lock when it wakes up
		myConditionVariable.wait(lock, [this]() {
			return threadsRunning < maxThreads; });


		// Insert code to start a thread
		if (queueOfWaitingThreads.size() == 0) {
			abort();
		}


		T* tempLIW = queueOfWaitingThreads[0];
		queueOfWaitingThreads.erase(queueOfWaitingThreads.begin());
		queueOfRunningThreads.push_back(tempLIW->getID());
		threadsRunning++;
		threadsWaiting--;


		//	CString strOutput;
		//	strOutput.Format(L"Thread ID %d - Starting \n", tempLIW->getID());
		//	logwithoutlock(strOutput);


		// This format of call seems to have fixed the issues with access violation. Let's hope it
		// keeps on working.
		std::thread t1(&T::startProcess, tempLIW);

		t1.detach();

		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
}

template <class T>
UINT QueueOfThreads<T>::numOfThreads() {
	// For testing
	unique_lock<mutex> lock(myMutex);
	return threadsRunning + threadsWaiting;
	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::iHaveFinished(UINT id) {
	decreaseCount(id);
#ifdef __linux__
	// Linux test code
	std::cout << "Thread " << id << " finished. Threads waiting&running " << threadsWaiting << "," << threadsRunning << std::endl;
#endif
}

template <class T>
void QueueOfThreads<T>::iAmWaiting() {
	if (threadsRunning == 0) abort(); // Test code

									  // The current thread is waiting on something, so let the queue know that other threads can be started
	unique_lock<mutex> lock(myMutex);

	threadsRunning--;
	threadsWaiting++;

	// Although the lock will release when it goes out of scope, I need to unlock it before calling notify
	lock.unlock();
	myConditionVariable.notify_all();

}

template <class T>
void QueueOfThreads<T>::iHaveStoppedWaiting() {
	if (threadsWaiting == 0) abort(); // Test code

	unique_lock<mutex> lock(myMutex);
	myConditionVariable.wait(lock, [this]() {
		return threadsRunning < maxThreads; });

	threadsRunning++;
	threadsWaiting--;

	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::waitForThread(T* pLIW) {
	unique_lock<mutex> lock(myMutex);

	myConditionVariable.wait(lock, [pLIW]() {
		return pLIW->bFinished; });

	lock.unlock();
	myConditionVariable.notify_all();

}


template <class T>
void QueueOfThreads<T>::logwithoutlock(std::string logString) {
	// Called if a lock has already been established

	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
}



template <class T>
void QueueOfThreads<T>::logwithlock(std::string logString) {
	unique_lock<mutex> lock(myMutex);
	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
	lock.unlock();
	myConditionVariable.notify_all();
}



template <class T>
void QueueOfThreads<T>::setNumThreads(UINT numThreads) {
	maxThreads = numThreads;
}

template <class T>
UINT QueueOfThreads<T>::getDeviceCores() {
	return deviceCores;
}


/*
GeneralIntWrapper.h

This class is a wrapper to LongInteger although it can also wrap other items. It allows LongIntegers to be sent
to QueueOfThreads and then collects the results of processing to be picked up by the caller.
It has been created to separate LongInteger and QueueOfThreads

At the moment it just calls the karatsuba algorithm. Will need to be amended to allow for calling any mr.
*/

#pragma once

#ifndef _WIN32
typedef unsigned int UINT;
#endif

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
#pragma once

// Interface class to define common messages the subclasses can receive

template<class T>
class ReceiveUpdateClass
{
public:
	// If I make the constructor virtual Visual Studio refuses to compile. Dunno why. GCC has no issues.
	ReceiveUpdateClass();
	// Virtual destructor needed so I can assign a subclass to a ReceiveUpdateClass pointer and not get memory leaks
	// if delete is called on that pointer
	virtual ~ReceiveUpdateClass();

	virtual void iHaveFinished(unsigned int) = 0;
	virtual void iAmWaiting() = 0;
	virtual void iHaveStoppedWaiting() = 0;
	
};

template <class T>
ReceiveUpdateClass<T>::ReceiveUpdateClass()
{
}

template <class T>
ReceiveUpdateClass<T>::~ReceiveUpdateClass()
{
}


#ifndef _WIN32
#include <string>
#include <fstream>
using std::string;
using std::ofstream;
///typedef unsigned int UINT;



#endif


/*
#pragma once

#ifndef _MYHARDWAREINFO_H_
#define _MYHARDWAREINFO_H_

#ifdef _WIN32
typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
#elif MACOS
// This was taken from stackexchange. I don't have access to a MAC so no idea if this works
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#include <thread>
#endif


class MyHardwareInfo
{
public:
	MyHardwareInfo();
	~MyHardwareInfo();

	int GetCPUCount();
	int GetPhysicalCores();
	int GetLogicalCores();
private:

	int mCPUs;
	int mPhysicalCores;
	int mLogicalCores;

	int init();
#ifdef _WIN32
	DWORD CountSetBits(ULONG_PTR bitMask);
#endif
};

#endif

*/

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
/*
Implementation of the QueueOfThreads template
Managed to work out how to move it into a separate file
The .h file includes this file at the end. All seems to work just fine.
*/

#include <thread>
#include <fstream>

template <class T>
QueueOfThreads<T>::QueueOfThreads() {
	threadsRunning = 0;
	threadsWaiting = 0;
	threadID = 0;
	//	deviceCores = std::thread::hardware_concurrency();

	deviceCores = 4;
	if (deviceCores < minThreads) {
		maxThreads = minThreads; // Default value
	}
	else {
		maxThreads = deviceCores;
	}

}

template <class T>
QueueOfThreads<T>::~QueueOfThreads() {
	// Can't exit whilst threads are running.
	// Set the shutting down flag (all should have a reference to that - use an interface)
	// and wait for them to finish

}

template <class T>
void QueueOfThreads<T>::decreaseCount(UINT id) {
	try {
		unique_lock<mutex> lock(myMutex);
		// Find out which thread has finished and remove it from the list
		UINT index = 0;
		bool bFound = false;

		while (!bFound && index < queueOfRunningThreads.size()) {
			if (queueOfRunningThreads[index] == id) {
				bFound = true;
			}
			else {
				index++;
			}
		}

		if (!bFound) {
			abort();
		}

		queueOfRunningThreads.erase(queueOfRunningThreads.begin() + index);

		threadsRunning--;
		lock.unlock();
		myConditionVariable.notify_all();

	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}

}

template <class T>
bool QueueOfThreads<T>::addToQueue(T* newLongInt) {
	try {

		unique_lock<mutex> lock(myMutex);

		newLongInt->setID(threadID);
		queueOfWaitingThreads.push_back(newLongInt);

		threadID++;
		threadsWaiting++;
		newLongInt->setCallback(this);

		// I was using a lambda and it was working fine, but this format of thread starting
		// matches up to the other one.
		// Starting a thread to start a thread may seem weird, but this functionality is just a placeholder
		std::thread t1(&QueueOfThreads<T>::startAThread, this);

		t1.detach();
		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
	catch (...) {

		std::string fred("Dunno what happened");

	}
	return true;
}

template <class T>
void QueueOfThreads<T>::startAThread() {
	if (threadsWaiting == 0) {
		return;
	}
	try {
		unique_lock<std::mutex> lock(myMutex);
		// The wait will unlock and then try to reacquire the lock when it wakes up
		myConditionVariable.wait(lock, [this]() {
			return threadsRunning < maxThreads; });


		// Insert code to start a thread
		if (queueOfWaitingThreads.size() == 0) {
			abort();
		}


		T* tempLIW = queueOfWaitingThreads[0];
		queueOfWaitingThreads.erase(queueOfWaitingThreads.begin());
		queueOfRunningThreads.push_back(tempLIW->getID());
		threadsRunning++;
		threadsWaiting--;


		//	CString strOutput;
		//	strOutput.Format(L"Thread ID %d - Starting \n", tempLIW->getID());
		//	logwithoutlock(strOutput);


		// This format of call seems to have fixed the issues with access violation. Let's hope it
		// keeps on working.
		std::thread t1(&T::startProcess, tempLIW);

		t1.detach();

		lock.unlock();
		myConditionVariable.notify_all();
	}
	catch (std::exception e) {

		std::string fred(e.what());

	}
}

template <class T>
UINT QueueOfThreads<T>::numOfThreads() {
	// For testing
	unique_lock<mutex> lock(myMutex);
	return threadsRunning + threadsWaiting;
	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::iHaveFinished(UINT id) {
	decreaseCount(id);
#ifdef __linux__
	// Linux test code
	std::cout << "Thread " << id << " finished. Threads waiting&running " << threadsWaiting << "," << threadsRunning << std::endl;
#endif
}

template <class T>
void QueueOfThreads<T>::iAmWaiting() {
	if (threadsRunning == 0) abort(); // Test code

									  // The current thread is waiting on something, so let the queue know that other threads can be started
	unique_lock<mutex> lock(myMutex);

	threadsRunning--;
	threadsWaiting++;

	// Although the lock will release when it goes out of scope, I need to unlock it before calling notify
	lock.unlock();
	myConditionVariable.notify_all();

}

template <class T>
void QueueOfThreads<T>::iHaveStoppedWaiting() {
	if (threadsWaiting == 0) abort(); // Test code

	unique_lock<mutex> lock(myMutex);
	myConditionVariable.wait(lock, [this]() {
		return threadsRunning < maxThreads; });

	threadsRunning++;
	threadsWaiting--;

	lock.unlock();
	myConditionVariable.notify_all();
}

template <class T>
void QueueOfThreads<T>::waitForThread(T* pLIW) {
	unique_lock<mutex> lock(myMutex);

	myConditionVariable.wait(lock, [pLIW]() {
		return pLIW->bFinished; });

	lock.unlock();
	myConditionVariable.notify_all();

}


template <class T>
void QueueOfThreads<T>::logwithoutlock(std::string logString) {
	// Called if a lock has already been established

	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
}



template <class T>
void QueueOfThreads<T>::logwithlock(std::string logString) {
	unique_lock<mutex> lock(myMutex);
	std::ofstream ffiillee;
	ffiillee.open("~/Desktop/threads.txt", std::ofstream::out | std::ofstream::ate | std::ofstream::app);
	if (ffiillee)
	{
		ffiillee << logString;
		ffiillee.close();
	}
	lock.unlock();
	myConditionVariable.notify_all();
}



template <class T>
void QueueOfThreads<T>::setNumThreads(UINT numThreads) {
	maxThreads = numThreads;
}

template <class T>
UINT QueueOfThreads<T>::getDeviceCores() {
	return deviceCores;
}





template<class T> class GeneralIntWrapper
{
public:
	GeneralIntWrapper();
	~GeneralIntWrapper();

	typedef T* (*Tfunction)(const T&, const T&, bool);

private:
	UINT id;
	T* param1;
	T* param2;
	T* pResult;
	ReceiveUpdateClass<GeneralIntWrapper<T>> *callbackObject;
	Tfunction startMethod;
	static QueueOfThreads<GeneralIntWrapper<T>> qot;

public:
	bool bRunning;
	bool bFinished;
	int startProcess();
	void setCallback(ReceiveUpdateClass<GeneralIntWrapper<T>>*);
	void setStartMethod(Tfunction newMethod);
	void setID(UINT);
	UINT getID();
	static QueueOfThreads<GeneralIntWrapper<T>>* getQOT();

	T* getResult();
	void setParams(const T& rParam1, const T& rParam2);
};


template <class T>
GeneralIntWrapper<T>::GeneralIntWrapper()
{
	param1 = nullptr;
	param2 = nullptr;
	pResult = nullptr;
	bRunning = false;
	bFinished = false;
}

template <class T>
GeneralIntWrapper<T>::~GeneralIntWrapper()
{
	delete param1;
	delete param2;
}

template <class T>
QueueOfThreads<GeneralIntWrapper<T>> GeneralIntWrapper<T>::qot;

template <class T>
QueueOfThreads<GeneralIntWrapper<T>>* GeneralIntWrapper<T>::getQOT()
{
	return &qot;
}

template <class T>
int GeneralIntWrapper<T>::startProcess()
{
	bRunning = true;

	// This will call any method that takes 2 parameters of type T and a 3rd parameter of bool
	pResult = startMethod(*(param1), *(param2), true);

	bRunning = false;
	// Need a way this can inform QueueOfThreads that it has finished.
	bFinished = true;
	callbackObject->iHaveFinished(id);
	return 0;
}

template <class T>
void GeneralIntWrapper<T>::setCallback(ReceiveUpdateClass<GeneralIntWrapper<T>>* newcallbackObject)
{
	callbackObject = newcallbackObject;
}

template <class T>
void GeneralIntWrapper<T>::setStartMethod(Tfunction newMethod)
{
	startMethod = newMethod;
}

template <class T>
void GeneralIntWrapper<T>::setID(UINT newID)
{
	id = newID;
}

template <class T>
UINT GeneralIntWrapper<T>::getID()
{
	return id;
}

template <class T>
T* GeneralIntWrapper<T>::getResult()
{
	return pResult;
}

template <class T>
void GeneralIntWrapper<T>::setParams(const T& rParam1, const T& rParam2)
{
	// Copy the parameters. This requires that the assignment operator is overloaded to be a deep copy (should be)
	param1 = new T;
	param2 = new T;

	*param1 = rParam1;
	*param2 = rParam2;
}


#ifndef _WIN32
/* Linux includes. Should cover all non-Windows platforms (and Windows, but Windows code was built using Microsoft-specific
   classes, such as CString), but only tested on Ubuntu 16 so far.
   For my reference - the preprocessor definitions for different platforms
   __linux__       Defined on Linux
   __sun           Defined on Solaris
   __FreeBSD__     Defined on FreeBSD
   __NetBSD__      Defined on NetBSD
   __OpenBSD__     Defined on OpenBSD
   __APPLE__       Defined on Mac OS X
   __hpux          Defined on HP-UX
   __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
   __sgi           Defined on Irix
   _AIX            Defined on AIX
   _WIN32          Defined on Windows

   I believe that __linux and linux work on the Linux platform as well.
*/
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <algorithm>
///typedef unsigned char byte; // Didn't realise byte and UINT were Microsoft specific definitions. Added them here for Linux
///typedef unsigned int UINT;
///typedef unsigned long ULONG;
///typedef unsigned long long ULONGLONG;



using std::stringstream;
using std::string;
using std::ifstream;
using std::ios;
#endif

// This definition is to add compatibility with C++11. The code is intended for C++14, but it turns out
// the template below is all that is needed to run under the C++11 standard
#if __cplusplus == 201103L
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&& ... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif

using std::vector;
using std::unique_ptr;
#if __cplusplus != 201103L
using std::make_unique;
#endif
using std::move;

// The class is named below with no implementation so as to avoid a Catch-22 situation with the typedefs
// The typedefs need to be defined using class LongInteger, but class LongInteger needs the typedefs
// So this definition says "I'm going to use a class called LongInteger and I'll fill in the details later on"
class LongInteger;
typedef GeneralIntWrapper<LongInteger> LongIntWrapper; // A shorthand to make it easier to type
typedef unique_ptr<LongInteger> LongIntegerUP; // Ditto
// This for passing a pointer to a function that takes 2 const LongInteger parameters and a bool and returns a pointer to a LongInteger
// The function pointer is referred to as 'Lifunction' in the code
typedef LongInteger* (*LIfunction)(const LongInteger&, const LongInteger&, bool);

// Forward declaration. For some reason I only need to forward declare this one and everything works
bool operator<(int lhs, const LongInteger& rhs);
bool operator<(UINT lhs, const LongInteger& rhs);


#define byte unsigned char
#define ULONG unsigned long
#define ULONGLONG unsigned long long
class LongInteger {
public:
	// Have these listed here (public and at the top of the class) whilst still working on them

	// Still in testing. Performance is weird in release build (improves dramatically at multiples of 350 and then drops
	// rapidly until the next multiple is hit), but works as expected in debug build. Haven't worked out why.
	static LongInteger* ToomCook3(const LongInteger&, const LongInteger&, bool bBackgroundThread = false);

	// This is under development. The code is rather messy as I'm struggling to follow the paper due to the heavy usage of maths
	// terminology I'm unfamiliar with.
	// So far it shows that it is a lot quicker than long division if the divisor is at least half the size (number of digits)
	// of the value. Otherwise it is a lot slower. So working on a framework to adjust the size of the divisor and then
	// adjust the results. Despite being a lot more work it is still quicker. Needs quite a bit of testing
	// to work out the optimal values.
	static void BurnikelZiegler(const LongInteger&, const LongInteger&, LongIntegerUP&, LongIntegerUP&);
	// This is the framework that does the adjustments prior to calling the BurnikelZiegler method
	static bool DivAndMod(const LongInteger&, const LongInteger&, LongIntegerUP&, LongIntegerUP&);
	static bool DivAndMod(const LongInteger&, const LongInteger&, LongInteger&, LongInteger&);


	static LongInteger sqrt(const LongInteger&);
	static LongInteger sqr(const LongInteger&);
	static LongInteger pow(const LongInteger&, const LongInteger&);
	static LongInteger factorial(const LongInteger&);
	static LongInteger log(const LongInteger&);
	static LongInteger log(const LongInteger&, const LongInteger&);
	static LongInteger ln(const LongInteger&);

private:
	// This is the front end to the Karatsuba algorithm which also tidies up any memory allocated
	static LongInteger multiplyChooser(const LongInteger&, const LongInteger&);
	// Restoring division seems to work fine. Some more testing needed to see what the performance is
	static void RestoringDivision(LongInteger&, LongInteger&, LongInteger*, LongInteger*);

	static bool TriedToReadE;

	static LongInteger ReadEFromFile(std::string path);


public: // Make this public during development
		// This is the recursive part of the karatsuba algorithm
	static LongInteger* karatsuba(const LongInteger&, const LongInteger&, bool bBackgroundThread = false);

	// Constants
public:
	static const UINT BASEVAL = 256; // The effective base of the numbers (each digit is 1 byte)
	static const UINT BASEVALBITS = 8; // Size of each digit in bits
	static const UINT BASEVALBITSSHIFT = 3; // If dividing/multiplying by basevalbits, using shifts
	static const byte BASEMAX = 255; // Highest value that can be stored in each digit
	static const UINT ABSMAXSIZE = 4294967295; // Largest number of values that can be stored (index is by uint, so 2^32-1)

	static const UINT MINSIZE = 50;
	static const UINT TINYSIZESTEP = 50;
	static const UINT SMALLSIZESTEP = 1000;
	static const UINT SIZESTEP = 10000; // Internal byte array is increased or decreased in block of this size
										//	static const UINT KARATSUBACUTOFF = 50; // Karatsuba cutoff size. Numbers below this size will use long multiplication
										//	static const UINT TOOMCOOK3CUTOFF = 150; // Testing shows this is the optimal value. Update - 150 is the best in debug builds. In release builds it is not. In release it is all over the place.
										//	static const UINT BURKINELZIEGLERCUTOFF = 50; // 50 seems to work well for the recursion point

										// Making these non-const so I can test different values
	static UINT KARATSUBACUTOFF;
	static UINT TOOMCOOK3CUTOFF;
	static UINT BURKINELZIEGLERCUTOFF;
	// Threading values are now calculated dynamically (after accidentally triggering 20,000 threads) and so are non-const
	static UINT KARATSUBATHREADING;
	static UINT TOOMCOOK3THREADING;

	static LongInteger E; // These aren't const as there will be an attempt to read in a value from file, else use the default.
	static UINT SIZEOFE; // Number of bytes that e has been shifted left by for the value above.

public:
	// For testing only
	void assignByteArray(byte*, UINT);

	// Constructors
	LongInteger();
	LongInteger(const int);
	LongInteger(const UINT);
	LongInteger(const ULONG);
	LongInteger(const ULONGLONG);
	LongInteger(const LongInteger&);
	LongInteger(const double);
	LongInteger(const long double);
	LongInteger(LongInteger*);

	// Add in wstring option as well once this is compiling
	LongInteger(const std::string&);

	~LongInteger();

	// Useful functions
	const UINT getSize() const;

	bool assignNumber(int);
	bool assignNumber(UINT);
	bool assignNumber(ULONG);
	bool assignNumber(ULONGLONG);
	bool assignNumber(double);
	bool assignNumber(long double);

	bool assignNumber(const std::string&);


	byte getDigit(UINT) const;
	bool setDigit(UINT, byte);
	// Split the current LongInt. Send in 2 LongInts to hold the result. Returns false if it fails
	bool split(LongInteger*, LongInteger*, UINT) const;
	// Split 'this' into 3 parts of UINT size and return as an array of LongIntegers
	UINT toomsplit(LongInteger**, UINT) const;



	std::string toDecimal();
	std::string toDecimal() const;
	std::string toHexString() const; // Useful for testing
	std::string toArrayNumbers(); // Also useful for testing

	explicit operator int() const; // Convert to int. Make it explicit to avoid auto casting which will cause confusion
	explicit operator UINT() const;

	// Arithmetic functions
	bool addNumber(int);
	bool addNumber(const LongInteger&);
	bool subtractNumber(int);
	bool subtractNumber(const LongInteger&);
	bool multiplyNumber(int);
	bool multiplyNumber(const LongInteger&);
	bool divideNumber(int);
	bool divideNumber(const LongInteger&);
	bool powerCalc(LongInteger&, const LongInteger&);
	bool powerCalc(const LongInteger&);
	bool powerCalc(int);

	bool arrowCalc(UINT, int);
	bool modulus(const LongInteger&);
	bool factorial();

	// Arithmetic operators
	LongInteger operator+(const LongInteger&) const; // Addition
	LongInteger operator+() const; // Unary plus
	LongInteger operator-(const LongInteger&) const;
	LongInteger operator-() const; // Unary negate
	LongInteger operator*(const LongInteger&) const;
	LongInteger operator/(const LongInteger&) const;
	LongInteger operator%(const LongInteger&) const;

	LongInteger operator+(int) const; // Addition
	LongInteger operator-(int) const;
	LongInteger operator*(int) const;
	LongInteger operator/(int) const;
	LongInteger operator%(int) const;

	LongInteger& operator=(const LongInteger&);
	LongInteger& operator++(); // Prefix increment
	LongInteger operator++(int); // Postfix increment (the int is unused - a placeholder in the syntax)
	LongInteger& operator+=(const LongInteger&); // Adding a LongInteger
	LongInteger& operator+=(int); // Adding an int
	LongInteger& operator--(); // Prefix decrement
	LongInteger operator--(int); // Postfix decrement
	LongInteger& operator-=(const LongInteger&);
	LongInteger& operator-=(int);
	LongInteger& operator*=(const LongInteger&);
	LongInteger& operator*=(int);
	LongInteger& operator/=(const LongInteger&);
	LongInteger& operator/=(int);
	LongInteger& operator%=(const LongInteger&);
	LongInteger& operator%=(int);

	// Bitwise operators
	bool bitwiseand(const LongInteger&);
	LongInteger operator&(const LongInteger&);
	LongInteger operator&(int);
	LongInteger& operator&=(const LongInteger&);
	LongInteger& operator&=(int);

	bool bitwiseor(const LongInteger&);
	LongInteger operator|(const LongInteger&);
	LongInteger operator|(int);
	LongInteger& operator|=(const LongInteger&);
	LongInteger& operator|=(int);

	bool bitwisenot();
	LongInteger operator~() const;

	bool bitwisexor(const LongInteger&);
	LongInteger operator^(const LongInteger&);
	LongInteger operator^(int);
	LongInteger& operator^=(const LongInteger&);
	LongInteger& operator^=(int);

	bool bitshiftright(const LongInteger&);
	bool bitshiftleft(const LongInteger&);
	bool bitshiftright(UINT);
	bool bitshiftleft(UINT);
	LongInteger operator >> (const LongInteger&);
	LongInteger operator >> (UINT);
	LongInteger& operator>>=(const LongInteger&);
	LongInteger& operator>>=(UINT);
	LongInteger operator<<(const LongInteger&);
	LongInteger operator<<(UINT);
	LongInteger& operator<<=(const LongInteger&);
	LongInteger& operator<<=(UINT);

	static LongInteger abs(const LongInteger&);

	bool equalsZero() const;
	bool isProcessing();
	// Commenting these 2 calls out as I need a better way of waiting on completion
	// This was a hack to get the program working properly in Windows
	void setProcessing(bool);
	//    void setProcessing(bool, CWinThread* = nullptr);
	//    HANDLE getProcessingHandle();
	bool isShuttingDown();
	void setShuttingDown(bool);

	inline bool overflow() const {
		return bOverflow;
	}

	bool writeToFile(std::string&);
	bool readFromFile(std::string&);


private:
	byte* digits = nullptr;
	bool bPositive = true;
	UINT maxSize = 0;
	UINT size = 0;
	bool bOverflow = false;
	bool static bShuttingDown;
	bool bProcessing;
	// Commented out at the moment. Not just because it is Windows specific, but
	// because I need a more secure way of waiting on completion
	//    CWinThread *thrProcessingRef = nullptr;

	void init();
	void reset(); // Reset the internal array
	void copy(const LongInteger&);
	void addInternal(byte*, UINT, UINT, UINT);
	void checkSize();
	void recalcMaxSize();
	void recalcMaxSizeAndClear();
	bool increaseSize();
	bool decreaseSize();
	bool increment(); // Helper function for ++
	bool decrement(); // Helper function for --

					  // Helper methods
	bool arrowCalc(const LongInteger&, UINT, LongInteger&);
	bool powerCalcHelper(const LongInteger&, LongInteger&);
	bool divHelper(int);
	bool divByByte(byte);
	bool multHelper(int);
	bool multHelper2(UINT);
	UINT UINTpower(UINT, UINT) const;

	// Helper methods for Burnikel-Ziegler division
	static LongIntegerUP merge(vector<LongIntegerUP>& vList, UINT uNumParts, UINT uSizeParts);
	static vector<LongIntegerUP> DivThreeHalvesByTwo(LongIntegerUP& a1, LongIntegerUP& a2, LongIntegerUP& a3, LongIntegerUP& b1, LongIntegerUP& b2, UINT uNumDigits);
	static vector<LongIntegerUP> DivTwoDigitsByOne(LongIntegerUP& AHigh, LongIntegerUP& ALow, LongIntegerUP& B, UINT uNumDigits);
	// A generic splitting function. Split the input LongInteger into UINT parts of UINT length and return as an array of LongIntegers
	static vector<LongIntegerUP> split(LongIntegerUP&, UINT, UINT);

	LongInteger* pSharedLongInt;

public:
	bool multiplyInternal(const LongInteger&);

	// comparison operators
public:
	inline bool isPositive() const { return bPositive; }

	inline bool operator<(const LongInteger& rhs) const {
		if (bOverflow || rhs.bOverflow) {
			return false;
		}

		if (bPositive != rhs.bPositive) {
			// If this is + and rhs is -, then return -, else return +. So return opposite of bPositive flag
			return !bPositive;
		}

		if (size < rhs.size) {
			return true;
		}
		if (size > rhs.size) {
			return false;
		}

		bool bLessThan = false;
		bool bLoop = true;
		bool bEquals = false;
		// Some amendments as the index is now a UINT and thus we can't go negative
		if (size > 0) {
			UINT index = size - 1;
			while (index > 0 && bLoop) {
				if (digits[index] < rhs.digits[index]) {
					bLessThan = true;
					bLoop = false;
				}
				else if (digits[index] > rhs.digits[index]) {
					bLoop = false;
				}
				--index;
			}
		}
		// Scenario for index = 0 and we haven't finished checking
		if (bLoop) {
			if (digits[0] < rhs.digits[0]) {
				bLessThan = true;
			}
			else if (digits[0] == rhs.digits[0])
			{
				// Added extra test as this was going wrong comparing negative numbers that were equal and returning true
				bEquals = true;
			}
		}

		if (bEquals) {
			return false;
		}
		else {
			return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
		}
	}

	inline bool operator>(const LongInteger& rhs) const {
		return rhs < (*this);
	}

	inline bool operator<=(const LongInteger& rhs) const {
		return !((*this) > rhs);
	}

	inline bool operator<=(int rhs) const {
		return !((*this) > rhs);
	}

	inline bool operator>=(const LongInteger& rhs) const {
		return !((*this) < rhs);
	}

	inline bool operator>=(int rhs) const {
		return !((*this) < rhs);
	}

	inline bool operator==(const LongInteger& rhs) const {
		if (bOverflow || rhs.bOverflow) {
			return false;
		}
		if (size != rhs.size) {
			return false;
		}
		if (bPositive != rhs.bPositive) {
			return false;
		}
		bool bEqual = true;
		// Amendments for using UINT as index instead of int. Can no longer check for less than zero
		// so we have to do this in 2 bits
		if (size > 0) {
			UINT iLoop = size - 1;
			while (iLoop > 0 && bEqual) {
				if (digits[iLoop] != rhs.digits[iLoop])
					bEqual = false;
				--iLoop;
			}
		}
		// Extra bit for the zeroth digit
		if (bEqual) {
			if (digits[0] != rhs.digits[0])
				bEqual = false;
		}
		return bEqual;
	}

	inline bool operator==(int rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1 && bPositive);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(int)) {
			return false;
		}

		bool bEquals = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt += (digits[i] << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == std::abs(rhs))
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator==(UINT rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(UINT)) {
			return false;
		}

		bool bEquals = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt += (digits[i] << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == rhs)
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator==(ULONGLONG rhs) const {
		if (rhs == 0) {
			return equalsZero();
		}
		// There are enough comparisons to 1 to justify a dedicated short-cut test
		if (rhs == 1) {
			return(size == 1 && digits[0] == 1);
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			return false;
		}

		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(ULONGLONG)) {
			return false;
		}

		bool bEquals = false;
		ULONGLONG thisAsInt = digits[0];
		ULONGLONG temp;

		for (UINT i = 1; i < size; i++)
		{
			temp = digits[i];
			thisAsInt += (temp << (LongInteger::BASEVALBITS * i));
		}

		if (thisAsInt == rhs)
		{
			bEquals = true;
		}
		return bEquals;
	}

	inline bool operator!=(const LongInteger& rhs) {
		return !((*this) == rhs);
	}

	inline bool operator!=(int rhs) {
		return !((*this) == rhs);
	}

	inline bool operator!=(UINT rhs) {
		return !((*this) == rhs);
	}

	// Add int versions of the comparison operators to avoid the overhead of converting ints to LongIntegers for comparisons.
	inline bool operator<(int rhs) const {
		if (bOverflow) {
			return false;
		}

		if ((bPositive && rhs < 0) || (!bPositive && rhs >= 0)) {
			// If this is + and rhs is -, then return -, else return +. So return opposite of bPositive flag
			return !bPositive;
		}
		// Comparison with zero. If both are zero
		if (rhs == 0) {
			if (equalsZero()) {
				return false;
			}
			else {
				return !bPositive;
			}
		}
		else {
			if (equalsZero()) {
				return (rhs > 0);
			}
		}

		if (size > sizeof(int)) {
			return false ^ !bPositive;
		}

		bool bLessThan = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt *= digits[i];
		}

		if (thisAsInt < (UINT)std::abs(rhs))
		{
			bLessThan = true;
		}
		else if (thisAsInt == (UINT)std::abs(rhs))
		{
			return false; // The return value for equal negative numbers was going wrong
		}
		return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
	}

	inline bool operator<(UINT rhs) const {
		if (bOverflow) {
			return false;
		}

		if (!bPositive) {
			// UINTs can only be positive, so if this is negative it is definately less than the UINT
			return true;
		}
		if (rhs == 0) {
			if (equalsZero()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (equalsZero()) {
				return false;
			}
		}

		if (size > sizeof(int)) {
			return false ^ !bPositive;
		}

		bool bLessThan = false;
		UINT thisAsInt = digits[0];

		for (UINT i = 1; i < size; i++)
		{
			thisAsInt *= digits[i];
		}

		if (thisAsInt < rhs)
		{
			bLessThan = true;
		}
		return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
	}

	inline bool operator>(int rhs) const
	{
		return rhs < (*this);
	}

	inline bool operator>(UINT rhs) const
	{
		return rhs < (*this);
	}
};


inline bool operator==(int lhs, const LongInteger& rhs) {
	return rhs == lhs;
}

inline bool operator==(UINT lhs, const LongInteger& rhs) {
	return rhs == lhs;
}

inline bool operator!=(int lhs, const LongInteger& rhs) {
	return !(rhs == lhs);
}

inline bool operator!=(UINT lhs, const LongInteger& rhs) {
	return !(rhs == lhs);
}

inline bool operator<(UINT lhs, const LongInteger& rhs) {
	if (rhs.overflow()) {
		return false;
	}

	bool bPositive = rhs.isPositive();

	if (!bPositive) {
		// If rhs is negative it is definately less than lhs as UINTs can't be negative
		return false;
	}
	if (rhs.equalsZero()) {
		if (lhs == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (lhs == 0) {
			return false;
		}
	}

	if (rhs.getSize() > sizeof(int)) {
		return true ^ !bPositive;
	}

	bool bLessThan = false;
	UINT thisAsInt = rhs.getDigit(rhs.getSize() - 1);

	if (rhs.getSize() > 1)
	{
		for (UINT i = rhs.getSize() - 1; i > 0; i--)
		{
			thisAsInt *= LongInteger::BASEVAL;
			thisAsInt += (rhs.getDigit(i - 1));
		}
	}

	if (lhs < thisAsInt)
	{
		bLessThan = true;
	}
	return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
}

inline bool operator<(int lhs, const LongInteger& rhs) {
	if (rhs.overflow()) {
		return false;
	}

	bool bPositive = rhs.isPositive();

	if ((bPositive && lhs < 0) || (!bPositive && lhs >= 0)) {
		// If this is + and rhs is -, then return -, else return +. So return bPositive flag
		return bPositive;
	}
	if (rhs.equalsZero()) {
		if (lhs == 0) {
			return false;
		}
		else {
			return (lhs < 0);
		}
	}
	else {
		if (lhs == 0) {
			return bPositive;
		}
	}

	if (rhs.getSize() > sizeof(int)) {
		return true ^ !bPositive;
	}

	bool bLessThan = false;
	UINT thisAsInt = rhs.getDigit(rhs.getSize() - 1);

	if (rhs.getSize() > 1)
	{
		for (UINT i = rhs.getSize() - 1; i > 0; i--)
		{
			thisAsInt *= LongInteger::BASEVAL;
			thisAsInt += (rhs.getDigit(i - 1));
		}
	}

	if ((UINT)std::abs(lhs) < thisAsInt)
	{
		bLessThan = true;
	}
	else if ((UINT)std::abs(lhs) == thisAsInt)
	{
		return false;
	}
	return (bLessThan ^ !bPositive); // Return the opposite result if the numbers are negative
}


inline bool operator>(int lhs, const LongInteger& rhs) {
	return rhs < lhs;
}

inline bool operator>(UINT lhs, const LongInteger& rhs) {
	return rhs < lhs;
}

inline bool operator>=(int lhs, const LongInteger& rhs) {
	return !(lhs < rhs);
}

inline bool operator>=(UINT lhs, const LongInteger& rhs) {
	return !(lhs < rhs);
}

inline bool operator<=(int lhs, const LongInteger& rhs) {
	return !(lhs > rhs);
}

inline bool operator<=(UINT lhs, const LongInteger& rhs) {
	return !(lhs > rhs);
}

inline LongInteger operator+(int lhs, const LongInteger& rhs) {
	return rhs + lhs;
}

inline LongInteger operator+(UINT lhs, const LongInteger& rhs) {
	return rhs + lhs;
}

inline LongInteger operator-(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value - rhs;
}

inline LongInteger operator-(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value - rhs;
}

inline LongInteger operator*(int lhs, const LongInteger& rhs) {
	return rhs * lhs;
}

inline LongInteger operator*(UINT lhs, const LongInteger& rhs) {
	return rhs * lhs;
}

inline LongInteger operator/(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value / rhs;
}

inline LongInteger operator/(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value / rhs;
}

inline LongInteger operator&(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value & rhs;
}

inline LongInteger operator&(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value & rhs;
}

inline LongInteger operator|(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value | rhs;
}

inline LongInteger operator|(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value | rhs;
}

inline LongInteger operator^(int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value ^ rhs;
}

inline LongInteger operator^(UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value ^ rhs;
}

inline LongInteger operator >> (int lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value >> rhs;
}

inline LongInteger operator >> (UINT lhs, const LongInteger& rhs) {
	LongInteger value = lhs;
	return value >> rhs;
}

#endif


// Based on the code of Roman Pasechnik. The logic has had no changes. I have simply adapted it to work with my LongInteger class

// Will need to replace the vector class with a user defined type as a vector has a max size determined by size_t (which
// is usually the same as int
// Will also need to change quite a few of the variables from ints to LongIntegers

class PrimeSieve
{
public:
	/** Constructor.
	Constructs a prime sieve for the integer range [1,n]. */
	PrimeSieve(const LongInteger& li);

	/** Get prime by index */
	LongInteger GetPrime(LongInteger index) { return m_LIMPrimes[index]; }
	
	/** Returns prime index in collection */
	LongInteger GetPrimeIndex(const LongInteger& number, LongInteger lowerBound, LongInteger upperBound);

	/** Get number of prime numbers in sieve */
	LongInteger GetNumberOfPrimes() { return m_NumberOfPrimes; }

	/** Gives the product of primes in range [_low, _high] */
	LongInteger Primorial(const LongInteger& low, const LongInteger& high);



private:

	//////////////////////////////////////////////////////////////////////////


	/** Prime number sieve, Eratosthenes (276-194 b. t.) This implementation
	considers only multiples of primes greater than 3, so the smallest value
	has to be mapped to 5.

	Note: There is no multiplication operation in this function.

	After execution of the function this boolean array includes
	all composite numbers in [5,n] disregarding multiples of 2 and 3. */
	static void SieveOfEratosthenes(BoolVec& composite);


	//////////////////////////////////////////////////////////////////////////


	/** Transforms the sieve of Eratosthenes
	into the sequence of prime numbers. */
	void MakePrimeList(const LongInteger& li);


	//////////////////////////////////////////////////////////////////////////


	/** Prime numbers */
	LongIntMap m_LIMPrimes;

	/** Number of primes in collection */
	LongInteger m_NumberOfPrimes;

};


#endif

#endif

class PrimeSwing
{
public:
	PrimeSwing();
	~PrimeSwing();


	/** Computes factorial of integer number */
//	LongInteger Factorial(int number);
	LongInteger Factorial(const LongInteger& number);
protected:
//	LongInteger Swing(int number, PrimeSieve& sieve);
	LongInteger Swing(const LongInteger& number, PrimeSieve& sieve);

private:
	/** Computes factorial of integer number recursively */
//	virtual void RecFactorial(LongInteger& result, int number, PrimeSieve& sieve);
	virtual void RecFactorial(LongInteger& result, const LongInteger& number, PrimeSieve& sieve);


	/** Gets multiplies for Swing function. */
//	IntVec GetMultiplies(int number, PrimeSieve& sieve);
	LongIntVec GetMultiplies(const LongInteger& number, PrimeSieve& sieve);

	static const int smallOddSwing[];
};

#endif

#include <stdexcept>
#undef min
#undef max
#include <limits>

#include <functional>

#include <cmath>
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>
// min and max are undefined before the inclusion of <limits> as Microsoft reused the min and max macros and this causes
// conflicts with (C++ standard) definitions in <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

bool LongInteger::bShuttingDown = false;
UINT LongInteger::BURKINELZIEGLERCUTOFF = 50;
UINT LongInteger::TOOMCOOK3CUTOFF = 150;
UINT LongInteger::TOOMCOOK3THREADING = 1000;
UINT LongInteger::KARATSUBACUTOFF = 50;
UINT LongInteger::KARATSUBATHREADING = 1000;
bool LongInteger::TriedToReadE = false;

LongInteger LongInteger::E = LongInteger::ReadEFromFile("~/Desktop/LongIntegerFramework/einhex.txt");

UINT LongInteger::SIZEOFE = 12;

void LongInteger::init() {
	// Create the byte array. Default size of SIZESTEP
	// Update - default size is MINSIZE. Trying to save memory
	size = 0;
	maxSize = MINSIZE;
	reset();

}

void LongInteger::reset() {
	// Create the byte array with the new size
	if (digits != nullptr)
		delete[] digits;
	digits = new byte[maxSize];
	std::memset(digits, 0, sizeof(byte) * maxSize);
	bOverflow = false;
	bProcessing = false;
	bPositive = true; // Can only be true or false, so we'll treat zero as positive
}

LongInteger LongInteger::ReadEFromFile(string inFilePath)
{
	// Read in the data
	bool returnflag;
	ifstream inFile(inFilePath, ios::in);
	LongInteger returnLInt;
	returnflag = inFile.is_open();
	if (returnflag)
	{
		// The file exists and has been opened. The digits will be 1 per line, in decimal, with the digits in order
		UINT numDigits = 0;
		LongInteger eFromFile;
		string line;
		bool loop = true;
		bool lineRead;
		while (loop)
		{
			std::getline(inFile, line);
			lineRead = inFile.fail() | inFile.eof();
			if (lineRead)
			{
				// First line seems to get gibberish characters. Will need to remove them
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] < '0' || line[i] > '9')
					{
						line[i] = '0';
					}
				}

				if (line.length() > 0)
				{
					int value = std::stoi(line);
					eFromFile <<= LongInteger::BASEVALBITS;
					eFromFile += value;
					numDigits++;
				}
				else
				{
					loop = false;
				}
			}
			else
			{
				loop = false;
			}
		}

		// If all has gone well the number of digits should equal the size of the new LongInteger
		if (numDigits > SIZEOFE && eFromFile.size > SIZEOFE && numDigits == eFromFile.size)
		{
			// If the number of digits read in is more than the current best guess then we will use it
			SIZEOFE = numDigits - 1; // minus 1 because the first digit will be before the period
			returnLInt = eFromFile;
		}
	}
	return returnLInt;
}


LongInteger LongInteger::multiplyChooser(const LongInteger& liOne, const LongInteger& liTwo) {
	// Wrapper class to handle memory management
	// The karatsuba and ToomCook3 functions needs to put memory on the heap, so the memory needs
	// to be managed manually. But we want all memory management within the class


	// Additional section added as part of multi-threading
	// As the size increases the number of threads increases exponentially if the thread cut-off is a fixed value.
	// So we will calculate a cut-off value that will allow a suitable number of threads to run -
	// not too many and not too few.
	// Each time a call to Karatsuba is made where iHalfSize ends up less than the threading cutoff we get
	// approx 3 times the number of threads
	// So take the number of cores, multiply by a fixed value (10 maybe?) to give enough threads that 100% core usage
	// happens without the queue getting ridiculous.
	// Then work out what iHalfSize will be and half it n times until 3^n is greater than the value from above.

	UINT minCalc = 500;
	if (liOne.size > 500 || liTwo.size > 500)
	{

		// There is only a single instance of QOT
		QueueOfThreads<LongIntWrapper>* qot = LongIntWrapper::getQOT();
		UINT deviceCores = qot->getDeviceCores();
		UINT targetThreads = deviceCores * 2;

		UINT uKCutOff = ((liOne.size > liTwo.size) ? liOne.size : liTwo.size) / 2;
		UINT uTCcutOff = uKCutOff;

		// Calculate the cut-off size to start threading for Karatsuba and ToomCook3 algorithms
		UINT numThreads = 1;
		while (numThreads < targetThreads) {
			numThreads = numThreads * 3;
			uKCutOff /= 2;
		}
		numThreads = 1;
		while (numThreads < targetThreads) {
			numThreads = numThreads * 5;
			uTCcutOff /= 2;
		}

		// Not sure if this is the optimal cutoff value
		if (uKCutOff < 500) {
			uKCutOff = 500;
		}
		if (uTCcutOff < 500) {
			uTCcutOff = 500;
		}

		// Comment out during performance testing
		LongInteger::KARATSUBATHREADING = uKCutOff;
		LongInteger::TOOMCOOK3THREADING = uTCcutOff;
	}
	else
	{
		LongInteger::KARATSUBATHREADING = LongInteger::ABSMAXSIZE;
		LongInteger::TOOMCOOK3THREADING = LongInteger::ABSMAXSIZE;
	}

	// Call ToomCook3, Karatsuba or Long Multiplication?

	LongInteger* returnValue;
	if ((liOne.size > TOOMCOOK3CUTOFF) || (liTwo.size > TOOMCOOK3CUTOFF))
	{
		returnValue = ToomCook3(liOne, liTwo);
	}
	else {
		if ((liOne.size > KARATSUBACUTOFF) || (liTwo.size > KARATSUBACUTOFF))
		{
			returnValue = karatsuba(liOne, liTwo);
		}
		else
		{
			returnValue = new LongInteger(liOne);
			returnValue->multiplyInternal(liTwo);
		}
	}

	return returnValue;
}


// Implementation of the Karatsuba algorithm for multiplication
// This is a static method

LongInteger* LongInteger::karatsuba(const LongInteger& liOne, const LongInteger& liTwo, bool bBackgroundThread)
{
	if ((liOne.size < KARATSUBACUTOFF) && (liTwo.size < KARATSUBACUTOFF))
	{
		LongInteger* returnValue = new LongInteger(liOne);
		returnValue->multiplyInternal(liTwo);
		return returnValue;
	}

	// Determine the size of the numbers, so we know where to split them
	UINT iSize = (liOne.size > liTwo.size) ? liOne.size : liTwo.size;
	UINT iHalfSize = iSize / 2;

	// Split the digit sequences about the middle
	LongInteger* liHighOne = new LongInteger();
	LongInteger* liLowOne = new LongInteger();
	LongInteger* liHighTwo = new LongInteger();
	LongInteger* liLowTwo = new LongInteger();
	liOne.split(liLowOne, liHighOne, iHalfSize);
	liTwo.split(liLowTwo, liHighTwo, iHalfSize);

	LongInteger* liZ0;
	LongInteger* liZ1;
	LongInteger* liZ2;

	if (iHalfSize > KARATSUBATHREADING) {
		QueueOfThreads<LongIntWrapper>* qot = LongIntWrapper::getQOT();
		LongIntWrapper* liw0 = new LongIntWrapper;
		LongIntWrapper* liw1 = new LongIntWrapper;
		LongIntWrapper* liw2 = new LongIntWrapper;
		liw0->setParams(*liLowOne, *liLowTwo);
		liw1->setParams((*liLowOne + *liHighOne), (*liLowTwo + *liHighTwo));
		liw2->setParams(*liHighOne, *liHighTwo);
		LIfunction fp = &LongInteger::karatsuba;
		liw0->setStartMethod(fp);
		liw1->setStartMethod(fp);
		liw2->setStartMethod(fp);
		qot->addToQueue(liw0);
		qot->addToQueue(liw1);
		qot->addToQueue(liw2);
		if (bBackgroundThread) {
			qot->iAmWaiting(); // Only call this if this process is called in a background thread.
		}
		qot->waitForThread(liw0);
		qot->waitForThread(liw1);
		qot->waitForThread(liw2);
		if (bBackgroundThread) {
			qot->iHaveStoppedWaiting();
		}
		liZ0 = liw0->getResult();
		liZ1 = liw1->getResult();
		liZ2 = liw2->getResult();
		delete liw0;
		delete liw1;
		delete liw2;
	}
	else {
		// 3 calls made to numbers approximately half the size
		liZ0 = karatsuba(*liLowOne, *liLowTwo, bBackgroundThread);
		liZ1 = karatsuba((*liLowOne + *liHighOne), (*liLowTwo + *liHighTwo), bBackgroundThread);
		liZ2 = karatsuba(*liHighOne, *liHighTwo, bBackgroundThread);
	}
	// The next step is this calculation:
	// return (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)
	// This calc is in base 10 whereas we are in base BASEVAL, which is the size of 1 byte
	// The numbers are represented internally as a byte array
	// So we will start with most complex bit - z1-z2-z0 * BASEVAL^(halfsize)
	// We will do the sums, then move liZ1 left by halfsize bytes
	(*liZ1) -= (*liZ2);
	(*liZ1) -= (*liZ0);
	liZ1->multHelper2(iHalfSize);
	// Then move liZ2 left by iSize bytes
	liZ2->multHelper2(iHalfSize * 2);
	// Then we add liZ0, liZ1 and liZ2 together

	LongInteger* returnValue = new LongInteger((*liZ2) + (*liZ1) + (*liZ0));

	delete liLowOne;
	delete liLowTwo;
	delete liHighOne;
	delete liHighTwo;
	delete liZ0;
	delete liZ1;
	delete liZ2;

	return returnValue;
}

bool LongInteger::split(LongInteger* liFront, LongInteger* liBack, UINT iSplit) const {
	// Split the current LongInteger into 2 bits at the point specified by iSplit

	if (iSplit >= size) {
		(*liFront) = (*this);
		liBack->init();
		return false;
	}

	// Put the first half of the current LongInteger in liFront
	liFront->size = iSplit;
	liFront->recalcMaxSizeAndClear();
	memcpy(liFront->digits, digits, iSplit * sizeof(byte));
	liFront->bPositive = bPositive;

	// Put the second half in liBack
	liBack->size = size - iSplit;
	liBack->recalcMaxSizeAndClear();
	memcpy(liBack->digits, digits + (iSplit * sizeof(byte)), ((size - iSplit) * sizeof(byte)));
	liBack->bPositive = bPositive;

	return true;
}

LongInteger::LongInteger() {
	init();
}

LongInteger::LongInteger(const int iNew) {
	assignNumber(iNew);
}

LongInteger::LongInteger(const UINT iNew) {
	assignNumber(iNew);
}

LongInteger::LongInteger(const ULONG iNew) {
	assignNumber(iNew);
}

LongInteger::LongInteger(const ULONGLONG iNew) {
	assignNumber(iNew);
}

LongInteger::LongInteger(const double dNew)
{
	assignNumber(dNew);
}

LongInteger::LongInteger(const long double dNew)
{
	assignNumber(dNew);
}

LongInteger::LongInteger(const LongInteger& oldLongInt) {
	size = oldLongInt.size;
	maxSize = oldLongInt.maxSize;
	reset();
	bPositive = oldLongInt.bPositive;
	bOverflow = oldLongInt.bOverflow;
	memcpy(digits, oldLongInt.digits, sizeof(byte) * maxSize);
}

LongInteger::LongInteger(LongInteger* pliCopyInt) {
	// Copy constructor for a pointer.
	// I've had to create some tortuous workarounds for assignments of points returned from a method
	size = pliCopyInt->size;
	maxSize = pliCopyInt->maxSize;
	reset();
	bPositive = pliCopyInt->bPositive;
	bOverflow = pliCopyInt->bOverflow;
	memcpy(digits, pliCopyInt->digits, sizeof(byte) * maxSize);
	delete pliCopyInt;
}

LongInteger::LongInteger(const string& strInput) {
	assignNumber(strInput);
}


LongInteger::~LongInteger() {
	delete[] digits;
}

const UINT LongInteger::getSize() const {
	return size;
}

bool LongInteger::assignNumber(UINT inNum) {
	// Clear out any existing number
	init();

	// Turn the int into base 16 digits and store in the internal array
	UINT index = 0;
	while (index < maxSize && inNum > 0) {
		digits[index] = inNum % BASEVAL;
		inNum /= BASEVAL;
		++index;
	}

	// It will be unlikely for an int to overflow the starting size of a LongInteger, so not bother checking for that
	size = index;
	return bOverflow;
}

bool LongInteger::assignNumber(int inNum) {
	// Clear out any existing number
	init();

	if (inNum < 0) {
		bPositive = false;
		inNum = -inNum;
	}

	// Turn the int into base 16 digits and store in the internal array
	UINT index = 0;
	while (index < maxSize && inNum > 0) {
		digits[index] = inNum % BASEVAL;
		inNum /= BASEVAL;
		++index;
	}

	// It will be unlikely for an int to overflow the starting size of a LongInteger, so not bother checking for that
	size = index;
	return bOverflow;
}

bool LongInteger::assignNumber(ULONG inNum) {
	// Clear out any existing number
	init();

	// Turn the int into base 16 digits and store in the internal array
	UINT index = 0;
	while (index < maxSize && inNum > 0) {
		digits[index] = inNum % BASEVAL;
		inNum /= BASEVAL;
		++index;
	}

	size = index;
	return bOverflow;
}

bool LongInteger::assignNumber(ULONGLONG inNum) {
	// Clear out any existing number
	init();

	// Turn the int into base 16 digits and store in the internal array
	UINT index = 0;
	while (index < maxSize && inNum > 0) {
		digits[index] = inNum % BASEVAL;
		inNum /= BASEVAL;
		++index;
	}

	size = index;
	return bOverflow;
}

bool LongInteger::assignNumber(double dNum)
{
	// Clear out any existing number
	init();

	UINT index = 0;
	double temp;
	dNum = floor(dNum);
	while (dNum > 0)
	{
		temp = floor(dNum / BASEVAL);
		digits[index] = (byte)(dNum - (temp * BASEVAL));
		++index;
		if (index >= maxSize)
			increaseSize();
	}

	size = index;
	return bOverflow;
}

bool LongInteger::assignNumber(long double dNum)
{
	// Clear out any existing number
	init();

	UINT index = 0;
	long double temp;
	dNum = floor(dNum);
	while (dNum > 0)
	{
		temp = floor(dNum / BASEVAL);
		digits[index] = (byte)(dNum - (temp * BASEVAL));
		dNum = temp;
		++index;
		if (index >= maxSize)
			increaseSize();
	}

	size = index;
	return bOverflow;
}



bool LongInteger::assignNumber(const string& in_number)

{
	// Accept a (potentially very large) number in a CString
	// Assume it is in decimal and turn it into an 8-bit byte array
	// Easy!

	// So create a temporary list to hold the digits we calculate
	// Put all the decimal digits in there, then loop through dividing by 256 and adding the remainder
	// to the digits list until the templist is empty
	init();


	if (in_number.length() == 0) {

		assignNumber(0);
		return !bOverflow;
	}


	byte* tempList = new byte[in_number.length()];
	UINT listLength = in_number.length();
	char s[2];


	UINT index = listLength - 1;
	s[1] = 0;
	UINT iStart = 0;
	if (in_number[0] == '-') {
		bPositive = false;
		iStart = 1;
		index--;
	}
	for (UINT i = iStart; i < listLength; i++, index--) {
		s[0] = in_number[i];

		tempList[index] = atoi(s);

	}
	if (!bPositive) listLength--;

	index = 0;
	bool finished = false;
	unsigned short remainder;
	unsigned short value;
	while (!finished && !bOverflow) {
		remainder = 0;
		// Loop through and divide each digit by BASEVAL, putting the remainder in the next digit down
		for (UINT i = listLength; i > 0; i--) {
			value = tempList[i - 1] + (remainder * 10);
			//			tempList[i] = value / BASEVAL;
			tempList[i - 1] = value >> BASEVALBITS;
			//			remainder = value % BASEVAL;
			remainder = (byte)value; // Only works when using base 256
		}
		// Anything left in remainder is the new digit
		digits[index] = (byte)remainder;

		//digits[index] = remainder;
		index++;

		// Check the temp list to see if we've finished
		while (listLength > 0 && tempList[listLength - 1] == 0) {
			listLength--;
		}
		if (listLength == 0 && tempList[0] == 0) {
			finished = true;
		}

		size = index + 1;
		while (size > maxSize) {
			increaseSize();
			if (bOverflow)
				return !bOverflow;
			if (bShuttingDown)
				return false;
		}
	}

	checkSize();


	delete[] tempList;

	return !bOverflow;
	}

byte LongInteger::getDigit(UINT index) const {
	if (index < 0 || index >= maxSize) {
		return -1;
	}

	return digits[index];
}

bool LongInteger::setDigit(UINT index, byte newValue) {
	if (index < 0 || index >= LongInteger::ABSMAXSIZE) {
		return false;
	}

	if (index > size) {
		size = index + 1;
		recalcMaxSize();
	}
	digits[index] = newValue;
	return true;
}



string LongInteger::toDecimal()

{
	// Convert the internal number into a decimal string
	// Create a copy of the number and start dividing each digit by 10, putting the overflow into the
	// number below, with the last overflow dropping out into the string

	// Trying to find some way to improve the algorithm below as this is by far the slowest part of the program
	// Converting large digits to decimal takes an unreasonable amount of time

	// Sanity check
	if (bOverflow) {

		return "NULL";


	}

	string output = "";
	stringstream outputstream;


	if (equalsZero()) {

		output = "0";

		return output;
	}

	// Find out how big we need to make the copy
	UINT listSize;
	// Check we don't have leading zeroes
	for (listSize = size - 1; listSize > 0 && digits[listSize] == 0; listSize--);
	if (listSize == 0 && digits[0] == 0) return output;

	byte* listCopy = new byte[listSize + 1];

	memcpy(listCopy, digits, sizeof(byte) * (listSize + 1));

	bool finished = false;
	UINT value = 0;
	UINT remainder = 0;
	while (!finished) {
		remainder = 0;
		// The use of 2 variables below is because UINTs can't be negative, so need to test for more than zero
		// This then leads to every index reference being (counter-1), unless we've already calculated it.
		// The approach below produces a tiny improvement over using a single variable. Every little bit helps
		for (UINT counter = listSize + 1, index = listSize; counter > 0; counter--, index--) {
			value = listCopy[index] + (remainder << BASEVALBITS); // Slight improvement over multiplying by BASEVAL (256)
			listCopy[index] = value / 10; // Surprisingly using bit hacking slowed this function down by a factor of 4
			remainder = value - (listCopy[index] * 10); // Using bit manipulation to multiply also slows this down by nearly 4 times
		}
		// The append below has a tiny impact on performance - less than 1%

		outputstream << remainder;


		// Check the temp list to see if we've finished
		while (listSize > 0 && listCopy[listSize] == 0) {
			listSize--;
		}
		if (listSize == 0 && listCopy[0] == 0) {
			finished = true;
		}
		if (bShuttingDown) {
			delete[] listCopy;

			return "Shutting Down";

		}
	}
	// The string is done, but it is backwards

	output = outputstream.str();
	std::reverse(output.begin(), output.end());


	if (!bPositive) {

		output = "-" + output;

	}
	delete[] listCopy;

	return output;
}



string LongInteger::toDecimal() const

{
	// Convert the internal number into a decimal string
	// Create a copy of the number and start dividing each digit by 10, putting the overflow into the
	// number below, with the last overflow dropping out into the string

	// Trying to find some way to improve the algorithm below as this is by far the slowest part of the program
	// Converting large digits to decimal takes an unreasonable amount of time

	// Sanity check
	if (bOverflow) {

		return "NULL";


	}

	string output = "";
	stringstream outputstream;


	if (equalsZero()) {

		output = "0";

		return output;
	}

	// Find out how big we need to make the copy
	UINT listSize;
	// Check we don't have leading zeroes
	for (listSize = size - 1; listSize > 0 && digits[listSize] == 0; listSize--);
	if (listSize == 0 && digits[0] == 0) return output;

	byte* listCopy = new byte[listSize + 1];

	memcpy(listCopy, digits, sizeof(byte) * (listSize + 1));

	bool finished = false;
	UINT value = 0;
	UINT remainder = 0;
	while (!finished) {
		remainder = 0;
		// The use of 2 variables below is because UINTs can't be negative, so need to test for more than zero
		// This then leads to every index reference being (counter-1), unless we've already calculated it.
		// The approach below produces a tiny improvement over using a single variable. Every little bit helps
		for (UINT counter = listSize + 1, index = listSize; counter > 0; counter--, index--) {
			value = listCopy[index] + (remainder << BASEVALBITS); // Slight improvement over multiplying by BASEVAL (256)
			listCopy[index] = value / 10; // Surprisingly using bit hacking slowed this function down by a factor of 4
			remainder = value - (listCopy[index] * 10); // Using bit manipulation to multiply also slows this down by nearly 4 times
		}
		// The append below has a tiny impact on performance - less than 1%

		outputstream << remainder;


		// Check the temp list to see if we've finished
		while (listSize > 0 && listCopy[listSize] == 0) {
			listSize--;
		}
		if (listSize == 0 && listCopy[0] == 0) {
			finished = true;
		}
		if (bShuttingDown) {
			delete[] listCopy;

			return "Shutting Down";

		}
	}
	// The string is done, but it is backwards

	output = outputstream.str();
	std::reverse(output.begin(), output.end());


	if (!bPositive) {

		output = "-" + output;

	}
	delete[] listCopy;

	return output;
}


LongInteger::operator int() const
{
	// Check the number held can be stored in an int
	if (size > sizeof(int))
		return 0;
	if (this->bPositive) {
		if ((*this) > (std::numeric_limits<int>::max()))
			return 0;
	}
	else {
		if (abs(*this) > (std::numeric_limits<int>::max()))
			return 0;
	}


	int iResult = (UINT)(*this); // Call the UINT conversion so we don't have to write the conversion code twice
	if (!bPositive)
		iResult *= -1;

	return iResult;
}


LongInteger::operator UINT() const
{
	// Convert the LongInteger into an unsigned int. If it is too big, return 0
	// Assume the user wants the absolute value, so we won't worry about pesky negative signs
	if (size > sizeof(UINT))
		return 0;
	// Use an unsigned int to hold the converted LongInteger
	UINT uResult = 0;
	for (UINT i = 0; i < size; i++) {
		uResult += (digits[i] * UINTpower(BASEVAL, i));
	}

	return uResult;
}


UINT LongInteger::UINTpower(UINT base, UINT power) const {
	UINT result = 1;
	for (UINT i = 0; i < power; i++) {
		result *= base;
	}
	return result;
}

bool LongInteger::addNumber(int iAdd) {
	// Sanity checks
	if (iAdd == 0) {
		return true;
	}

	// The simplest way to handle this is to turn the int into a LongInteger and call that addition
	// (Surprising complications can occur otherwise)
	LongInteger liAdd = iAdd;

	return addNumber(liAdd);
}

bool LongInteger::addNumber(const LongInteger & liAdd) {
	// Adding is easy. Assume each digit in the input is in the range 0-255.
	// We just add each digit in the ranges and then balance the numbers

	// If this and liAdd are positive, carry on
	// If this is + and liAdd is -, then call subtract with liAdd as +
	if (bPositive) {
		if (!liAdd.bPositive) {
			return this->subtractNumber(-liAdd);
		}
	}
	else
		// If this is - and liAdd is +, then subtract liAdd from this
		// If both are - then add them
	{
		if (liAdd.bPositive) {
			return this->subtractNumber(-liAdd);
		}
	}

	UINT loopSize = liAdd.size;
	if (loopSize > size) {
		size = loopSize;
		recalcMaxSize();
		if (bOverflow) return false;
	}

	short workingVal = 0;
	short overflow = 0;
	for (UINT index = 0; index < loopSize; index++) {
		workingVal = digits[index] + liAdd.digits[index] + overflow;
		if (workingVal >= BASEVAL) {
			digits[index] = workingVal % BASEVAL;
			overflow = workingVal / BASEVAL;
		}
		else {
			digits[index] = (byte)workingVal;
			overflow = 0;
		}
	}

	UINT iDigit;
	UINT liDigit;
	while (overflow > 0 && size <= maxSize && !bShuttingDown) {
		iDigit = (loopSize < size) ? digits[loopSize] : 0;
		liDigit = (loopSize < liAdd.size) ? liAdd.digits[loopSize] : 0;
		workingVal = iDigit + liDigit + (overflow % BASEVAL);
		digits[loopSize] = workingVal % BASEVAL;
		overflow = workingVal / BASEVAL;
		++loopSize;
		// Left in here for safety. Should never happen
		if (loopSize >= size) {
			size = loopSize + 1;
			while (size >= maxSize) {
				increaseSize();
			}
		}
	}
	checkSize();

	return true;
}

bool LongInteger::subtractNumber(int iAdd) {
	// Sanity checks
	if (iAdd < 0) {
		return addNumber(-iAdd);
	}
	if (iAdd == 0) {
		return true;
	}
	subtractNumber(LongInteger(iAdd));

	return bOverflow;
}

bool LongInteger::subtractNumber(const LongInteger & liMinus) {
	// We just subtract each digit in the ranges and then balance the numbers

	// Some sanity checks.
	if (liMinus.size == 0) {
		return false;
	}

	// Subtracting a negative is the same as adding a positive
	if ((bPositive && !liMinus.bPositive) || (!bPositive && liMinus.bPositive)) {
		addNumber(-liMinus);
		return bOverflow;
	}
	// Check for going negative
	// If liMinus is greater than *this, we will go negative
	// So set the flag for negative and subtract *this from liMinus
	LongInteger liWorking;
	// Some manipulations to avoid making a copy. Looks might complicated, but it is checking for
	// abs(liMinus) > abs(*this). The abs operator makes a copy with bPositive set to positive, so
	// it is a bit of an overhead. Hence the flag manipulation below
	bool bGreater = false;
	// Test manually as the non-abs function depends on the signs and we want a sign-independant test that doesn't do copying
	if (liMinus.size > size) {
		bGreater = true;
	}
	else {
		/* This needs fixed
		It needs to check all digits
		*/
		if (liMinus.size == size) {
			bool bLoop = true;
			UINT uIndex = liMinus.size - 1;
			while (bLoop) {
				if (liMinus.digits[uIndex] > digits[uIndex]) {
					bGreater = true;
					bLoop = false;
				}
				else
					if (liMinus.digits[uIndex] < digits[uIndex]) {
						bLoop = false;
					}
					else {
						// Digits are the same
						if (uIndex > 0)
							uIndex--;
						else
							bLoop = false;
					}
			}
		}
	}

	if (bGreater) {
		LongInteger liTemp = (*this);
		*this = liMinus;
		liWorking = liTemp;
		bPositive = !bPositive;
	}
	else {
		liWorking = liMinus;
	}

	// Start subtracting
	UINT indexSize = liWorking.size;

	short workingVal = 0;
	short overflow = 0;
	for (UINT index = 0; index < indexSize; index++) {
		if (bShuttingDown) {
			return false; // Bailout condition if the program is shutting down mid-calculation
		}
		workingVal = digits[index] - liWorking.digits[index] - overflow;
		overflow = 0;
		while (workingVal < 0) {
			workingVal += BASEVAL;
			++overflow;
		}
		digits[index] = (byte)workingVal;
	}
	// Check if the subtracting needs to borrow from higher digits
	while (overflow > 0 && indexSize < size) {
		workingVal = digits[indexSize] - overflow;
		overflow = 0;
		while (workingVal < 0) {
			workingVal += BASEVAL;
			++overflow;
		}
		digits[indexSize] = (byte)workingVal;
		++indexSize;
	}

	if (overflow > 0) {
		// If the overflow is still non-zero and we've reached the end of the numbers, then something has gone wrong
		bOverflow = true;
		return false;
	}

	// The size of the number might be smaller
	checkSize();
	return bOverflow;
}

LongInteger LongInteger::abs(const LongInteger & liValue) {
	LongInteger returnValue(liValue);
	returnValue.bPositive = true;
	return returnValue;
}

LongInteger& LongInteger::operator=(const LongInteger & li) {
	// Detect the scenario of self-assignment
	if (this == &li)
		return *this;
	// Delete the existing byte array and copy all info from the new LongInteger
	copy(li);
	return *this;
}

void LongInteger::copy(const LongInteger & li) {
	maxSize = li.maxSize;
	delete[] digits;
	digits = new byte[maxSize];
	size = li.size;
	memcpy(digits, li.digits, sizeof(byte) * maxSize);
	bPositive = li.bPositive;
	bOverflow = li.bOverflow;
}

bool LongInteger::increment() {
	bool bDone = false;

	UINT index = 0;
	while (!bDone) {
		if (digits[index] == BASEMAX) {
			digits[index] = 0;
			++index;
			while (index >= maxSize) {
				increaseSize();
				bDone = bOverflow;
			}
			if (index >= size)
				digits[index] = 0;
		}
		else {
			++digits[index];
			bDone = true;
		}
	}
	if (index >= size)
		size = (index + 1);
	return bOverflow;
}

// Prefix ++ operator

LongInteger& LongInteger::operator++() {
	if (bPositive)
		increment();
	else
		decrement();
	return *this;
}

// Postfix ++ operator

LongInteger LongInteger::operator++(int) {
	LongInteger liTemp(*this);
	operator++();
	return liTemp;
}

bool LongInteger::decrement() {
	bool bDone = false;

	// Sanity checks
	if (size == 1 && digits[0] == 1) {
		size = 0;
		digits[0] = 0;
		bPositive = true; // Zero is always treated as positive
		return bOverflow;
	}
	if (size == 0 || (size == 1 && digits[0] == 0)) {
		// Decrementing zero gives us -1
		size = 1;
		digits[0] = 1;
		bPositive = false;
		return bOverflow;
	}

	UINT index = 0;
	while (!bDone) {
		if (digits[index] == 0) {
			digits[index] = BASEMAX;
			++index;
			if (index >= size) {
				bDone = true;
				bOverflow = true;
			}
		}
		else {
			--digits[index];
			bDone = true;
		}
	}
	if (index != 0) checkSize();
	return bOverflow;
}

LongInteger& LongInteger::operator--() {
	if (bPositive)
		decrement();
	else
		increment();
	return *this;
}

LongInteger LongInteger::operator--(int) {
	LongInteger liTemp(*this);
	operator--();
	return liTemp;
}

LongInteger& LongInteger::operator+=(const LongInteger & liAdd) {
	addNumber(liAdd);
	return *this;
}

LongInteger& LongInteger::operator+=(int iAdd) {
	addNumber(iAdd);
	return *this;
}

LongInteger& LongInteger::operator-=(const LongInteger & liAdd) {
	subtractNumber(liAdd);
	return *this;
}

LongInteger& LongInteger::operator-=(int iAdd) {
	subtractNumber(iAdd);
	return *this;
}

LongInteger& LongInteger::operator*=(const LongInteger & liAdd) {
	multiplyNumber(liAdd);
	return *this;
}

LongInteger& LongInteger::operator*=(int iAdd) {
	multiplyNumber(iAdd);
	return *this;
}

LongInteger& LongInteger::operator/=(const LongInteger & liDivide) {
	divideNumber(liDivide);
	return *this;
}

LongInteger& LongInteger::operator/=(int iDivide) {
	divideNumber(iDivide);
	return *this;
}

LongInteger LongInteger::operator+(const LongInteger & rhs) const {
	LongInteger value = *this;
	value += rhs;
	return value;
}

LongInteger LongInteger::operator-(const LongInteger & rhs) const {
	LongInteger value = *this;
	value -= rhs;
	return value;
}

LongInteger LongInteger::operator*(const LongInteger & rhs) const {
	LongInteger value = *this;
	value *= rhs;
	return value;
}

LongInteger LongInteger::operator/(const LongInteger & rhs) const {
	LongInteger value = *this;
	value /= rhs;
	return value;
}

bool LongInteger::multiplyNumber(const LongInteger & liMult) {
	bool bFinal;
	// Sort out the signs
	if (bPositive != liMult.bPositive)
		bFinal = false;
	else
		bFinal = true;

	(*this) = multiplyChooser(*this, liMult);

	// Handle the special case of multiplying zero by a negative number
	if (size == 0) bFinal = true;

	bPositive = bFinal;

	return bOverflow;
}

bool LongInteger::multiplyNumber(int iMult) {
	if (iMult == BASEVAL) {
		multHelper(iMult);
		return !bOverflow;
	}

	LongInteger liMult(iMult);

	return (multiplyNumber(liMult));
}

bool LongInteger::multiplyInternal(const LongInteger & liMult) {
	// We will assume that the digits of liMult are all in range 0-255. This means that all values will be held by a byte
	// Multiplying needs to be done 1 digit of the multiplier at a time and we need another memory storage area to hold
	// the result


	bool bFinalSign = !(bPositive ^ liMult.bPositive);

	// How big will the resulting number be?
	UINT inSize = liMult.size;
	UINT tempSize = size + inSize;

	byte* tempArea = new byte[tempSize];
	memset(tempArea, 0, sizeof(byte) * tempSize);
	UINT workingVal; // uint is at least 32 bits
	UINT overflow = 0;
	UINT tempIndex = 0;

	// Go through each digit in the input
	for (UINT inIndex = 0; inIndex < inSize; ++inIndex) {
		if (bShuttingDown) {
			delete[] tempArea;
			return false;
		}
		// Now loop through each value in the current structure, multiply and add the result to the temporary store
		tempIndex = inIndex;
		for (UINT index = 0; index < size; ++index) {
			workingVal = digits[index] * liMult.digits[inIndex];
			addInternal(tempArea, tempIndex, workingVal, 2); // 2 bytes is the max size of a sum of 2x1 byte numbers)
			++tempIndex;
		}
	}

	// Now put the temporary values into the original
	size = tempSize;
	recalcMaxSize();
	memcpy(digits, tempArea, sizeof(byte) * tempSize);
	checkSize();
	bPositive = bFinalSign;

	delete[] tempArea;

	return true;
}

void LongInteger::addInternal(byte * list, UINT offset, UINT value, UINT length) {
	// Add an unsigned int (which could hold up to length bytes) to the list starting from offset index

	byte* byteValues = (byte*)& value;
	UINT result;
	byte overflow = 0;

	for (UINT counter = 0; counter < length; ++counter) {
		result = byteValues[counter] + list[offset] + overflow;
		list[offset] = (byte)result;
		overflow = result / BASEVAL;
		++offset;
		while (offset > (maxSize - 1)) {
			increaseSize();
			if (bOverflow)
				return;
		}
	}

	while (overflow > 0) {
		result = list[offset] + overflow;
		list[offset] = (byte)result;
		overflow = result / BASEVAL;
		++offset;
	}
}

void LongInteger::checkSize() {
	if (size == 0) {
		if (maxSize > MINSIZE)
			decreaseSize();
		return;
	}
	UINT startSize = size;
	UINT index = size - 1;
	while (index > 0 && digits[index] == 0) {
		--size;
		--index;
	}
	if (index == 0 && digits[index] == 0) {
		size = 0;
		bPositive = true; // Zero is positive for the purposes of this class
	}
	if (startSize != size) decreaseSize();
}

void LongInteger::recalcMaxSize() {
	// Used when maxSize needs to be recalculated
	UINT oldMaxSize = maxSize;
	if (size >= SIZESTEP) {
		maxSize = (size - (size % SIZESTEP));
		if (maxSize > LongInteger::ABSMAXSIZE - SIZESTEP)
		{
			this->bOverflow = true;
			maxSize = ABSMAXSIZE;
		}
		else
		{
			maxSize += SIZESTEP;
		}
	}
	else if (size >= SMALLSIZESTEP) {
		maxSize = (size - (size % SMALLSIZESTEP)) + SMALLSIZESTEP;
	}
	else {
		maxSize = (size - (size % TINYSIZESTEP)) + TINYSIZESTEP;
	}

	if (maxSize != oldMaxSize) {
		UINT copySize = oldMaxSize;
		if (maxSize < oldMaxSize) copySize = maxSize;
		byte* tempDigits = digits;
		digits = new byte[maxSize];
		memset(digits, 0, sizeof(byte) * maxSize);
		memcpy(digits, tempDigits, sizeof(byte) * copySize);
		delete[] tempDigits;
	}
}


void LongInteger::recalcMaxSizeAndClear() {
	// Used when maxSize needs to be recalculated
	UINT oldMaxSize = maxSize;
	if (size >= SIZESTEP) {
		maxSize = (size - (size % SIZESTEP));
		if (maxSize > LongInteger::ABSMAXSIZE - SIZESTEP)
		{
			this->bOverflow = true;
			maxSize = ABSMAXSIZE;
		}
		else
		{
			maxSize += SIZESTEP;
		}
	}
	else if (size >= SMALLSIZESTEP) {
		maxSize = (size - (size % SMALLSIZESTEP)) + SMALLSIZESTEP;
	}
	else {
		maxSize = (size - (size % TINYSIZESTEP)) + TINYSIZESTEP;
	}

	if (digits != nullptr) {
		delete digits;
	}
	digits = new byte[maxSize];
	memset(digits, 0, sizeof(byte) * maxSize);
}


bool LongInteger::arrowCalc(UINT arrows, int powerValue) {
	LongInteger liValue = powerValue;
	LongInteger baseValue = *this;
	bool returnValue = arrowCalc(baseValue, arrows, liValue);
	*this = liValue;
	return returnValue;
}

bool LongInteger::arrowCalc(const LongInteger & baseValue, UINT arrows, LongInteger & liValue) {
	if (bOverflow) return false;
	LongInteger liWorking;

	if (arrows == 1) {
		// If the level is 1, then calculate the answer, which is 2^value
		// So that is 2*2 repeated 'value'-1 times

		// powerCalc updates the 1st parameter, but for this scenario we want to retain the 1st param and update the 2nd
		liWorking = baseValue;
		powerCalc(liWorking, liValue);
		if (bShuttingDown) {
			return false;
		}
		liValue = liWorking;
	}
	else {
		// x^x (y times) and arrow level
		if (arrows > 2) {
			arrowCalc(baseValue, (arrows - 1), liValue);
		}

		// calc baseValue to the power baseValue, loopValue times. Put the answer in liValue
		LongInteger loopValue = liValue;
		LongInteger runningValue = baseValue;
		--loopValue;
		while (!(loopValue == 0)) {
			powerCalcHelper(baseValue, runningValue);
			if (bShuttingDown) {
				return false;
			}
			--loopValue;
		}
		liValue = runningValue;
	}

	return !bOverflow;
}

bool LongInteger::equalsZero() const {
	if (size == 0 || (size == 1 && digits[0] == 0))
		return true;
	else
		return false;
}

bool LongInteger::powerCalc(LongInteger & liValue, const LongInteger & liPower) {
	// Calculate the power by using powers of 2
	// We will have a loop where we divide liPower by 2 and multiply a copy of liValue by itself,
	// adding this copy to a running total every time liPower is odd
	// Just realised this is a bit like old-fashioned multiplication

	if (liPower == 0)
	{
		liValue = 1;
		return true;
	}

	LongInteger liMultiples = liValue;
	LongInteger liTotal = 1;
	LongInteger liCounter = liPower;

	while (liCounter > 1) {
		// Find out if liCounter is odd
		if ((liCounter.digits[0] % 2) != 0) {
			liTotal *= liMultiples;
		}
		liCounter /= 2;
		liMultiples *= liMultiples;
	}
	// Last value is alway 1, thus always odd
	liTotal *= liMultiples;

	liValue = liTotal;

	return !bOverflow;
}

bool LongInteger::powerCalcHelper(const LongInteger & value, LongInteger & powerIn) {
	// Calculate a power by performing multiplication repeatedly
	// This is a helper for the arrow function - it changes the 2nd parameter rather than the first as would normally be expected

	LongInteger liMult = value;
	bOverflow = !(powerCalc(liMult, powerIn));
	powerIn = liMult;

	return !bOverflow;
}

bool LongInteger::powerCalc(int powerIn) {
	return powerCalc(*this, powerIn);
}

bool LongInteger::powerCalc(const LongInteger & powerIn) {
	return powerCalc(*this, powerIn);
}

bool LongInteger::divideNumber(const LongInteger & liDivide) {
	LongIntegerUP upliQuotient = make_unique<LongInteger>(0);
	LongIntegerUP upliModulus = make_unique<LongInteger>(0);

	bool bSuccess = DivAndMod(*this, liDivide, upliQuotient, upliModulus);

	if (!bSuccess) {
		*this = 0;
		bOverflow = true;
	}
	else {
		*this = *upliQuotient;
	}

	return bOverflow;
}

bool LongInteger::DivAndMod(const LongInteger & liValue, const LongInteger & liDivide, LongInteger & liQuotient, LongInteger & liModulus)
{
	// Front end to DivAndMod that takes the quotient and modulus values as LongInteger references
	LongIntegerUP upliQuotient;
	LongIntegerUP upliModulus;

	upliQuotient = make_unique<LongInteger>(liQuotient);
	upliModulus = make_unique<LongInteger>(liModulus);

	bool worked = DivAndMod(liValue, liDivide, upliQuotient, upliModulus);

	if (worked) {
		liQuotient = *upliQuotient;
		liModulus = *upliModulus;
	}
	return worked;
}


bool LongInteger::DivAndMod(const LongInteger & liValue, const LongInteger & liDivide, LongIntegerUP & upliQuotient, LongIntegerUP & upliModulus) {
	// The divide and modulus functions were created separately, but it will save a lot of hassle by combining them - especially as
	// it is the same code in the 2 functions


	// How to divide? Can you divide 1 digit at a time?
	// Division is big subtraction, but if the divisor is small that will be a lot of
	// subtractions.
	// However... the divisor can be multiplied until it is just a bit smaller than
	// the number being divided and then subtracted. This will reduce the number of subtractions

	bool bSuccess = true;
	// Dividing zero doesn't get you anywhere
	if (liValue.size == 0)
		return !bSuccess;

	// Compare sizes
	// If the divisor is bigger than the number being divided then result is zero and the modulus is the value
	if (liDivide.size > liValue.size) {
		upliQuotient = make_unique<LongInteger>(0);
		upliModulus = make_unique<LongInteger>(liValue);
		return bSuccess;
	}
	// Don't divide by zero
	if (liDivide.equalsZero()) {
		return !bSuccess;
	}

	LongInteger liDivCopy = liDivide;
	LongInteger liValueCopy = liValue;

	// Turn the calculation into a +ve dividing a +ve and also work out what the final sign will be
	bool bFinal = !(liValue.bPositive ^ liDivide.bPositive);
	liDivCopy.bPositive = true;
	liValueCopy.bPositive = true;


	// If the value is large and the divisor is at least half the size of the value, then Burnikel-Zeigler division is quicker
	if (liValueCopy.size > BURKINELZIEGLERCUTOFF) {
		if (liDivCopy.size > ((liValueCopy.size * 4) / 5)) {
			BurnikelZiegler(liValueCopy, liDivCopy, upliQuotient, upliModulus);
			upliQuotient->bPositive = bFinal;
			return bSuccess;
		}
		else {
			// Increase the size of the divisor until it is at least half the size of the value
			// Then do the division
			// Then divide the modulus by the amount we had "buffed" the divisor, noting the quotient
			// Then multiply the original quotient by the "buffed" amount and add the new quotient
			// This seems like a lot of work, but it is quicker

			UINT uIncrement = liValueCopy.size - liDivCopy.size;
			if (uIncrement <= 2) {
				uIncrement = 2;
			}
			else {
				uIncrement /= 2;
			}

			LongInteger liNewDivide = liDivCopy;
			LongInteger liOffset = uIncrement;
			liOffset *= LongInteger::BASEVALBITS;
			liNewDivide <<= liOffset;

			DivAndMod(liValueCopy, liNewDivide, upliQuotient, upliModulus);

			liNewDivide.bitshiftright(liOffset);
			LongIntegerUP upliNewQuotient = make_unique<LongInteger>(0);
			LongIntegerUP upliNewModulus = make_unique<LongInteger>(0);
			DivAndMod(*upliModulus, liNewDivide, upliNewQuotient, upliNewModulus);

			upliQuotient->bitshiftleft(liOffset);
			*upliQuotient += *upliNewQuotient;
			upliModulus = move(upliNewModulus);
			// Set the correct sign
			upliQuotient->bPositive = bFinal;

			return bSuccess;
		}
	}

	// Use a LongInteger for the subtractor as the number could potentially end up being very large
	LongInteger liNumOfSubtractions = 1;
	LongInteger liWorkingQuot = 0;
	LongInteger liSubtractor = liDivCopy;
	LongInteger liWorkingMod = liValueCopy;


	// multiply the divisor by 256 until the size is the same as the target.
	// Subtract until the divider is greater than the target.
	// Then divide by 256 and repeat until the divisor is back down to it's original size
	// We don't have fractions or decimals so that will be the end
	UINT iLevel = 0;
	while (liSubtractor.size < liWorkingMod.size) {
		liNumOfSubtractions *= BASEVAL;
		liSubtractor *= BASEVAL;
		++iLevel;
	}

	bool doLoop = true;
	while (doLoop) {
		while (liWorkingMod >= liSubtractor) {
			if (bShuttingDown) {
				return false;
			}
			liWorkingMod -= liSubtractor;
			liWorkingQuot += liNumOfSubtractions;
		}
		if (iLevel > 0) {
			liNumOfSubtractions /= BASEVAL;
			liSubtractor /= BASEVAL;
		}
		if (iLevel == 0) {
			doLoop = false;
		}
		else {
			--iLevel;
		}
	}

	upliQuotient = make_unique<LongInteger>(liWorkingQuot);
	upliQuotient->bPositive = bFinal;
	upliModulus = make_unique<LongInteger>(liWorkingMod);

	return bSuccess;
}


bool LongInteger::divideNumber(int iDivide) {
	// Divide using an integer

	// If the divisor is BASEVAL then call a special function
	// This is because the division operation uses division by BASEVAL internally,
	// so you would get endless recursion if you didn't handle this specific value differently
	if (iDivide == BASEVAL) {
		divHelper(iDivide);
		return !bOverflow;
	}
	if (iDivide > 0 && iDivide < 256) {
		this->divByByte((byte)iDivide);
		return !bOverflow;
	}
	if (iDivide < 0 && iDivide > -256) {
		this->divByByte((byte)std::abs(iDivide));
		this->bPositive = !(this->bPositive);
		return !bOverflow;
	}

	*this /= LongInteger(iDivide);

	return !bOverflow;
}


bool LongInteger::divHelper(int iDivide) {
	if (iDivide != BASEVAL) {
		return !bOverflow;
	}

	// This division is by the unit storage amount - i.e. move each digit down one
	// Slightly quicker version of shifting right by 8 bits
	if (size == 1) {
		digits[0] = 0;
	}
	else {
		for (UINT i = 1; i < size; ++i) {
			digits[i - 1] = digits[i];
		}
	}
	--size;
	digits[size] = 0;

	decreaseSize();

	return !bOverflow;
}

bool LongInteger::multHelper(int iMult) {
	if (iMult != BASEVAL) {
		return !bOverflow;
	}
	if (size >= maxSize)
	{
		recalcMaxSize();
		if (bOverflow)
			return !bOverflow;
	}

	// This multiplication is by the unit storage amount - i.e. move each digit up one
	for (int i = size; i > 0; --i) {
		digits[i] = digits[i - 1];
	}
	digits[0] = 0;
	++size;

	return !bOverflow;
}


bool LongInteger::multHelper2(UINT iMult) {
	// We want to increase the size of this number by iMult bytes
	UINT oldSize = size;
	size += iMult;
	recalcMaxSize();

	byte* newDigits = new byte[maxSize];
	memset(newDigits, 0, maxSize * sizeof(byte));
	// Copy the data. This works because it copies from zero upwards and the lowest digit is in place zero.
	memcpy(newDigits + iMult, digits, sizeof(byte) * oldSize);
	delete[] digits;
	digits = newDigits;

	return true;
}


bool LongInteger::increaseSize() {
	// The current 'maxSize' is not big enough. Let us see if we can increase the size
	// without making it bigger than 'ABSMAXSIZE'
	if (maxSize == ABSMAXSIZE) {
		bOverflow = true;
		return bOverflow;
	}

	UINT newMaxSize;
	// Try to work out the next size to set the value to
	if (maxSize >= SIZESTEP) {
		newMaxSize = maxSize + SIZESTEP;
	}
	else if (maxSize >= SMALLSIZESTEP) {
		newMaxSize = maxSize + SMALLSIZESTEP;
	}
	else {
		newMaxSize = maxSize + TINYSIZESTEP;
	}

	if (newMaxSize > ABSMAXSIZE)
		newMaxSize = ABSMAXSIZE;

	// Now to create a new data array of bytes on the heap, copy the existing values across and delete the original
	byte* newDigits = new byte[newMaxSize];
	// Copy the data. This works because it copies from zero upwards and the lowest digit is in place zero.
	memcpy(newDigits, digits, sizeof(byte) * maxSize);
	// Set the remaining digits to zero
	memset(newDigits + (maxSize * sizeof(byte)), 0, (newMaxSize - maxSize) * sizeof(byte));

	delete digits;
	digits = newDigits;
	maxSize = newMaxSize;

	return bOverflow;
}


bool LongInteger::decreaseSize() {
	// Can we decrease the size? The smallest size allowed is 'MINSIZE'
	if (maxSize <= MINSIZE)
		return false;

	// Check the size. Subtract 10 from maxSize to prevent borderline cases, where the program
	// starts repeatedly adding and removing data blocks
	UINT subtractSize;
	if (size > (SIZESTEP + SIZESTEP)) {
		subtractSize = SIZESTEP;
	}
	else if (size > (SMALLSIZESTEP + SMALLSIZESTEP)) {
		subtractSize = SMALLSIZESTEP;
	}
	else {
		subtractSize = TINYSIZESTEP;
	}

	if ((size + subtractSize) > (maxSize - 10))
		return false;

	UINT newMaxSize;
	if (size >= SIZESTEP) {
		newMaxSize = ((size / SIZESTEP) * SIZESTEP) + SIZESTEP;
	}
	else if (size >= SMALLSIZESTEP) {
		newMaxSize = ((size / SMALLSIZESTEP) * SMALLSIZESTEP) + SMALLSIZESTEP;
	}
	else {
		newMaxSize = ((size / TINYSIZESTEP) * TINYSIZESTEP) + TINYSIZESTEP;
	}
	if (newMaxSize < MINSIZE)
		newMaxSize = MINSIZE;

	// Check that the number can fit inside the new smaller structure
	bool allZero = true;
	for (UINT i = newMaxSize; i < maxSize && allZero; ++i) {
		if (digits[i] != 0) allZero = false;
	}
	if (!allZero)
		return false;

	// Create the new smaller structure
	byte* newDigits = new byte[newMaxSize];

	// Copy the data.
	memcpy(newDigits, digits, sizeof(byte) * newMaxSize);

	delete[] digits;
	digits = newDigits;
	maxSize = newMaxSize;

	return true;
}


bool LongInteger::isProcessing() {
	return bProcessing;
}


void LongInteger::setProcessing(bool bValue)
{
	bProcessing = bValue;
}

// Commenting these out as I need a better way of waiting for process completion

/*
void LongInteger::setProcessing(bool bValue, CWinThread *thrRef)
{
bProcessing = bValue;
if (bProcessing && thrRef != nullptr)
thrProcessingRef = thrRef;
if (!bProcessing)
thrProcessingRef = nullptr;
}


HANDLE LongInteger::getProcessingHandle()
{
return thrProcessingRef->m_hThread;
}
*/

bool LongInteger::isShuttingDown() {
	return bShuttingDown;
}

void LongInteger::setShuttingDown(bool bValue) {
	bShuttingDown = bValue;
}

bool LongInteger::modulus(const LongInteger & liDivide) {
	LongIntegerUP upliQuotient = make_unique<LongInteger>(0);
	LongIntegerUP upliModulus = make_unique<LongInteger>(0);

	bool bSuccess = DivAndMod(*this, liDivide, upliQuotient, upliModulus);

	if (!bSuccess) {
		*this = 0;
	}
	else {
		*this = *upliModulus;
	}

	return bOverflow;
}

LongInteger& LongInteger::operator%=(const LongInteger & liMod) {
	modulus(liMod);
	return *this;
}

LongInteger& LongInteger::operator%=(int iMod) {
	if (iMod <= 0)
		return *this;
	LongInteger value = iMod;
	modulus(value);
	return *this;
}

LongInteger LongInteger::operator%(const LongInteger & liMod) const {
	LongInteger value = *this;
	value %= liMod;
	return value;
}

LongInteger LongInteger::operator%(int iMod) const {
	if (iMod <= 0)
		return *this;
	LongInteger value = *this;
	value %= iMod;
	return value;
}

LongInteger LongInteger::operator+(int iAdd) const {
	if (iAdd == 0)
		return *this;
	LongInteger value = *this;
	value += iAdd;
	return value;
}

LongInteger LongInteger::operator-(int iMinus) const {
	if (iMinus == 0)
		return *this;
	LongInteger value = *this;
	value -= iMinus;
	return value;
}

LongInteger LongInteger::operator*(int iMult) const {
	LongInteger value = *this;
	value *= iMult;
	return value;
}

LongInteger LongInteger::operator/(int iDiv) const {
	if (iDiv == 0) {
		LongInteger liReturn(0);
		liReturn.bOverflow = true;
		return liReturn;
	}
	LongInteger value = *this;
	value /= iDiv;
	return value;
}

bool LongInteger::bitwiseand(const LongInteger & liAnd) {
	// Bitwise AND method
	// AND this with liAnd
	//
	// Loop through each byte in the digits array and AND them
	if (size <= 0 || liAnd.size <= 0)
	{
		reset(); // anything AND zero is zero
		return bOverflow;
	}

	UINT numLoops = (size > liAnd.size ? size : liAnd.size);

	for (UINT i = 0; i < numLoops; i++) {
		digits[i] &= liAnd.digits[i];
	}

	if (size > liAnd.size) {
		for (UINT i = liAnd.size; i < size; i++) {
			digits[i] = 0; // anything AND zero is zero
		}
	}

	checkSize();

	return bOverflow;
}

LongInteger LongInteger::operator&(const LongInteger & liAnd) {
	// Bitwise AND operator
	LongInteger value = *this;
	value &= liAnd;
	return value;
}

LongInteger LongInteger::operator&(int iAnd) {
	LongInteger value = *this;
	value &= iAnd;
	return value;
}

LongInteger& LongInteger::operator&=(const LongInteger & liAnd) {
	bitwiseand(liAnd);
	return *this;
}

LongInteger& LongInteger::operator&=(int iAnd) {
	bitwiseand(iAnd);
	return *this;
}

bool LongInteger::bitwiseor(const LongInteger & liOR) {

	// Bitwise OR method
	// OR this with liOR
	//
	// Loop through each byte in the digits array and OR them
	if (size <= 0 || liOR.size <= 0) // Anything OR zero is itself
		return bOverflow;

	// Don't want to overflow either of the numbers' internal byte arrays
	UINT numLoops = (size > liOR.size ? liOR.size : size);

	for (UINT i = 0; i < numLoops; i++) {
		digits[i] |= liOR.digits[i];
	}

	if (size > liOR.size) {
		for (UINT i = liOR.size; i < size; i++) {
			digits[i] = digits[i]; // anything OR zero is itself
		}
	}

	if (size < liOR.size) {
		for (UINT i = size; i < liOR.size; i++) {
			while (i >= maxSize) increaseSize();
			digits[i] = liOR.digits[i]; // Anything OR zero is itself
			size++;
		}
	}

	checkSize();

	return bOverflow;
}

LongInteger LongInteger::operator|(const LongInteger & liOR) {
	// Bitwise OR operator
	LongInteger value = *this;
	value |= liOR;
	return value;
}

LongInteger LongInteger::operator|(int iOR) {
	LongInteger value = *this;
	value |= iOR;
	return value;
}

LongInteger& LongInteger::operator|=(const LongInteger & liOR) {
	bitwiseor(liOR);
	return *this;
}

LongInteger& LongInteger::operator|=(int iOR) {
	bitwiseor(iOR);
	return *this;
}

bool LongInteger::bitwisenot() {
	// Invert all the bits
	for (UINT i = 0; i < size; i++) {
		digits[i] = ~(digits[i]);
	}

	checkSize(); // In case any leading digits have been set to zero

	return bOverflow;
}

LongInteger LongInteger::operator~() const {
	LongInteger value = *this;
	value.bitwisenot();
	return value;
}

bool LongInteger::bitwisexor(const LongInteger & liXOR) {

	// Bitwise XOR method
	// XOR this with liXOR
	//
	// Loop through each byte in the digits array and XOR them
	if (size <= 0 || liXOR.size <= 0) // Anything XOR zero is itself
		return bOverflow;

	// Don't want to overflow either of the numbers' internal byte arrays
	UINT numLoops = (size > liXOR.size ? liXOR.size : size);

	for (UINT i = 0; i < numLoops; i++) {
		digits[i] ^= liXOR.digits[i];
	}

	if (size > liXOR.size) {
		for (UINT i = liXOR.size; i < size; i++) {
			digits[i] = digits[i]; // anything XOR zero is itself
		}
	}

	if (size < liXOR.size) {
		for (UINT i = size; i < liXOR.size; i++) {
			while (i >= maxSize) increaseSize();
			digits[i] = liXOR.digits[i]; // Anything XOR zero is itself
			size++;
		}
	}

	checkSize();

	return bOverflow;
}

LongInteger LongInteger::operator^(const LongInteger & liXOR) {
	// Bitwise XOR operator
	LongInteger value = *this;
	value ^= liXOR;
	return value;
}

LongInteger LongInteger::operator^(int iXOR) {
	LongInteger value = *this;
	value ^= iXOR;
	return value;
}

LongInteger& LongInteger::operator^=(const LongInteger & liXOR) {
	bitwisexor(liXOR);
	return *this;
}

LongInteger& LongInteger::operator^=(int iXOR) {
	bitwisexor(iXOR);
	return *this;
}

bool LongInteger::bitshiftright(const LongInteger & liShift) {
	// Rightshift all the bits by liShift amount
	// Every multiple of 8 in liShift is a full byte to the right
	// So start by getting liShift div 8 and moving all bytes by that amount

	// This is an implementation that assumes the indexing can be by LongInteger
	// and not UINT as is assumed elsewhere (but has to use a cast as the array
	// uses UINT as an index

	// First a sanity check. A little like a sanity clause, but without the reindeer.
	// Shifting zero or shifting by zero achieves nothing - so just return
	if (size == 0 || liShift.size == 0) {
		return bOverflow;
	}

	LongInteger liMoveBytes = liShift;
	liMoveBytes.bitshiftright(BASEVALBITSSHIFT); // This should call the UNIT version
	UINT iMoveBits = liShift.digits[0] % BASEVALBITS;

	// And another check
	if (liMoveBytes > size) {
		init();
		checkSize();
		return bOverflow;
	}

	// The digits need to be shifted down by liMoveBytes, starting from zero
	for (UINT i = 0, j = (UINT)liMoveBytes; j < size; ++i, ++j) {
		digits[i] = digits[j];
	}
	// Blank out the other digits
	for (UINT uLoop = (size - (UINT)liMoveBytes); uLoop < size; ++uLoop) {
		digits[uLoop] = 0;
	}
	checkSize();

	// Create a bitmask
	byte bBitMask = 0;
	for (UINT i = 0; i < iMoveBits; i++) {
		bBitMask <<= 1;
		bBitMask += 1;
	}

	if (bBitMask == 0) return bOverflow;

	// Now move each digit by any bits left over
	UINT iUnderflow = 0;
	UINT iTemp;
	UINT index;
	for (UINT uLoop = size; uLoop > 0; --uLoop) {
		index = uLoop; // Index of digit to adjust converted to a UINT
		index--; // A workaround to deal with LongIntegers (and UINT) not being negative and the end test for the loop
		iTemp = digits[index] >> iMoveBits;
		iTemp += iUnderflow;
		iUnderflow = digits[index] & bBitMask;
		iUnderflow <<= (BASEVALBITS - iMoveBits);
		digits[index] = (byte)iTemp;
	}

	checkSize();
	return bOverflow;
}

bool LongInteger::bitshiftright(UINT uShift) {
	// Rightshift all the bits by uShift amount
	// Every multiple of 8 in uShift is a full byte to the right
	// So start by getting uShift div 8 and moving all bytes by that amount

	// First a sanity check. A little like a sanity clause, but without the reindeer.
	UINT uMoveBytes = uShift / 8;
	UINT iMoveBits = uShift % 8;
	if (uMoveBytes > size) {
		init();
		checkSize();
		return bOverflow;
	}

	// And another check
	// Shifting zero or shifting by zero achieves nothing - so just return
	if (size == 0 || uShift == 0) {
		return bOverflow;
	}

	// The digits need to be shifted down by uMoveBytes, starting from zero
	for (UINT i = 0, j = uMoveBytes; j < size; ++i, ++j) {
		digits[i] = digits[j];
	}
	// Blank out the other digits
	for (UINT uLoop = (size - uMoveBytes); uLoop < size; ++uLoop) {
		digits[uLoop] = 0;
	}
	checkSize();

	// Create a bitmask
	byte bBitMask = 0;
	for (UINT i = 0; i < iMoveBits; i++) {
		bBitMask <<= 1;
		bBitMask += 1;
	}

	if (bBitMask == 0) return bOverflow;

	// Now move each digit by any bits left over
	UINT iUnderflow = 0;
	UINT iTemp;
	// A separate index variable is a workaround to deal with LongIntegers (and UINT) not being negative and the end test for the loop
	for (UINT uLoop = size, index = size - 1; uLoop > 0; --uLoop, --index) {
		iTemp = digits[index] >> iMoveBits;
		iTemp += iUnderflow;
		iUnderflow = digits[index] & bBitMask;
		iUnderflow <<= (BASEVALBITS - iMoveBits);
		digits[index] = (byte)iTemp;
	}

	checkSize();
	return bOverflow;
}

bool LongInteger::bitshiftleft(const LongInteger & liShift) {
	// Leftshift all the bits by liShift amount
	// Every multiple of 8 in liShift is a full byte to the left
	// So start by getting liShift div 8 and moving all bytes by that amount

	// This is an implementation that assumes the indexing can be by LongInteger
	// and not UINT as is assumed elsewhere

	// First some sanity checks. A little like a sanity clause, but without the reindeer.
	// Left shifting zero doens't do anything (except cause issues with the loops)
	if (size == 0 || (size == 1 && digits[0] == 0))
		return bOverflow;
	// Check we aren't going to increase the number beyond max size
	LongInteger liMoveBytes = liShift;
	liMoveBytes.bitshiftright(BASEVALBITSSHIFT);
	UINT iMoveBits = liShift.digits[0] % BASEVALBITS;
	if (liMoveBytes > LongInteger::ABSMAXSIZE) {
		bOverflow = true;
		return bOverflow;
	}

	// And another check
	// Shifting zero or shifting by zero achieves nothing - so just return
	if (size == 0 || liShift.size == 0) {
		return bOverflow;
	}

	// Work out the new size needed
	UINT newSize = (UINT)(size + liMoveBytes);
	UINT oldSize = size;
	size = newSize;
	recalcMaxSize();

	// The bits below are all wrong
	// Got to here

	// The digits need to be shifted up by liMoveBytes
	// Some artificial manipulation of uMoveTo as we can't check for it being less than zero
	// as UINTs can't be negative (i.e stick in -1 and +1 where needed)
	UINT uMoveTo = (size - 1);
	UINT uMoveFrom = (uMoveTo - (size - oldSize)) + 1;

	while (uMoveFrom > 0) {
		digits[uMoveTo] = digits[(uMoveFrom - 1)];
		--uMoveFrom;
		--uMoveTo;
	}
	// Blank out the other digits
	for (UINT uLoop = 0; uLoop < (size - oldSize); ++uLoop) {
		digits[uLoop] = 0;
	}
	checkSize();

	// Create a bitmask
	byte bBitMask = 0;
	for (UINT i = 0; i < iMoveBits; i++) {
		bBitMask <<= 1;
		bBitMask += 1;
	}

	if (bBitMask == 0) return bOverflow;

	// Now move each digit by any bits left over
	UINT iMoveUp = 0;
	UINT iTemp;
	UINT index;
	for (UINT uLoop = 0; uLoop < size; ++uLoop) {
		index = uLoop;
		iTemp = digits[index] << iMoveBits;
		iTemp += iMoveUp;
		iMoveUp = iTemp / 256;
		digits[uLoop] = (byte)iTemp;
	}
	if (iMoveUp != 0) {
		size++;
		if (size > maxSize) {
			recalcMaxSize();
		}
		digits[size - 1] = (byte)iMoveUp;
	}
	checkSize();

	return bOverflow;
}

bool LongInteger::bitshiftleft(UINT uShift) {
	// Leftshift all the bits by liShift amount
	// Every multiple of 8 in liShift is a full byte to the left
	// So start by getting liShift div 8 and moving all bytes by that amount

	// First some sanity checks. A little like a sanity clause, but without the reindeer.
	// Left shifting zero doens't do anything (except cause issues with the loops)
	if (size == 0 || (size == 1 && digits[0] == 0))
		return bOverflow;
	// Check we aren't going to increase the number beyond max size
	UINT uMoveBytes = uShift / 8;
	UINT iMoveBits = uShift % 8;
	if (uMoveBytes > (LongInteger::ABSMAXSIZE - size)) {
		bOverflow = true;
		return bOverflow;
	}

	// And another check
	// Shifting zero or shifting by zero achieves nothing - so just return
	if (size == 0 || uShift == 0) {
		return bOverflow;
	}

	// Work out the new size needed
	UINT newSize = size + uMoveBytes;
	UINT oldSize = size;
	size = newSize;
	recalcMaxSize();

	// The bits below are all wrong
	// Got to here

	// The digits need to be shifted up by uMoveBytes
	// Some artificial manipulation of uMoveTo as we can't check for it being less than zero
	// as UINTs can't be negative (i.e stick in -1 and +1 where needed)
	UINT uMoveTo = (size - 1);
	UINT uMoveFrom = (uMoveTo - (size - oldSize)) + 1;

	while (uMoveFrom > 0) {
		digits[uMoveTo] = digits[(uMoveFrom - 1)];
		--uMoveFrom;
		--uMoveTo;
	}
	// Blank out the other digits
	for (UINT uLoop = 0; uLoop < (size - oldSize); ++uLoop) {
		digits[uLoop] = 0;
	}
	checkSize();

	// Create a bitmask
	byte bBitMask = 0;
	for (UINT i = 0; i < iMoveBits; i++) {
		bBitMask <<= 1;
		bBitMask += 1;
	}

	if (bBitMask == 0) return bOverflow;

	// Now move each digit by any bits left over
	UINT iMoveUp = 0;
	UINT iTemp;
	UINT index;
	for (UINT uLoop = 0; uLoop < size; ++uLoop) {
		index = uLoop;
		iTemp = digits[index] << iMoveBits;
		iTemp += iMoveUp;
		iMoveUp = iTemp / 256;
		digits[uLoop] = (byte)iTemp;
	}
	if (iMoveUp != 0) {
		size++;
		if (size > maxSize) {
			recalcMaxSize();
		}
		digits[size - 1] = (byte)iMoveUp;
	}
	checkSize();

	return bOverflow;
}

LongInteger LongInteger::operator >> (const LongInteger & rhs) {
	LongInteger value = *this;
	value >>= rhs;
	return value;
}

LongInteger LongInteger::operator >> (UINT rhs) {
	LongInteger value = *this;
	value >>= rhs;
	return value;
}

LongInteger& LongInteger::operator>>=(const LongInteger & rhs) {
	bitshiftright(rhs);
	return *this;
}

LongInteger& LongInteger::operator>>=(UINT rhs) {
	bitshiftright(rhs);
	return *this;
}

LongInteger LongInteger::operator<<(const LongInteger & rhs) {
	LongInteger value = *this;
	value <<= rhs;
	return value;
}

LongInteger LongInteger::operator<<(UINT rhs) {
	LongInteger value = *this;
	value <<= rhs;
	return value;
}

LongInteger& LongInteger::operator<<=(const LongInteger & rhs) {
	bitshiftleft(rhs);
	return *this;
}

LongInteger& LongInteger::operator<<=(UINT rhs) {
	bitshiftleft(rhs);
	return *this;
}

LongInteger* LongInteger::ToomCook3(const LongInteger & liOne, const LongInteger & liTwo, bool bBackgroundThread) {
	// A sanity check
	if (liOne.equalsZero() || liTwo.equalsZero())
		return new LongInteger(0);

	// kFactor is the split level. This will be implemented as Toom-3, which uses a kFactor of 3
	// The algorithm is specific to a kFactor of 3, but I'll create this constant to make it clear
	// why (and when) I'm using 3. This will be help if I ever try to implement ToomCook with a different kFactor
	const UINT kFactor = 3;

	// Note the signs of the two inputs for the final result
	bool bFinalSign = !(liOne.bPositive ^ liTwo.bPositive);

	// The ToomCook algorithm has 5 main steps
	// 1 - Splitting
	// 2 - Evaluation
	// 3 - Pointwise multiplication
	// 4 - Interpolation
	// 5 - Recomposition

	// Implement this as Toom-3 initially

	// 1 - Splitting
	// We split the numbers up into kFactor bits.
	LongInteger* liM[kFactor];
	LongInteger* liN[kFactor];
	for (UINT i = 0; i < kFactor; i++) {
		liM[i] = new LongInteger;
		liN[i] = new LongInteger;
	}


	UINT uSplit;

	// Split the numbers into kFactor(3) parts
	uSplit = liOne.size > liTwo.size ? liOne.size : liTwo.size;
	uSplit /= kFactor;
	if (uSplit == 0) uSplit = 1;

	uSplit = liOne.toomsplit(liM, uSplit);
	uSplit = liTwo.toomsplit(liN, uSplit);


	// 2 - Evaluation
	//
	// For Toom-3, we will end up with the equations:
	// p(x) = m2*x^2 + m1*x^1 + m0
	// q(x) = n2*x^2 + n1*x^1 + n0
	//
	// For evaluation, we will use the points 0, 1, -1, -2 & infinity
	//
	// p(0) = m0 + m1(0) + m2(0^2) = 0
	// p(1) = m0 + m1(1) + m2(1^2) = m0 + m1 + m2
	// p(-1) = m0 + m1(-1) + m2(-1^2) = m0 - m1 + m2
	// p(-2) = m0 + m1(-2) + m2(-2^2) = m0 - 2m1 + 4m2
	// p(@) = m2
	//
	// Faster evaluation
	// p0 = m0 + m2
	// p(0) = m0
	// p(1) = p0 + m1
	// p(-1) = p0 - m1
	// p(-2) = (p(-1) + m2) * 2 - m0
	// p(@) = m2

	// Note that the example above (taken from wikipedia) has the elements of m & n in the opposite order from our array

	// Array: 0=0, 1=1, 2=-1, 3=-2, 4=infinity
	LongInteger* liEvalM[5];
	LongInteger* liEvalN[5];
	LongInteger* liP0M = new LongInteger;
	LongInteger* liP0N = new LongInteger;
	for (UINT i = 0; i < 5; i++) {
		liEvalM[i] = new LongInteger;
		liEvalN[i] = new LongInteger;
	}

	*liP0M = *liM[0] + *liM[2];
	*liP0N = *liN[0] + *liN[2];
	*liEvalM[0] = *liM[0];
	*liEvalN[0] = *liN[0];
	//	*liEvalM[1] = *liP0M + *liM[1];
	*liEvalM[1] = *liP0M;
	*liEvalM[1] += *liM[1];
	//	*liEvalN[1] = *liP0N + *liN[1];
	*liEvalN[1] = *liP0N;
	*liEvalN[1] += *liN[1];
	//	*liEvalM[2] = *liP0M - *liM[1];
	*liEvalM[2] = *liP0M;
	*liEvalM[2] -= *liM[1];
	//	*liEvalN[2] = *liP0N - *liN[1];
	*liEvalN[2] = *liP0N;
	*liEvalN[2] -= *liN[1];
	//	*liEvalM[3] = ((*liEvalM[2] + *liM[2]) << 1) - *liM[0];
	*liEvalM[3] = *liEvalM[2];
	*liEvalM[3] += *liM[2];
	*liEvalM[3] <<= 1;
	*liEvalM[3] -= *liM[0];
	//	*liEvalN[3] = ((*liEvalN[2] + *liN[2]) << 1) - *liN[0];
	*liEvalN[3] = *liEvalN[2];
	*liEvalN[3] += *liN[2];
	*liEvalN[3] <<= 1;
	*liEvalN[3] -= *liN[0];
	*liEvalM[4] = *liM[2];
	*liEvalN[4] = *liN[2];

	// 3 - Pointwise multiplication
	//
	// This is where some recursion comes into effect.
	// If the operands are small enough we switch to a different algorithm

	// We will also check for threading

	LongInteger* liPointwise[5];

	if (LongInteger::TOOMCOOK3THREADING > liOne.size && LongInteger::TOOMCOOK3THREADING > liTwo.size)
	{
		for (UINT i = 0; i < 5; i++) {
			if (liEvalM[i]->size > TOOMCOOK3CUTOFF || liEvalN[i]->size > TOOMCOOK3CUTOFF) {
				liPointwise[i] = ToomCook3(*liEvalM[i], *liEvalN[i]);
			}
			else {
				liPointwise[i] = karatsuba(*liEvalM[i], *liEvalN[i], bBackgroundThread);
			}
		}
	}
	else
	{
		QueueOfThreads<LongIntWrapper>* qot = LongIntWrapper::getQOT();
		LongIntWrapper* liw0 = new LongIntWrapper;
		LongIntWrapper* liw1 = new LongIntWrapper;
		LongIntWrapper* liw2 = new LongIntWrapper;
		LongIntWrapper* liw3 = new LongIntWrapper;
		LongIntWrapper* liw4 = new LongIntWrapper;

		liw0->setParams(*liEvalM[0], *liEvalN[0]);
		liw1->setParams(*liEvalM[1], *liEvalN[1]);
		liw2->setParams(*liEvalM[2], *liEvalN[2]);
		liw3->setParams(*liEvalM[3], *liEvalN[3]);
		liw4->setParams(*liEvalM[4], *liEvalN[4]);

		LIfunction fp = &LongInteger::ToomCook3;

		liw0->setStartMethod(fp);
		liw1->setStartMethod(fp);
		liw2->setStartMethod(fp);
		liw3->setStartMethod(fp);
		liw4->setStartMethod(fp);

		qot->addToQueue(liw0);
		qot->addToQueue(liw1);
		qot->addToQueue(liw2);
		qot->addToQueue(liw3);
		qot->addToQueue(liw4);

		if (bBackgroundThread) {
			qot->iAmWaiting(); // Only call this if this process is called in a background thread.
		}

		qot->waitForThread(liw0);
		qot->waitForThread(liw1);
		qot->waitForThread(liw2);
		qot->waitForThread(liw3);
		qot->waitForThread(liw4);

		if (bBackgroundThread) {
			qot->iHaveStoppedWaiting();
		}

		liPointwise[0] = liw0->getResult();
		liPointwise[1] = liw1->getResult();
		liPointwise[2] = liw2->getResult();
		liPointwise[3] = liw3->getResult();
		liPointwise[4] = liw4->getResult();

		delete liw0;
		delete liw1;
		delete liw2;
		delete liw3;
		delete liw4;
	}

	// 4 - Interpolation
	//
	// This is the most complex step. It is the reverse of the Evaluation step
	// We need to determine the coefficients for the polynomial given the points used
	// This leads to a matrix
	// |r(0)  |     |0^0   0^1   0^2   0^3   0^4 |    |r0|
	// |r(1)  |     |1^0   1^1   1^2   1^3   1^4 |    |r1|
	// |r(-1) |  =  |-1^0  -1^1  -1^2  -1^3  -1^4|  = |r2|
	// |r(-2) |     |-2^0  -2^1  -2^2  -2^3  -2^4|    |r3|
	// |r(@)  |     |0     0     0     0     1   |    |r4|
	//
	// | 1   0   0   0   0 |   |r0|
	// | 1   1   1   1   1 |   |r1|
	// | 1   -1  1   -1  1 |   |r2|
	// | 1   -2  4   -8  16|   |r3|
	// | 0   0   0   0   1 |   |r4|
	//
	// We can make use of the fact that due to the choice of evaluation points, the matrix is invertable
	//
	// |r0|  | 1     0     0     0     0   |   |r(0) |
	// |r1|  | 1/2   1/3   -1    1/6   -2  |   |r(1) |
	// |r2|  | -1    1/2   1/2   0     -1  |   |r(-1)|
	// |r3|  | -1/2  1/6   1/2   -1/6  2   |   |r(-2)|
	// |r4|  | 0     0     0     0     1   |   |r(@) |
	//
	// The difficulty is in finding an efficient method to compute the above
	// A sequence for Toom-3 given by Bodrato will be used

	LongInteger* liResult[5];
	for (UINT i = 0; i < 5; i++)
		liResult[i] = new LongInteger;

	*liResult[0] = *liPointwise[0];
	*liResult[4] = *liPointwise[4];
	//	*liResult[3] = (*liPointwise[3] - *liPointwise[1]) / 3;
	*liResult[3] = *liPointwise[3];
	*liResult[3] -= *liPointwise[1];
	*liResult[3] /= 3;
	//	*liResult[1] = (*liPointwise[1] - *liPointwise[2]) >> 1;
	*liResult[1] = *liPointwise[1];
	*liResult[1] -= *liPointwise[2];
	*liResult[1] >>= 1;
	//	*liResult[2] = *liPointwise[2] - *liPointwise[0];
	*liResult[2] = *liPointwise[2];
	*liResult[2] -= *liPointwise[0];
	//	*liResult[3] = ((*liResult[2] - *liResult[3]) >> 1) + (*liPointwise[4] << 1);
	*liResult[3] = (*liResult[2] - *liResult[3]);
	*liResult[3] >>= 1;
	*liResult[3] += (*liPointwise[4] << 1);
	//	*liResult[2] = *liResult[2] + *liResult[1] - *liResult[4];
	*liResult[2] += *liResult[1];
	*liResult[2] -= *liResult[4];
	//	*liResult[1] = *liResult[1] - *liResult[3];
	*liResult[1] -= *liResult[3];


	// 5 - Recomposition
	//
	// We have the parts of the final values. Time to put it back together
	for (UINT i = 1; i < 5; i++) {
		*liResult[i] = *liResult[i] << (BASEVALBITS * (i * uSplit));
	}

	LongInteger* liReturn = new LongInteger;
	for (UINT i = 0; i < 5; i++) {
		*liReturn += *liResult[i];
	}

	// Memory clean up
	for (UINT i = 0; i < kFactor; i++) {
		delete liM[i];
		delete liN[i];
	}
	for (UINT i = 0; i < 5; i++) {
		delete liEvalM[i];
		delete liEvalN[i];
		delete liPointwise[i];
		delete liResult[i];
	}
	delete liP0M;
	delete liP0N;

	liReturn->bPositive = bFinalSign;
	if (liReturn->equalsZero()) liReturn->bPositive = true;


	return liReturn;
}

UINT LongInteger::toomsplit(LongInteger * *liList, UINT uDigits) const {
	// liList is an vector of LongIntegers. We will split up *this into chunks and
	// put these in liList
	// We assume that the members of liList have already been created, so we just need to fill them in

	UINT uStep = uDigits;
	UINT uNumSplits = 3;
	if ((uStep * 2) >= size) uNumSplits = 2;
	if (uStep >= size) uNumSplits = 1;

	for (UINT i = 0; i < uNumSplits; i++) {
		UINT uStart = uStep * i;
		UINT uEnd = uStart + uStep;
		if (uEnd > size) uEnd = size;
		// Handle numbers where the digits don't divide into 3 (i.e. the highest number chunk has more digits than the others)
		if (i == 2) uEnd = size;

		// Put the current chunk into the LongInteger
		liList[i]->size = (uEnd - uStart);
		liList[i]->recalcMaxSizeAndClear();
		memcpy(liList[i]->digits, digits + uStart, uEnd - uStart);
		liList[i]->checkSize(); // Get rid of any leading zeroes
	}

	if (uNumSplits < 3)
		liList[2]->assignNumber(0);
	if (uNumSplits < 2)
		liList[1]->assignNumber(0);

	return uStep; // Return the number of digits each has been divided into
}

vector<LongIntegerUP> LongInteger::split(LongIntegerUP & liToSplit, UINT uNumParts, UINT uDigits) {
	// We will split up the input LongInteger into uNumParts and return as
	// an array of LongIntegers
	// We will create the LongIntegers in this method

	vector<LongIntegerUP> vList(uNumParts);
	for (UINT i = 0; i < uNumParts; i++) {
		vList[i] = make_unique<LongInteger>(0);
	}

	UINT uNumSplits = uNumParts;
	while ((uDigits * (uNumParts - 1) >= liToSplit->size) && (uNumSplits > 1))
		uNumSplits--;

	if (uNumSplits == 0) return vList;

	for (UINT i = 0; i < uNumSplits; i++) {
		UINT uStart = uDigits * i;
		UINT uEnd = uStart + uDigits;
		// Handle numbers that don't evenly divide into uDigit parts
		if (uEnd > liToSplit->size) uEnd = liToSplit->size;
		if (i == (uNumSplits - 1)) uEnd = liToSplit->size;

		// Put the current chunk into the LongInteger
		vList[i]->size = (uEnd - uStart);
		vList[i]->recalcMaxSizeAndClear();
		memcpy(vList[i]->digits, liToSplit->digits + uStart, uEnd - uStart);
		vList[i]->checkSize();
	}

	while (uNumSplits < uNumParts) {
		vList[uNumSplits]->assignNumber(0);
		uNumSplits++;
	}

	return move(vList);
}

LongInteger LongInteger::operator-() const {
	// Negate the LongInteger
	// We will return a copy with the sign inverted
	LongInteger liReturn(*this);
	liReturn.bPositive = !liReturn.bPositive;
	return liReturn;
}

LongInteger LongInteger::operator+() const {
	// Added for completeness
	// Makes no change to the number
	return LongInteger(*this);
}

void LongInteger::assignByteArray(byte * newArray, UINT newSize) {
	// Copy a byte array
	size = newSize;
	recalcMaxSize();
	memcpy(digits, newArray, newSize);
	checkSize();
}

bool LongInteger::divByByte(byte bDiv) {
	// Divide this by a number between 1 and 255
	if (size == 0) return !bOverflow;

	unsigned short remainder = 0;
	unsigned short working;
	for (UINT i = size; i != 0; i--) {
		remainder += digits[i - 1];
		working = remainder / bDiv;
		remainder = remainder % bDiv;
		digits[i - 1] = (byte)working;
		remainder *= 256;
	}

	checkSize();
	return !bOverflow;
}


string LongInteger::toHexString() const {
	// Output the number represented as a hex string (helps in testing really big numbers)
	char hexchars[] = "0123456789ABCDEF";

	stringstream resultstream;
	byte highValue;
	byte lowValue;
	for (UINT i = 0; i < size; i++) {
		highValue = digits[i] / 16;
		lowValue = digits[i] % 16;

		if (i != 0) resultstream << ".";
		resultstream << i;
		resultstream << highValue;
		resultstream << lowValue;
	}
	return resultstream.str();
}



string LongInteger::toArrayNumbers() {
	// Output the number represented as each decimal number in the array (helps in testing really big numbers)
	stringstream result;
	for (UINT i = 0; i < size; i++) {
		if (i != 0) result << ".";
		result << "[" << i << "]" << digits[i];
	}
	return result.str();
}


void LongInteger::RestoringDivision(LongInteger & liValue, LongInteger & liDiv, LongInteger * liResult, LongInteger * liModulus) {
	// Slow division - restoring division
	// Divide N by D, placing the quotient in Q and the remainder in R

	// n = number of digits in the quotient
	// q(n) is the nth digit of the quotient


	// P = N
	// D = D << n
	// for i = n-1 to 0
	//   P = 2P - D
	//   if P >= 0 then
	//		q(i) = 1
	// else
	//   q(i) = 0
	//   P = P + D

	/*
	7/2=111/10
	P=111
	D=1000
	i=1
	P=2P-D=1110-1000=110
	q(1)=1
	i=0
	P=2P-D=1100-1000=100
	q(0)=1
	P>>2=1
	Q=11

	9/2=1001/10
	P=1001
	D=10<<3=10000
	i=2
	P=2P-D=10010-10000=10
	q(2)=1
	i=1
	P=2P-D=100-10000=-1100
	q(1)=0
	P=-1100+10000=100
	i=0
	P=2P-D=1000-10000=-1000
	q(0)=0
	P=-1000+10000=1000
	P>>3=1

	8/2=1000/10
	P=1000
	D=10<<3=10000
	i=2
	P=2P-D=10000-10000=0
	q(2)=1
	i=1
	P=2P-D=0-10000=-10000
	q(1)=0
	P=-10000+10000=0
	i=0
	P=2P-D=0-10000=-100000
	q(0)=0
	P=-10000+10000=0
	P>>3=0
	*/

	// I understand how this works in binary. Still puzzled about higher bases
	// So let us implement this non-disaster-in-progress in binaryness

	// The number must be larger than the divisor for it to work
	// Well, technically if the divisor is larger then the remainder is the original number
	if (liValue < liDiv) {
		*liResult = 0;
		*liModulus = liValue;
		return;
	}

	LongInteger P = liValue;
	LongInteger D = liDiv << (liValue.size * BASEVALBITS);
	byte* Q = new byte[liValue.size];
	for (UINT i = liValue.size; i > 0; i--) {
		Q[i - 1] = 0;
		for (UINT j = 8; j > 0; j--) {
			P <<= 1;
			P -= D;
			if (P >= 0) {
				// Set the appropriate bit in Q
				byte addbit = 1 << (j - 1);
				Q[i - 1] += addbit;
			}
			else {
				P += D;
			}
		}
	}
	P >>= (liValue.size * BASEVALBITS);

	liResult->assignByteArray(Q, liValue.size);
	*liModulus = P;
	delete Q;
}

void LongInteger::BurnikelZiegler(const LongInteger & liValue, const LongInteger & liDiv, LongIntegerUP & liResult, LongIntegerUP & liModulus) {
	// Looked at other algorithm (e.g. Newton-Raphson division) and many of them use floating point numbers
	// So we shall move on to Burnikel-Ziegler division

	// The first part is DivTwoDigitsByOne
	// It needs to split the numbers, so we shall test the split code

	// Very much in the testing phase, hence the chaotic layout (plus it is rather hard to understand the paper as I don't really
	// know maths notation - so a lot of trial and error)



	// DivTwoDigitsByOne(AHigh, ALow, B), return quotient Q and remainder S
	//
	// 1) Let [a1,a2] = AH, [a3,a4] = AL, and [b1,b2] = B
	// 2) [q1,R] = DivThreeHalvesByTwo(a1,a2,a3,b1,b2)
	// 3) Let [r1,r2]=R
	// 4) [q2,S] = DivThreeHalvesByTwo(r1,r2,a4,b1,b2)
	// 5) Return Q=[q1,q2] and S

	// DivThreeHalvesByTwo(a1,a2,a3,b1,b2)
	//
	// 6) q=[a1,a2]/b1;
	// 7) c=[a1,a2]-q*b1
	// 8) D=q*b2
	// 9) R=[r1,r2]=[c,a3]-D
	//10) if(R<0) {
	//11)   q--;
	//12)   R+=B;
	//13)   if(R<0) {
	//14)      q--;
	//15)      R+=B;
	//16)   }
	//17) }
	//18) Return quotient q and remainder R

	UINT uDigits = (liValue.size + 3) / 4;
	vector<LongIntegerUP> vASplit(2);

	// tempUP added to make gcc compiler happy. VS accepts this as an anonymous
	// parameter, but gcc refuses to compile
	LongIntegerUP tempUP = make_unique<LongInteger>(liValue);
	vASplit = move(split(tempUP, 2, uDigits * 2));

	LongIntegerUP tempUP2 = make_unique<LongInteger>(liDiv);
	vector<LongIntegerUP> vResult = DivTwoDigitsByOne(vASplit[1], vASplit[0], tempUP2, uDigits);

	liResult = move(vResult[0]);
	liModulus = move(vResult[1]);

}

vector<LongIntegerUP> LongInteger::DivTwoDigitsByOne(LongIntegerUP & AHigh, LongIntegerUP & ALow, LongIntegerUP & B, UINT uNumDigits) {
	// DivTwoDigitsByOne(AHigh, ALow, B), return quotient Q and remainder S
	//
	// 1) Let [a1,a2] = AH, [a3,a4] = AL, and [b1,b2] = B
	// 2) [q1,R] = DivThreeHalvesByTwo(a1,a2,a3,b1,b2)
	// 3) Let [r1,r2]=R
	// 4) [q2,S] = DivThreeHalvesByTwo(r1,r2,a4,b1,b2)
	// 5) Return Q=[q1,q2] and S


	/*
	Input Two nonnegative integers A and B, such that A<βnB and βn/2 ≤ B<βn.
	n must be even.
	Output The quotient A/B and the remainder A mod B.
	1. Let A = A3β3n/2 +A2βn +A1βn/2 +A0 and B = B1βn/2 +B0, with 0 ≤ Ai <
	βn/2 and 0 ≤ Bi < βn/2.
	2. Compute the high half Q1 of the quotient as Q1 = A3βn+A2βn/2+A1
	B with remainder
	R1 using algorithm 3.4.
	3. Compute the low half Q0 of the quotient as Q0 = R1βn/2+A4
	B with remainder
	R0 using algorithm 3.4.
	4. Return the quotient Q = Q1βn/2 + Q0 and the remainder R = R0.

	*/
	vector<LongIntegerUP> vReturn(2); // Return Q & S

									  // Decide how many digits we are chopping up the numbers by (it needs to be consistent)
	if (uNumDigits == 0) uNumDigits = 1;

	vector<LongIntegerUP> vWorking;
	vWorking = move(LongInteger::split(AHigh, 2, uNumDigits));
	LongIntegerUP a1 = move(vWorking[1]);
	LongIntegerUP a2 = move(vWorking[0]);
	vWorking = move(LongInteger::split(ALow, 2, uNumDigits));
	LongIntegerUP a3 = move(vWorking[1]);
	LongIntegerUP a4 = move(vWorking[0]);
	vWorking = move(LongInteger::split(B, 2, uNumDigits));
	LongIntegerUP b1 = move(vWorking[1]);
	LongIntegerUP b2 = move(vWorking[0]);

	vector<LongIntegerUP> vResult1, vResult2;
	// 2) [q1,R] = DivThreeHalvesByTwo(a1,a2,a3,b1,b2)
	LongInteger a1a2a3 = (*a1 << (uNumDigits * BASEVALBITS * 2)) + (*a2 << (uNumDigits * BASEVALBITS)) + *a3;

	if (a1a2a3 < *B) {
		vResult1.push_back(make_unique<LongInteger>(LongInteger()));
		vResult1.push_back(make_unique<LongInteger>(a1a2a3));
	}
	else
		vResult1 = DivThreeHalvesByTwo(a1, a2, a3, b1, b2, uNumDigits);

	// 3) Let [r1,r2]=R
	vWorking = move(LongInteger::split(vResult1[1], 2, uNumDigits));
	LongIntegerUP r1 = move(vWorking[1]);
	LongIntegerUP r2 = move(vWorking[0]);

	// 4) [q2,S] = DivThreeHalvesByTwo(r1,r2,a4,b1,b2)
	a1a2a3 = (*vResult1[1] << (uNumDigits * BASEVALBITS)) + *a4;
	if (a1a2a3 < *B) {
		vResult2.push_back(make_unique<LongInteger>(LongInteger()));
		vResult2.push_back(make_unique<LongInteger>(a1a2a3));
	}
	else {
		vResult2 = DivThreeHalvesByTwo(r1, r2, a4, b1, b2, uNumDigits);
	}
	// 5) Return Q=[q1,q2] and S
	vReturn[1] = move(vResult2[1]);
	vector<LongIntegerUP> Q(2);
	Q[1] = move(vResult1[0]);
	Q[0] = move(vResult2[0]);
	vReturn[0] = move(merge(Q, 2, uNumDigits));

	return move(vReturn);
}

vector<LongIntegerUP> LongInteger::DivThreeHalvesByTwo(LongIntegerUP & a2, LongIntegerUP & a1, LongIntegerUP & a0, LongIntegerUP & b1, LongIntegerUP & b0, UINT uNumDigits) {
	// DivThreeHalvesByTwo(a1,a2,a3,b1,b2)
	//
	// 6) q=[a1,a2]/b1;
	// 7) c=[a1,a2]-q*b1
	// 8) D=q*b2
	// 9) R=[r1,r2]=[c,a3]-D
	//10) if(R<0) {
	//11)   q--;
	//12)   R+=B;
	//13)   if(R<0) {
	//14)      q--;
	//15)      R+=B;
	//16)   }
	//17) }
	//18) Return quotient q and remainder R

	/*
	Input Two nonnegative integers A and B, such that A<βnB and β2n/2 ≤ B <
	β2n. n must be even.
	Output The quotient A/B and the remainder A mod B.
	1. Let A = A2β2n + A1βn + A0 and B = B1βn + B0, with 0 ≤ Ai < βn and
	0 ≤ Bi < βn.
	2. If A2 < B1, compute Q = A2βn+A1 / B1  with remainder R1 using algorithm 3.3;
	otherwise, let Q = βn − 1 and R1 = (A2 − B1)βn + A1 + B1.
	3. R ← R1βn + A4 − QB 0
	4. If R < 0, R ← R + B and Q ← Q − 1.
	5. If R < 0, R ← R + B and Q ← Q − 1.
	6. Return Q = Q and R = R.
	*/

	/*
	For A/B, B needs to be less than A, but more than A/10.
	The second criteria - B >= (BASE^2n)/2 & B < BASE^2n doesn't seem necessary in my tests so far. Will check further

	If B is less than A/10, then it needs to be multiplied by 10 (for base 256, this equates to left shifted)
	and then the final result also needs left shifted by the same amount, the high digits of the remainder added (and removed from the remainder)
	Checking for this is best done in the calling program
	*/

	/*
	This has ended up diverging from the algorithm described and from an example implementation I found, which
	worries me somewhat. Part of it is because I'm working in base 256 and the descriptions
	are for binary, but even so there shouldn't have been major changes.
	There is even a completely new logic block to handle scenarios not mentioned in the original algorithm,
	and an optimisation attempt that is getting so complex I'm losing track of what it does.
	This is all going horribly wrong.
	*/

	vector<LongIntegerUP> vResult(2); // To hold q & R
	vector<LongIntegerUP> vMerge(2);

	LongIntegerUP B(nullptr);
	LongIntegerUP Q, R;

	Q = make_unique<LongInteger>(0);
	R = make_unique<LongInteger>(0);

	if (*b1 != 0) {
		*Q = ((*a2) << (uNumDigits * LongInteger::BASEVALBITS)) + (*a1);
		// The next 2 lines can be done recursively as they are division and modulus

		if (Q->size > BURKINELZIEGLERCUTOFF) {
			LongIntegerUP temp;
			BurnikelZiegler(*Q, *b1, temp, R);
			Q = move(temp);
		}
		else {
			LongIntegerUP Q2 = make_unique<LongInteger>(0);
			DivAndMod(*Q, *b1, Q2, R);
			Q = move(Q2);
		}
	}
	else {
		// I am baffled. The line below doesn't work as expected and instead gives the result 255
		// no matter what value uNumDigits is. However, the calculation works.
		// I've worked out why the number goes wrong - it is calculating 1 rightshifted as a UINT,
		// which can't be shifted more than 3 bytes left.
		// However, I cannot explain why the calculation still works.
		*Q = (1 << (uNumDigits * BASEVALBITS)) - 1;
		*R = ((*a2) << (uNumDigits * LongInteger::BASEVALBITS)) + *a1;
	}

	*R = (*R << (uNumDigits * LongInteger::BASEVALBITS)) + *a0 - (*Q * *b0);

	vMerge[0] = make_unique<LongInteger>(*b0);
	vMerge[1] = make_unique<LongInteger>(*b1);
	B = move(merge(vMerge, 2, uNumDigits));

	// Added to handle a scenario not mentioned in the algorithm
	// Need to speed this up a bit as it can loop for up to 256^uNumDigits-1 times - which can be a lot!
	// Speed up code added by adding left-shifts. uDiff is the number of bits to left-shift
	// There are still awkward scenarios. The worst case is that this loop runs for log2(B) times, which isn't great
	// but a lot less than before

	while (*R >= *B || *R < 0) {
		if (*R >= *B) {
			if (R->size < B->size) {
				*R -= *B;
				(*Q)++;
			}
			else {
				UINT uDiff = R->size - B->size;
				uDiff *= BASEVALBITS;
				// Try to get the exact number of bits different
				if (R->digits[(R->size - 1)] > B->digits[(B->size - 1)]) {
					int uDiffBits = R->digits[(R->size - 1)] / B->digits[(B->size - 1)];
					while (uDiffBits > 1) {
						uDiffBits /= 2;
						uDiff++;
					}
				}
				else {
					int uDiffBits = B->digits[(B->size - 1)] / R->digits[(R->size - 1)];
					while (uDiffBits > 1) {
						uDiffBits /= 2;
						uDiff--;
					}
				}
				// *temp created to check we aren't deleting too large a number
				// It is very hard to get the balance between too large and too small
				// This is an overhead, but it should reduce the number of loops and so
				// save more than it costs
				// Changed the test as I encountered a scenario where the overall while loop went into an infinite cycle
				LongInteger* temp = new LongInteger(*B << uDiff);
				while (temp->size == R->size && temp->digits[temp->size - 1] > R->digits[R->size - 1] && uDiff > 0) {
					*temp >>= 1;
					uDiff--;
				}
				if (temp->size > 1 && temp->size == R->size && temp->digits[temp->size - 1] == R->digits[R->size - 1] &&
					temp->digits[temp->size - 2] > R->digits[R->size - 2] && uDiff > 0) {
					*temp >>= 1;
					uDiff--;
				}

				*R -= *temp;
				delete temp;
				*Q += (LongInteger(1) << uDiff);
			}
		}
		else {
			// In some scenarios R can end up massively negative, so make B a lot bigger
			if (R->size < B->size) {
				// If B is already bigger than R then just add it to R to make R positive
				*R += *B;
				(*Q)--;
			}
			else {
				UINT uDiff = R->size - B->size;
				uDiff *= BASEVALBITS;
				// Try to get the exact number of bits different
				int uDiffBits = R->digits[(R->size - 1)] / B->digits[(B->size - 1)];
				while (uDiffBits > 1) {
					uDiffBits /= 2;
					uDiff++;
				}
				if (uDiff > 0)
					uDiff--;

				*R += (*B << uDiff);
				*Q -= (LongInteger(1) << uDiff);
			}
		}
	}


	vResult[0] = move(Q);
	vResult[1] = move(R);

	return vResult;

}

LongIntegerUP LongInteger::merge(vector<LongIntegerUP> & vList, UINT uNumParts, UINT uSizeParts) {
	// Merge the contents of liList into a single LongInteger

	// Need to rework this as I've hit scenarios where the components can be bigger than uSizeParts
	// It originally used memcpy for speed, but with potentially overlapping values that can't be used
	LongIntegerUP liReturn;

	LongInteger liWorking;

	for (UINT i = 0; i < uNumParts; i++) {
		liWorking += (*vList[i] << (i * uSizeParts * BASEVALBITS));
	}

	liReturn = make_unique<LongInteger>(liWorking);

	return liReturn;
}


bool LongInteger::factorial()
{
	// Can't find any way other than multiplying sequentially, but I'll have a think

	if (!bPositive)
	{
		bOverflow = true;
		return false;
	}

	if (equalsZero())
	{
		assignNumber(1);
		return !bOverflow;
	}

	LongInteger* counter = new LongInteger(*this);
	LongInteger* runningTotal = new LongInteger(1);

	while (*counter > 1 && runningTotal->bPositive)
	{
		*runningTotal *= *counter;
		(*counter)--;
	}

	if (runningTotal->bPositive)
	{
		copy(*runningTotal);
	}
	else
	{
		bOverflow = true;
	}
	return !bOverflow;
}


LongInteger LongInteger::sqrt(const LongInteger & liInput)
{
	// Calculate the positive square root (rounded to the nearest integer) of the input value

	// Now the question is ... how do you calculate square roots for a number held in a byte array?

	// The square root will have approximately half the number of digits and the leading digit will be changed to the
	// square root of itself. This has so far given a reasonable starting guess value

	LongInteger liGuess; // The guess at what the square root is

	UINT index = 0;
	for (UINT i = 0; i < liInput.size; i += 2)
	{
		UINT temp = liInput.digits[i];
		LongInteger liTemp(temp);
		liTemp <<= (BASEVALBITS * index);
		liGuess += liTemp;
		index++;
	}
	liGuess.digits[liGuess.size - 1] = (byte)std::sqrt(liGuess.digits[liGuess.size - 1]);

	// We now have a guess for the squareroot.
	// Using the Babylonian method:
	// To calculate sqrt(a), we take guess x and see if x^2 is within 1 of a.
	// If not, we take (x + a/x)/2 as the new x and try again
	// This will need to be tested for very large values. Tests of up to 100,000 digit numbers have
	// passed and the performance has been good.

	bool foundX = false;
	LongInteger liPossible;

	while (!foundX)
	{
		liPossible = (liGuess + (liInput / liGuess)) / 2;
		if (abs(liPossible - liGuess) <= 1)
		{
			foundX = true;
			liGuess = liPossible;
			// We've found an answer that is either the value we want or 1 more than the value we want
			// (remember we are rounding down, so 4.999999 would become 4)
			if ((liGuess * liGuess) > liInput)
			{
				liGuess--;
			}
		}
		else
		{
			liGuess = liPossible;
		}
	}

	return liGuess;
}

LongInteger LongInteger::sqr(const LongInteger & liValue)
{
	// I've ended up wanted to square values often enough that a dedicated function for it would be useful
	return (liValue * liValue);
}


LongInteger LongInteger::pow(const LongInteger & liValue, const LongInteger & liPower)
{
	// A more user-friendly power calculation algorithm.
	// It calls the powerCalc algorithm in such a way that the 2 input parameters aren't changed and the return
	// value is the result rather than a bool
	LongInteger liReturn(liValue);
	liReturn.powerCalc(liPower);
	return liReturn;
}

/*
LongInteger LongInteger::factorial(const LongInteger & liValue)
{
	PrimeSwing ps;
	return ps.Factorial(liValue);
}
*/

LongInteger LongInteger::log(const LongInteger & liValue)
{
	// We will calculate the log rounded down to the nearest whole integer

	// To calculate the first digit of the log take the value and divide repeatedly by the log base
	// until the value is less than the log base. This is the integer part of the answer
	// To get the first digit after the decimal point you would take the final value and raise to the power of the log base
	// and repeat the process above. Continue until you have as many digits as you need.
	// Here we only need 1 so it is much simpler.
	//
	// As the data is held against base 256, we shall calculate log256
	// And this is MUCH easier. It is the number of digits minus 1.

	if (!(liValue.equalsZero()) && liValue.bPositive)
	{
		return LongInteger(liValue.size - 1);
	}
	else
	{
		LongInteger returnValue;
		returnValue.bOverflow = true;
		return returnValue;
	}
}

LongInteger LongInteger::log(const LongInteger & liValue, const LongInteger & liBase)
{
	// To calculate the first digit of the log take the value and divide repeatedly by the log base
	// until the value is less than the log base. This is the integer part of the answer
	// To get the first digit after the decimal point you would take the final value and raise to the power of the log base
	// and repeat the process above. Continue until you have as many digits as you need.
	// Here we only need the integer value so it is much simpler.

	if (liValue.equalsZero() || !liValue.bPositive || liBase.equalsZero() || !liBase.bPositive || liValue == 1)
	{
		LongInteger returnValue;
		returnValue.bOverflow = true;
		return returnValue;
	}

	LongInteger liRoot(liValue);
	LongInteger liCount;

	while (liRoot > liBase)
	{
		liRoot /= liBase;
		liCount++;
	}

	return liCount;
}

LongInteger LongInteger::ln(const LongInteger & lin)
{
	// Natural log.
	// The constant 'E' is the approximate value of e times 256^12 (or more if read from file) - i.e. e shifted left 11 bytes and then rounded off
	LongInteger workingValue(lin);

	// Take the input value, shift it left so it is the same 'base' as E then repeatedly divide
	LongInteger returnValue;

	LongInteger quotient, modulus;

	workingValue <<= (BASEVALBITS * SIZEOFE);
	while (workingValue > LongInteger::E)
	{
		LongInteger::DivAndMod(workingValue, LongInteger::E, quotient, modulus);
		// As 'E' is multiplied by 256^12 we need to adjust the result of the division by the same amount
		workingValue = quotient << (BASEVALBITS * SIZEOFE);
		// To avoid rounding errors as much as possible, let us add the modulus back in
		// We need to adjust it upwards by 256^12 and then divide by E to get the part of the modulus we need
		// (it is a fraction with base 'E'*256^12, which is why we adjust it by these values. It does make sense. Trust me.)
		modulus <<= (BASEVALBITS * SIZEOFE);
		modulus /= LongInteger::E;
		workingValue += modulus;
		returnValue++;
	}

	return returnValue;
}

#ifdef WIN32
bool LongInteger::writeToFile(CString & fileName)
{
	// Write out the data to file
	bool returnflag;
	CFile outFile;
	returnflag = outFile.Open(fileName, CFile::modeCreate | CFile::modeWrite);
	if (returnflag) {
		outFile.Write(digits, maxSize);
		outFile.Close();
	}
	return returnflag;
}

bool LongInteger::readFromFile(CString & fileName)
{
	// Read in the data
	bool returnflag;
	CFile inFile;
	returnflag = inFile.Open(fileName, CFile::modeRead);
	if (returnflag) {
		ULONGLONG fileSize = inFile.GetLength();
		if (fileSize > MAXULONG64)
		{
			return false;
		}
		byte* newData = new byte[fileSize];
		inFile.Read(newData, (UINT)fileSize);
		assignByteArray(newData, (UINT)fileSize);
		inFile.Close();
		delete newData;
	}
	return returnflag;
}
#else
bool LongInteger::writeToFile(string & fileName)
{
	// Write out the data to file
	ofstream outFile(fileName, ios::out);
	bool returnflag = outFile.is_open();
	if (returnflag) {
		for (UINT i = 0; i < maxSize; i++)
		{
			outFile << digits[i];
		}
		outFile.close();
	}
	return returnflag;
}

bool LongInteger::readFromFile(string & fileName)
{
	// Read in the data
	bool returnflag;
	ifstream inFile(fileName, ios::in);
	returnflag = inFile.is_open();
	string strLine;
	if (returnflag) {
		std::streampos begin, end;
		begin = inFile.tellg();
		inFile.seekg(0, ios::end);
		end = inFile.tellg();
		int fileSize = end - begin;

		inFile.seekg(0, ios::beg);
		byte* newData = new byte[fileSize];
		std::getline(inFile, strLine);
		std::strcpy((char*)newData, strLine.c_str());
		assignByteArray(newData, fileSize);
		inFile.close();
		delete newData;
	}
	return returnflag;
}


#endif



 using namespace std;

int main(int argc, char** argv) {


     
    string a;
    ifstream fin("input.txt");
	ofstream fout("output.txt");



    fin >> a;
    LongInteger value1(a);

    for(int i = 0;i<10;i++){
        LongInteger::sqrt(value1);
    }

    fout << LongInteger::sqrt(value1).toDecimal() << endl;
    return 0;

    LongInteger value2(10);
    LongInteger value3("10");
    LongInteger value4(value3);
    value1 = value2 * value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 / value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 + value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 - value3;
    cout << value1.toDecimal() << endl;
    value1 = value2;
    value1.powerCalc(value3);
    cout << value1.toDecimal() << endl;

    value1 = 100000;
    cout << value1.toDecimal() << endl;
    string value = "100000000000000000000";
    value2 = value;
    cout << value2.toDecimal() << endl;
    value3 = value2 * value2;
    value3 *= value2;
    value3 *= value2;
    value3 *= value2;
    cout << value3.toDecimal() << endl;
    cout << value3.getSize() << endl;

    LongInteger::KARATSUBACUTOFF = 20;
    LongInteger::KARATSUBATHREADING = 50;
    for( int i = 0; i < 14; i++) {
        value3 *= value3;
//        cout << value3.toDecimal() << endl;
        cout << value3.getSize() << endl;
    }
    return 0;
}

