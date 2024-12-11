#include "IntVector.hpp"

namespace src::Merge::Vector3
{

// Konstruktor przenoszacy
IntVector::IntVector(IntVector&& other)
: values{std::move(other.values)}
{ }

// konstruktor kopiujacy
IntVector::IntVector(const IntVector& other)
: values{std::move(other.values)}
{ }

// Operator przenoszacy
IntVector& IntVector::operator=(const IntVector&& other)
{
    if (this != &other)
    {
        this->values = std::move(other.values);
    }
    return *this;
}

// Operator kopiujacy
IntVector& IntVector::operator=(const IntVector& other)
{
    if (this != &other)
    {
        this->values = other.values;
    }
    return *this;
}

bool IntVector::operator==(const IntVector& other) const
{
    if (this->size() != other.size())
        return false;
    
    for (unsigned int i = 0; i < this->size(); ++i)
    {
        if (this->at(i) != other.at(i))
            return false;
    }
    return true;
}

bool IntVector::operator<(const IntVector& other) const
{
    return std::lexicographical_compare(
        this->values.begin(), this->values.end(), other.values.begin(), other.values.end());
}

} // namespace src::Merge::Vector3
