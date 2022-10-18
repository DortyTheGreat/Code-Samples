/*-------1---------2---------3---------4---------5---------6---------7---------8---------9---------0
 *
 * PrimeCount.cp - Implementation of a class for counting primes
 *
 * Copyright (C) 2003 by Christian Bau.
 * Version 0.92, 25/Sep/2003
 *
 * This code is unfinished work in progress. For this reason, you may download this code and use it
 * on the computer that you used for downloading, but any further distribution is strictly
 * prohibited. Future, improved versions will be available without such restrictions.
 *
 * The class TMLPRimeCount has been tested and has been found to calculate pi (N) correctly for all
 * test values. The test values include N = 10^k for 3 <= k <= 19, and N = m * 10^k for 1 <= m <= 10,
 * k = 12, 13, 14 and 18.
 *
 * Execution time on a PowerPC G4 at 733 MHz is less than 46 seconds for pi (10^15) and less than
 * eight hours for pi (10^19), execution times are similar for a Celeron processor at 1700 MHz.
 *
 --------1---------2---------3---------4---------5---------6---------7---------8---------9--------*/

/*-------1---------2---------3---------4---------5---------6---------7---------8---------9---------0
 *
 * PrimeCount.h - Header file for a class for counting primes
 *
 * Copyright (C) 2003 by Christian Bau
 *
 --------1---------2---------3---------4---------5---------6---------7---------8---------9--------*/

#ifndef PRIMECOUNT_H_
#define PRIMECOUNT_H_
#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>
/*
 * This class calculates pi (N), the number of primes <= N, using various algorithms. In order to
 * hide implementation details, this class has static functions that can return objects that do the
 * actual calculations using different algorithms.
 *
 * Usage:
 *
 * Use the various factory functions to create TPrimeCount objects implementing various algorithms.
 * Each of the factory functions returns either a pointer to an object or NULL if the call was not
 * successful. maxN is the largest value N for which this object must be capable of calculating
 * pi (N); the default value will create an object that handles the maximum possible range. Use
 * "delete" to delete a TPrimeCount object when it is not needed anymore.
 *
 * The function Pi (N) will return pi (N), that is the number of primes <= N. If N > MaxArgument ()
 * then the result will be zero.
 *
 * MaxArgument () will return the maximum argument for which Pi (N) can be evaluated. If the
 * argument to the factory function was not 2^64 - 1 then MaxArgument () >= maxN, otherwise
 * MaxArgument () is as large as possible. BytesNeeded () is the amount of storage in bytes needed
 * by the object.
 *
 * Every TPrimeCount object has a "SelfTest" function which will test its correctness. This function
 * may take very long to execute. It should return a value of zero. If not, then the code is broken
 * and needs to be fixed.
 */
class TPrimeCount {

public:
	// Create an object that is capable of calculating pi (N) for all values pi <= maxN or return
	// NULL. The destructor can be used to delete any such object.
	static TPrimeCount* MakeLegendreCounter (unsigned long long maxN = 0);
	static TPrimeCount* MakeMeisselCounter (unsigned long long maxN = 0);
	static TPrimeCount* MakeLehmerCounter (unsigned long long maxN = 0);
	static TPrimeCount* MakeMeisselLehmerCounter (unsigned long long maxN = 0);

	virtual ~TPrimeCount (void) {};

	// Return pi (N); N must be in the range from 0 to maxN. If N exceeds the allowed range then
	// the result will be zero.
	virtual unsigned long long Pi (unsigned long long N) = 0;

	// Return a rough estimate for pi (N).
	double PiEstimate (double N);

	// Return the maximum value for which Pi (N) can be calculated, and return a good estimate for
	// the total storage in bytes used by the object.
	unsigned long long MaxArgument (void) { return fMaxArgument; }
	virtual unsigned long BytesNeeded (void) = 0;

	// Perform a self test and return 0 if everything is fine. Otherwise, some debugging will be
	// needed to find what is wrong.
	virtual int SelfTest (void) = 0;

protected:
	// The constructor is protected, so that only the factory functions in this class can call it.
	TPrimeCount (void) {};

	// Field holding the maximum argument that can be evaluated.
	unsigned long long fMaxArgument;
};

#endif /* PRIMECOUNT_H_ */

#include <string>
#include <math.h>

using namespace std;


// Define some suitable types for handling 8, 16, 32 and 64 bit unsigned integers. The Standard C
// types would normally be suitable for this. However, the type "unsigned long" could be 64 bit, so
// using "unsigned long" to store 32 bit values might be quite wasteful. Note that if int = 16 bit,
// then only shifts by up to 15 bits are defined; unsigned long can be shifted by 31 bit.

typedef unsigned char uint8;
typedef unsigned short uint16;

#if ((UINT_MAX >> 15) >> 15) >= 3
	typedef int int32;
	typedef unsigned int uint32;
#else
	typedef long int32;
	typedef unsigned long uint32;
#endif

#if ((ULONG_MAX >> 31) >> 31) >= 3
	typedef long int64;
	typedef unsigned long uint64;
#else
	typedef long long int64;
	typedef unsigned long long uint64;
#endif


// In this section, there is a selection of #define's that can be modified for tuning this
// implementation. Before using this code on a particular implementation, it would be worthwhile
// to find settings that produce the fastest code.


// In the Extended Meissel-Lehmer Algorithm, we choose a value M close to N^(1/3). Starting at
// N = M_BREAK_EVEN, M is chosen slightly larger as N^(1/3) * (log (N) / log (M_BREAK_EVEN)).
#define M_BREAK_EVEN			5e6


// Define DIVIDE_BY_HAND to 1 to use a handcoded function that will calculate x / y for certain
// values without actually performing a divide operation.
#define DIVIDE_BY_HAND			0


// Set CACHE_SIZE to the size of the data cache in bytes. Best results may be achieved by choosing
// the value slightly larger than the actual cache size; some experimentation is recommended for
// best results.
#define CACHE_SIZE				28000


// This should be defined as 1, 2 or 3. It determines what method is used to store primes in
// a TPrimeList object. If PRIME_LIST_METHOD is 1 then the differences between primes are stored.
// If PRIME_LIST_METHOD is 2 then every 1024th prime is stored, and the difference to that prime.
// If PRIME_LIST_METHOD is 3 then all primes are stored. Method 1 seems significantly slower,
// although that could perhaps be improved. Method 2 is just slightly slower than method 3, but
// uses half the memory.
#define PRIME_LIST_METHOD		2


// This should be defined as 2, 5 or 7 (any other value requires code changes). It determines which
// numbers are stored in the TFactorTable class. If FACTOR_TABLE_METHOD = 2 then a TFactorTable only
// fFactorTable contains entries for odd numbers. If FACTOR_TABLE_METHOD = 5 then a TFactorTable
// contains entries for all numbers not divisible by 2, 3 or 5. If FACTOR_TABLE_METHOD = 7 then
// a TFactorTable contains entries for all numbers not divisible by 2, 3, 5 or 7. A value of 7
// makes the mapping index <-> number more complicated but saves same storage, which might save
// some time.
#define FACTOR_TABLE_METHOD		2


// This should be defined as 5, 6, or 7. It is the largest k for which the TPhiTable class
// calculates phi (N, k) directly by using a lookup-table. The table size is 2 x 2310 bytes for
// PHI_LOOKUP_TABLE = 5, 2 x 30030 bytes for PHI_LOOKUP_TABLE = 6, and 4 x 510510 bytes for
// PHI_LOOKUP_TABLE = 7.
#define PHI_LOOKUP_TABLE		5

// CHOICE_FOR_C is the value that we choose for c in the TMLPrimeCount class. c must be in the
// range 1 <= c <= 9. Furthermore, if FACTOR_TABLE_METHOD is 5 or 7, then c must be at least
// 3 or 4.
#define CHOICE_FOR_C			9

#if CHOICE_FOR_C == 1
	#define PRIME_C				2
	#define PRIME_C_PLUS1		3
#elif CHOICE_FOR_C == 2
	#define PRIME_C				3
	#define PRIME_C_PLUS1		5
#elif CHOICE_FOR_C == 3
	#define PRIME_C				5
	#define PRIME_C_PLUS1		7
#elif CHOICE_FOR_C == 4
	#define PRIME_C				7
	#define PRIME_C_PLUS1		11
#elif CHOICE_FOR_C == 5
	#define PRIME_C				11
	#define PRIME_C_PLUS1		13
#elif CHOICE_FOR_C == 6
	#define PRIME_C				13
	#define PRIME_C_PLUS1		17
#elif CHOICE_FOR_C == 7
	#define PRIME_C				17
	#define PRIME_C_PLUS1		19
#elif CHOICE_FOR_C == 8
	#define PRIME_C				19
	#define PRIME_C_PLUS1		23
#elif CHOICE_FOR_C == 9
	#define PRIME_C				23
	#define PRIME_C_PLUS1		29
#else
	#error CHOICE_FOR_C must be a number from 1 to 9
#endif


// Various defines that control verification of this code. The SelfTest () method will test
// everything that is defined here and will return zero if all tests passed, n if the n-th test
// failed. For an intensive test, set all defines to 1 and check whether SelfTest () returns 0.
// If it doesn't return 0 then the source code needs consulting.

#define TEST_PRIME_TABLE			0			// Test the table of prime numbers
#define TEST_FACTOR_TABLE_INDEX		0			// Test the indexing into the factor table
#define TEST_NTH_PRIME				0			// Test function NthPrime
#define TEST_PHI_TABLES				0			// Test the contents of tables fPhi2Table etc.
#define TEST_PHI_FUNCTIONS			0			// Test the functions phi1, phi2 etc.
#define TEST_FACTOR_TABLE			0			// Test the functions phi1, phi2 etc.
#define TEST_PHI					0			// Test the phi (N, k) function
#define TEST_SLOW_PI				0			// Test the function slow_pi (n)
#define TEST_PI_ALGORITHM1			0			// Test the function pi_algorithm1 (n)
#define TEST_PI_ALGORITHM2			0			// Test the function pi_algorithm2 (n)
#define TEST_PI						1			// Test the function Pi (n)



/*
 * Define some useful constants. P_n is the product of the first n primes. Q_n is the product
 * of (p - 1) over the first n primes p.
 */
const uint32 P_1 = 2;			const uint32 Q_1 = 1;
const uint32 P_2 = P_1 * 3;		const uint32 Q_2 = Q_1 * 2;
const uint32 P_3 = P_2 * 5;		const uint32 Q_3 = Q_2 * 4;
const uint32 P_4 = P_3 * 7;		const uint32 Q_4 = Q_3 * 6;
const uint32 P_5 = P_4 * 11;	const uint32 Q_5 = Q_4 * 10;
const uint32 P_6 = P_5 * 13;	const uint32 Q_6 = Q_5 * 12;
const uint32 P_7 = P_6 * 17;	const uint32 Q_7 = Q_6 * 16;
const uint32 P_8 = P_7 * 19;	const uint32 Q_8 = Q_7 * 18;
const uint32 P_9 = P_8 * 23;	const uint32 Q_9 = Q_8 * 22;


/*
 * This is a helper class that uses tables to calculate the functions phi (N, 1), phi (N, 2)
 * etc. up to phi (N, 9).
 */
#pragma mark --- class TPhiTable ---
class TPhiTable {

	// Constructor: Fill the tables as required. There is no need for a destructor.
public:
	TPhiTable (void);

	// Functions to calculate phi (N, k) for small k in constant time. These functions are defined
	// for 1 <= k <= 9; change PHI_LOOKUP_TABLE to find the most efficient code.
	uint64 phi1 (uint64 N);
	uint64 phi2 (uint64 N);
	uint64 phi3 (uint64 N);
	uint64 phi4 (uint64 N);
	uint64 phi5 (uint64 N);
	uint64 phi6 (uint64 N);
	uint64 phi7 (uint64 N);
	uint64 phi8 (uint64 N);
	uint64 phi9 (uint64 N);

	uint32 phi1 (uint32 N);
	uint32 phi2 (uint32 N);
	uint32 phi3 (uint32 N);
	uint32 phi4 (uint32 N);
	uint32 phi5 (uint32 N);
	uint32 phi6 (uint32 N);
	uint32 phi7 (uint32 N);
	uint32 phi8 (uint32 N);
	uint32 phi9 (uint32 N);

	// The following arrays are set up to contain the number of integers <= i that are not divisible
	// by the first k primes. These tables are essential for calculating phi1 to phi9 quickly.
	uint8 fPhi2Table [P_2];
	uint8 fPhi3Table [P_3];
	uint8 fPhi4Table [P_4];
	uint16 fPhi5Table [P_5];
#if PHI_LOOKUP_TABLE == 6
	uint16 fPhi6Table [P_6];
#elif PHI_LOOKUP_TABLE == 7
	uint16 fPhi6Table [P_6];
	uint32 fPhi7Table [P_7];
#elif PHI_LOOKUP_TABLE != 5
	#error PHI_LOOKUP_TABLE must be defined as 5, 6 or 7.
#endif
};

/*
 * Constructor: Initialise fPhi2Table up to fPhi7Table according to the definition: fPhi(k)Table [i]
 * is the number of integers <= i that are not divisible by the first (k) primes.
 */
TPhiTable::TPhiTable (void) {

	uint32 i, count;

	for (i = 0, count = 0; i < P_2; ++i) {
		if (i % 2 && i % 3) ++count;
		fPhi2Table [i] = count;
	}

	for (i = 0, count = 0; i < P_3; ++i) {
		if (i % 2 && i % 3 && i % 5) ++count;
		fPhi3Table [i] = count;
	}

	for (i = 0, count = 0; i < P_4; ++i) {
		if (i % 2 && i % 3 && i % 5 && i % 7) ++count;
		fPhi4Table [i] = count;
	}

	for (i = 0, count = 0; i < P_5; ++i) {
		if (i % 2 && i % 3 && i % 5 && i % 7 && i % 11) ++count;
		fPhi5Table [i] = count;
	}

#if PHI_LOOKUP_TABLE >= 6
	for (i = 0, count = 0; i < P_6; ++i) {
		if (i % 2 && i % 3 && i % 5 && i % 7 && i % 11 && i % 13) ++count;
		fPhi6Table [i] = count;
	}
#endif

#if PHI_LOOKUP_TABLE >= 7
	for (i = 0, count = 0; i < P_7; ++i) {
		if (i % 2 && i % 3 && i % 5 && i % 7 && i % 11 && i % 13 && i % 17) ++count;
		fPhi7Table [i] = count;
	}
#endif
}


/*
 * Evaluate phi (N, k) for the trivial cases k = 1 to 9.
 */
uint64 TPhiTable::phi1 (uint64 N) {

	// Calculate phi (N, 1) = (N + 1) / 2
	return (N + 1) / 2;
}

uint64 TPhiTable::phi2 (uint64 N) {

	// Calculate phi (N, 2). Use a table of values for phi (N, 2) for N < P_2, then note that
	// phi (N, 2) = Q_2 * (N / P_2) + phi (N % P_2, 2).
	uint64 T = N == (uint32) N ? (uint32) N / P_2 : N / P_2;
	uint32 R = (uint32) N - P_2 * (uint32) T;

	return Q_2 * T + fPhi2Table [R];
}

uint64 TPhiTable::phi3 (uint64 N) {

	// Calculate phi (N, 3). Use a table of values for phi (N, 3) for N < P_3, then note that
	// phi (N, 3) = Q_3 * (N / P_3) + phi (N % P_3, 3).
	uint64 T = N == (uint32) N ? (uint32) N / P_3 : N / P_3;
	uint32 R = (uint32) N - P_3 * (uint32) T;

	return Q_3 * T + fPhi3Table [R];
}

uint64 TPhiTable::phi4 (uint64 N) {

	// Calculate phi (N, 4). Use a table of values for phi (N, 4) for N < P_4, then note that
	// phi (N, 4) = Q_4 * (N / P_4) + phi (N % P_4, 4).
	uint64 T = N == (uint32) N ? (uint32) N / P_4 : N / P_4;
	uint32 R = (uint32) N - P_4 * (uint32) T;

	return Q_4 * T + fPhi4Table [R];
}

uint64 TPhiTable::phi5 (uint64 N) {

	// Calculate phi (N, 5). Use a table of values for phi (N, 5) for N < P_5, then note that
	// phi (N, 5) = Q_5 * (N / P_5) + phi (N % P_5, 5).
	uint64 T = N == (uint32) N ? (uint32) N / P_5 : N / P_5;
	uint32 R = (uint32) N - P_5 * (uint32) T;

	return Q_5 * T + fPhi5Table [R];
}

uint64 TPhiTable::phi6 (uint64 N) {

	// Calculate phi (N, 6) using the formula phi (N, 6) = Q_6 * (N / P_6) + phi (N % P_6, 6).
	// This is of advantage because N % P_6 fits into an uint32. From then on the recursion
	// formula is used in a straightforward way, or use a lookup table if it is available.
	uint64 T = N == (uint32) N ? (uint32) N / P_6 : N / P_6;
	uint32 R = (uint32) N - P_6 * (uint32) T;

#if PHI_LOOKUP_TABLE >= 6
	return T * Q_6 + fPhi6Table [R];
#else

	uint32 sum1 = R / P_5;
	uint32 sum2 = fPhi5Table [R % P_5] - fPhi5Table [R / 13];

	return T * Q_6 + (Q_5 * sum1 + sum2);
#endif
}

uint64 TPhiTable::phi7 (uint64 N) {

	// Calculate phi (N, 7) using the formula phi (N, 7) = Q_7 * (N / P_7) + phi (N % P_7, 7).
	// This is of advantage because N % P_7 fits into an uint32. From then on the recursion
	// formula is used in a straightforward way, or use a lookup table if it is available.
	uint64 T = N == (uint32) N ? (uint32) N / P_7 : N / P_7;
	uint32 R = (uint32) N - P_7 * (uint32) T;

#if PHI_LOOKUP_TABLE >= 7
	return T * Q_7 + fPhi7Table [R];
#elif PHI_LOOKUP_TABLE >= 6
	uint32 sum1 = R / P_6;
	uint32 sum2 = fPhi6Table [R % P_6] - fPhi6Table [R / 17];

	return T * Q_7 + (Q_6 * sum1 + sum2);
#else

	uint32 N1, N2, N3, N4;
	uint32 sum1 = 0, sum2 = 0;

	N1 = R; N2 = N1 / 13; N3 = N1 / 17; N4 = N1 / (13 * 17);

	sum1 += N1 / P_5 - N2 / P_5 - N3 / P_5;
	sum2 += fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4];

	return T * Q_7 + (Q_5 * sum1 + sum2);
#endif
}

