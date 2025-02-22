// Copyright (C) 2019-2025 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// { dg-do compile { target c++20 } }

#include <utility>
#include <tuple>

constexpr int
test01(int i, int j)
{
  using T = std::tuple<int>;
  std::pair<int, int> p0, p1;
  std::pair<int, int> pij(std::piecewise_construct, T(i), T(j));
  std::pair<int, int> pji(std::piecewise_construct, T(j), T(i));
  p0.swap(pij);
  swap(p1, pji);
  return p0.first - p0.second - p1.first + p1.second;
}

static_assert( test01(5, 100) == -190 );
