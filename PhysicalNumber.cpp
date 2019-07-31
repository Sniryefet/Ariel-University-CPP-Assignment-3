#include <iostream>
#include <stdexcept>
#include <string>
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
using std::istream, std::ostream, std::endl, std::stod, std::ios;
#define epsilon 0.0000001

PhysicalNumber::PhysicalNumber(const long double value, const Unit unit_type)
{
  this->value = value;
  this->unit_type = unit_type;
}
PhysicalNumber::PhysicalNumber(const PhysicalNumber &other)
{
  this->value = other.value;
  this->unit_type = other.unit_type;
}

PhysicalNumber &PhysicalNumber::operator+=(const PhysicalNumber &other)
{
  if (this->unit_type / 3 != other.unit_type / 3)
    throw std::invalid_argument("Cannot use addition on different unit types!");


  this->value += static_cast<long double>(other.value * (double(unit_values[other.unit_type]) / double(unit_values[this->unit_type])));

  return *this;
}

PhysicalNumber &PhysicalNumber::operator-=(const PhysicalNumber &other)
{
  if (this->unit_type / 3 != other.unit_type / 3)
    throw std::invalid_argument("Cannot use addition on different unit types!");

  this->value -= static_cast<long double>(other.value * (double(unit_values[other.unit_type]) / double(unit_values[this->unit_type])));

  return *this;
}
PhysicalNumber &PhysicalNumber::operator=(const PhysicalNumber &other)
{
  this->value = other.value;
  this->unit_type = other.unit_type;
  return *this;
}

const PhysicalNumber PhysicalNumber::operator+() const
{
  return PhysicalNumber((this->value), this->unit_type);
}
const PhysicalNumber PhysicalNumber::operator-() const
{
  return PhysicalNumber(-(this->value), this->unit_type);
}

const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber &y) const
{
  if (this->unit_type / 3 != y.unit_type / 3)
    throw std::invalid_argument("Cannot use addition on different unit types!");

  long double value = this->value + static_cast<long double>(y.value * (double(unit_values[y.unit_type]) / unit_values[this->unit_type]));

  return PhysicalNumber(value, this->unit_type); //temp
}

const PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber &y) const
{
  if (this->unit_type / 3 != y.unit_type / 3)
    throw std::invalid_argument("Cannot use addition on different unit types!");

  long double value = this->value - static_cast<long double>(y.value * (double(unit_values[y.unit_type]) / unit_values[this->unit_type]));

  return PhysicalNumber(value, this->unit_type); //temp
}

bool ariel::operator==(const PhysicalNumber &x, const PhysicalNumber &y)
{
  if (x.unit_type / 3 != y.unit_type / 3)
    throw "Cannot use addition on different unit types!";

  long double basicvaly = static_cast<long double>(y.value * (double(unit_values[y.unit_type]) / double(unit_values[x.unit_type])));
  return (x.value > basicvaly - epsilon) && (x.value < basicvaly + epsilon);
}

bool ariel::operator!=(const PhysicalNumber &x, const PhysicalNumber &y)
{
  return !(x == y);
}

bool ariel::operator>(const PhysicalNumber &x, const PhysicalNumber &y)
{
  if (x.unit_type / 3 != y.unit_type / 3)
    throw "Cannot use addition on different unit types!";

  long double basicvaly = static_cast<long double>(y.value * (double(unit_values[y.unit_type]) / unit_values[x.unit_type]));
  return x.value > basicvaly;
  //return x.value - basicvaly > epsilon;
}

bool ariel::operator<(const PhysicalNumber &x, const PhysicalNumber &y)
{
  if (x.unit_type / 3 != y.unit_type / 3)
    throw "Cannot use addition on different unit types!";

  long double basicvaly = static_cast<long double>(y.value * (double(unit_values[y.unit_type]) / unit_values[x.unit_type]));
  return x.value < basicvaly;
  //return x.value - basicvaly < -epsilon;
}

bool ariel::operator>=(const PhysicalNumber &x, const PhysicalNumber &y)
{
  return !(x < y); // as '<' is the completement of '>='
}

bool ariel::operator<=(const PhysicalNumber &x, const PhysicalNumber &y)
{
  return !(x > y); // as '>' is the completement of '<='
}

PhysicalNumber &PhysicalNumber::operator++() // pre
{
  ++this->value;
  return *this;
}

PhysicalNumber &PhysicalNumber::operator--() // pre
{
  --this->value;
  return *this;
}

PhysicalNumber PhysicalNumber::operator++(int x) // post
{
  PhysicalNumber tmp = *this;
  ++this->value;
  return tmp;
}

PhysicalNumber PhysicalNumber::operator--(int x) // post
{
  PhysicalNumber tmp = PhysicalNumber(*this);
  --this->value;
  return tmp;
}

ostream &ariel::operator<<(ostream &s, const PhysicalNumber &n)
{
  return (s << n.value << "[" << unit_types[n.unit_type] << "]");
}

istream &ariel::operator>>(istream &s, PhysicalNumber &n)
{ //see: https://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
  // remember place for rewinding
  ios::pos_type startPosition = s.tellg();
  try
  {
    std::string str(std::istreambuf_iterator<char>(s), {});
    string::size_type loc1 = str.find('[', 0);
    string::size_type loc2 = str.find(']', 0);
    if (loc1 == string::npos || loc2 == string::npos)
    {
      auto errorState = s.rdstate(); // remember error state
      s.clear();                     // clear error so seekg will work
      s.seekg(startPosition);        // rewind
      s.clear(errorState);           // set back the error flag
      return s;
    }
    // throw std::invalid_argument("Error [Input >>]: Couldnt parse the stream, format mismatch. "+str);

    string type = str.substr(loc1 + 1, loc2 - loc1 - 1);
    long double num = std::stod(str.substr(0, loc1));

    //TYPEAMOUNT is defined as macro at Unit.hpp
    int i = 0;
    for (i = 0; i < TYPEAMOUNT; ++i)
    {
      if (type == (unit_types[i]))
      {
        n = PhysicalNumber(num, (Unit)i);
        break;
      }
    }
    //if(i == TYPEAMOUNT) // type not found
    //throw std::invalid_argument("Error [Input >>]: Couldnt parse the stream, type mismatch. "+str);
  }
  catch (const std::exception &e)
  {
    // do nothing
    auto errorState = s.rdstate(); // remember error state
    s.clear();                     // clear error so seekg will work
    s.seekg(startPosition);        // rewind
    s.clear(errorState);           // set back the error flag
  }
  return s;
}