uint64 TPhiTable::phi8 (uint64 N) {

	// Calculate phi (N, 8) using the formula phi (N, 8) = Q_8 * (N / P_8) + phi (N % P_8, 8).
	// This is of advantage because N % P_8 fits into an uint32. From then on the recursion
	// formula is used in a straightforward way.
	uint64 T = N == (uint32) N ? (uint32) N / P_8 : N / P_8;
	uint32 R = (uint32) N - P_8 * (uint32) T;

#if PHI_LOOKUP_TABLE >= 7
	uint32 sum1 = R / P_7;
	uint32 sum2 = fPhi7Table [R % P_7] - fPhi7Table [R / 19];

	return T * Q_8 + (Q_7 * sum1 + sum2);

#else

	uint32 N1, N2, N3, N4;
	uint32 sum1 = 0, sum2 = 0;

#if PHI_LOOKUP_TABLE >= 6
	N1 = R; N2 = N1 / 17; N3 = N1 / 19; N4 = N1 / (17 * 19);

	sum1 += N1 / P_6 - N2 / P_6 - N3 / P_6;
	sum2 += fPhi6Table [N1 % P_6] - fPhi6Table [N2 % P_6]
		  - fPhi6Table [N3 % P_6] + fPhi6Table [N4];

	return T * Q_8 + (Q_6 * sum1 + sum2);
#else
	// We need to calculate phi (R, 8) using a lookup-table for phi (K, 5) and by using the
	// recursion formula. It just so happens for weird mathematical reasons that division by
	// 19 is slightly more complicated than division by 13 or 17, so we avoid it if possible.
	N1 = R; N2 = N1 / 13; N3 = N1 / 17; N4 = N1 / (13 * 17);

	sum1 += N1 / P_5 - N2 / P_5 - N3 / P_5 + N4 / P_5;
	sum2 += fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4 % P_5];


	N1 = R / 19; N2 = N1 / 13; N3 = N1 / 17; N4 = N1 / (13 * 17);

	sum1 -= N1 / P_5 - N2 / P_5 - N3 / P_5;
	sum2 -= fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4];

	return T * Q_8 + (Q_5 * sum1 + sum2);
#endif
#endif
}

uint64 TPhiTable::phi9 (uint64 N) {

	// Calculate phi (N, 9) using the formula phi (N, 9) = Q_9 * (N / P_9) + phi (N % P_9, 9).
	// This is of advantage because N % P_9 fits into an uint32. From then on the recursion
	// formula is used in a straightforward way.
	uint64 T = N == (uint32) N ? (uint32) N / P_9 : N / P_9;
	uint32 R = (uint32) N - P_9 * (uint32) T;

	uint32 N1, N2, N3, N4;
	uint32 sum1 = 0, sum2 = 0;


#if PHI_LOOKUP_TABLE >= 7
	N1 = R; N2 = N1 / 23; N3 = N1 / 19; N4 = N1 / (19 * 23);

	sum1 += N1 / P_7 - N2 / P_7 - N3 / P_7;
	sum2 += fPhi7Table [N1 % P_7] - fPhi7Table [N2 % P_7]
		  - fPhi7Table [N3 % P_7] + fPhi7Table [N4];

	return T * Q_9 + (Q_7 * sum1 + sum2);
#elif PHI_LOOKUP_TABLE >= 6
	N1 = R; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 += N1 / P_6 - N2 / P_6 - N3 / P_6 + N4 / P_6;
	sum2 += fPhi6Table [N1 % P_6] - fPhi6Table [N2 % P_6]
		  - fPhi6Table [N3 % P_6] + fPhi6Table [N4 % P_6];

	N1 = R / 19; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 -= N1 / P_6 - N2 / P_6 - N3 / P_6;
	sum2 -= fPhi6Table [N1 % P_6] - fPhi6Table [N2 % P_6]
		  - fPhi6Table [N3 % P_6] + fPhi6Table [N4];

	return T * Q_9 + (Q_6 * sum1 + sum2);
#else
	// We need to calculate phi (R, 9) using a lookup-table for phi (K, 5) and by using the
	// recursion formula. It just so happens for weird mathematical reasons that division by
	// 19 is slightly more complicated than division by 13, 17 or 23, so we avoid it if possible.
	N1 = R; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 += N1 / P_5 - N2 / P_5 - N3 / P_5 + N4 / P_5;
	sum2 += fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4 % P_5];


	N1 = R / 13; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 -= N1 / P_5 - N2 / P_5 - N3 / P_5 + N4 / P_5;
	sum2 -= fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4 % P_5];


	N1 = R / 19; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 -= N1 / P_5 - N2 / P_5 - N3 / P_5 + N4 / P_5;
	sum2 -= fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4 % P_5];


	N1 = N1 / 13; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 += N1 / P_5 - N2 / P_5 - N3 / P_5;
	sum2 += fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4];

	return T * Q_9 + (Q_5 * sum1 + sum2);
#endif
}

/*
 * Evaluate phi (N, k) for the trivial cases k = 1 to 9.
 */
uint32 TPhiTable::phi1 (uint32 N) {

	// Calculate phi (N, 1) = (N + 1) / 2
	return (N + 1) / 2;
}

uint32 TPhiTable::phi2 (uint32 N) {

	// Calculate phi (N, 2). Use a table of values for phi (N, 2) for N < P_2, then note that
	// phi (N, 2) = Q_2 * (N / P_2) + phi (N % P_2, 2).
	uint32 T = N / P_2;
	uint32 R = N - P_2 * T;

	return Q_2 * T + fPhi2Table [R];
}

uint32 TPhiTable::phi3 (uint32 N) {

	// Calculate phi (N, 3). Use a table of values for phi (N, 3) for N < P_3, then note that
	// phi (N, 3) = Q_3 * (N / P_3) + phi (N % P_3, 3).
	uint32 T = N / P_3;
	uint32 R = N - P_3 * T;

	return Q_3 * T + fPhi3Table [R];
}

uint32 TPhiTable::phi4 (uint32 N) {

	// Calculate phi (N, 4). Use a table of values for phi (N, 4) for N < P_4, then note that
	// phi (N, 4) = Q_4 * (N / P_4) + phi (N % P_4, 4).
	uint32 T = N / P_4;
	uint32 R = N - P_4 * T;

	return Q_4 * T + fPhi4Table [R];
}

uint32 TPhiTable::phi5 (uint32 N) {

	// Calculate phi (N, 5). Use a table of values for phi (N, 5) for N < P_5, then note that
	// phi (N, 5) = Q_5 * (N / P_5) + phi (N % P_5, 5).
	uint32 T = N / P_5;
	uint32 R = N - P_5 * T;

	return Q_5 * T + fPhi5Table [R];
}

uint32 TPhiTable::phi6 (uint32 N) {

	// Calculate phi (N, 6) using the formula phi (N, 6) = Q_6 * (N / P_6) + phi (N % P_6, 6).
	// This is of advantage because N % P_6 fits into an uint32. From then on the recursion
	// formula is used in a straightforward way, or use a lookup table if it is available.
	uint32 T = N / P_6;
	uint32 R = N - P_6 * T;

#if PHI_LOOKUP_TABLE >= 6
	return T * Q_6 + fPhi6Table [R];
#else

	uint32 sum1 = R / P_5;
	uint32 sum2 = fPhi5Table [R % P_5] - fPhi5Table [R / 13];

	return T * Q_6 + (Q_5 * sum1 + sum2);
#endif
}

uint32 TPhiTable::phi7 (uint32 N) {

	// Calculate phi (N, 7) using the formula phi (N, 7) = Q_7 * (N / P_7) + phi (N % P_7, 7).
	// This is of advantage because N % P_7 fits into an uint32. From then on the recursion
	// formula is used in a straightforward way, or use a lookup table if it is available.
	uint32 T = N / P_7;
	uint32 R = N - P_7 * T;

#if PHI_LOOKUP_TABLE >= 7
	return T * Q_7 + fPhi7Table [R];
#elif PHI_LOOKUP_TABLE >= 6
	uint32 sum1 = R / P_6;
	uint32 sum2 = fPhi6Table [R % P_6] - fPhi6Table [R / 17];

	return T * Q_7 + (Q_6 * sum1 + sum2);
#else

	uint32 N1, N2, N3, N4;
	uint32 sum1 = 0, sum2 = 0;

	N1 = R; N2 = N1 / 13; N3 = N1 / 17; N4 = N1 / (13 * 17);

	sum1 += N1 / P_5 - N2 / P_5 - N3 / P_5;
	sum2 += fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4];

	return T * Q_7 + (Q_5 * sum1 + sum2);
#endif
}

uint32 TPhiTable::phi8 (uint32 N) {

	// Calculate phi (N, 8) using the formula phi (N, 8) = Q_8 * (N / P_8) + phi (N % P_8, 8).
	// This is of advantage because N % P_8 fits into an uint32. From then on the recursion
	// formula is used in a straightforward way.
	uint32 T = N / P_8;
	uint32 R = N - P_8 * T;

#if PHI_LOOKUP_TABLE >= 7
	uint32 sum1 = R / P_7;
	uint32 sum2 = fPhi7Table [R % P_7] - fPhi7Table [R / 19];

	return T * Q_8 + (Q_7 * sum1 + sum2);

#else

	uint32 N1, N2, N3, N4;
	uint32 sum1 = 0, sum2 = 0;

#if PHI_LOOKUP_TABLE >= 6
	N1 = R; N2 = N1 / 17; N3 = N1 / 19; N4 = N1 / (17 * 19);

	sum1 += N1 / P_6 - N2 / P_6 - N3 / P_6;
	sum2 += fPhi6Table [N1 % P_6] - fPhi6Table [N2 % P_6]
		  - fPhi6Table [N3 % P_6] + fPhi6Table [N4];

	return T * Q_8 + (Q_6 * sum1 + sum2);
#else
	// We need to calculate phi (R, 8) using a lookup-table for phi (K, 5) and by using the
	// recursion formula. It just so happens for weird mathematical reasons that division by
	// 19 is slightly more complicated than division by 13 or 17, so we avoid it if possible.
	N1 = R; N2 = N1 / 13; N3 = N1 / 17; N4 = N1 / (13 * 17);

	sum1 += N1 / P_5 - N2 / P_5 - N3 / P_5 + N4 / P_5;
	sum2 += fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4 % P_5];


	N1 = R / 19; N2 = N1 / 13; N3 = N1 / 17; N4 = N1 / (13 * 17);

	sum1 -= N1 / P_5 - N2 / P_5 - N3 / P_5;
	sum2 -= fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4];

	return T * Q_8 + (Q_5 * sum1 + sum2);
#endif
#endif
}

uint32 TPhiTable::phi9 (uint32 N) {

	// Calculate phi (N, 9) using the formula phi (N, 9) = Q_9 * (N / P_9) + phi (N % P_9, 9).
	// This is of advantage because N % P_9 fits into an uint32. From then on the recursion
	// formula is used in a straightforward way.
	uint32 T = N / P_9;
	uint32 R = N - P_9 * T;

	uint32 N1, N2, N3, N4;
	uint32 sum1 = 0, sum2 = 0;


#if PHI_LOOKUP_TABLE >= 7
	N1 = R; N2 = N1 / 23; N3 = N1 / 19; N4 = N1 / (19 * 23);

	sum1 += N1 / P_7 - N2 / P_7 - N3 / P_7;
	sum2 += fPhi7Table [N1 % P_7] - fPhi7Table [N2 % P_7]
		  - fPhi7Table [N3 % P_7] + fPhi7Table [N4];

	return T * Q_9 + (Q_7 * sum1 + sum2);
#elif PHI_LOOKUP_TABLE >= 6
	N1 = R; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 += N1 / P_6 - N2 / P_6 - N3 / P_6 + N4 / P_6;
	sum2 += fPhi6Table [N1 % P_6] - fPhi6Table [N2 % P_6]
		  - fPhi6Table [N3 % P_6] + fPhi6Table [N4 % P_6];

	N1 = R / 19; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 -= N1 / P_6 - N2 / P_6 - N3 / P_6;
	sum2 -= fPhi6Table [N1 % P_6] - fPhi6Table [N2 % P_6]
		  - fPhi6Table [N3 % P_6] + fPhi6Table [N4];

	return T * Q_9 + (Q_6 * sum1 + sum2);
#else
	// We need to calculate phi (R, 9) using a lookup-table for phi (K, 5) and by using the
	// recursion formula. It just so happens for weird mathematical reasons that division by
	// 19 is slightly more complicated than division by 13, 17 or 23, so we avoid it if possible.
	N1 = R; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 += N1 / P_5 - N2 / P_5 - N3 / P_5 + N4 / P_5;
	sum2 += fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4 % P_5];


	N1 = R / 13; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 -= N1 / P_5 - N2 / P_5 - N3 / P_5 + N4 / P_5;
	sum2 -= fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4 % P_5];


	N1 = R / 19; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 -= N1 / P_5 - N2 / P_5 - N3 / P_5 + N4 / P_5;
	sum2 -= fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4 % P_5];


	N1 = N1 / 13; N2 = N1 / 23; N3 = N1 / 17; N4 = N1 / (17 * 23);

	sum1 += N1 / P_5 - N2 / P_5 - N3 / P_5;
	sum2 += fPhi5Table [N1 % P_5] - fPhi5Table [N2 % P_5]
		  - fPhi5Table [N3 % P_5] + fPhi5Table [N4];

	return T * Q_9 + (Q_5 * sum1 + sum2);
#endif
}

/*
 * This is a helper class that can hold a list of prime numbers and gives fast access to those
 * prime numbers. Storage requirement is one byte per prime number. Getting the next or previous
 * prime number is extremely fast, but there are also reasonably efficient ways to get the nth
 * prime or to calculate pi (x) or to check whether a number x is a prime. Can handle primes up
 * to 436,000,000.
 */
#pragma mark --- class TPrimeList ---
class TPrimeList {
public:
	// Constructor and destructor. The constructor sets all fields to 0 or NULL, the destructor
	// deletes any storage that has been allocated.
	inline TPrimeList (void);
	inline ~TPrimeList (void) { this->HandlePrimesUpTo (0); }

	// Set up the TPrimeList to handle all the primes <= maxPrime. This will either fail or succeed,
	// this can be checked by calling MaxPrime () which will either return a value >= the argument,
	// or return 0.
	void HandlePrimesUpTo (uint32 maxPrime);

	// Return the number of primes stored and the largest prime stored. Return the number of bytes
	// needed for this object.
	inline uint32 NumberOfPrimes (void) { return fNumberOfPrimes; }
	inline uint32 MaxPrime (void) { return fMaxPrime; }
	inline uint32 BytesNeeded (void);

	// Return the next prime number, given its index and the previous prime number. Return the
	// previous prime number, given its index and the next larger prime number. These calls are
	// highly efficient. Return the nth prime. NextPrime and PreviousPrime are efficient in all
	// versions; NthPrime is not too efficient if method = 1.
#if PRIME_LIST_METHOD == 1
	uint32 NthPrime (uint32 N);
	inline uint32 NextPrime (uint32 index, uint32 previous) {
		return previous + fPrimeDelta [index];
	}
	inline uint32 PreviousPrime (uint32 index, uint32 next) {
		return next - fPrimeDelta [index + 1];
	}
#else
	inline uint32 NthPrime (uint32 N);
	inline uint32 NextPrime (uint32 index, uint32 previous) {
		previous = 0; return this->NthPrime (index);
	}
	inline uint32 PreviousPrime (uint32 index, uint32 next) {
		next = 0; return this->NthPrime (index);
	}
#endif

	// Return pi (N), or return whether N is prime.
	uint32 Pi (uint32 N);
	bool IsPrime (uint32 N);

private:
	// Number of primes stored and largest prime stored, and a function which will add another
	// prime.
	uint32 fNumberOfPrimes;
	uint32 fMaxPrime;
	void AddPrime (uint32 prime) {
		++fNumberOfPrimes;
#if PRIME_LIST_METHOD == 1
		fPrimeDelta [fNumberOfPrimes] = prime - fMaxPrime;
#elif PRIME_LIST_METHOD == 2
		if (fNumberOfPrimes % 1024 == 0) fPrimeTable [fNumberOfPrimes / 1024] = prime;
		fPrimeDelta [fNumberOfPrimes] = prime - fPrimeTable [fNumberOfPrimes / 1024];
#else
		fPrimeTable [fNumberOfPrimes] = prime;
#endif
		fMaxPrime = prime;
	}

#if PRIME_LIST_METHOD == 1
	// fPrimeDelta [i] = p(i) - p(i-1), assuming p(0) = 0.
	uint8* fPrimeDelta;
#elif PRIME_LIST_METHOD == 2
	// fPrimeTable [k] = p(1024 * k), fPrimeDelta [i] = p(i) - p (1024 * (i/1024))
	uint16* fPrimeDelta;
	uint32* fPrimeTable;
#else
	// fPrimeTable [i] = p(i)
	uint32* fPrimeTable;
#endif

	// Variables used by functions NthPrime () and Pi (): fPrime is the prime number (fIndex).
	uint32 fPrime;
	uint32 fIndex;
};

// Constructor. Sets variables to 0 or NULL.
inline TPrimeList::TPrimeList (void) {
	fNumberOfPrimes = fMaxPrime = 0;
#if PRIME_LIST_METHOD <= 2
	fPrimeDelta = NULL;
#endif
#if PRIME_LIST_METHOD >= 2
	fPrimeTable = NULL;
#endif
}

// Return the number of bytes needed by an object.
inline uint32 TPrimeList::BytesNeeded (void) {
#if PRIME_LIST_METHOD == 1
	return sizeof (*this) + (fNumberOfPrimes + 1) * sizeof (*fPrimeDelta);
#elif PRIME_LIST_METHOD == 2
	return sizeof (*this) + (fNumberOfPrimes + 1) * sizeof (*fPrimeDelta)
						  + (fNumberOfPrimes / 1024 + 1) * sizeof (*fPrimeTable);
#else
	return sizeof (*this) + (fNumberOfPrimes + 1) * sizeof (*fPrimeTable);
#endif
}


// Return the nth prime number.
uint32 TPrimeList::NthPrime (uint32 N) {

#if PRIME_LIST_METHOD == 1
	uint32 index = fIndex;
	uint32 prime = fPrime;

	while (N < index) prime -= fPrimeDelta [index--];
	while (N > index) prime += fPrimeDelta [++index];

	fIndex = index;
	fPrime = prime;

	return prime;
#elif PRIME_LIST_METHOD == 2
	return fPrimeTable [N / 1024] + fPrimeDelta [N];
#else
	return fPrimeTable [N];
#endif
}

// Find pi (N), the number of primes <= N.
uint32 TPrimeList::Pi (uint32 N) {

	uint32 index = fIndex;
	uint32 prime = fPrime;

	while (prime < N) prime = this->NextPrime (++index, prime);
	while (prime > N) prime = this->PreviousPrime (--index, prime);

	fIndex = index;
	fPrime = prime;

	return index;
}

// Find whether or not N is a prime number
bool TPrimeList::IsPrime (uint32 N) {

	uint32 index = fIndex;
	uint32 prime = fPrime;

	while (prime < N) prime = this->NextPrime (++index, prime);
	while (prime > N) prime = this->PreviousPrime (--index, prime);

	fIndex = index;
	fPrime = prime;

	return prime == N;
}


