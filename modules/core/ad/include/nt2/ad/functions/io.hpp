//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_IO_HPP_INCLUDED
#define NT2_AD_IO_HPP_INCLUDED

#include <nt2/include/functions/ad.hpp>
#include <iostream>

namespace nt2
{
  namespace ad
  {
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, valder<T> const& v)
    {
      os << "\n";
      os << boost::simd::details::display(v.val()) << "  ";
      os << "\n";
      os << boost::simd::details::display(v.vder()) << "  ";
      os << "\n";

      return os;
    }
  }
}

#endif
