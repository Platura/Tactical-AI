#include "TacticalMap.h"
#include <cassert>
#include <tgmath.h>
#include <algorithm>
#include <queue>


TacticalMap::TacticalMap(uint32_t size_x, uint32_t size_y, float value) 
{
    Field::init(size_x, size_y, value);
}

TacticalMap::TacticalMap(Field<float>&& value) : Field(value)
{
}
TacticalMap::TacticalMap(Field<float>& value) :Field(value){}

TacticalMap& TacticalMap::operator*=(TacticalMap const& a)
{
    // TODO: hier return-Anweisung eingeben
    auto const size_x = getSizeX();
    auto const size_y = getSizeX();

    assert(getSizeX() == a.getSizeX());
    assert(getSizeY() == a.getSizeY());


    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) *= a.at(x, y);
        }
    }

    return *this;
}

TacticalMap& TacticalMap::operator*=(float const& value)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeX();

    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) *= value;
        }
    }

    return *this;
}

TacticalMap& TacticalMap::operator^=(TacticalMap const& other)
{
    // TODO: hier return-Anweisung eingeben
    return *this;
}

TacticalMap& TacticalMap::operator+=(TacticalMap const& a)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeX();

    assert(getSizeX() == a.getSizeX());
    assert(getSizeY() == a.getSizeY());


    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) += a.at(x, y);
        }
    }

    return *this;
}

TacticalMap& TacticalMap::operator+=(float const& value)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeY();

    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) += value;
        }
    }
    return *this;
}

TacticalMap& TacticalMap::operator/=(TacticalMap const& a)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeX();

    assert(getSizeX() == a.getSizeX());
    assert(getSizeY() == a.getSizeY());


    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) /= a.at(x, y);
        }
    }

    return *this;
}

TacticalMap& TacticalMap::operator/=(float const& value)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeY();

    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) /= value;
        }
    }
    return *this;
}

TacticalMap& TacticalMap::operator-=(TacticalMap const& a)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeX();

    assert(getSizeX() == a.getSizeX());
    assert(getSizeY() == a.getSizeY());


    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) -= a.at(x, y);
        }
    }

    return *this;
}

TacticalMap& TacticalMap::weight(float const& value)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeY();

    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) *= value;
        }
    }
    return *this;
}

TacticalMap& TacticalMap::invert()
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeX();

    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) = std::fabs(1 - at(x, y));
        }
    }
    return *this;
}

TacticalMap& TacticalMap::max(TacticalMap const& a)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeX();

    assert(getSizeX() == a.getSizeX());
    assert(getSizeY() == a.getSizeY());


    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            at(x, y) = std::max(at(x,y), a.at(x, y));
        }
    }
    return *this;
}

aiPosition TacticalMap::getMaxValue()
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeX();

    float max_value=0.f;
    aiPosition max_position = { 0,0 };
    for (auto x = 0u; x < size_x; x++)
    {
        for (auto y = 0u; y < size_y; y++)
        {
            if (max_value < at(x, y))
            {
                max_value = at(x, y);
                max_position = { (float)x,(float)y };
            }
                
        }
    }
    return max_position;
}

struct ComparePairByFirst {
    bool operator()(const std::pair<float, aiPosition>& a, const std::pair<float, aiPosition>& b) const {
        return a.first > b.first;  // for a min-heap with priority_queue
    }
};

std::vector<aiPosition> TacticalMap::getTopNValues(int count)
{
    auto const size_x = getSizeX();
    auto const size_y = getSizeY();

    std::priority_queue<std::pair<float, aiPosition>, std::vector<std::pair<float, aiPosition>>, ComparePairByFirst > pq;

    for (unsigned int x = 0; x < size_x; ++x)
    {
        for (unsigned int y = 0; y < size_y; ++y)
        {
            float value = at(x, y);
            aiPosition pos = { static_cast<float>(x), static_cast<float>(y) };

            if (pq.size() < count)
            {
                pq.emplace(value, pos);
            }
            else if (value > pq.top().first)
            {
                pq.pop();
                pq.emplace(value, pos);
            }
        }
    }

    // Extract results into a vector (from highest to lowest)
    std::vector<aiPosition> result;
    while (!pq.empty())
    {
        result.push_back(pq.top().second);
        pq.pop();
    }

    return result;
}


TacticalMap operator*(TacticalMap const& a, TacticalMap const& b)
{
    TacticalMap result = a; // Copy from a;
    result *= b;
    return std::move(result);
}

TacticalMap operator-(TacticalMap const& a, TacticalMap const& b)
{
    TacticalMap result = a; // Copy from a;
    result -= b;
    return std::move(result);
}

TacticalMap operator/(TacticalMap const& a, TacticalMap const& b)
{
    TacticalMap result = a; // Copy from a;
    result /= b;
    return std::move(result);
}

TacticalMap max(TacticalMap const& a, TacticalMap const& b)
{
    TacticalMap result = a;
    result.max(b);
    return std::move(result);
}

TacticalMap invert(TacticalMap const& a)
{
    TacticalMap result = a;
    result.invert();
    return std::move(result);
}
