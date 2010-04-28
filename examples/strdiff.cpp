
#include "../src/dtl.hpp"
#include "common.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

using dtl::Diff;

int main(int argc, char *argv[]){
    
    if (isFewArgs(argc)) {
        cerr << "few argument" << endl;
        return -1;
    }
    
    typedef char elem;
    typedef string sequence;
    sequence A(argv[1]);
    sequence B(argv[2]);
    
    Diff<elem, sequence> d(A, B);
    //d.onOnlyEditDistance();
    d.compose();
    
    // editDistance
    cout << "editDistance:" << d.getEditDistance() << endl;
    
    // Longest Common Subsequence
    vector<elem> lcs_v = d.getLcsVec();
    sequence lcs_s(lcs_v.begin(), lcs_v.end());
    cout << "LCS:" << lcs_s << endl;
    
    // Shortest Edit Script
    cout << "SES" << endl;
    d.printSES();
    
    return 0;
}
