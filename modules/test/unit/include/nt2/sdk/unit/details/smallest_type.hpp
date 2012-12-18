//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_SMALLEST_TYPE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_SMALLEST_TYPE_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Compute the smallest type between T and U
  template< class T, class U
          , class pT = typename boost::dispatch::meta::primitive_of<T>::type
          , class pU = typename boost::dispatch::meta::primitive_of<U>::type
          >
  struct  smallest_impl
        : boost::mpl::if_c <(sizeof(pT) <= sizeof(pU)), T , U >
  {};

  /// INTERNAL ONLY
  /// Cast a value toward the smallest type compatible with T and U for
  /// proper ULP comparisons
  template<class T, class U>
  typename smallest_impl<T, U>::type
  smallest_a(T const& a, U const&)
  {
    return typename smallest_impl<T, U>::type(a);
  }

  /// INTERNAL ONLY
  /// Cast a value toward the smallest type compatible with T and U for
  /// proper ULP comparisons
  template<class T, class U>
  typename smallest_impl<T, U>::type
  smallest_b(T const&, U const& b)
  {
    return typename smallest_impl<T, U>::type(b);
  }
} }

#endif
