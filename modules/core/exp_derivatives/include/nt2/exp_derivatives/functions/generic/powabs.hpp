//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_POWABS_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_POWABS_HPP_INCLUDED
#include <nt2/exponential/functions/powabs.hpp>
#include <nt2/exp_derivatives/functions/powabs.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( powabs_, tag::cpu_
                            , (order1)(order2)(A0)(A1)
                            , (unspecified_<order1>)
                              (unspecified_<order2>)
                              (generic_<floating_<A0>>)
                              (generic_<floating_<A1>>)
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
      return powabs(u, v);
    }

    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                         , const boost::mpl::long_<0>
                                         , const A0& u, const A1& v) const
    {
      return powabs(u, minusone(v))*v;
    }

    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                         , const boost::mpl::long_<1>
                                         , const A0& u, const A1& v) const
    {
      return  powabs(u, v)*log(u);
    }
    template<long P>
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                         , const boost::mpl::long_<0>
                                         , const A0& u, const A1& v) const
    {
      return powabs(u, v-sA0(P))*fact(boost::mpl::long_<P>(), v);
    }

    BOOST_FORCEINLINE result_type fact(const boost::mpl::long_<1>, const A1&v) const
    {
      return v;
    }

    template <long P>
      BOOST_FORCEINLINE result_type fact(const boost::mpl::long_<P>, const A1&v) const
    {
      return (v-sA0(P-1))*fact(boost::mpl::long_<P-1>(), v);
    }

    template<long Q>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                           , const boost::mpl::long_<Q>
                                           , const A0& u, const A1& v) const
    {
      return powabs(u, v)*pow<Q>(log(u)) ;
    }

    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                         , const boost::mpl::long_<1>
                                         , const A0& u, const A1& v) const
    {
      return powabs(u, v-sA0(1))*fma(log(u), v, One<sA0>());
    }

  };
} }


#endif
