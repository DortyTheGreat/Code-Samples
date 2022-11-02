#include "testlib.h"

struct LCM{
    uint64_t mult, incr, mod;
    pure uint64_t step(const uint64_t& arg){ return (arg*mult + incr) % mod; }
    ///pure void step(uint64_t& arg){ arg = (arg*mult + incr) % mod; }
};
LCM L1, L2;

uint64_t transform(string path, uint64_t start){
    for(int i = 0; i < path.size(); ++i){
        if (path[i] == 'f' ){
            start = L1.step(start);
        }else{
            start = L2.step(start);
        }
    }
    return start;
}

int main(int argc, char* argv[]) {
    // This command initializes checker environment.
    registerTestlibCmd(argc, argv);
    // Now there are three global variables specifying testlib streams:
    // inf - stream with the testdata.
    // ouf - stream with the contestant output.
    // ans - stream with the jury answer.
    // All those streams provide the similar interface for reading data.

    // This function reads a single integer from the participant output that
    // should be between -2000 and 2000. If it doesn't belong to the specified
    // range, checker finishes with verdict _pe and comment saying that [sum of numbers]
    // is outside of the specified range.
    string pans = ouf.readString();

    L1.mult = inf.readInt(); // no need to additionally call readSpace() or readEoln() since
    L1.incr = inf.readInt(); // there is no need to validate input file in the checker
    L1.mod = inf.readInt();
    L2.mult = inf.readInt();
    L2.incr = inf.readInt();
    L2.mod = inf.readInt();

    uint64_t start = inf.readInt();
    uint64_t end = inf.readInt();
    // This function reads a single integer from the jury output. Here we suppose
    // that jury's answer is correct and we do not need to additionally verify it.

    auto t = transform(pans,start);
    if (t == end)
        quitf(_ok, "The path is correct."); // This finishes checker with verdit OK.
    else
        // quitf handles a comment like printf, i. e. you may use specifiers like
        // %d, %s etc in the comment.
        quitf(_wa, "The path is wrong: expected = %d, found = %s", end, t.c_str());
}
