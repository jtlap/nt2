//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_NTHROOT_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_NTHROOT_HPP_INCLUDED
#include <nt2/exponential/functions/nthroot.hpp>
#include <nt2/exp_derivatives/functions/nthroot.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( nthroot_, tag::cpu_
                            , (order)(A0)(A1)
                            , (unspecified_<order>)
                              (generic_<unspecified_<A0>>)
                              (generic_<integer_<A1>>)
                            )
  {
    typedef A0                                                 result_type;
    typedef typename meta::scalar_of<A0>::type                         sA0;
    BOOST_FORCEINLINE result_type operator()( const order&
                                            , const A0& u
                                            , const A1& n) const
    {
      return compute(order(), u, n);
    }
  private:
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                         , const A0& u, const A1& n) const
    {
      return nthroot(u, n);
    }

    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                         , const A0& u, const A1& n) const
    {
      return nthroot(u, n)*rec(sA0(n)*u);
    }

    template<long P>
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                         , const A0& u, const A1& n) const
    {
      return nthroot(u, n)*pow<P>(rec(u))*fact(boost::mpl::long_<P>(), rec(sA0(n)));
    }

    BOOST_FORCEINLINE result_type fact(const boost::mpl::long_<1>, const A0&rn) const
    {
      return rn;
    }

    template <long P>
      BOOST_FORCEINLINE result_type fact(const boost::mpl::long_<P>, const A0&rn) const
    {
      return (rn-sA0(P-1))*fact(boost::mpl::long_<P-1>(), rn);
    }

  };
} }


#endif
