#include <iostream>
#include <exception>
#include "Unit.h"
using std::istream,std::ostream;

namespace ariel
{

class PhysicalNumber
{
    long double value;
    Unit unit_type;

  public:
    PhysicalNumber(const long double value, const Unit unit_type);
    PhysicalNumber(const PhysicalNumber &other);

    PhysicalNumber &operator+=(const PhysicalNumber &other);
    PhysicalNumber &operator-=(const PhysicalNumber &other);
    PhysicalNumber &operator=(const PhysicalNumber &other);

    const PhysicalNumber operator+() const;
    const PhysicalNumber operator-() const;
    PhysicalNumber& operator++();
    PhysicalNumber& operator--();
    PhysicalNumber operator++(int);
    PhysicalNumber operator--(int);

    const PhysicalNumber operator+(const PhysicalNumber &y) const;
    const PhysicalNumber operator-(const PhysicalNumber &y) const;

    friend bool operator==(const PhysicalNumber &x,const PhysicalNumber &y);
    friend bool operator!=(const PhysicalNumber &x,const PhysicalNumber &y);
    friend bool operator>(const PhysicalNumber &x,const PhysicalNumber &y);
    friend bool operator<(const PhysicalNumber &x,const PhysicalNumber &y);
    friend bool operator>=(const PhysicalNumber &x,const PhysicalNumber &y);
    friend bool operator<=(const PhysicalNumber &x,const PhysicalNumber &y);
  
    friend ostream &operator<<(ostream &s,const PhysicalNumber &n);
    friend istream &operator>>(istream &s, PhysicalNumber &n);

};

bool operator==(const PhysicalNumber &x,const PhysicalNumber &y);
bool operator!=(const PhysicalNumber &x,const PhysicalNumber &y);
bool operator>(const PhysicalNumber &x,const PhysicalNumber &y);
bool operator<(const PhysicalNumber &x,const PhysicalNumber &y);
bool operator>=(const PhysicalNumber &x,const PhysicalNumber &y);
bool operator<=(const PhysicalNumber &x,const PhysicalNumber &y);
ostream &operator<<(ostream &s, const PhysicalNumber &n);
istream &operator>>(istream &s, PhysicalNumber &n);

} // namespace ariel