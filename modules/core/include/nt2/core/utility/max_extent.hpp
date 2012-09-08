//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_AS_INDEX_HPP_INCLUDED
#define NT2_CORE_UTILITY_AS_INDEX_HPP_INCLUDED

#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace details
{
  template<class A, class B> struct max_extent
  {
    typedef typename meta::call<tag::extent_(A const&)>::type exta_t;
    typedef typename meta::call<tag::extent_(B const&)>::type extb_t;
    typedef typename details::max<exta_t,extb_t>::result_type type;
  };
} }

namespace nt2
{
  // For any 2 entities, return the maximum extent of both
  template<class A, class B>
  typename details::max_extent<A,B>::type max_extent(A const& a, B const& b)
  {
    return nt2::max(nt2::extent(a),nt2::extent(b));
  }
}

#endif