/*
 * Set up a TPrimeList to handle primes up to maxPrime
 */
void TPrimeList::HandlePrimesUpTo (uint32 maxPrime) {

	// Delete any existing list of primes and set the pointers to NULL. Then set all important
	// variables to NULL. Return if maxPrime == 0.
#if PRIME_LIST_METHOD <= 2
	::free (fPrimeDelta); fPrimeDelta = NULL;
#endif
#if PRIME_LIST_METHOD >= 2
	::free (fPrimeTable); fPrimeTable = NULL;
#endif

	fNumberOfPrimes = fMaxPrime = 0;
	fPrime = fIndex = 0;
	if (maxPrime == 0)
		return;


	// Return if the largest prime is too large. The first gap between primes that is greater than
	// 255 happens a bit above 436 million, so that is where we give up.
	if (maxPrime > 436000000)
		return;

	// Calculate how many prime numbers there will be. The following formula never underestimates
	// the number of primes.
	uint32 maxCount = 100;
	if (maxPrime > 100)
		maxCount += (uint32) (maxPrime / (::log (maxPrime) - 1.08));

	// Allocate memory for the primes. This may fail, so return if it fails. Also make sure that
	// maxCount is not too large for an argument to ::malloc.
#if PRIME_LIST_METHOD == 1
	fPrimeDelta = (uint8 *) ::malloc ((maxCount + 1) * sizeof (*fPrimeDelta));
	if (fPrimeDelta == NULL)
		return;

	fPrimeDelta [0] = 0;
#elif PRIME_LIST_METHOD == 2
	fPrimeDelta = (uint16 *) ::malloc ((maxCount + 1) * sizeof (*fPrimeDelta));
	if (fPrimeDelta == NULL)
		return;

	fPrimeTable = (uint32 *) ::malloc ((maxCount / 1024 + 1) * sizeof (*fPrimeTable));
	if (fPrimeTable == NULL) {
		::free (fPrimeDelta);
		fPrimeDelta = NULL;
		return;
	}

	fPrimeTable [0] = 0;
	fPrimeDelta [0] = 0;
#else
	fPrimeTable = (uint32 *) ::malloc ((maxCount + 1) * sizeof (*fPrimeTable));
	if (fPrimeTable == NULL)
		return;

	fPrimeTable [0] = 0;
#endif


	uint32 next_prime;
	uint32 i, divisor;
	uint32 start_sieve, end_sieve;

	// Store the data for the first prime p = 2. Then find the first hundred primes using trial
	// division to get things going.
	this->AddPrime (2);

	for (next_prime = 3; fNumberOfPrimes < 100; next_prime += 2) {
		bool is_prime = true;
		for (i = 2, divisor = 3; divisor * divisor <= next_prime;
														divisor = this->NextPrime (++i, divisor)) {
			if (next_prime % divisor == 0) { is_prime = false; break; }
		}
		if (is_prime) {
			this->AddPrime (next_prime);
		}
	}

	// From now on we can use a sieve to find the remaining primes. The sieve has an arbitrary
	// size of 10000 and represents odd integers. The sieve is filled with 1s; then the multiple
	// of all odd primes starting with the square of each odd prime are set to 0, and everything
	// that is left at 1 is a prime.
	for (start_sieve = next_prime; fNumberOfPrimes < maxCount; start_sieve += 20000) {

		uint8 sieve [10000];
		::memset (sieve, 1, 10000);

		end_sieve = start_sieve + 20000;
		for (i = 2, divisor = 3; divisor * divisor < end_sieve;
														divisor = this->NextPrime (++i, divisor)) {
			uint32 quot = (start_sieve + divisor - 1) / divisor;
			if (quot < divisor) quot = divisor;
			if (quot % 2 == 0) ++quot;
			uint32 index = (divisor * quot - start_sieve) / 2;
			while (index < 10000) { sieve [index] = 0; index += divisor; }
		}

		for (i = 0; i < 10000; ++i) {
			if (sieve [i] && fNumberOfPrimes < maxCount) {
				this->AddPrime (start_sieve + 2 * i);
			}
		}
	}

	// Store the largest prime number and the number of primes. Initialise fPrime and fIndex so
	// that NthPrime and Pi can start from there.
}




/*
 * This is a helper class that can be used to find prime numbers by using a sieve. This class is
 * not particularly efficient, but it doesn't take too much storage either. It relies on an
 * external table for prime numbers.
 */
#pragma mark --- class TPrimeSieve ---
class TPrimeSieve {

	// Constructor and destructor. Both are quite trivial. MaxNumber returns the largest number
	// that can be handled by this sieve.
public:
	TPrimeSieve (TPrimeList* primeList);
	~TPrimeSieve (void) { }
	uint32 MaxNumber (void) { return fMaxNumber; }

	// PrimeAfter (N) returns the smallest prime number > N. PrimeBefore (N) returns the largest
	// prime number less than N. IsPrime (N) returns true if and only if N is a prime number.
	uint32 PrimeAfter (uint32 N);
	uint32 PrimeBefore (uint32 N);
	bool IsPrime (uint32 N);

private:
	// Number of bytes used in the prime sieve. This should probably be a power of two; it need not
	// be very large.
	enum { ePrimeSieveSize = 2048 };

	// Data structures: A sieve of ePrimeSieveSize bytes is used to represent 8 * ePrimeSieveSize
	// odd numbers, so a range of 16 * ePrimeSieveSize integers can be described. One variable
	// indicates the start of that range, it is always a multiple of 16 * ePrimeSieveSize.
	uint64 fSieveStart;
	uint8 fSieve [ePrimeSieveSize];

	// Pointer to a list of primes that we are using. fMaxNumber is the largest number that this
	// class can possibly handle.
	TPrimeList* fPrimeList;
	uint32 fMaxNumber;

	// FillSieve fills the sieve, starting at some multiple of 16 * ePrimeSieveSize.
	void FillSieve (uint32 sieveStart);
};

// Constructor: Store the prime number list, set the start of the sieve to an invalid value so that
// the first sieve will be constructed automatically, and calculate the largest number that can be
// handled by checking the largest prime in the prime number list.
TPrimeSieve::TPrimeSieve (TPrimeList* primeList) {

	fPrimeList = primeList;
	fSieveStart = 1;

	uint64 limit = primeList->MaxPrime ();
	limit = limit * limit;
	limit = limit - limit % (16ul * ePrimeSieveSize) - 1;
	fMaxNumber = limit == (uint32) limit ? limit : (uint32) -1;
}


void TPrimeSieve::FillSieve (uint32 sieveStart) {

	// We want one bit set for each odd prime number. So we start by setting all the bits, then
	// for each prime we clear one bit for each odd multiple of that prime number. The only
	// exception is that a bit for the number 1 will remain set.
	::memset (&fSieve [0], 0xff, ePrimeSieveSize);
	uint32 i, p, j;
	for (i = 2, p = 3; p*p < sieveStart + (16ul * ePrimeSieveSize);
																p = fPrimeList->NextPrime (++i, p)) {
		for (j = sieveStart == 0 ? p * p / 2 : (p - 1) - ((sieveStart + (p - 1)) / 2) % p;
															j < (8ul * ePrimeSieveSize); j += p) {
			fSieve [j / 8] &= ~(1u << (j % 8));
		}
	}

	fSieveStart = sieveStart;
}

// Return the smallest prime number > N
uint32 TPrimeSieve::PrimeAfter (uint32 N) {

	// Handle the special case N < 2 by returning 2. If N >= 2 then we are looking for an odd
	// prime. Increase N by one, then we look for the smallest prime >= N. We calculate the
	// start of the sieve which must be a multiple of 32768, and the bit offset for N.
	if (N < 2) return 2;

	N += 1;
	uint32 bitOffset = N % (16ul * ePrimeSieveSize);
	uint32 sieveStart = N - bitOffset;
	bitOffset = bitOffset / 2;

	// Outer loop: If the sieve doesn't start where it should then fill the sieve at the new
	// start. Look for a bit that is set. Return if a bit set is found, indicating a prime.
	// Otherwise increase the bit offset until we reach the end of the sieve. At the end of the
	// sieve, change the sieve start and switch to the next sieve at bit offset 0.
	for (;;) {
		if (sieveStart != fSieveStart)
			this->FillSieve (sieveStart);

		for (; bitOffset < (8ul * ePrimeSieveSize); ++bitOffset) {
			if (fSieve [bitOffset / 8] & (1u << (bitOffset % 8)))
				return sieveStart + 2*bitOffset + 1;
		}
		sieveStart += (16ul * ePrimeSieveSize);
		bitOffset = 0;
	}
}

// Return the largest prime number < N
uint32 TPrimeSieve::PrimeBefore (uint32 N) {

	// Handle the special case N <= 2 by returning 0 or 2. If N >= 3 then we are looking for an odd
	// prime, and we know there is one. We calculate the start of the sieve which must be a multiple
	// of 32768, and the bit offset for N.
	if (N <= 3) return (N == 3 ? 2 : 0);

	N -= 2;
	uint32 bitOffset = N % 32768;
	uint32 sieveStart = N - bitOffset;
	bitOffset = bitOffset / 2;

	// Outer loop: If the sieve doesn't start where it should then fill the sieve at the new
	// start. Look for a bit that is set. Return if a bit set is found, indicating a prime.
	// Otherwise increase the bit offset until we reach the end of the sieve. At the end of the
	// sieve, change the sieve start and switch to the next sieve at bit offset 0.
	for (;;) {
		if (sieveStart != fSieveStart)
			this->FillSieve (sieveStart);

		for (;;) {
			if (fSieve [bitOffset / 8] & (1u << (bitOffset % 8)))
				return sieveStart + 2*bitOffset + 1;
			if (bitOffset == 0) break;
			--bitOffset;
		}
		sieveStart -= 32768;
		bitOffset = (32768 - 1) / 2;
	}
}

// Returns true iff N is a prime
bool TPrimeSieve::IsPrime (uint32 N) {

	// Handle the special case N = 2 and the case of even numbers. Then calculate the start of the
	// sieve and the bit offset, and check the right bit.

	if (N <= 2 || N % 2 == 0) return N == 2;
	uint32 bitOffset = N % 32768;
	uint32 sieveStart = N - bitOffset;
	bitOffset = bitOffset / 2;

	if (sieveStart != fSieveStart)
		this->FillSieve (sieveStart);

	return (fSieve [bitOffset / 8] & (1u << (bitOffset % 8))) != 0;
}


/*
 * This is a helper class that can hold information about the smallest factor of any integer, and
 * whether the number of factors is even or odd. To be more space efficient, it only holds
 * information about numbers that are not divisible by any prime <= FACTOR_TABLE_METHOD, which may
 * be 2, 5 or 7.
 *
 * GetEntry (index) returns the entry for a number that is stored in the table, given the index of
 * that number. The entry for a number x is 65534 if x = 1, x if x is a prime <= 65535, 65535 if
 * x is a prime >= 65535, n if n is the smallest factor of x and the number of factors is odd,
 * n-1 if n is the smallest factor of x and the number of factors is even, and 0 if x is not
 * square-free.
 *
 * To examine all numbers low <= x < high, calculate ilow, ihigh = NumberToIndex (low, high),
 * examine all indices ilow <= index < ihigh, and convert those that are of interest back to
 * numbers by calling IndexToNumber (index).
 *
 * To check whether a number is prime free with no prime factor <= p, check that GetEntry ()
 * returns a value > p. As a special case if p == 2 check that GetEntry () returns a value > 0;
 * this is correct because no variant of the table stores even numbers.
 */
#pragma mark --- class TFactorTable ---
class TFactorTable {
public:
	// Constructor and destructor: Constructor initialises some tables and initialises fields to
	// zero and NULL. Destructor deallocates any storage used.
	TFactorTable (void);
	~TFactorTable (void) {}

	// Make sure that all numbers <= maxNumber can be handled, and that at least one further prime
	// number >= 400 can be handled.
	void HandleNumbersUpTo (uint32 maxNumber);

	// Return the number of entries and the largest number handled. Return the number of bytes
	// needed for this object.
	uint32 NumberOfEntries (void) { return fTableSize; }
	uint32 MaxNumber (void) { return fMaxNumber; }
	uint32 BytesNeeded (void) { return sizeof (*this) + fTableSize * sizeof (uint16); }

	// For higher storage and search efficiency, a TFactorTable only contains entries for numbers
	// that are not divisible by the smallest primes, for example 2, 3, 5 and 7. There is a mapping
	// between numbers and indices used by the TFactorTable. When trying to examine all numbers with
	// values low <= x < high, convert low and high to indices using the function NumberToIndex,
	// examine all indices in the range, then convert each index that is accepted back to a number
	// by calling IndexToNumber.
	inline uint32 NumberToIndex (uint32 N);
	inline uint32 IndexToNumber (uint32 N);

	// Get an entry by index
	uint32 GetEntry (uint32 index) { return fEntries [index]; }

private:
	uint16 *fEntries;
	uint32 fMaxNumber;
	uint32 fTableSize;

#if FACTOR_TABLE_METHOD == 5
	// fIndexToNumberTable [i-1] is the i-th number 0 <= j < P_3 that is not divisible by 2, 3
	// or 5. fNumberToIndexTable [i] is the number of integers < i not divisible by 2, 3 or 5.
	uint8 fIndexToNumberTable [Q_3];
	uint8 fNumberToIndexTable [P_3];
#elif FACTOR_TABLE_METHOD == 7
	// fIndexToNumberTable [i-1] is the i-th number 0 <= j < P_4 that is not divisible by
	// 2, 3, 5 or 7. fNumberToIndexTable [i] is the number of integers < i not divisible by
	// 2, 3, 5 or 7.
	uint8 fIndexToNumberTable [Q_4];
	uint8 fNumberToIndexTable [P_4];
#elif FACTOR_TABLE_METHOD != 2
	#error FACTOR_TABLE_METHOD must be defined as 2, 5 or 7.
#endif
};


// Constructor for TFactorTable: Initialise the translation tables.
TFactorTable::TFactorTable (void) {

	fEntries = NULL;
	fMaxNumber = fTableSize = 0;

#if FACTOR_TABLE_METHOD == 5
	// Initialise tables fIndexToNumberTable and fNumberToIndexTable.

	uint32 i, count;

	for (i = 0, count = 0; i < P_3; ++i) {
		fNumberToIndexTable [i] = count;
		if (i % 2 && i % 3 && i % 5)
			fIndexToNumberTable [count++] = i;
	}
#endif

#if FACTOR_TABLE_METHOD == 7
	// Initialise tables fIndexToNumberTable and fNumberToIndexTable.

	uint32 i, count;

	for (i = 0, count = 0; i < P_4; ++i) {
		fNumberToIndexTable [i] = count;
		if (i % 2 && i % 3 && i % 5 && i % 7) {
			fIndexToNumberTable [count++] = i;
		}
	}
#endif
}


// This function maps an index into the table entries to a number. The entries in the table refer to
// odd integers, integers not divisible by 2, 3 or 5, or integers not divisible by 2, 3, 5 or 7,
// depending on the macro FACTOR_TABLE_METHOD
inline uint32 TFactorTable::IndexToNumber (uint32 index) {

#if FACTOR_TABLE_METHOD == 2
	return index * 2 + 1;
#elif FACTOR_TABLE_METHOD == 5
	return P_3 * (index / Q_3) + fIndexToNumberTable [index % Q_3];
#elif FACTOR_TABLE_METHOD == 7
	return P_4 * (index / Q_4) + fIndexToNumberTable [index % Q_4];
#else
	#error FACTOR_TABLE_METHOD must be defined as 2, 5 or 7.
#endif
}

// This function maps a number to an index into the entries. If the number does not correspond
// exactly to an entry then the index of the next entry is returned.
inline uint32 TFactorTable::NumberToIndex (uint32 number) {

#if FACTOR_TABLE_METHOD == 2
	return number / 2;
#elif FACTOR_TABLE_METHOD == 5
	return Q_3 * (number / P_3) + fNumberToIndexTable [number % P_3];
#elif FACTOR_TABLE_METHOD == 7
	return Q_4 * (number / P_4) + fNumberToIndexTable [number % P_4];
#else
	#error FACTOR_TABLE_METHOD must be defined as 2, 5 or 7.
#endif
}


void TFactorTable::HandleNumbersUpTo (uint32 maxNumber) {

	// Remove an existing factor table.
	::free (fEntries);
	fEntries = NULL;
	fMaxNumber = fTableSize = 0;

	// We want to include at least one prime number after maxNumber. For p < 2^32, gaps between
	// prime numbers are less than 400. Return with failure if this would overflow.
	if (maxNumber > 0xffffffff - 402)
		return;

	// We will want to store information about all numbers < tableLimit. We get the size of the
	// table by calling NumberToIndex. Try to allocate the memory for the table and return if this
	// fails. tableLimit is large enough so that the table will contain at least another prime,
	// and that prime will be greater than 400.
	uint32 tableLimit = maxNumber + 400 + 1;
	uint32 tableSize = this->NumberToIndex (tableLimit);
	fEntries = (uint16 *) ::malloc (tableSize * sizeof (uint16));
	if (fEntries == NULL)
		return;


	// We initialise all entries as if they were large primes, that is setting them to a value of
	// 65535. Change the entry belonging to x = 1 to 65534.
	uint32 i;

	fEntries [0] = 65534;
	for (i = 1; i < tableSize; ++i)
		fEntries [i] = 65535;


	// Loop over all the prime numbers p stored in the table that could have multiples in the
	// table. If the table doesn't contain multiples of 7, for example, then 11 * p is the smallest
	// multiple of p that could be stored in the table, so we examine only primes p such that
	// 11*p < tableLimit.
	//
	// All odd multiples k*p of p have p as a prime factor. If k*p was so far marked as a prime
	// number then p is the smallest prime factor; change the value stored to p according to the
	// rules. If k*p was not marked as a prime number then we have found another prime factor; we
	// change the entry from even to odd or vice versa. The entry for the number p itself is changed
	// to p if p <= 65533.
	//
	// If p*p < tableLimit then we need to change the entries for all multiples of p*p to 0, because these
	// multiples are not square free.
	uint32 max_prime = (tableLimit - 1) / this->IndexToNumber (1) + 1;

	for (i = 1; i < tableSize; ++i) {

		// Find the next prime number in the table.
		if (fEntries [i] != 65535) continue;
		uint32 p = this->IndexToNumber (i);

		// Change the entry for the prime number itself unless it is >= 65535. Don't do anything
		// else if the prime number is so large that its multiples are not in the table. The
		// first multiple that we would check is 3*p, 7*p or 11*p, depending on FACTOR_TABLE_METHOD.
		if (p < 65535) fEntries [i] = p;
		if (p >= max_prime) continue;


		// p is a prime number. Loop through the odd multiples of p that are stored in the table.
		// If any multiple is so far marked as prime, then p is the smallest prime factor of that
		// multiple. If the multiple is so far a square-free composite number, then change whether
		// the number of prime factors is even or odd.
		uint32 j, factor, index, multiple, max_factor;
		max_factor = (tableLimit - 1) / p + 1;

		for (j = 1; ; j++) {
			factor = this->IndexToNumber (j);
			if (factor >= max_factor)
				break;

			multiple = p * factor;
			index = this->NumberToIndex (multiple);
			if (fEntries [index] == 65535) {
				fEntries [index] = p;
			} else if (fEntries [index] > 0) {
				fEntries [index] ^= 0x01;
			}
		}

		// If p*p < tableLimit, then change all odd multiples of p*p to 0 because they are
		// not square-free numbers.
		if (p < max_factor) {
			for (j = 0; ; j++) {
				factor = p * this->IndexToNumber (j);
				if (factor >= max_factor)
					break;

				multiple = p * factor;
				index = this->NumberToIndex (multiple);
				fEntries [index] = 0;
			}
		}
	}

	// We only wanted to have one prime number after maxNumber. So we can now look for the last
	// prime number in the table, and set maxNumber equal to that prime minus 1.
	for (i = tableSize - 1; ; --i) {
		if (fEntries [i] == 65535 || fEntries [i] == this->IndexToNumber (i))
			break;
	}

	fMaxNumber = this->IndexToNumber (i) - 1;
	fTableSize = tableSize;
}


