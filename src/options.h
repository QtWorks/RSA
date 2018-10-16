#ifndef OPTIONS_H
#define OPTIONS_H

struct Options
{
    bool grouping;
    long primeRange;
    Options() : Options(false, 100){}
    Options(const bool grouping, const long primeRange) : grouping{grouping}, primeRange{primeRange}{}
};

#endif // OPTIONS_H
