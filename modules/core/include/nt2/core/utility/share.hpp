//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_SHARE_HPP_INCLUDED
#define NT2_CORE_UTILITY_SHARE_HPP_INCLUDED

#include <iterator>
#include <nt2/sdk/memory/fixed_allocator.hpp>

namespace nt2
{
  template<class Iterator>
  memory::fixed_allocator<typename std::iterator_traits<Iterator>::value_type>
  share(Iterator begin, Iterator end)
  {
    memory::fixed_allocator<typename std::iterator_traits<Iterator>::value_type>
    that(begin,end);
    return that;
  }
}

#endif
