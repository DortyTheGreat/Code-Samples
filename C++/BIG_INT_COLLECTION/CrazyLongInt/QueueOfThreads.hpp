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