// Implementation of 64 bit division under the following assumptions: We have 12 < y < 2^32. We
// have 2^k < y <= 2^(k+1), and both k and f = floor (2^(32 + k) / y) are passed as arguments.
#if DIVIDE_BY_HAND
static uint64 divide (uint64 x, uint32 y, uint32 k, uint32 f) {

	// Calculate z which is about x/y * 2^(k - 32). Using a good compiler, z will be calculated
	// using a single instruction.
	uint32 z = (uint32) ((((uint32) (x >> 32)) * (uint64) f) >> 32);

	// Let result = z multiplied by 2^(32 - k). This should be done using a simple shift
	// instruction, but the code generated for this is horrible. Do things by hand instead.
	uint32 result_hi = z >> k;
	uint32 result_lo = z << (32 - k);
	uint64 result = (((uint64) result_hi) << 32) | (uint64) result_lo;

	// Subtract result * y from x. Then the value to be returned is result + x / y. We want to know
	// how large x could be after this operation: result would be equal to x / y except for various
	// errors we made. f may be too small by 1. x >> 32 is up to 1 smaller than x / 2^32, so their
	// product may be too small by (f + 2^32). This is divided by 2^32, so the error is reduced to
	// f / 2^32 + 1, plus another error of 1 because we are shifting and not dividing, for a total
	// error in z up to 2 + f / 2^32. This error is multiplied by 2^(32 - k), so the error in
	// result is up to 2^(32 - k) * (2 + f / 2^32). The remainder of x is equal to that error,
	// multiplied by y = 2^(32 + k) / f, so the remainder is at most 2^32 * (2 * 2^32 / f + 1),
	// which is at most 5 x 2^32.
	x -= y * result;

	// We want to calculate x / y similar to what we did before. To get maximum precision, we
	// calculate x << 29 which is less than 1.25 * 2^63, so it just fits into 64 bit. This is
	// multiplied by f the way we did it before. The result is about x / y * 2^(k-3), so we shift
	// it to the right by (k - 3) bits to get approximately x / y.
	uint32 xhi = (uint32) (x >> 32);
	uint32 xlo = (uint32) x;

	uint32 shifted = (xhi << 29) | (xlo >> 3);
	z = (uint32) ((shifted * (uint64) f) >> 32);
	z >>= (k - 3);

	// Now we have z about x / y; we need to calculate how much the error could be. We started
	// with x < 5 * 2^32. shifted = x / 8 with an error of at most 7/8; shifted < 5 * 2^29. This
	// was multiplied by f, so the error in the product is at most 7/8 * f + 5*2^29 <= 1.5 * 2^32.
	// This is shifted by 32, dividing the error by 2^32 and adding one to the error, so the error
	// in z before the last shift is at most 2.5. If the last shift (z >> (k - 3)) shifts by
	// at least one bit position then the error goes down to (2.5 / 2) + 1/2 = 1.75, so we can
	// guarantee that either z or z + 1 is the correct result. If k = 3, then an individual
	// examination with tighther error bounds for the special cases will show that this stays
	// true for k >= 12.

	// To check whether z or (z + 1) is the correct result, subtract x - y * z. If the result
	// is >= y then z + 1 is the correct result. We can use a 32 bit operation if y < 2^31.
	if ((uint32) x - y * z >= y)
		++z;

	return result + z;
}
#endif

/*
 * This class is an extension of the TPrimeCount class which contains functionality that we did
 * not wish to make available to the outside.
 */
class TPrimeCountExt : public TPrimeCount {

	// All functions may be called from the factory functions in class TPrimeCount. All functions
	// may also be called from derived classes, but not from anywhere else.
	friend class TPrimeCount;
protected:

	// Constructor and destructor: Allocate some things that are common to all implementations
	TPrimeCountExt (void);
	virtual ~TPrimeCountExt (void);

	// Return pi (N); N must be in the range from 0 to maxN. If N exceeds the allowed range then
	// the result will be zero. Derived classes must implement the pi_large () function which will
	// only be called with values that are reasonably large but not greater than MaxArgument ().
	virtual uint64 Pi (uint64 N);
	virtual uint64 pi_large (uint64 N) = 0;


	// fPhiTable can be used to evaluate phi (N, k) quickly for 1 <= k <= 9. The function phi_small
	// accesses this table to return phi (N, k) for small k. The argument for phi_small must be
	// in the required range, and phi_small is most efficient if k is a constant.
	TPhiTable fPhiTable;
	inline uint64 phi_small (uint64 N, uint32 k) {
		return k == 1 ? fPhiTable.phi1 (N) :
			   k == 2 ? fPhiTable.phi2 (N) :
			   k == 3 ? fPhiTable.phi3 (N) :
			   k == 4 ? fPhiTable.phi4 (N) :
			   k == 5 ? fPhiTable.phi5 (N) :
			   k == 6 ? fPhiTable.phi6 (N) :
			   k == 7 ? fPhiTable.phi7 (N) :
			   k == 8 ? fPhiTable.phi8 (N) :
						fPhiTable.phi9 (N);
	}

	// fPrimeList can be used to access all primes quickly. To use it, HandlePrimesInListUpTo
	// must be called successfully.
	TPrimeList fPrimeList;

	uint32 NthPrime (uint32 N) { return fPrimeList.NthPrime (N); }
	uint32 PiUsingList (uint32 N) { return fPrimeList.Pi (N); }

	uint32 NextPrime (uint32 index, uint32 previous) {
		return fPrimeList.NextPrime (index, previous);
	}
	uint32 PreviousPrime (uint32 index, uint32 next) {
		return fPrimeList.PreviousPrime (index, next);
	}
};

/*
 * Constructor and destructor: Create and destroy some data structures common to all
 * implementations.
 */
TPrimeCountExt::TPrimeCountExt (void) {

}

TPrimeCountExt::~TPrimeCountExt (void) {
}

/*
 * Common implementation of the pi () functions. Checks whether the value is not too large and
 * not too small.
 */
uint64 TPrimeCountExt::Pi (uint64 N) {

	// Return 0 if N is too large.
	if (N > this->MaxArgument ()) return 0;

	// Handle trivial cases: We can calculate phi (N, c) directly. If N < p(c) then we handle all
	// cases individually. If N < p(c+1)^2 then we call phi_small. Everything else call pi_large.
	const uint32 c			= CHOICE_FOR_C;
	const uint32 pc   		= PRIME_C;
	const uint32 pc_plus_1  = PRIME_C_PLUS1;

	if (N < pc) {
		return N <  2 ? 0 : N <  3 ? 1 : N <  5 ? 2 : N <  7 ? 3 : N < 11 ? 4 :
			   N < 13 ? 5 : N < 17 ? 6 : N < 19 ? 7 : N < 23 ? 8 : 9;
	} else if (N < pc_plus_1 * pc_plus_1) {
		return this->phi_small (N, c) + c - 1;
	} else {
		return this->pi_large (N);
	}
}

/*
 * Return a rough estimate for pi (N). This uses the formula for the logarithmic integral:
 *
 *	li (x) = gamma + log log x + sum ((log x)^k) / k! / k, 1 <= k <= inf).
 */
double TPrimeCount::PiEstimate (double N) {

	if (N < 3.0) return (N < 2.0 ? 0.0 : 1.0);

	double gamma = 0.57721566490153286060651209008;
	double log_N = ::log (N);
	double sum = gamma + ::log (log_N);

	double k;
	double delta = log_N;
	double next;
	for (k = 1.0; (next = sum + delta / k) != sum; k += 1.0, delta = delta * log_N / k)
		sum = next;

	return sum;
}

/*
 * This class calculates pi (N), using Legendre's formula.
 *
 * Let pi (N) be the number of primes <= N. Let phi (N, k) be the number of positive integers <= N
 * that are not divisible by any of the k smallest primes. Let p(k) be the k-th smallest prime.
 *
 * The following formulas, found by Legendre, produce a reasonably fast method to calculate pi (N):
 * Let k = pi (sqrt (N)). Then pi (N) = phi (N, k) + k - 1. phi (N, k) can be calculated as
 * phi (N, k) = N if k = 0, and phi (N, k) = phi (N, k-1) - phi (N / p(k), k-1) if k > 0. The
 * formula pi (N) = phi (N, k) + k - 1 is actually true for pi (sqrt (N)) <= k <= pi (N).
 *
 * For a small constant c, for example c = 5, phi (N, c) can be calculated in constant time: Let
 * P = product (p(k)) for 1 <= k <= c, let Q = product (p(k) - 1) for 1 <= k <= c. Then
 * phi (N, c) = Q * (N / P) + phi (N % P, c) and phi (N % p, c) can be found by using a lookup-
 * table. For N < (p (c))^2, we use this directly to calculate pi (N), handling the cases where
 * N < p(c) individually.
 */
#pragma mark --- class TLegendrePrimeCount ---
class TLegendrePrimeCount : public TPrimeCountExt {

public:
	// Constructor and destructor are empty; nothing is needed except the base class functionality.
	TLegendrePrimeCount (void) { }
	~TLegendrePrimeCount (void) { }

	// SelfTest (): Calling this function causes an intensive test of all functions in this class.
	// If the result is non-zero then the n-th of those tests failed, and some bug needs fixing.
	virtual int SelfTest (void);

	// BytesNeeded (): Returns the number of bytes of memory used by the implementation.
	virtual unsigned long BytesNeeded (void);

	// Calculate pi_large for large values of N.
	virtual uint64 pi_large (uint64 N);

private:
	// Calculate phi (N, k) where N >= p (k+1)^2
	uint64 phi_fast (uint64 N, uint32 k);
//	uint32 phi_fast (uint32 N, uint32 k);
};

// BytesNeeded () returns the number of bytes of memory used by the implementation.
unsigned long TLegendrePrimeCount::BytesNeeded (void) {

	return sizeof (*this) + fPrimeList.BytesNeeded ();
}

// SelfTest (): Calling this function causes an intensive test of all the functions in this class
int TLegendrePrimeCount::SelfTest (void) {
	return 0;
}

// Calculate pi_large for large values of N.
uint64 TLegendrePrimeCount::pi_large (uint64 N) {

	// We calculate K2 = pi (N^(1/2)) or slightly larger, then use the formula pi (N) =
	// phi (N, K2) + K2 - 1; using phi (N, k) = phi (N, k-1) - phi (N / p(k), k - 1). We start a
	// sum with K2 - 1.

	uint32 N2 = (uint32) (::sqrt ((double) N) + 0.5);
	uint32 K2 = this->Pi (N2);

	uint64 sum = K2 - 1;

	// If K2 is greater than the number of primes in the prime list then we use a sieve;
	// we use the recursion formula repeatedly until we have to add a number phi (N, k) where
	// p (k) is in the sieve.
	uint32 primesInList = fPrimeList.NumberOfPrimes ();

	if (K2 > primesInList) {
		TPrimeSieve sieve (&fPrimeList);
		uint32 p = N2 + 1;
		while (K2 > primesInList) {
			p = sieve.PrimeBefore (p);
			sum -= this->phi_fast (N / p, --K2);
		}
	}

	// Use the function phi_fast for the rest of the calculation.
	return sum + phi_fast (N, K2);
}

// Two almost identical functions to calculate phi (N, k) where N >= p (k+1)^2.
uint64 TLegendrePrimeCount::phi_fast (uint64 N, uint32 k) {

	if (N == (uint32) N) return this->phi_fast ((uint32) N, k);

//	Subtract phi (N / p(k), k-1) as long as N / p(k) >= p(k)^2.
//	If N / p(k) < p(k)^2: Numbers not divisible by first k-1 primes are 1, primes >= p(k),

	return 0;
//	phi (x, k-1) = phi (x, k-2) - 1
}


/*
 * class TIncrementalSieve is a most important data structure: It allows fast calculation of
 * phi (x, k) for large values of x and k. phi (x, k) is the number of integers that are not
 * divisible by the first k primes.
 */
#pragma mark --- class TMLPrimeCount ---

/*
 * This class calculates pi (N), the number of primes <= N, using the Extended Meissel-Lehmer
 * Algorithm, as described by Lagarias, Miller and Odlyzko.
 *
 * Let pi (N) be the number of primes <= N. Let phi (N, k) be the number of positive integers <= N
 * that are not divisible by any of the k smallest primes. Let phi (N, x, k) = phi (N / x, k)
 * if x = 1 or x is the product of an even number of primes, and phi (N, x, k) = -phi (N / x, k)
 * if x is a prime or the product of an odd number of primes. Let p(k) be the k-th smallest prime.
 *
 * The following formulas, found by Legendre, produce a reasonably fast method to calculate pi (N):
 * Let k = pi (sqrt (N)). Then pi (N) = phi (N, k) + k - 1. phi (N, k) can be calculated as
 * phi (N, k) = N if k = 0, and phi (N, k) = phi (N, k-1) - phi (N / p(k), k-1) if k > 0. The
 * formula pi (N) = phi (N, k) + k - 1 is actually true for pi (sqrt (N)) <= k <= pi (N).
 *
 * For a small constant c, for example c = 5, phi (N, c) can be calculated in constant time: Let
 * P = product (p(k)) for 1 <= k <= c, let Q = product (p(k) - 1) for 1 <= k <= c. Then
 * phi (N, c) = Q * (N / P) + phi (N % P, c) and phi (N % p, c) can be found by using a lookup-
 * table. For N < (p (c))^2, we use this directly to calculate pi (N), handling the cases where
 * N < p(c) individually.
 *
 * For large N, we choose a constant 1 <= M <= sqrt (N), preferably M about N^(1/3). With
 * K = pi (sqrt (N)), phi (N, K) can by calcuated by adding phi (N, x, c+1) over the square-free
 * integers x <= M with no prime factor p <= p (c+1), then adding phi (N, x * p(k+1), k) over the
 * square-free  integers M / p(k+1) + 1 <= x <= M with no prime factor p <= p(k+1),
 * for c+1 <= k <= pi (M)-1, then adding phi (N, p(k+1), k) for pi (M) <= k <= K-1.
 */
class TMLPrimeCount : public TPrimeCountExt {

	// Function MakeMeisselLehmerCounter has access to quite a few internals of this function.
	friend TPrimeCount* TPrimeCount::MakeMeisselLehmerCounter (uint64 maxN);

private:
	// Constructor and destructor: The constructor creates an object that can be used to calculate
	// pi (N) for N <= maxNumber; the destructor destroys such an object. Only the function
	// MakeMeisselLehmerCounter can construct such an object. After the object is created,
	// MakeMeisselLehmerCounter will check the result of MaxArgument () and destroy the object if
	// not enough memory could be allocated.
	TMLPrimeCount (uint64 maxNumber);
	~TMLPrimeCount (void);

	// SelfTest (): Calling this function causes an intensive test of all functions in this class.
	// If the result is non-zero then the n-th of those tests failed, and some bug needs fixing.
	virtual int SelfTest (void);

	// BytesNeeded (): Returns the number of bytes of memory used by the implementation.
	virtual unsigned long BytesNeeded (void);

	virtual uint64 pi_large (uint64 N);


	// These functions are there to be able to check things.

	// slow_phi returns phi (N, k) using the recursion formula in a slightly optimised form. It
	// does not use any other code except NthPrime and is very useful to verify other code. It is
	// quite slow but simple.
	uint64 slow_phi (uint64 N, uint32 k);

	// phi (N, k) calculates phi (N, k) using a faster algorithm.
	uint64 phi (uint64 N, uint32 k);

	uint64 slow_pi (uint64 N);

	// This is a function used to check the algorithm for calculating pi (N).
	uint64 pi_algorithm1 (uint64 N);
	uint64 pi_algorithm2 (uint64 N);

private:
	// fFactorTable allows for quick access to factors of any number.
	TFactorTable fFactorTable;


	// Data structures for the sieve. eSieveBytes is the size of the sieve in bytes. This number
	// might be very performance critical, but some testing is required. It must be a multiple of
	// 4620 which is 4 * (3 * 5 * 7 * 11), so that multiples of 3, 5, 7 and 11 can be removed easily
	// from the sieve.
	enum { eSieveBytes = 4620 * (CACHE_SIZE / 4620 + (CACHE_SIZE < 4620)) };

	// fSieve is the sieve itself, using one bit for every odd integer. The size of the sieve is a
	// multiple of 3*5*7*11 which has the advantage that multiples of 3, 5, 7 and 11 can be removed
	// easily. Its size is chosen so that it fits well into cache memory.
	uint32 *fSieve;

	// fCounter512 counts the number of bits set in each group of 16 consecutive words = 512 bits.
	uint16 fCounter512 [eSieveBytes / 64 + 1];

	// This is where the sieve starts at the moment; multiple of SieveSize. And the number of
	// integers handled by the sieve, equal to SieveSize or less.
	uint64 fSieveStart;
	uint32 fSieveSize;

	// We need to keep track of values phi (N, k) for earlier sieves; this table will do this.
	// fSieveTotals [i] is either phi (fSieveStart, i) or phi (fSieveStart + fSieveSize, i).
	// fBitsInPartialSieve is the numbe of bits that remain set in the current sieve. fThisPhi
	// equals phi (fSieveStart, k) while we are finding values of phi (x, k). fSievedPrimes is the
	// number of primes that are handled within this call to pi_large (), fMaxSievedPriems is the
	// maximum that could be handled.
	uint32 fSievedPrimes;
	uint32 fMaxSievedPrimes;
	uint64 *fSieveTotals;
	uint32 fBitsInPartialSieve;
	uint64 fThisPhi;

	// This function is used for the initial setup of the sieve: sieveStart must be a multiple of
	// the sieve size; size is the number integers that we want to handle (typically less than
	// the maximum on the last use of the sieve).
	void StartSieve (uint64 sieveStart, uint32 size, uint32 nPrimes);

