//======================================================
// MMsieve - prime generator boolean

// Copyright [2017] [mgr inz. Marek Matusiak]

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//======================================================
#include <iostream>
#include <ctime>
#include<fstream>
#include <utility>
#include <algorithm>
#include <vector>

clock_t start;

#define CHAR_WORD uint64_t
#define WORD_BYTES 8
template<typename T>
void InsaneMemcpy(T* pDest, const T* pSource, const std::size_t& sizeBytes)
{
  CHAR_WORD* p_dest = (CHAR_WORD*)pDest;
  const CHAR_WORD* p_source = (const CHAR_WORD*)pSource;
  *(p_dest) = *(p_source);
  for (std::size_t i = 0; i < (sizeBytes+WORD_BYTES-1)/WORD_BYTES - 1; ++i)
  {
    *(++p_dest) = *(++p_source);
  }
}

using namespace std;
struct MMSieve{
    bool *Sieve;
    vector<unsigned int> primes;
    unsigned int e, p, n;

    unsigned int size;

    MMSieve(unsigned int _n) : n(_n){
        Sieve= new bool[(max(2*n + 1u, 6u))];
        e = 2;
        p = 2;
        Sieve[0] = false;
        Sieve[1] = false;
        Sieve[2] = true;
        Sieve[3] = true;
        Sieve[4] = false;
        Sieve[5] = true;

        primes.push_back(2);
        primes.push_back(3);
        primes.push_back(5);
    }

    ~MMSieve(){
        delete [] Sieve;
    }

    int nextPrime(int p)
    {
        do{++p;}while (!Sieve[p]);
        return p;
    }

    void generator()
    {
        int l = (e - p + 1);
        size = (p) * l + nextPrime(p) - 1;
        if (size > n) size = n;
        cout << l << " " << p << " " << size << " " << e+1 << endl;

        #define meme 1
        #if meme
        for(int i = 0; (i < p) && (e+1 + i*l < n);++i){
            ///cout << e+1 + i*l << " " << p << endl;
            memcpy(Sieve+(e+1 + i*l),Sieve+p,l * sizeof(bool));
        }
        #else
        for (int i = e + 1; i <= size; i++)
        {
            Sieve[i] = Sieve[i - l];
        }
        #endif // meme


    }

    /// Убирает все числа сомножаемые на p, до некого e включительно
    void cleaning()
    {

        for (int i = e; i >= p; --i)
        {

            if (Sieve[i])
            {
                ///cout << i * p << endl;
                Sieve[i * p] = false;
            }

        }
    }

    /// Собственно всё и делает
    void populate(){
    do{

        generator();
        cleaning();
        e = p * (e - p + 1) + nextPrime(p) - 1;
        p = nextPrime(p);

    }
    while ((p * e <= n && p * e > 0));

    float timeA =(float)(clock() - start)/1000;
    cout << ( "Action time  = " );
    cout << timeA << " s" << size;

    generator();

    timeA =(float)(clock() - start)/1000;
    cout << ( "Action time  = " );
    cout << timeA << " s" << size;

    do{
        e = n/p;
        cleaning();
        p = nextPrime(p);
    }
    while (p * p <= n);
    }
};



// -------------------end generator------------------------

// ---------------------cleaning---------------------------


// ----------------end cleaning------------------
int  main()
{

    int num = 1000 * 1000 * 1000;
    ///cout << "Enter the maximum number: ";
    ///cin >> num;
    MMSieve sv(num);
    start = clock();

    cout << "Filled array " << endl;

    sv.populate();
    float timeA =(float)(clock() - start)/1000;
    cout << ( "Action time  = " );
    cout << timeA << " s";
    //----------------------------- RECODR TO FILE --------------------------
    ofstream record ("prime.txt");
    int k=0;
    for (int i=0; i<= min(num,10000); i++)
    {
        if(sv.Sieve[i])
        {
            k+=1;
            record << i <<" ";
            if (k%25==0)
            {
                record << "\n";
            }
        }

    }
    record.close();


    return 0;
}
