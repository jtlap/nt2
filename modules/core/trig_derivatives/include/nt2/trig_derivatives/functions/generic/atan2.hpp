//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_ATAN2_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_ATAN2_HPP_INCLUDED
#include <nt2/trigonometric/functions/atan2.hpp>
#include <nt2/trig_derivatives/functions/atan2.hpp>
#include <nt2/include/functions/simd/atan.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( atan2_, tag::cpu_
                            , (order1)(order2)(A0)(A1)
                            , (unspecified_<order1>)
                              (unspecified_<order2>)
                              (generic_<unspecified_<A0>>)
                              (generic_<unspecified_<A1>>)
                            )
  {
    typedef A0                                                 result_type;
    typedef typename meta::scalar_of<A0>::type                         sA0;
    BOOST_FORCEINLINE result_type operator()( const order1&
                                            , const order2&
                                            , const A0& u
                                            , const A1& v) const
    {
      return compute(order1(), order2(), u, v);
    }
  private:
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                         , const boost::mpl::long_<0>
                                         , const A0& u, const A1& v) const
    {
      return atan2(u, v);
    }

    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                         , const boost::mpl::long_<0>
                                         , const A0& u, const A1& v) const
    {
      return -v*atan<1>(v/u)*sqr(rec(u));
    }

    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                         , const boost::mpl::long_<1>
                                         , const A0& u, const A1& v) const
    {
      return  rec(u)*atan<1>(v/u);;
    }
    template<long P>
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                         , const boost::mpl::long_<0>
                                         , const A0& u, const A1& v) const
    {
      return -atan<P>(u/v)*pow<P>(rec(v));
    }

    template<long Q>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                           , const boost::mpl::long_<Q>
                                           , const A0& u, const A1& v) const
    {
      return atan<Q>(v/u)*pow<Q>(rec(u));
    }

    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                         , const boost::mpl::long_<1>
                                         , const A0& u, const A1& v) const
    {
      A0 u2 = sqr(u);
      A0 v2 = sqr(v);
      return -(u2 - v2)/sqr((u2 + v2));
    }


  };
} }


#endif