	// The first function removes the next prime and does all the necessary things. RemovePrimes
	// does the same, but doesn't keep values of phi and the array fCounter32 up-to-date, except
	// for the last value of phi.
	void RemovePrime (uint32 primeIndex);
	void RemovePrimes (uint32 primeIndex, uint32 lastPrimeIndex);

	// Lookup phi (x, k), where x must be in the range sieveStart <= x < sieveStart + size, and
	// k must have the correct value. phi2 is the same, but doesn't rely on the array fCounter512.
	uint64 PhiUsingSieve (uint64 x);
	uint64 PhiUsingSieve2 (uint64 x);

	// This function returns the sum of all phi values for a given prime
	uint64 SumPhiValues (uint64 N, uint64 startDivisor, uint32 k);

	// We need to keep track of other things. When we are looking for divisors p(j) to divide
	// N / p(j) / p(k+1) to get a value inside the sieve, we start with j = fPrimeIndex [k] and
	// proceed to smaller values; the first j beyond the sieve will then be stored into fPrimeIndex
	// so we can start there in the next sieve.
	uint32 *fPrimeIndex;

	// These are used to accelerate the sieving process: For every prime p(k), fFirstBitIndex is
	// the index of the first bit in the sieve representing a multiple of p(k) that needs to be
	// deleted. To remove multiples of p(k), we delete bit number fFirstBitIndex [k] and increase
	// fFirstBitIndex by p(k) as long as fFirstBitIndex is less than the number of bits in the sieve.
	// Then we subtract that number of bits in the sieve to get the correct index for the next sieve.
	uint32 *fFirstBitIndex;

	// Out of every 30 consecutive integers, only 8 are not multiples of 2, 3 or 5. If the current
	// multiple of p(k) is p(k) * (30i + j), and j is the n-th of these eight numbers, then
	// fMultiplier [k] = n. Depending on the value, we know that we can skip one or two odd
	// multiples of p(k) because they can be divided by 3 or 5.
	uint8 *fMultiplier;

	// fFirstPrimeInSieve and fLastPrimeInSieve are the indices of the first and the last prime
	// that are in the range from fSieveStart to fSieveStart + fSieveSize - 1. fLastPrimeToRemove
	// is the index of the last prime of which multiples need to be removed.
	uint32 fFirstPrimeInSieve;
	uint32 fLastPrimeInSieve;
	uint32 fLastPrimeToRemove;

	// The first two variables are set whenever we have counted the bits in the first words of the
	// sieve. The second set is set when we know how many bits are set in groups of 16 words.
	uint32 fWordsCounted;
	uint32 fBitsInFirstWords;
	uint32 f16WordsCounted;
	uint32 fBitsInFirst16Words;

	// We need an array that translates an integer into a number of bits. fBitCount [i] equals the
	// number of bits set in the number i. The BitCount () function returns the number of bits in
	// a 32 bit number quickly.
	uint8 fBitCount [2048];
	inline uint32 BitCount (uint32 word) {
		return fBitCount [word >> 22] + fBitCount [(word >> 11) & 0x7ff]
									  + fBitCount [word & 0x7ff];
	}




	// Two arrays to support fast divide operations. For every prime number p stored, find k such
	// that 2^k < p <= 2^(k + 1), then calculate 2^(32 + k) / p.
#if DIVIDE_BY_HAND
	uint8 *fPrimeShift;
	uint32 *fPrimeInverse;
#endif
};

// SelfTest performs all kinds of tests and returns zero if all tests passed.
int TMLPrimeCount::SelfTest (void) {

	int err = -1;

	if (TEST_PRIME_TABLE) {

		// Test the primes_delta table and return 1 if there is an error. We check by hand that
		// primes_delta [0] = 0 and primes_delta [1] = 2; this checks the first prime. Then we
		// check whether odd numbers >= 3 are primes by trial division by odd integers up to
		// the square root of each prime. This checks whether the primes table has been initialised,
		// whether the sieve worked correctly, and whether the difference between any two primes
		// did fit into an uint8. This has been tested with PRIME_TABLE_SIZE = 1,000,000.
		err = 1;

		uint32 prime_count = 0;
		uint32 prev_prime = 0;
		uint32 next_prime;

		if (prime_count < fPrimeList.NumberOfPrimes ()) {
			next_prime = 2;
			if (next_prime != this->NextPrime (++prime_count, prev_prime)) goto exit;
			prev_prime = next_prime;
		}

		for (next_prime = 3; prime_count < fPrimeList.NumberOfPrimes (); next_prime += 2) {
			uint32 divisor;
			bool is_prime = true;

			for (divisor = 3; divisor * divisor <= next_prime; divisor += 2) {
				if (next_prime % divisor == 0) { is_prime = false; break; }
			}

			if (is_prime) {
				if (next_prime != this->NextPrime (++prime_count, prev_prime)) goto exit;
				prev_prime = next_prime;
			}
		}
	}

	if (TEST_FACTOR_TABLE_INDEX) {

		// Test whether the functions IndexToNumber and NumberToIndex work correctly. This has
		// been tested for all numbers up to 250,000,000 and with FACTOR_TABLE_METHOD = 2, 5 and 7.
		err = 2;

		uint32 index, number;
		bool valid;

		for (index = 0, number = 1; number <= 250ul * 1000 * 1000; ++number) {
			valid = FACTOR_TABLE_METHOD == 2 ? (number % 2) != 0
				  : FACTOR_TABLE_METHOD == 5 ? (number % 2) && (number % 3) && (number % 5)
				  : FACTOR_TABLE_METHOD == 7 ? (number % 2) && (number % 3) && (number % 5)
				  															&& (number % 7)
				  : false;

			if (fFactorTable.NumberToIndex (number) != index) goto exit;
			if (valid && fFactorTable.IndexToNumber (index) != number) goto exit;
			if (valid) ++index;
		}
	}

	if (TEST_NTH_PRIME) {

		// Test whether the function NthPrime works correctly. This assumes that the prime
		// delta table has already been tested. We test all primes sequentially, then backwards,
		// then every third prime, then every tenth prime.

		err = 3;
		uint32 i, prime;

		for (i = 1, prime = 2; i < fPrimeList.NumberOfPrimes ();
														prime = this->NextPrime (++i, prime))
			if (this->NthPrime (i) != prime) goto exit;
		for (; i >= 1; prime = this->PreviousPrime (--i, prime))
			if (this->NthPrime (i) != prime) goto exit;

		for (i = 1, prime = 2; i < fPrimeList.NumberOfPrimes ();
														prime = this->NextPrime (++i, prime))
			if (i % 3 == 0 && this->NthPrime (i) != prime) goto exit;
		for (; i >= 1; prime = this->PreviousPrime (--i, prime))
			if (i % 3 == 0 && this->NthPrime (i) != prime) goto exit;

		for (i = 1, prime = 2; i < fPrimeList.NumberOfPrimes ();
														prime = this->NextPrime (++i, prime))
			if (i % 10 == 0 && this->NthPrime (i) != prime) goto exit;
		for (; i >= 1; prime = this->PreviousPrime (--i, prime))
			if (i % 10 == 0 && this->NthPrime (i) != prime) goto exit;
	}

	if (TEST_PHI_TABLES) {

		// Test the contents of the tables fPhi2Table etc. by comparing them with the results of
		// the slow_phi function. This is a complete test.

		err = 4;
		uint32 i;

		for (i = 0; i < P_2; ++i) if (this->slow_phi (i, 2) != fPhiTable.fPhi2Table [i]) goto exit;
		for (i = 0; i < P_3; ++i) if (this->slow_phi (i, 3) != fPhiTable.fPhi3Table [i]) goto exit;
		for (i = 0; i < P_4; ++i) if (this->slow_phi (i, 4) != fPhiTable.fPhi4Table [i]) goto exit;
		for (i = 0; i < P_5; ++i) if (this->slow_phi (i, 5) != fPhiTable.fPhi5Table [i]) goto exit;

#if PHI_LOOKUP_TABLE >= 6
		for (i = 0; i < P_6; ++i) if (this->slow_phi (i, 6) != fPhiTable.fPhi6Table [i]) goto exit;
#endif

#if PHI_LOOKUP_TABLE == 7
		for (i = 0; i < P_7; ++i) if (this->slow_phi (i, 7) != fPhiTable.fPhi7Table [i]) goto exit;
#endif
	}

	if (TEST_PHI_FUNCTIONS) {

		// Test whether the functions phi1, phi2 to phi9 are correct by comparing with the results
		// of the slow_phi function. This has been tested for six million values from 0 to 10^18,
		// using all possible values for PHI_LOOKUP_TABLE.

		err = 5;
		uint64 i, limit, delta;
		for (limit = 1000, delta = 1; limit < 1000000ull * 1000000ull * 1000000ull;
													limit *= 10, delta *= 10) {
			for (i = 0; i < limit; i += delta) {
				if (this->phi_small (i, 1) != this->slow_phi (i, 1)) goto exit;
				if (this->phi_small (i, 2) != this->slow_phi (i, 2)) goto exit;
				if (this->phi_small (i, 3) != this->slow_phi (i, 3)) goto exit;
				if (this->phi_small (i, 4) != this->slow_phi (i, 4)) goto exit;
				if (this->phi_small (i, 5) != this->slow_phi (i, 5)) goto exit;
				if (this->phi_small (i, 6) != this->slow_phi (i, 6)) goto exit;
				if (this->phi_small (i, 7) != this->slow_phi (i, 7)) goto exit;
				if (this->phi_small (i, 8) != this->slow_phi (i, 8)) goto exit;
				if (this->phi_small (i, 9) != this->slow_phi (i, 9)) goto exit;
			}
		}
	}

	if (TEST_FACTOR_TABLE) {

		// Test the contents of fFactorTable.
		err = 6;
		uint32 i;
		for (i = 0; i < fFactorTable.NumberOfEntries (); ++i) {
			uint32 n = fFactorTable.IndexToNumber (i);
			uint32 value = fFactorTable.GetEntry (i);

			if (n == 1) { if (value != 65534) goto exit; continue; }
			if (n % 2 == 0) goto exit;

			int factor_count = 0;
			uint32 smallest_factor = 0;
			uint32 remainder = n;
			bool square_free = true;

			uint32 index, divisor;
			for (index = 2, divisor = 3; divisor * divisor <= remainder;
											divisor = this->NextPrime (++index, divisor)) {
				if (remainder % divisor != 0) continue;
				if (factor_count == 0) smallest_factor = divisor;
				++factor_count;
				remainder /= divisor;
				if (remainder % divisor == 0) { square_free = false; break; }
			}

			if (remainder > 1) {
				if (factor_count == 0) smallest_factor = remainder;
				++factor_count;
			}

			if (! square_free) {
				if (value != 0) goto exit;
			} else if (factor_count == 1) {
				if (n != smallest_factor) goto exit;
				if (value != (smallest_factor < 65535 ? smallest_factor : 65535)) goto exit;
			} else if (smallest_factor % 2 == 0) {
				goto exit;
			} else if (factor_count % 2 == 0) {
				if (value != smallest_factor - 1) goto exit;
			} else {
				if (value != smallest_factor) goto exit;
			}
		}
	}


	if (TEST_PHI) {

		// Test whether the results of function phi (N, k) are correct by comparing with the
		// results of functions phi1, phi2 etc.

		err = 7;
		uint64 i, limit, delta;
		for (limit = 100000, delta = 1; limit < 1000000ull * 1000000ull * 1000000ull;
													limit *= 10, delta *= 10) {
			for (i = 0; i < limit; i += delta) {
				if (this->phi_small (i, 1) != this->phi (i, 1)) goto exit;
				if (this->phi_small (i, 2) != this->phi (i, 2)) goto exit;
				if (this->phi_small (i, 3) != this->phi (i, 3)) goto exit;
				if (this->phi_small (i, 4) != this->phi (i, 4)) goto exit;
				if (this->phi_small (i, 5) != this->phi (i, 5)) goto exit;
				if (this->phi_small (i, 6) != this->phi (i, 6)) goto exit;
				if (this->phi_small (i, 7) != this->phi (i, 7)) goto exit;
				if (this->phi_small (i, 8) != this->phi (i, 8)) goto exit;
				if (this->phi_small (i, 9) != this->phi (i, 9)) goto exit;
			}
		}
	}

	if (TEST_SLOW_PI) {

		// Test the result of the slow_pi function. We compare results with information taken
		// from the prime number array.

		err = 8;
		uint32 i;
		uint32 prime_index = 1, prime = 2;
		uint32 result = 0;
		for (i = 0; i <= 100000; ++i) {
			if (i == prime) { ++result; prime = this->NthPrime (++prime_index); }
			uint32 check = this->slow_pi (i);
			if (result != check)
				goto exit;
		}
	}

	if (TEST_PI_ALGORITHM1) {

		// Test the result of the pi_algorithm1 function. We compare results with information taken
		// from the prime number array.

		err = 9;
		uint32 i;
		uint32 prime_index = 1, prime = 2;
		uint32 result = 0;
		for (i = 0; i <= 3000000; ++i) {
			if (i == prime) { ++result; prime = this->NthPrime (++prime_index); }
			uint32 check = this->pi_algorithm1 (i);
			if (result != check && i > 10000) goto exit;
		}
	}

	if (TEST_PI_ALGORITHM2) {

		// Test the result of the pi_algorithm2 function. We compare results with information taken
		// from the prime number array.

		err = 10;
		uint32 i;
		uint32 prime_index = 1, prime = 2;
		uint32 result = 0;
		for (i = 0; i <= 200000; ++i) {
			if (i == prime) { ++result; prime = this->NthPrime (++prime_index); }
			uint32 check = this->pi_algorithm2 (i);
			if (result != check) goto exit;
		}
	}

	if (TEST_PI) {

		// Test the result of the pi function. We compare results with information taken
		// from the prime number array.

		err = 11;
		uint32 i;
		uint32 prime_index = 1, prime = 2;
		uint32 result = 0;
		for (i = 0; i <= 100; ++i) {
			if (i == prime) { ++result; prime = this->NthPrime (++prime_index); }
			uint32 check = this->Pi (i);
			if (result != check) goto exit;
		}

		err = 12;
		if (this->Pi (1000) != 168) goto exit;
		if (this->Pi (10000) != 1229) goto exit;
		if (this->Pi (100000) != 9592) goto exit;
		if (this->Pi (1000000) != 78498) goto exit;
		if (this->Pi (10000000) != 664579) goto exit;
		if (this->Pi (100000000) != 5761455) goto exit;
		if (this->Pi (1000000000) != 50847534) goto exit;
		//if (this->Pi (10000000000) != 455052511) goto exit;
		//if (this->Pi (100000000000) != 4118054813ul) goto exit;
		//if (this->Pi (1000000000000) != 37607912018) goto exit;
		//if (this->Pi (10000000000000) != 346065536839) goto exit;
		//if (this->Pi (100000000000000) != 3204941750802) goto exit;
		//if (this->Pi (1000000000000000) != 29844570422669) goto exit;
		//if (this->Pi (10000000000000000) != 279238341033925) goto exit;
		//if (this->Pi (100000000000000000) != 2623557157654233) goto exit;
		//if (this->Pi (1000000000000000000) != 24739954287740860) goto exit;
		//if (this->Pi (10000000000000000000) != 234057667276344607) goto exit;
	}

	// Exit reporting a failure or success.
	err = 0;
exit:
	return err;
}
// BytesNeeded () returns the number of bytes of memory used by the implementation.
unsigned long TMLPrimeCount::BytesNeeded (void) {

	uint32 bytesNeeded = sizeof (*this);
	bytesNeeded += fPrimeList.BytesNeeded () - sizeof (fPrimeList);
	bytesNeeded += fFactorTable.BytesNeeded () - sizeof (fFactorTable);

	bytesNeeded += (eSieveBytes / 4 + 16) * sizeof (uint32); // fSieve

	bytesNeeded += (fMaxSievedPrimes + 1) * sizeof (uint64); // fSieveTotals
	bytesNeeded += (fMaxSievedPrimes + 1) * sizeof (uint32); // fPrimeIndex
	bytesNeeded += (fMaxSievedPrimes + 1) * sizeof (uint32); // fFirstBitIndex
	bytesNeeded += (fMaxSievedPrimes + 1) * sizeof (uint8); // fMultiplier

#if DIVIDE_BY_HAND
	bytesNeeded += (fPrimeList.NumberOfPrimes () + 1) * sizeof (uint8); // fPrimeShift
	bytesNeeded += (fPrimeList.NumberOfPrimes () + 1) * sizeof (uint32); // fPrimeInverse
#endif

	return bytesNeeded;
}


// Constructor: Create a new TMLPrimeCount object. Initialises everything if this is the first object
// allocated.
TMLPrimeCount::TMLPrimeCount (uint64 maxNumber) {

#if DIVIDE_BY_HAND
	// Initialise plain pointers to NULL.
	fPrimeShift = NULL;
	fPrimeInverse = NULL;
#endif

	// Calculate N3 and M: N32 is the cube root of maxNumber, M is the maximum value that M could
	// ever have in the algorithm. At the moment we set this to 5 * N3; maybe it should be larger.
	double N3_double = ::pow ((double) maxNumber, 1.0 / 3.0) + 2;
	double M_double = 5.0 * N3_double;
	uint32 N3 = (uint32) N3_double;
	uint32 M = (uint32) M_double;

	// Initialise the prime number list to handle all primes up to M; initialise the factor table
	// to handle factors of all numbers up to M.
	fPrimeList.HandlePrimesUpTo (M);
	fFactorTable.HandleNumbersUpTo (M);

	uint32 Pi_M = fPrimeList.NumberOfPrimes ();
	if (Pi_M == 0 || fFactorTable.MaxNumber () == 0)
		return;

	uint32 Pi_N3 = fPrimeList.Pi (N3);

	// Fill the bitcount array. fBitCount [i] is set to the number of bits that are set in the
	// number i. This is done recursively: fBitCount [0] = 0, and fBitCount [2^k + i] =
	// fBitCount [i] + 1 if i < 2^k.
	{
		int i, j;

		fBitCount [0] = 0;
		for (i = 1; i <= sizeof (fBitCount) / 2; i *= 2) {
			for (j = 0; j < i; ++j) {
				fBitCount [i + j] = fBitCount [j] + 1;
			}
		}
	}

	// Allocate storage for the sieve and for all kinds of data. If any of the allocations fail then
	// free everything and set it back to 0.
	fSieve = (uint32 *) ::malloc ((eSieveBytes / 4 + 16) * sizeof (uint32));
	fSieveTotals = (uint64 *) ::malloc ((Pi_N3 + 1) * sizeof (uint64));
	fPrimeIndex = (uint32 *) ::malloc ((Pi_N3 + 1) * sizeof (uint32));
	fFirstBitIndex = (uint32 *) ::malloc ((Pi_N3 + 1) * sizeof (uint32));
	fMultiplier = (uint8 *) ::malloc ((Pi_N3 + 1) * sizeof (uint8));

#if DIVIDE_BY_HAND
	fPrimeShift = (uint8 *) ::malloc ((Pi_M + 1) * sizeof (uint8));
	fPrimeInverse = (uint32 *) ::malloc ((Pi_M + 1) * sizeof (uint32));
#endif

	if (fSieve == NULL || fSieveTotals == NULL || fPrimeIndex == NULL ||
		fFirstBitIndex == 0 || fMultiplier == NULL)
		return;

#if DIVIDE_BY_HAND
	if (fPrimeShift == NULL || fPrimeInverse == NULL)
		return;
#endif


#if DIVIDE_BY_HAND
	// Allocate and fill the arrays fPrimeInverse and fPrimeShift. Let p (k) be the k-th smallest
	// prime. Choose n such that 2^n < p (k) <= 2^(n+1). Then fPrimeShift [k] = n, and
	// fPrimeInverse [k] = floor (2^(32 + n) / p (k)). These two arrays are used for fast
	// multiplication on some machines.
	uint32 i, shift;
	for (i = 1, shift = 0; i <= Pi_M; ++i) {
		uint32 p = fPrimeList.NthPrime (i);
		while (p > (((uint32) 2) << shift)) ++shift;
		fPrimeShift [i] = shift;
		fPrimeInverse [i] = (uint32) ((((uint64) 1) << (32 + shift)) / p);
	}
#endif

	// If everything has been initialised without problems then set fMaxArgument to maxNumber.
	// Also store how many primes can be used in the sieving process.
	fMaxArgument = maxNumber;
	fMaxSievedPrimes = Pi_N3;
}

