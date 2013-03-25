//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_UNIT_SDK_MEMORY_LOCAL_IO_HPP_INCLUDED
#define NT2_UNIT_SDK_MEMORY_LOCAL_IO_HPP_INCLUDED

#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/unit/io.hpp>
#include <iostream>

// Local stream inserter to satisfy NT2_TEST_EQUAL
template<class T, class S, class Sema>
std::ostream& operator<<( std::ostream& os
                        , nt2::memory::container<T,S,Sema> const& c
                        )
{
  os << "[";
  for(std::size_t i=0;i<c.size();++i) os << " " << c[i];
  os << "]";
  return os;
}

#endif
