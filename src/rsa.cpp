#include "rsa.h"

vector<int64>* calculateSieveOfEratosthenes( const int64 range ) {
    vector<int64> *primeNumbers {};
    const int64    squareRoot   { (int64)std::floor( std::sqrt( range ) ) };
    return primeNumbers;
}

int64 rsa::max( const int64 first, const int64 second ) {
    if ( first > second ) {
        return first;
    }
    return second;
}

int64 rsa::ggt( const int64 first, const int64 second ) {
    if ( second ) {
        return ggt( second, first % second );
    }
    return first;
}

int64 rsa::modularPower(int64 base, int64 power, int64 mod){
    int64 result {1};
    while (0 < power){
        if (1 == power % 2){
            result = (result * base) % mod;
            power--;
        } else {
            base = (base * base) % mod;
            power /= 2;
        }
    }
    return result;
}

shared_ptr<vector<int64>> rsa::encode(const rsa::Key key, shared_ptr<string> message){
    auto output = std::make_shared<vector<int64>>();

    for (const auto &current : *message){
        output->push_back(rsa::modularPower(current, key.e, key.n));
    }
    return output;
}

shared_ptr<string> rsa::decode(const rsa::Key key, shared_ptr<vector<int64>> message){
    std::stringstream stream{};

    for (const auto &current : *message){
        stream << static_cast<char>(rsa::modularPower(current, key.d, key.n));
    }
    return std::make_shared<string>(stream.str());
}