// Destructor: Deallocate all data that might have been allocated. Most of the data is stored
// in objects, so no code for those is needed in the destructor.
TMLPrimeCount::~TMLPrimeCount (void) {

	::free (fSieve);
	::free (fSieveTotals);
	::free (fPrimeIndex);
	::free (fFirstBitIndex);
	::free (fMultiplier);

#if DIVIDE_BY_HAND
	std::free (fPrimeShift);
	std::free (fPrimeInverse);
#endif
}


// Slow function for calculating phi (N, k). Only used for testing purposes. Uses the NthPrime
// function, so this must be checked first.
uint64 TMLPrimeCount::slow_phi (uint64 N, uint32 k) {

	if (k > fPrimeList.NumberOfPrimes ()) return 0;

	// phi (N, k) is 0 if N = 0, 1 if N = 1 and N if k = 0. Otherwise we can use the recursion
	// formula phi (N, k) = phi (N, k-1) - phi (N / p (k), k-1); applying this recursion formula
	// in a loop means phi (N, k) = phi (N, 0) - sum over phi (N / p (k), k-1) for 1 <= k <= N. We
	// also know that phi (N, k) = 1 if 1 <= N < p (k+1) or phi (N / p (k), k-1) = 1 if
	// p(k) <= N < p(k)^2, and if this is the case for one k then it is the case for every larger k
	// as well.

	if (k == 0 || N <= 1) return N;

	uint32 i;
	uint64 result = N;

	for (i = 1; i <= k; ++i) {
		uint32 p = this->NthPrime (i);
		uint64 N2 = N / p;
		if (N2 >= p) { result -= this->slow_phi (N2, i-1); continue; }

		while (N < this->NthPrime (k)) --k;
		result -= (k - i + 1); break;
	}

	return result;
}


// Moderately fast function for calculating phi (N, k).
uint64 TMLPrimeCount::phi (uint64 N, uint32 k) {

	// Cannot handle k > fPrimeList.NumberOfPrimes (), then handle k <= 9 by using the phi(n) functions.

	if (k > fPrimeList.NumberOfPrimes ()) return 0;
	if (k == 0) return N;
	if (k <= 9) return this->phi_small (N, k);

	// Handle N = 0, handle N < NthPrime (k+1).
	if (N == 0) return 0;
	if (N < this->NthPrime (k+1)) return 1;

	uint32 i;
	uint64 result = this->phi_small (N, 9);

	for (i = 10; i <= k; ++i) {
		uint32 p = this->NthPrime (i);
		uint64 N2 = N / p;
		if (N2 >= p) { result -= this->phi (N2, i-1); continue; }

		while (N < this->NthPrime (k)) --k;
		result -= (k - i + 1); break;
	}

	return result;
}


#if FACTOR_TABLE_METHOD == 5 && CHOICE_FOR_C < 3
	#error CHOICE_FOR_C must be at least 3 when FACTOR_TABLE_METHOD is 5
#endif
#if FACTOR_TABLE_METHOD == 7 && CHOICE_FOR_C < 4
	#error CHOICE_FOR_C must be at least 4 when FACTOR_TABLE_METHOD is 7
#endif


// This is a function used to describe and test the method for calculating pi (N). It is not fast
// as the sieve is not implemented; it only describes which values of phi (N, k) have to be
// calculated and in which order.
uint64 TMLPrimeCount::pi_algorithm1 (uint64 N) {

	// Choose constants c; pc = prime number c, pc_1 = prime number c+1. c must not be
	// greater than 10.
	const uint32 c		= CHOICE_FOR_C;
	const uint32 pc   	= PRIME_C;
	const uint32 pc_1	= PRIME_C_PLUS1;

	// Choose c = 5, M = N ^ (1/3). If N < p (c) use a lookup table. If N < p(c+1)^2 then call
	// phi directly.
	if (N < pc) return N < 2 ? 0 : N < 3 ? 1 : N < 5 ? 2 : N < 7 ? 3 : N < 11 ? 4 :
					   N < 13 ? 5 : N < 17 ? 6 : N < 19 ? 7 : N < 23 ? 8 : 9;
	if (N < pc_1*pc_1) return this->phi_small (N, c) + c - 1;

	// Calculate K2 = pi (N^(1/2)), K3 = pi (N^(1/3)). Make sure the result is not too small
	// and not much too large. Calculate M arbitrary as N^(1/3), pi_M = pi (M).
	uint32 K2 = this->pi_algorithm1 ((uint64) (::sqrt ((double) N) + 0.5));
	uint32 K3 = this->pi_algorithm1 ((uint64) (::pow ((double) N, 1.0 / 3.0) + 0.5));

	uint32 M = (uint32) ::pow ((double) N, 1.0 / 3.0);
	uint32 pi_M = this->pi_algorithm1 (M);

	// To calculate pi (N): Start with K2 - 1.
	uint64 sum1 = K2 - 1;
	uint64 sum2 = 0;
	uint64 phi_value;
	uint32 k, j, pk, start, end, entry;


	// Add phi (N, x, c) for 1 <= x <= M, where x is square-free with no prime factor <= p(c).
	// If x has a square factor then the factor table has a value of 0. If x has a prime factor p,
	// p <= pc, then the factor table contains p-1 or p. We are looking for entries greater than pc.
	// We have to watch out for the case c = 1, pc = 2: Values with a smallest prime factor of 3
	// and an even number of prime factors are identified by an entry of 2.
	start = fFactorTable.NumberToIndex (1);
	end = fFactorTable.NumberToIndex (M + 1);
	for (j = start; j < end; ++j) {
		entry = fFactorTable.GetEntry (j);
		if (entry <= (pc == 2 ? 0 : pc)) continue;
		phi_value = this->phi_small (N / fFactorTable.IndexToNumber (j), c);
		if (entry & 0x01) sum2 += phi_value; else sum1 += phi_value;
	}

	// Let k = c. If k <= pi_M - 2 then add phi (N, x*p(k+1), c) for square-free integers x with
	// M/p(k+1) + 1 <= x <= M with no prime factor <= p(k+1), then let k = k+1. This looks exactly
	// the same as the next loop, but here we should call one of the functions phi1 to phi9.
	k = c; pk = pc_1;
	if (k + 2 <= pi_M) {
		start = fFactorTable.NumberToIndex (M / pk + 1);
		end = fFactorTable.NumberToIndex (M + 1);
		for (j = start; j < end; ++j) {
			entry = fFactorTable.GetEntry (j);
			if (entry <= pk) continue;
			phi_value = this->phi_small (N / fFactorTable.IndexToNumber (j) / pk, c);
			if (entry & 0x01) sum1 += phi_value; else sum2 += phi_value;
		}
		++k;
	}

	// As long as k <= pi_M - 2 add phi (N, x*p(k+1), k) for square-free integers x with
	// M / p(k+1) + 1 <= x <= M with no prime factor <= p(k+1), then let k = k+1. This looks exactly
	// like the previous loop, but here we should use a sieve.
	for (; k + 2 <= pi_M; ++k) {
		pk = this->NthPrime (k+1);
		start = fFactorTable.NumberToIndex (M / pk + 1);
		end = fFactorTable.NumberToIndex (M + 1);
		for (j = start; j < end; ++j) {
			entry = fFactorTable.GetEntry (j);
			if (entry <= pk) continue;
			phi_value = this->phi (N / fFactorTable.IndexToNumber (j) / pk, k);
			if (entry & 0x01) sum1 += phi_value; else sum2 += phi_value;
		}
	}

	// Start at least with k >= pi_M. Then add phi (N, p(k+1), k) as long as k < K2;
	// if k >= k0
	if (k < pi_M)
		k = pi_M;

	// Add phi (N, p(k+1), k), pi (M) <= k < pi (N^(1/2))
	for (; k < K3; ++k) {
		pk = this->NthPrime (k+1);
		sum2 += this->phi (N / pk, k);
	}
	// Add phi (N, p(k+1), k), pi (M) <= k < K2)
	for (; k < K2; ++k) {
		pk = this->NthPrime (k+1);
		sum2 += this->phi (N / pk, K3);
		sum1 += k - K3;
	}

	return sum1 - sum2;
}

// This is a function used to describe and test the method for calculating pi (N). It is not fast
// as the sieve is not implemented; it only describes which values of phi (N, k) have to be
// calculated and in which order.
uint64 TMLPrimeCount::pi_algorithm2 (uint64 N) {

	// Choose constants c; pc = prime number c, pc_1 = prime number c+1.
	const uint32 c		= CHOICE_FOR_C;
	const uint32 pc   	= PRIME_C;
	const uint32 pc_1	= PRIME_C_PLUS1;

	// If N < p (c) use a lookup table. If N < p(c+1)^2 then call phi directly.
	if (N < pc) return N < 2 ? 0 : N < 3 ? 1 : N < 5 ? 2 : N < 7 ? 3 : N < 11 ? 4 :
					   N < 13 ? 5 : N < 17 ? 6 : N < 19 ? 7 : N < 23 ? 8 : 9;
	if (N < pc_1*pc_1) return this->phi_small (N, c) + c - 1;

	// Calculate K2 = pi (N^(1/2)), K3 = pi (N^(1/3)). Make sure the result is not too small
	// and not much too large.
	uint64 N2 = (uint64) (::sqrt ((double) N) + 0.5);
	uint64 N3 = (uint64) (::pow ((double) N, 1.0 / 3.0) + 0.5);
	uint32 K2 = this->pi_algorithm2 (N2);
	uint32 K3 = this->pi_algorithm2 (N3);

	// Calculate M arbitrary as N^(1/3), pi_M = pi (M), but make sure that 2 <= M <= N^(1/2).
	// Also make sure that M doesn't exceed any of our limits; M must be small enough so that we
	// can look up factors in the factor table, and that we can look up primes <= M in the prime
	// number table.
	uint32 M = (uint32) ::pow ((double) N, 1.0 / 3.0);
	if (M >= N2) M = N2 - 1;
	if (M > fPrimeList.MaxPrime ()) M = fPrimeList.MaxPrime ();
	if (M < 1) M = 1; if (M > fFactorTable.MaxNumber ()) M = M > fFactorTable.MaxNumber ();
	uint32 pi_M = this->pi_algorithm2 (M);

	// Let KM = smallest number k >= c such that p(k+1) * p(k+2) > M. Make sure that KM <= pi_M.
	uint32 KM = c;
	while (this->NthPrime (KM + 1) * this->NthPrime (KM + 2) <= M) ++KM;
	if (KM > pi_M) KM = pi_M;


	// To calculate pi (N): Start with K2 - 1.
	uint64 sum1 = K2 - 1;
	uint64 sum2 = 0;
	uint64 phi_value;
	uint32 k, j, pk, entry;
	uint32 end = fFactorTable.NumberToIndex (M + 1);


	// Add phi (N, x, c) for 1 <= x <= M, where x is square-free with no prime factor <= p(c).
	// If x has a square factor then the factor table has a value of 0. If x has a prime factor p,
	// p <= pc, then the factor table contains p-1 or p. We are looking for entries greater than pc.
	// We have to watch out for the case c = 1, pc = 2: Values with a smallest prime factor of 3
	// and an even number of prime factors are identified by an entry of 2.
	for (j = fFactorTable.NumberToIndex (1); j < end; ++j) {
		entry = fFactorTable.GetEntry (j);
		if (entry <= (pc == 2 ? 0 : pc)) continue;
		phi_value = this->phi_small (N / fFactorTable.IndexToNumber (j), c);
		if (entry & 0x01) sum2 += phi_value; else sum1 += phi_value;
	}

	// If c < pi_M then add phi (N, x*p(c+1), c) for square-free integers x with
	// M/p(c+1) + 1 <= x <= M with no prime factor <= p(c+1).
	if (c < pi_M) {
		for (j = fFactorTable.NumberToIndex (M / pc_1 + 1); j < end; ++j) {
			entry = fFactorTable.GetEntry (j);
			if (entry <= pc_1) continue;
			phi_value = this->phi_small (N / fFactorTable.IndexToNumber (j) / pc_1, c);
			if (entry & 0x01) sum1 += phi_value; else sum2 += phi_value;
		}
	}

	// As long as k < pi_M and p (k+1)*p(k+2) <= M add phi (N, x*p(k+1), k) for square-free
	// integers x with M / p(k+1) + 1 <= x <= M with no prime factor <= p(k+1), then let k = k+1.
	// This is very similar to the previous loop, but here we should use a sieve.
	k = c; if (k < pi_M) ++k;
	for (; k < KM; ++k) {
		pk = this->NthPrime (k+1);
		for (j = fFactorTable.NumberToIndex (M / pk + 1); j < end; ++j) {
			entry = fFactorTable.GetEntry (j);
			if (entry <= pk) continue;
			phi_value = this->phi (N / fFactorTable.IndexToNumber (j) / pk, k);
			if (entry & 0x01) sum1 += phi_value; else sum2 += phi_value;
		}
	}

	// As long as k < pi_M add phi (N, x*p(k+1), k) for all primes p (k+2) <= x <= M, then
	// let k = k+1. Here we can avoid looking through the factor table, as we know that no
	// composite number can have very large factors.
	for (; k < pi_M; ++k) {
		pk = this->NthPrime (k+1);
		for (j = k + 2; j <= pi_M; ++j) {
			phi_value = this->phi (N / this->NthPrime (j) / pk, k);
			sum1 += phi_value;
		}
	}

	// Add phi (N, p(k+1), k), pi (M) <= k < K3
	for (; k < K3; ++k) {
		pk = this->NthPrime (k+1);
		sum2 += this->phi (N / pk, k);
	}

	// Add phi (N, p(k+1), K3), K3 <= k < K2). Note that we need a sieve to find these large
	// primes; our primes table is only supposed to cover the range up to N^(1/3).
	for (; k < K2; ++k) {
		pk = this->NthPrime (k+1);
		sum2 += this->phi (N / pk, K3);
		sum1 += k - K3;
	}

	return sum1 - sum2;
}

/*
 * Two simple functions to be able to check other calculations.
 */
uint64 TMLPrimeCount::slow_pi (uint64 N) {
	if (N < 11) return N < 2 ? 0 : N < 3 ? 1 : N < 5 ? 2 : N < 7 ? 3 : 4;

	uint32 root_2 = (uint32) ::sqrt ((double) N);
	if ((uint64) root_2 * root_2 > N) --root_2;
	if ((uint64) (root_2 + 1) * (root_2 + 1) <= N) ++root_2;
	uint32 k = this->slow_pi (root_2);
	return this->phi (N, k) + k - 1;
}

