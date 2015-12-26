#ifndef TKTLOCK_H_
#define TKTLOCK_H_

#include <tbb/atomic.h>

//from https://www.quora.com/How-does-an-MCS-lock-work
//and Lock Cohorting: A General Technique for Designing NUMA Locks
//(DAVID DICE and VIRENDRA J. MARATHE, Oracle Labs NIR SHAVIT, MIT)
class TKTLock
{
public:
	TKTLock()
	{
		request=0;
		grant=0;
	}

	void lock()
	{
		uint64_t my_request = request.fetch_and_increment();
		while(my_request != grant){}
	}

	void unlock()
	{
		grant++;
	}	
private:
	tbb::atomic<uint64_t> request;
	uint64_t grant;
};

#endif
