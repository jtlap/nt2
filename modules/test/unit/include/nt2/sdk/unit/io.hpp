//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_IO_HPP_INCLUDED
#define NT2_SDK_UNIT_IO_HPP_INCLUDED

#include <vector>
#include <iosfwd>

template<class T, class Alloc>
std::ostream& operator<<(std::ostream& os, std::vector<T, Alloc> const& v)
{
  typedef typename std::vector<T, Alloc>::const_iterator iterator_t;

  os << "\n";
  for(iterator_t it = v.begin(); it != v.end(); ++it)
    os << *it << "  ";
  os << "\n";

  return os;
}

#endif