uint64 TMLPrimeCount::pi_large (uint64 N) {

	// Define some constants: c is chosen so that we can calculate phi (x, c) directly. pc is the
	// (c)th prime number. pc_1 is the (c+1)st prime number.
	const uint32 c		= CHOICE_FOR_C;
	const uint32 pc   	= PRIME_C;
	const uint32 pc_1	= PRIME_C_PLUS1;


	// Trivial cases where N < p (c+1)^2 are not passed to this function, they are already handled
	// by the caller. This guarantees at least N >= 9.


	// Calculate N2 = floor (N^(1/2), N3 = floor (N^(1/3)), K2 = pi (N2) and K3 = pi (N3). Make sure
	// that the result is not too small and not much too large. Neither N2 nor N3 may be chosen too
	// small, but N2 may be as large as floor (sqrt (N+1) + 1), N3 may be larger without problems.
	double N_double = (double) N;
	uint64 N2 = (uint64) (::sqrt (N_double) + 0.5);
	uint64 N3 = (uint64) (::pow (N_double, 1.0 / 3.0) + 0.5);
	uint32 K2 = this->pi_algorithm2 (N2);
	uint32 K3 = this->pi_algorithm2 (N3);


	// Calculate M arbitrary as N^(1/3), pi_M = pi (M), but make sure that 1 <= M <= N^(1/2).
	// Also make sure that M doesn't exceed any of our limits; M must be small enough so that we
	// can look up factors in the factor table, and that we can look up primes <= M in the prime
	// number table.
	double m_factor = 1.0;
	if (N_double > M_BREAK_EVEN) m_factor = ::log (N_double) / ::log (M_BREAK_EVEN);
	uint32 M = (uint32) (::pow (N_double, 1.0 / 3.0) * m_factor);
	if (M >= N2) M = N2 - 1;
	if (M > fPrimeList.MaxPrime ()) M = fPrimeList.MaxPrime ();
	if (M < N3) M = N3; if (M > fFactorTable.MaxNumber ()) M = fFactorTable.MaxNumber ();

	// Find the smallest possible divisor: This is the smallest number > M that is square-free and
	// is not divisible by any prime number <= p (c). There is such a number in the table because
	// we made sure when the table was created.
	uint32 start = fFactorTable.NumberToIndex (M + 1), end, j;
	uint32 smallest_divisor;

	for (j = start; ; ++j) {
		if (fFactorTable.GetEntry (j) > (pc == 2 ? 0 : pc)) {
			smallest_divisor = fFactorTable.IndexToNumber (j);
			break;
		}
	}

	// Find the largest possible divisor: One part of the algorithm might divide by numbers close
	// to M^2, another might divide by numbers close to N2. The smallest value that could ever be
	// looked up in a sieve is N / largest_divisor.
	uint64 largest_divisor = (uint64) M * (uint64) M;
	if (N2 > largest_divisor) largest_divisor = N2;

	// We now set M equal to the smallest divisor minus 1; making M as large as possible can only
	// make things faster. Also calculate pi_M = pi (M). Then calculate the end of the sieve; this
	// is equal to (N / smallest_divisor + 1).
	M = smallest_divisor - 1;
	uint32 pi_M = this->pi_algorithm2 (M);
	uint64 phiSieveEnd = (N / smallest_divisor + 1);

	// Let KM = smallest number k >= c such that p(k+1) * p(k+2) > M. Make sure that KM <= pi_M.
	uint32 KM = c;
	while (this->NthPrime (KM + 1) * this->NthPrime (KM + 2) <= M) ++KM;
	if (KM > pi_M) KM = pi_M;

	// Make sure that K3 >= KM.
	if (K3 < KM) K3 = KM;

	// To calculate pi (N): Start with K2 - 1.
	uint64 sum1 = (K2 - 1) + (uint64) (pi_M - K3 - 1) * (uint64) (pi_M - K3) / 2;
	uint64 sum2 = 0;
	uint64 phi_value;
	uint32 k, pk, entry;
	end = fFactorTable.NumberToIndex (M + 1);

	// Arrange a sieve to find primes in reverse order, starting with prime number K2 which is
	// the largest prime <= N2.
	TPrimeSieve sieve (&this->fPrimeList);
	uint32 currentPrime = sieve.PrimeBefore (N2 + 1);
	uint32 currentPrimeIndex = K2 - 1;


	// Add phi (N, x, c) for 1 <= x <= M, where x is square-free with no prime factor <= p(c).
	// If x has a square factor then the factor table has a value of 0. If x has a prime factor p,
	// p <= pc, then the factor table contains p-1 or p. We are looking for entries greater than pc.
	// We have to watch out for the case c = 1, pc = 2: Values with a smallest prime factor of 3
	// and an even number of prime factors are identified by an entry of 2.
	start = fFactorTable.NumberToIndex (1);
	for (j = start; j < end; ++j) {
		entry = fFactorTable.GetEntry (j);
		if (entry <= (pc == 2 ? 0 : pc)) continue;
		phi_value = this->phi_small (N / fFactorTable.IndexToNumber (j), c);
		if (entry & 0x01) sum2 += phi_value; else sum1 += phi_value;
	}

	// If c < pi_M then add phi (N, x*p(c+1), c) for square-free integers x with
	// M/p(c+1) + 1 <= x <= M with no prime factor <= p(c+1).
	if (c < pi_M) {
		start = fFactorTable.NumberToIndex (M / pc_1 + 1);
		for (j = start; j < end; ++j) {
			entry = fFactorTable.GetEntry (j);
			if (entry <= pc_1) continue;
			phi_value = this->phi_small (N / fFactorTable.IndexToNumber (j) / pc_1, c);
			if (entry & 0x01) sum1 += phi_value; else sum2 += phi_value;
		}
	}

	// Loop over the partial sieves.
	uint64 sieveStart;
	uint64 sieveEnd;
	uint64 startDivisor;
	uint64 endDivisor;
	uint64 divisor;

	// Reset the sieve totals.
	fSievedPrimes = K3;
	for (k = 0; k <= K3; ++k)
		fSieveTotals [k] = 0;

	for (k = 0; k < KM; ++k)
		fPrimeIndex [k] = end;

	// GetPrimeIndex () returns the index of the largest prime that we try as a divisor. Usually
	// we would try to divide by all primes up to pi_M, but we know that if a divisor is large
	// enough then phi (N / (p * p(k+1)), k) will be equal to 1.
	unsigned long lastPrime = pi_M;
	for (; k < K3; ++k) {
		uint64 p_squared = (uint64) this->NthPrime (k + 1);
		p_squared *= p_squared;
		while (this->NthPrime (lastPrime) * p_squared > N)
			lastPrime -= 1;

		if (lastPrime < k + 1) lastPrime = k + 1;
		fPrimeIndex [k] = lastPrime;
		sum1 += pi_M - lastPrime;
	}

	unsigned long pi_Lookup = K3;

	for (sieveStart = 0, endDivisor = N; sieveStart != phiSieveEnd;
												sieveStart = sieveEnd, endDivisor = startDivisor) {
		// Determine where this partial sieve ends; it goes from sieveStart to sieveEnd. From then
		// on we handle only the divisors where sieveStart <= N / divisor < sieveEnd. This will
		// be divisors such that startDivisor < divisor <= endDivisor;
		sieveEnd = sieveStart + 16 * eSieveBytes;
		if (sieveEnd > phiSieveEnd) sieveEnd = phiSieveEnd;
		startDivisor = N / sieveEnd;

		// As long as k < pi_M and p (k+1)*p(k+2) <= M add phi (N, x*p(k+1), k) for square-free
		// integers x with M / p(k+1) + 1 <= x <= M with no prime factor <= p(k+1), then let
		// k = k+1. This is very similar to the previous loop, but here we should use a sieve.
		k = c < pi_M ? c + 1 : pi_M;
		this->StartSieve (sieveStart, sieveEnd - sieveStart, k-1);
		for (; k < KM; ++k) {
			this->RemovePrime (k);
			pk = this->NthPrime (k+1);
			start = startDivisor >= pk * (uint64) 0xfffffffe ? 0xffffffff :
										fFactorTable.NumberToIndex (startDivisor / pk + 1);
			for (j = fPrimeIndex [k] - 1; j >= start; --j) {
				entry = fFactorTable.GetEntry (j);
				if (entry <= pk) continue;
				divisor = fFactorTable.IndexToNumber (j) * (uint64) pk;
				phi_value = this->PhiUsingSieve (N / divisor);
				if (entry & 0x01) sum1 += phi_value; else sum2 += phi_value;
			}
			if (start < fPrimeIndex [k]) fPrimeIndex [k] = start;
		}


		for (; k < pi_Lookup; ++k) {
			this->RemovePrime (k);
			sum1 += this->SumPhiValues (N, startDivisor, k);
		}

#if 0
		// As long as k < pi_M add phi (N, x*p(k+1), k) for all primes p (k+2) <= x <= M, then
		// let k = k+1. Here we can avoid looking through the factor table, as we know that no
		// composite number can have very large factors.
#if DIVIDE_BY_HAND
		for (; k < pi_Lookup; ++k) {
			this->RemovePrime (k);
			j = fPrimeIndex [k];
			if (j >= k + 2) {
				pk = this->NthPrime (k+1);
				if (this->NthPrime (j) * (uint64) pk > startDivisor) {
					uint64 quot = ::divide (N, pk, fPrimeShift [k+1], fPrimeInverse [k+1]);
					for (; j >= k + 2; --j) {
						uint32 prime = this->NthPrime (j);
						uint64 quot2 = ::divide (quot, prime, fPrimeShift [j], fPrimeInverse [j]);
						if (quot2 >= sieveEnd) break;
						phi_value = this->PhiUsingSieve (quot2);
						sum1 += phi_value;
					}
					fPrimeIndex [k] = j;
				}
			}
		}
#else
		for (; k < pi_Lookup; ++k) {
			this->RemovePrime (k);
			pk = this->NthPrime (k+1);
			for (j = fPrimeIndex [k]; j >= k + 2; --j) {
				divisor = this->NthPrime (j) * (uint64) pk;
				if (divisor <= startDivisor) break;
				phi_value = this->PhiUsingSieve (N / divisor);
				sum1 += phi_value;
			}
			fPrimeIndex [k] = j;
		}
#endif
#endif

		// If GetPrimeIndex (k) < k + 2 then the previous loop will never iterate again, so
		// make pi_Lookup smaller to prevent unnecessary work. Removing primes from the sieve
		// will be done anyway in other code.
		while (pi_Lookup > KM && fPrimeIndex [pi_Lookup - 1] < (pi_Lookup - 1) + 2)
			--pi_Lookup;

		// Add phi (N, p(k+1), k) for max (c, pi_M) <= k < K2. This is equal to
		// (k - pi_M) - phi (N / p(k+1), pi_M). We need a sieve to find these large primes; our primes
		// table is only supposed to cover the range up to N^(1/3).
		// Within the sieve, we want to handle all prime factors in descending order to make the
		// overall algorithm easier; this guarantees that values are looked up in ascending order.
		this->RemovePrimes (k, K3);

		while (currentPrime > startDivisor && currentPrimeIndex >= pi_M && currentPrimeIndex >= c) {
			sum1 += currentPrimeIndex - K3;
			sum2 += this->PhiUsingSieve2 (N / currentPrime);
			--currentPrimeIndex;
			currentPrime = sieve.PrimeBefore (currentPrime);
		}
	}

	return sum1 - sum2;
}



void TMLPrimeCount::StartSieve (uint64 sieveStart, uint32 size, uint32 nPrimes) {

	// Store the start and the size of the sieve.
	fSieveStart = sieveStart;
	fSieveSize = size;

	uint32 i, mult, j, p;

	// Set the three fields fFirstPrimeInSieve, fLastPrimeInSieve, fLastPrimeToRemove. Initially,
	//
	if (sieveStart == 0) {
		fLastPrimeInSieve = 0;
		fLastPrimeToRemove = 0;
	}
	fFirstPrimeInSieve = fLastPrimeInSieve + 1;
	while (fLastPrimeInSieve < fSievedPrimes) {
		p = this->NthPrime (fLastPrimeInSieve + 1);
		if (p >= sieveStart + size) break;
		++fLastPrimeInSieve;
	}
	while (fLastPrimeToRemove < fSievedPrimes) {
		p = this->NthPrime (fLastPrimeToRemove + 1);
		uint64 p2 = (uint64) p * (uint64) p;
		if (p2 >= sieveStart + size) break;
		fFirstBitIndex [++fLastPrimeToRemove] = ((uint32) p2 - (uint32) sieveStart - 1) / 2;
		fMultiplier [fLastPrimeToRemove] = (p % 30) * 8 / 30;
	}

	// Set the variables fWordsCounted and fBitsInFirstWords, as nothing has been counted yet.
	fWordsCounted = 0;
	fBitsInFirstWords = 0;
	f16WordsCounted = 0;
	fBitsInFirst16Words = 0;

	// Set the first three words to 0xffffffff, that is all even numbers have been removed because
	// they were never actually stored. Then remove all multiples of three from the first three
	// words if requested.
	fSieve [0] = fSieve [1] = fSieve [2] = 0xffffffff;
	if (nPrimes >= 2) {
		for (i = 3/2; i < 3 * 32; i += 3) {
			fSieve [i / 32] &= ~(1ul << (i % 32));
		}
	}

	// Copy into the first fifteen words, then remove multiples of five from the first 15 words.
	for (i = 3; i < 15; ++i)
		fSieve [i] = fSieve [i-3];

	if (nPrimes >= 3) {
		for (i = 5/2; i < 15 * 32; i += 5) {
			fSieve [i / 32] &= ~(1ul << (i % 32));
		}
	}

	// Copy into the first 3*5*7 words, then remove multiples of seven from the first 105 words.
	for (i = 15; i < 105; ++i)
		fSieve [i] = fSieve [i-15];

	if (nPrimes >= 4) {
		for (i = 7/2; i < 105 * 32; i += 7) {
			fSieve [i / 32] &= ~(1ul << (i % 32));
		}
	}

	// Copy into the first 3*5*7*11 words, then remove multiples of 11 from the first 1155 words.
	for (i = 105; i < 1155; ++i)
		fSieve [i] = fSieve [i-105];

	if (nPrimes >= 5) {
		for (i = 11/2; i < 1155 * 32; i += 11) {
			fSieve [i / 32] &= ~(1ul << (i % 32));
		}
	}

	// Translate size into odd numbers, then into words, rounded up. Duplicate the first 1155 words
	// as far as needed. Remove unneeded bits in the last word. Then make sure the number of words
	// is a multiple of 16 by storing some more zeroes.
	size = (size + 1) / 2;
	uint32 words = (size + 31) / 32;
	for (i = 1155; i < words; ++i)
		fSieve [i] = fSieve [i-1155];

	if (size % 32 != 0)
		fSieve [words - 1] &= ~ (0xfffffffful << (size % 32));

	while (words % 16 != 0)
		fSieve [words++] = 0;


	// Remove all the other primes as requested. The bit offset for the first bit is a bit tricky,
	// but not too tricky.
	for (j = 6, p = 13; j <= nPrimes; p = this->NthPrime (++j)) {
		if (j >= fFirstPrimeInSieve && j <= fLastPrimeInSieve) {
			i = (p - (uint32) sieveStart - 1) / 2;
			fSieve [i / 32] &= ~(1ul << (i % 32));
		}
		if (j <= fLastPrimeToRemove) {
			if ((i = fFirstBitIndex [j]) < size) {
				switch (mult = fMultiplier [j]) {
				startAgain: ;
					case 0: fSieve [i / 32] &= ~(1ul << (i % 32));
							i += 3*p; mult = 1; if (i >= size) break;
					case 1: fSieve [i / 32] &= ~(1ul << (i % 32));
							i += 2*p; mult = 2; if (i >= size) break;
					case 2: fSieve [i / 32] &= ~(1ul << (i % 32));
							i += 1*p; mult = 3; if (i >= size) break;
					case 3: fSieve [i / 32] &= ~(1ul << (i % 32));
							i += 2*p; mult = 4; if (i >= size) break;
					case 4: fSieve [i / 32] &= ~(1ul << (i % 32));
							i += 1*p; mult = 5; if (i >= size) break;
					case 5: fSieve [i / 32] &= ~(1ul << (i % 32));
							i += 2*p; mult = 6; if (i >= size) break;
					case 6: fSieve [i / 32] &= ~(1ul << (i % 32));
							i += 3*p; mult = 7; if (i >= size) break;
					case 7: fSieve [i / 32] &= ~(1ul << (i % 32));
							i += 1*p; mult = 0; if (i >= size) break;
					goto startAgain;
				}

				fMultiplier [j] = mult;
			}
			fFirstBitIndex [j] = i - size;
		}
	}

	// Fill counters for groups of 16 words and count the bits in complete groups of two words.
	uint32 bitsTotal = 0;
	for (i = 0; i < words / 16; ++i) {
		uint32 bitCount =
			this->BitCount (fSieve [16*i    ]) + this->BitCount (fSieve [16*i + 1])
		  + this->BitCount (fSieve [16*i + 2]) + this->BitCount (fSieve [16*i + 3])
		  + this->BitCount (fSieve [16*i + 4]) + this->BitCount (fSieve [16*i + 5])
		  + this->BitCount (fSieve [16*i + 6]) + this->BitCount (fSieve [16*i + 7])
		  + this->BitCount (fSieve [16*i + 8]) + this->BitCount (fSieve [16*i + 9])
		  + this->BitCount (fSieve [16*i +10]) + this->BitCount (fSieve [16*i +11])
		  + this->BitCount (fSieve [16*i +12]) + this->BitCount (fSieve [16*i +13])
		  + this->BitCount (fSieve [16*i +14]) + this->BitCount (fSieve [16*i +15]);
		fCounter512 [i] = bitCount;
		bitsTotal += bitCount;
	}

	fBitsInPartialSieve = bitsTotal;
	fThisPhi = fSieveTotals [nPrimes];
	fSieveTotals [nPrimes] += bitsTotal;
}

void TMLPrimeCount::RemovePrime (uint32 primeIndex) {

	uint32 *sieve = fSieve;

	if (primeIndex >= fFirstPrimeInSieve && primeIndex <= fLastPrimeInSieve) {
		uint32 i = (this->NthPrime (primeIndex) - (uint32) fSieveStart - 1) / 2;
		uint32 index = i / 32;
		uint32 mask = 1ul << (i % 32);
		if (sieve [index] & mask) {
			sieve [index] &= ~mask;
			fCounter512 [index/16] -= 1;
			fBitsInPartialSieve -= 1;
		}
	}

	if (primeIndex <= fLastPrimeToRemove) {
		uint32 size = (fSieveSize + 1) / 2;
		uint32 i = fFirstBitIndex [primeIndex];
		if (i < size) {
			uint32 index, mask, prev, mult;
			uint32 bitsTotal = fBitsInPartialSieve;
			uint32 p = this->NthPrime (primeIndex);

			switch (mult = fMultiplier [primeIndex]) {
			startAgain: ;
				case 0: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							fCounter512 [index/16]--; bitsTotal--;
						}
						i += 3*p; mult = 1; if (i >= size) break;
				case 1: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							fCounter512 [index/16]--; bitsTotal--;
						}
						i += 2*p; mult = 2; if (i >= size) break;
				case 2: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							fCounter512 [index/16]--; bitsTotal--;
						}
						i += 1*p; mult = 3; if (i >= size) break;
				case 3: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							fCounter512 [index/16]--; bitsTotal--;
						}
						i += 2*p; mult = 4; if (i >= size) break;
				case 4: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							fCounter512 [index/16]--; bitsTotal--;
						}
						i += 1*p; mult = 5; if (i >= size) break;
				case 5: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							fCounter512 [index/16]--; bitsTotal--;
						}
						i += 2*p; mult = 6; if (i >= size) break;
				case 6: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							fCounter512 [index/16]--; bitsTotal--;
						}
						i += 3*p; mult = 7; if (i >= size) break;
				case 7: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							fCounter512 [index/16]--; bitsTotal--;
						}
						i += 1*p; mult = 0; if (i >= size) break;
				goto startAgain;
			}

			fMultiplier [primeIndex] = mult;
			fBitsInPartialSieve = bitsTotal;
		}
		fFirstBitIndex [primeIndex] = i - size;
	}

	fThisPhi = fSieveTotals [primeIndex];
	fSieveTotals [primeIndex] = fThisPhi + fBitsInPartialSieve;

	fWordsCounted = 0;
	fBitsInFirstWords = 0;
	f16WordsCounted = 0;
	fBitsInFirst16Words = 0;
}

