#include "rsa.h"

shared_ptr<vector<int64>> rsa::calculateSieveOfEratosthenes( const int64 range ) {
    auto         primeNumbers = std::make_shared<vector<int64>>();
    const int64  squareRoot     {static_cast<int_fast64_t>(std::sqrt(range))};
    vector<bool> markedNumbers  (range + 1, false);

    for (int64 i = 2; i <= squareRoot; i++) {
        if (!markedNumbers[i]) {
            for (int64 multiplier = i * i; multiplier <= range; multiplier += i) {
                markedNumbers[multiplier] = true;
            }
        }
    }

    for (int64 i = 2; i < range + 1; i++) {
        if (!markedNumbers[i]) {
            primeNumbers->push_back(i);
        }
    }

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

shared_ptr<vector<int64>> rsa::generatePairs(shared_ptr<vector<int64>> input){
    auto         output = std::make_shared<vector<int64>>();
    const size_t END {input->size() - 1};

    for (size_t i = 0; i < END; i+= 2) {
        output->push_back(input->at(i) + input->at(i + 1));
    }
    if (END % 2 == 0) {
        output->push_back(input->at(END));
    }

    return output;
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
