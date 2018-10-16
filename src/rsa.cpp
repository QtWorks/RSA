#include "rsa.h"

shared_ptr<vector<int64>> rsa::calculateSieveOfEratosthenes(const int64 range) {
    auto         primeNumbers = make_shared<vector<int64>>();
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

int64 rsa::max(const int64 first, const int64 second) {
    if ( first > second ) {
        return first;
    }
    return second;
}

int64 rsa::ggt(const int64 first, const int64 second) {
    if ( second ) {
        return ggt(second, first % second);
    }
    return first;
}

int64 rsa::extendedGcd(int64 a, int64 b){
    int64 u       {1};
    int64 v       {0};
    int64 s       {0};
    int64 t       {1};
    int64 q       {0};
    int64 aHelper {0};
    int64 uHelper {0};
    int64 vHelper {0};

    while (0 < b){
        q       = a / b;
        aHelper = b;
        b       = a - q * b;
        a       = aHelper;
        uHelper = s;
        s       = u - q * s;
        u       = uHelper;
        vHelper = t;
        t       = v - q * t;
        v       = vHelper;
    }

    return u;
}

shared_ptr<vector<int64>> rsa::stringToIntVector(shared_ptr<string> text){
    auto numbers = make_shared<vector<int64>>();

    for (const auto & c : *text){
        numbers->push_back(static_cast<int64>(c));
    }

    return numbers;
}

shared_ptr<string> rsa::intVectorToString(shared_ptr<vector<int64>> numbers){
    stringstream output{};

    for (const auto & number : *numbers){
        output << static_cast<char>(number);
    }

    return make_shared<string>(output.str());
}

template<class T>
void debug (shared_ptr<vector<T>> elements){
    for (const auto & element : *elements){
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

shared_ptr<vector<int64>> rsa::generatePairs(shared_ptr<vector<int64>> input){
    auto         output = make_shared<vector<int64>>();
    const size_t END {input->size() - 1};

    for (size_t i = 0; i < END; i+= 2) {
        output->push_back(input->at(i) + (input->at(i + 1) * BASIS));
    }
    if (END % 2 == 0) {
        output->push_back(input->at(END));
    }
    debug(output);
    return output;
}

shared_ptr<vector<int64>> rsa::splitPairs(shared_ptr<vector<int64>> numbers){
    auto output = make_shared<vector<int64>>();

    for (const int64 number : *numbers){
        output->push_back(number % BASIS);
        int64 second = static_cast<int64>(number / BASIS);
        std::cout << number % BASIS << "   " << second << std::endl;
        if (0 < second){
            output->push_back(second);
        }
    }
    debug(output);
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
    auto output = make_shared<vector<int64>>();

    for (const auto &current : *message){
        output->push_back(rsa::modularPower(current, key.e, key.n));
    }
    return output;
}

shared_ptr<vector<int64>> rsa::encode(const rsa::Key key, shared_ptr<vector<int64>> message){
    auto output = make_shared<vector<int64>>();

    for (const auto &current : *message){
        output->push_back(rsa::modularPower(current, key.e, key.n));
    }
    return output;
}

shared_ptr<vector<int64>> rsa::decode(const rsa::Key key, shared_ptr<vector<int64>> message){
    auto output = make_shared<vector<int64>>();

    for (const auto &current : *message){
        output->push_back(rsa::modularPower(current, key.d, key.n));
    }
    return output;
}
