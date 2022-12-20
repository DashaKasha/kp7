#include <iostream>
#include <unordered_set>
#include <fstream>
#include <vector>
#include "TimeLogger.h"

using namespace std;



class MyHashFunc {
private:
    static int M;
    static int K;
public:
    size_t operator()(const string str_) const {
        long long s = 0;
        long long m = 1;
        for (char c : str_) {
            s += c * m;
            m *= static_cast<long long>(K);
        }
        return s % M;
    }
};

typedef unordered_set<string, MyHashFunc> set;

int MyHashFunc::K = 128;
int MyHashFunc::M = 97;
const int k = 128;
const int m = 97;


int main() {
    const string pathRes = "results.txt";
    const string pathEl = "elements.txt";

    unordered_set<string, MyHashFunc> set;

    ifstream readF("dostoevsky.txt");
    ofstream outF("results.txt");
    TimeLogger logger(pathRes);
    string buffer;
    size_t size1 = 0;
    size_t size = 0;
    logger.start();
    readF >> buffer;
    while (!readF.eof()) {
        set.insert(buffer);
        readF >> buffer;
    }
    readF.close();


    logger.finish();
    logger.log("unordered_set", "read", "K, M", 0);

    logger.start();
    set.find("выразить");
    logger.finish();
    logger.log("unordered_set", "find", "K, M", 0);

    ofstream write(pathEl);
    write << "hash; elems" << endl;
    for (size_t i = 0; i < m; i++) {
        write << i << " " << set.bucket_size(i) << endl;
    }
    write.close();
    return 0;

}