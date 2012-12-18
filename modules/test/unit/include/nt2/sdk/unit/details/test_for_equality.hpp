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

#include <nt2/sdk/unit/details/is_sequence.hpp>
#include <nt2/sdk/unit/details/smallest_type.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_not_equal.hpp>
#include <boost/simd/sdk/simd/details/operators.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <algorithm>

namespace nt2 { namespace details
{
  template< class A, class B
          , bool IsASeq=nt2::details::is_sequence<A>::value
          , bool IsBSeq=nt2::details::is_sequence<B>::value
          >
  struct test_for_equality_
  {
    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      return is_equal(a,b) || ( is_not_equal(a,a) && is_not_equal(b,b) );
    }
  };

  template<class A, class B>
  struct  test_for_equality_<A, B, true, true>
  {
    struct check_
    {
      template<class U,class V>
      BOOST_FORCEINLINE bool operator()(U const& a, V const& b ) const
      {
        return test_for_equality_<U,V>()(a,b);
      }
    };

    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      return std::equal(a.begin(),a.end(),b.begin(),check_());
    }
  };

  template<class A, class B>
  struct  test_for_equality_<A, B, false, true>
  {
    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      return test_for_equality_<A,typename B::value_type>()(a,*b.begin());
    }
  };

  template<class A, class B>
  struct  test_for_equality_<A, B, true, false>
  {
    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      return test_for_equality_<typename A::value_type,B>()(*a.begin(),b);
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