void TMLPrimeCount::RemovePrimes (uint32 primeIndex, uint32 lastPrimeIndex) {

	while (primeIndex <= lastPrimeIndex &&
		   lastPrimeIndex >= fFirstPrimeInSieve && primeIndex <= fLastPrimeInSieve)
		this->RemovePrime (primeIndex++);

	if (primeIndex > lastPrimeIndex)
		return;

	uint32 *sieve = fSieve;
	uint32 size = (fSieveSize + 1) / 2;
	uint32 bitsTotal = fBitsInPartialSieve;

	uint32 lastPrimeToRemove = fLastPrimeToRemove;
	if (lastPrimeToRemove > lastPrimeIndex) lastPrimeToRemove = lastPrimeIndex;

	for (; primeIndex <= lastPrimeToRemove; ++primeIndex) {

		uint32 i = fFirstBitIndex [primeIndex];
		if (i < size) {
			uint32 index, mask, prev, mult;
			uint32 p = this->NthPrime (primeIndex);

			switch (mult = fMultiplier [primeIndex]) {
			startAgain: ;
				case 0: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							bitsTotal--;
						}
						i += 3*p; mult = 1; if (i >= size) break;
				case 1: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							bitsTotal--;
						}
						i += 2*p; mult = 2; if (i >= size) break;
				case 2: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							bitsTotal--;
						}
						i += 1*p; mult = 3; if (i >= size) break;
				case 3: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							bitsTotal--;
						}
						i += 2*p; mult = 4; if (i >= size) break;
				case 4: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							bitsTotal--;
						}
						i += 1*p; mult = 5; if (i >= size) break;
				case 5: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							bitsTotal--;
						}
						i += 2*p; mult = 6; if (i >= size) break;
				case 6: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							bitsTotal--;
						}
						i += 3*p; mult = 7; if (i >= size) break;
				case 7: index = i / 32; mask = 1ul << (i % 32);
						if ((prev = sieve [index]) & mask) {
							sieve [index] = prev & ~mask;
							bitsTotal--;
						}
						i += 1*p; mult = 0; if (i >= size) break;
				goto startAgain;
			}

			fMultiplier [primeIndex] = mult;
		}
		fFirstBitIndex [primeIndex] = i - size;
	}
	fThisPhi = fSieveTotals [lastPrimeIndex];
	fSieveTotals [lastPrimeIndex] = fThisPhi + bitsTotal;

	fWordsCounted = 0;
	fBitsInFirstWords = 0;
}

uint64 TMLPrimeCount::PhiUsingSieve (uint64 x) {

	// Adjust x by the sieve start, and translate it into a bit count. We need to return how many
	// of the first x2 bits are set. Translate the bit count into a number of 32 bit words.
	uint32 x2 = (uint32) x - (uint32) fSieveStart;
	x2 = (x2 + 1) / 2;
	uint32 words = x2 / 32;

	// How many words did we check the last time, and what was the result. Then calculate how many
	// 32 bit words have been added. Special case delta <= 1 is worth handling separately because
	// it is very common.
	uint32 i = fWordsCounted;
	uint32 result = fBitsInFirstWords;
	uint32 delta = words - i;
	uint32 *sieve = fSieve;

	if (delta <= 1) {
		if (delta == 1) {
			result += this->BitCount (sieve [i++]);
			fWordsCounted = i;
			fBitsInFirstWords = result;
		}

		result += this->BitCount (sieve [words] & ~(0xfffffffful << (x2 % 32)));
		return fThisPhi + result;
	}

	// If eight or more complete 32 bit words are added then add groups of 16 words. Add until we
	// are close to the correct number of groups or until we are slightly too large.
	if (delta >= 8) {
		i = f16WordsCounted;
		result = fBitsInFirst16Words;

		while (i < words - 7) {
			result += fCounter512 [i / 16];
			i += 16;
		}
		f16WordsCounted = i;
		fBitsInFirst16Words = result;

		// i can be too large by up to eight words. Make sure that i is not too large.
		if (i > words) {
			result -= this->BitCount (sieve [--i]);
			if (i >= words + 4) {
				result -= this->BitCount (sieve [i-1]) + this->BitCount (sieve [i-2])
						+ this->BitCount (sieve [i-3]) + this->BitCount (sieve [i-4]);
				i -= 4;
			}
			if (i >= words + 2) {
				result -= this->BitCount (sieve [i-1]) + this->BitCount (sieve [i-2]);
				i -= 2;
			}
			if (i > words)
				result -= this->BitCount (sieve [--i]);
		}
		delta = words - i;
	}


	// Now we have 0 <= delta <= 7. Add four, two and one complete words if needed.
	if (delta & 0x04) {
		result += this->BitCount (sieve [i  ]) + this->BitCount (sieve [i+1])
				+ this->BitCount (sieve [i+2]) + this->BitCount (sieve [i+3]);
		i += 4;
	}
	if (delta & 0x02) {
		result += this->BitCount (sieve [i  ]) + this->BitCount (sieve [i+1]);
		i += 2;
	}
	if (delta & 0x01) {
		result += this->BitCount (sieve [i++]);
	}

	// Store the new word count. Add the remaining bits and return.
	fWordsCounted = i;
	fBitsInFirstWords = result;

	result += this->BitCount (sieve [words] & ~(0xfffffffful << (x2 % 32)));
	return fThisPhi + result;
}

uint64 TMLPrimeCount::PhiUsingSieve2 (uint64 x) {

	// Adjust x by the sieve start, and translate it into a bit count. We need to return how many
	// of the first x2 bits are set. Translate the bit count into a number of 32 bit words.
	uint32 x2 = (uint32) x - (uint32) fSieveStart;
	x2 = (x2 + 1) / 2;
	uint32 words = x2 / 32;

	// How many words did we check the last time, and what was the result. Then add the remaining
	// words; store the result for the next call. Add remaining bits and return.
	uint32 i = fWordsCounted;
	uint32 result = fBitsInFirstWords;
	uint32 *sieve = fSieve;

	while (i < words) result += this->BitCount (sieve [i++]);
	fWordsCounted = i;
	fBitsInFirstWords = result;

	result += this->BitCount (sieve [words] & ~(0xfffffffful << (x2 % 32)));
	return fThisPhi + result;
}

uint64 TMLPrimeCount::SumPhiValues (uint64 N, uint64 startDivisor, uint32 k)
{
	// As long as k < pi_M add phi (N, x*p(k+1), k) for all primes p (k+2) <= x <= M, then
	// let k = k+1. Here we can avoid looking through the factor table, as we know that no
	// composite number can have very large factors.

	uint64 sum = 0;
	uint32 j = fPrimeIndex [k];
	if (j < k + 2) return 0;

	uint32 pk = this->NthPrime (k+1);

#if DIVIDE_BY_HAND
	if (this->NthPrime (j) * (uint64) pk <= startDivisor)
		return 0;

	uint64 sieveEnd = fSieveStart + fSieveSize;
	uint64 quot = ::divide (N, pk, fPrimeShift [k+1], fPrimeInverse [k+1]);
#endif

	uint32 i = fWordsCounted;
	uint32 result = fBitsInFirstWords;
	uint32 *sieve = fSieve;
	uint32 sieveWord = fSieve [i];
	uint32 jStart = j;


	for (; j >= k + 2; --j) {
		uint32 prime = this->NthPrime (j);
		uint64 quot2;

#if DIVIDE_BY_HAND
		quot2 = ::divide (quot, prime, fPrimeShift [j], fPrimeInverse [j]);
		if (quot2 >= sieveEnd) break;
#else
		uint64 divisor = prime * (uint64) pk;
		if (divisor <= startDivisor) break;
		quot2 = N / divisor;
#endif

		// Adjust x by the sieve start, and translate it into a bit count. We need to return how many
		// of the first x2 bits are set. Translate the bit count into a number of 32 bit words.
		uint32 x2 = ((uint32) quot2 - (uint32) fSieveStart + 1) / 2;
		uint32 words = x2 / 32;


		// How many words did we check the last time, and what was the result. Then calculate how many
		// 32 bit words have been added. Special case delta <= 1 is worth handling separately because
		// it is very common.
		uint32 delta = words - i;
		if (delta == 0) goto addphi;
		if (delta == 1) {
			result += this->BitCount (sieveWord);
			sieveWord = sieve [++i];
			goto addphi;
		}


		// If eight or more complete 32 bit words are added then add groups of 16 words. Add until we
		// are close to the correct number of groups or until we are slightly too large.
		if (delta >= 8) {
			i = f16WordsCounted;
			result = fBitsInFirst16Words;

			while (i < words - 7) {
				result += fCounter512 [i / 16];
				i += 16;
			}
			f16WordsCounted = i;
			fBitsInFirst16Words = result;

			// i can be too large by up to eight words. Make sure that i is not too large.
			if (i > words) {
				result -= this->BitCount (sieve [--i]);
				if (i >= words + 4) {
					result -= this->BitCount (sieve [i-1]) + this->BitCount (sieve [i-2])
							+ this->BitCount (sieve [i-3]) + this->BitCount (sieve [i-4]);
					i -= 4;
				}
				if (i >= words + 2) {
					result -= this->BitCount (sieve [i-1]) + this->BitCount (sieve [i-2]);
					i -= 2;
				}
				if (i > words)
					result -= this->BitCount (sieve [--i]);
			}
			delta = words - i;
			sieveWord = sieve [i];
		}


		// Now we have 0 <= delta <= 7. Add four, two and one complete words if needed.
		if (delta & 0x04) {
			result += this->BitCount (sieveWord) + this->BitCount (sieve [i+1])
					+ this->BitCount (sieve [i+2]) + this->BitCount (sieve [i+3]);
			sieveWord = sieve [i += 4];
		}
		if (delta & 0x02) {
			result += this->BitCount (sieveWord) + this->BitCount (sieve [i+1]);
			sieveWord = sieve [i += 2];
		}
		if (delta & 0x01) {
			result += this->BitCount (sieveWord);
			sieveWord = sieve [i += 1];
		}

		// Store the new word count. Add the remaining bits and return.
addphi:
		sum += result + this->BitCount (sieveWord & ~(0xfffffffful << (x2 % 32)));
	}

	fWordsCounted = i;
	fBitsInFirstWords = result;

	fPrimeIndex [k] = j;
	return sum + (jStart - j) * fThisPhi;
}

/*
 * Implemention of the factory functions. Several are not implemented yet and will always return
 * NULL.
 */
TPrimeCount* TPrimeCount::MakeLegendreCounter (uint64 maxN) {

	// We determine carefully what is the largest argument N that could possibly be handled. If
	// maxN is greater than the maximum then return NULL. If maxN = 0 then set maxN to the
	// maximum possible value.

	uint64 maxPossible = 0xf000000000000000ull;
	if (maxN > maxPossible) return NULL;
	if (maxN == 0) maxN = maxPossible;

	// Create a new TLegendrePrimeCount. We want a list of primes containing all integers up to
	// M ^ (1/3), and at least up to 100.
	TLegendrePrimeCount* primeCount = new TLegendrePrimeCount;
	double M_double = ::pow ((double) maxN, 1.0 / 3.0) + 2;
	uint32 limit = (uint32) M_double;
	if (limit < 100) limit = 100;

	// Allocate required storage data. If this fails then delete the object and return NULL.
	primeCount->fPrimeList.HandlePrimesUpTo (limit);

	if (primeCount->fPrimeList.MaxPrime () == 0) {
		delete primeCount;
		return NULL;
	} else {
		return primeCount;
	}
}

TPrimeCount* TPrimeCount::MakeMeisselCounter (uint64 maxN) {
	maxN = 0;
	return NULL;
}

TPrimeCount* TPrimeCount::MakeLehmerCounter (uint64 maxN) {
	maxN = 0;
	return NULL;
}

TPrimeCount* TPrimeCount::MakeMeisselLehmerCounter (uint64 maxN) {

	// We determine carefully what is the largest argument N that could possibly be handled. If
	// maxN is greater than the maximum then return NULL. If maxN = 0 then set maxN to the
	// maximum possible value.

	uint64 maxPossible = 18000000000000000000ull;
	if (maxN > maxPossible) return NULL;
	if (maxN == 0) maxN = maxPossible;

	// Create a new TMLPrimeCount. We want a list of primes containing all integers up to
	// M ^ (1/3) and a factor table for all those integers.
	TMLPrimeCount* primeCount = new TMLPrimeCount (maxN);
	if (primeCount != NULL && primeCount->MaxArgument () == 0) {
		delete primeCount;
		primeCount = NULL;
	}

	return primeCount;
}









/*-------1---------2---------3---------4---------5---------6---------7---------8---------9---------0
 *
 * main.cp - Testbed for class TLMPrimeCount.
 *
 * Copyright (C) 2003 by Christian Bau
 *
 --------1---------2---------3---------4---------5---------6---------7---------8---------9--------*/

#include <string>
#include <ctime>
#include <iostream>
#include <stdio.h>

using namespace std;

static double Seconds (void) {
	return (double) ::clock () / (double) CLOCKS_PER_SEC;
}



static void TestOneArgument (TPrimeCount* pc, unsigned long long arg, unsigned long long check) {
	double start = Seconds ();
	unsigned long long compare = pc->Pi (arg);
	double end = Seconds ();

	if (check == compare)
		::cout << end - start << " seconds: Pi (" << arg << ") = " << compare << ::endl;
	else
		::cout << end - start << " seconds: Pi (" << arg << ") = " << compare <<
									", should be " << check <<
									", difference = " << (long long) compare - check
									<< "." << ::endl;
}

static void TestPrimeCount (TPrimeCount* pc) {
/* 1e3 */	TestOneArgument (pc, 1000, 168);
/* 1e4 */	TestOneArgument (pc, 10000, 1229);
/* 1e5 */	TestOneArgument (pc, 100000, 9592);
/* 1e6 */	TestOneArgument (pc, 1000000, 78498);
/* 1e7 */	TestOneArgument (pc, 10000000, 664579);
/* 1e8 */	TestOneArgument (pc, 100000000, 5761455);
/* 1e9 */	TestOneArgument (pc, 1000000000, 50847534);
/* 1e10 */	TestOneArgument (pc, 10000000000ull, 455052511ull);
/* 1e11 */	TestOneArgument (pc, 100000000000ull, 4118054813ull);

/* 1e12 */	TestOneArgument (pc, 1000000000000ull, 37607912018ull);
/* 2e12 */	TestOneArgument (pc, 2000000000000ull, 73301896139ull);
/* 3e12 */	TestOneArgument (pc, 3000000000000ull, 108340298703ull);
/* 4e12 */	TestOneArgument (pc, 4000000000000ull, 142966208126ull);
/* 5e12 */	TestOneArgument (pc, 5000000000000ull, 177291661649ull);
/* 6e12 */	TestOneArgument (pc, 6000000000000ull, 211381427039ull);
/* 7e12 */	TestOneArgument (pc, 7000000000000ull, 245277688804ull);
/* 8e12 */	TestOneArgument (pc, 8000000000000ull, 279010070811ull);
/* 9e12 */	TestOneArgument (pc, 9000000000000ull, 312600354108ull);

/* 1e13 */	TestOneArgument (pc, 10000000000000ull, 346065536839ull);
/* 2e13 */	TestOneArgument (pc, 20000000000000ull, 675895909271ull);
/* 3e13 */	TestOneArgument (pc, 30000000000000ull, 1000121668853ull);
/* 4e13 */	TestOneArgument (pc, 40000000000000ull, 1320811971702ull);
/* 5e13 */	TestOneArgument (pc, 50000000000000ull, 1638923764567ull);
/* 6e13 */	TestOneArgument (pc, 60000000000000ull, 1955010428258ull);
/* 7e13 */	TestOneArgument (pc, 70000000000000ull, 2269432871304ull);
/* 8e13 */	TestOneArgument (pc, 80000000000000ull, 2582444113487ull);
/* 9e13 */	TestOneArgument (pc, 90000000000000ull, 2894232250783ull);

/* 1e14 */	TestOneArgument (pc, 100000000000000ull, 3204941750802ull);
/* 2e14 */	TestOneArgument (pc, 200000000000000ull, 6270424651315ull);
/* 3e14 */	TestOneArgument (pc, 300000000000000ull, 9287441600280ull);
/* 4e14 */	TestOneArgument (pc, 400000000000000ull, 12273824155491ull);
/* 5e14 */	TestOneArgument (pc, 500000000000000ull, 15237833654620ull);
/* 6e14 */	TestOneArgument (pc, 600000000000000ull, 18184255291570ull);
/* 7e14 */	TestOneArgument (pc, 700000000000000ull, 21116208911023ull);
/* 8e14 */	TestOneArgument (pc, 800000000000000ull, 24035890368161ull);
/* 9e14 */	TestOneArgument (pc, 900000000000000ull, 26944926466221ull);

/* 1e15 */	TestOneArgument (pc, 1000000000000000ull, 29844570422669ull);

/* 1e16 */	TestOneArgument (pc, 10000000000000000ull, 279238341033925ull);
/* 2e16 */	TestOneArgument (pc, 20000000000000000ull, 547863431950008ull);
/* 4e16 */	TestOneArgument (pc, 40000000000000000ull, 1075292778753150ull);

/* 1e17 */	TestOneArgument (pc, 100000000000000000ull, 2623557157654233ull);
/* 1e18 */	TestOneArgument (pc, 1000000000000000000ull, 24739954287740860ull);
/* 2e18 */	TestOneArgument (pc, 2000000000000000000ull, 48645161281738535ull);
/* 3e18 */	TestOneArgument (pc, 3000000000000000000ull, 72254704797687083ull);
/* 4e18 */	TestOneArgument (pc, 4000000000000000000ull, 95676260903887607ull);
/* 4e18 */	TestOneArgument (pc, 4185296581467695669ull, 100000000000000000ull);
/* 5e18 */	TestOneArgument (pc, 5000000000000000000ull, 118959989688273472ull);
/* 6e18 */	TestOneArgument (pc, 6000000000000000000ull, 142135049412622144ull);
/* 7e18 */	TestOneArgument (pc, 7000000000000000000ull, 165220513980969424ull);
/* 8e18 */	TestOneArgument (pc, 8000000000000000000ull, 188229829247429504ull);
/* 9e18 */	TestOneArgument (pc, 9000000000000000000ull, 211172979243258278ull);

/* 1e19 */	TestOneArgument (pc, 10000000000000000000ull, 234057667276344607ull);

TestOneArgument (pc, 11000000000000000000ull, pc->PiEstimate (1.1e19));
TestOneArgument (pc, 12000000000000000000ull, pc->PiEstimate (1.2e19));
TestOneArgument (pc, 13000000000000000000ull, pc->PiEstimate (1.3e19));
TestOneArgument (pc, 14000000000000000000ull, pc->PiEstimate (1.4e19));
TestOneArgument (pc, 15000000000000000000ull, pc->PiEstimate (1.5e19));
TestOneArgument (pc, 16000000000000000000ull, pc->PiEstimate (1.6e19));
TestOneArgument (pc, 17000000000000000000ull, pc->PiEstimate (1.7e19));
TestOneArgument (pc, 18000000000000000000ull, pc->PiEstimate (1.8e19));
}

#if 0
pi(2e19)        =      460 637 655 126 005 490
pi(4e19)        =      906 790 515 105 576 571
pi(1e20)        =    2 220 819 602 560 918 840
#endif


int main (void) {

	TPrimeCount* primeCount = TPrimeCount::MakeMeisselLehmerCounter ();
	if (primeCount == 0) {
		::cout << "Creating a TPrimeCount object failed." << ::endl;
		return 0;
	}

	::cout << "TMLPrimeCount object can handle pi (N) for N <= " <<
					primeCount->MaxArgument () << ::endl;
	::cout << "TMLPrimeCount object requires " << primeCount->BytesNeeded () <<
					" bytes of memory" << ::endl;
	::cout << "Starting SelfTest" << ::endl;
	int err = primeCount->SelfTest ();
	::cout << "TMLPrimeCount::SelfTest () returned " << err << ::endl;
	TestPrimeCount (primeCount);
	delete primeCount;
	return 0;
}
