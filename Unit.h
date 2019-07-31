#pragma once
#include <iostream>
#define TYPEAMOUNT 9
using std::string;

namespace ariel {
    enum Unit
{
    CM,
    M,
    KM,
    SEC,
    MIN,
    HOUR,
    G,
    KG,
    TON
};
const static long unit_values[9] = {1, 100, 100000, 1, 60, 3600, 1, 1000, 1000000};
const static string unit_types[9] = {"cm", "m", "km", "sec", "min", "hour", "g", "kg", "ton"};
}