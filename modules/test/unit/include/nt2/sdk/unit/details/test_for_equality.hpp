//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_TEST_FOR_EQUALITY_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_TEST_FOR_EQUALITY_HPP_INCLUDED

#include <algorithm>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>

namespace nt2 { namespace details
{
  template<class A, class B, class Enable=void>
  struct test_for_equality_
  {
    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      return (a == b) || ((a!=a) && (b!=b) );
    }
  };

  template<class A>
  struct  test_for_equality_
          < A, A
          , typename  boost::dispatch::meta::
                      enable_if_type<typename A::const_iterator>::type
          >
  {
    struct check_
    {
      template<class U>
      BOOST_FORCEINLINE bool operator()(U const& a, U const& b ) const
      {
        return test_for_equality_<U,U>()(a,b);
      }
    };

    BOOST_FORCEINLINE bool operator()(A const& a, A const& b) const
    {
      return std::equal(a.begin(),a.end(),b.begin(),check_());
    }
  };
} }

namespace nt2 { namespace unit
{
  template<class A, class B>
  bool test_for_equality(A const& a, B const& b)
  {
    return details::test_for_equality_<A,B>()(a,b);
  }
} }

#endif
