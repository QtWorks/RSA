#ifndef RSA_H
#define RSA_H
#include <memory>
#include <string>
#include <vector>
#include <sstream>

using std::vector;
using std::shared_ptr;
using std::string;
using int64 = int_fast64_t;

namespace rsa
{
    struct Key {
        const int64 e;
        const int64 d;
        const int64 n;
    };

    vector<int64>* calculateSieveOfEratosthenes( const int );
    int64 max( const int64, const int64 );
    int64 ggt( const int64, const int64 );
    // function generatePairs()
    int64 modularPower(int64, int64, int64);
    shared_ptr<vector<int64>> encode(const Key, shared_ptr<string>);
    shared_ptr<string> decode(const Key, shared_ptr<vector<int64>>);
}

#endif // RSA_H
