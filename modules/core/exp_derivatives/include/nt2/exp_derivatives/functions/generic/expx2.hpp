//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_EXPX2_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_EXPX2_HPP_INCLUDED
#include <nt2/include/functions/simd/expx2.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/two.hpp>


namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( expx2_, tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              (generic_<unspecified_<A0>>)
                            )
  {
    typedef A0 result_type;
      typedef typename meta::scalar_of<A0>::type                    sA0;
    BOOST_FORCEINLINE result_type operator()(const order&
                                            , const A0& u) const
    {
      return compute(order(), u);
    }
  private:
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                         , const A0& u) const
    {
      return expx2(u);
    }
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                         , const A0& u) const
    {
      return Two<A0>()*u*expx2(u);
    }
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                         , const A0& u) const
    {
      return Two<sA0>()*oneplus(Two<A0>()*sqr(u))*expx2(u);
    }
    template < long P>
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                         , const A0& u) const
    {
      return fma(compute(boost::mpl::long_<P-1>(u)), u, boost::mpl::long_<P-2>(u))*Two<sA0>();
    }

  };
} }


#endif
