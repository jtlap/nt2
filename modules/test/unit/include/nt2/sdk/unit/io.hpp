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
#include <iostream>
#include <algorithm>

namespace std
{
  template<typename T, typename A>
  inline std::ostream& operator<<(std::ostream& os, std::vector<T,A> const& v)
  {
    typedef typename std::vector<T,A>::const_iterator iterator_t;

    os << "\n";
    for(iterator_t it = v.begin(); it != v.end(); ++it)
      os << *it << "  ";
    os << "\n";

    return os;
  }

  template<typename T1, typename T2>
  inline std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> const& xpr)
  {
    os << "[" << xpr.first << ",  " << xpr.second << "]";
    return os;
  }
}

#endif
