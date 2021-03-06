/*
    Copyright 2007-2008 by Robert Knight <robertknight@gmail.com>
    Copyright 2020 by Tomaz Canabrava <tcanabrava@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301  USA.
*/

#include "FilterChain.h"
#include "Filter.h"

using namespace Konsole;
FilterChain::~FilterChain()
{
    qDeleteAll(_filters);
}

void FilterChain::addFilter(Filter *filter)
{
    _filters.append(filter);
}

void FilterChain::removeFilter(Filter *filter)
{
    _filters.removeAll(filter);
}

void FilterChain::reset()
{
    for(auto *filter : _filters) {
        filter->reset();
    }
}

void FilterChain::setBuffer(const QString *buffer, const QList<int> *linePositions)
{
    for(auto *filter : _filters) {
        filter->setBuffer(buffer, linePositions);
    }
}

void FilterChain::process()
{
    for( auto *filter : _filters) {
        filter->process();
    }
}

void FilterChain::clear()
{
    _filters.clear();
}

QSharedPointer<HotSpot> FilterChain::hotSpotAt(int line, int column) const
{
    for(auto *filter : _filters) {
        QSharedPointer<HotSpot> spot = filter->hotSpotAt(line, column);
        if (spot != nullptr) {
           return spot;
        }
    }
    return nullptr;
}

QList<QSharedPointer<HotSpot>> FilterChain::hotSpots() const
{
    QList<QSharedPointer<HotSpot>> list;
    for (auto *filter : _filters) {
        list.append(filter->hotSpots());
   }
    return list;
}
