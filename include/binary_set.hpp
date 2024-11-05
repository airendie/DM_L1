#ifndef BINARY_SET_HPP
#define BINARY_SET_HPP

#include "universum.hpp"

#include <set>

using std::multiset;

class BinarySet : public multiset<BinaryNumber>
{
private:
    Universum *m_universum;
public:
    BinarySet(Universum *uni) : m_universum(uni) {}

    BinarySet getUnionWith(const BinarySet &other) const;
    BinarySet getIntersectionWith(const BinarySet &other) const;
    BinarySet getDifferenceWith(const BinarySet &other) const;
    BinarySet getSymmetricalDifferenceWith(const BinarySet &other) const;

    void print() const;
};

#endif // end of binary_set.hpp