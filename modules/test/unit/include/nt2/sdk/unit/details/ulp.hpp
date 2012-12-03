//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_ULP_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_ULP_HPP_INCLUDED

#include <algorithm>
#include <nt2/sdk/unit/config.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <nt2/sdk/unit/details/smallest_type.hpp>

namespace nt2 { namespace details
{
  double max_ulps(double a, double b);
  float  max_ulps(float  a, float  b);

  template<class A, class B, class Enable=void>
  struct max_ulp_
  {
    typedef typename smallest_impl<A,B>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A const& a, B const& b) const
    {
      return max_ulps ( nt2::details::smallest_a(a,b)
                      , nt2::details::smallest_b(a,b)
                      );
    }
  };

  template<class A, class B>
  struct  max_ulp_
          < A, B
          , typename  boost::dispatch::meta::
                      enable_if_type<typename A::const_iterator>::type
          >
  {
    typedef typename smallest_impl< typename A::value_type
                                  , typename B::value_type
                                  >::type                         result_type;
    BOOST_FORCEINLINE result_type operator()(A const& a, A const& b) const
    {
      result_type res = 0;

      typename A::const_iterator ab = a.begin();
      typename A::const_iterator ae = a.end();
      typename B::const_iterator bb = b.begin();

      while(ab != ae)
      {
        res = std::max( res
                      , max_ulp_< typename A::value_type
                                , typename B::value_type
                                >()(*ab,*bb)
                      );
        ab++;
        bb++;
      }

      return res;
    }
  };
} }

namespace nt2 { namespace unit
{
  template<class A, class B> BOOST_FORCEINLINE
  typename details::max_ulp_<A,B>::result_type max_ulp(A const& a, B const& b)
  {
    return details::max_ulp_<A,B>()(a,b);
  }
} }

#endif
