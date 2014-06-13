//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MEMORY_IO_HPP_INCLUDED
#define MEMORY_IO_HPP_INCLUDED

#include <iostream>
#include <algorithm>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/simd/sdk/details/io_fix.hpp>

//==============================================================================
// Local iostream insertion for NT2_TEST_EQUAL
//==============================================================================
namespace nt2 { namespace memory
{
  template<typename T, typename A> inline std::ostream&
  operator<<(std::ostream& os, buffer<T,A> const& v)
  {
    typedef typename buffer<T,A>::const_iterator iterator_t;

    os << "\n";
    for(iterator_t it = v.begin(); it != v.end(); ++it)
      os << boost::simd::details::display(*it) << "  ";
    os << "\n";

    return os;
  }
} }

#endif

