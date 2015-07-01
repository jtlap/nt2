//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          EXPRECNEGCistributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_EXPRECNEGC_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_EXPRECNEGC_HPP_INCLUDED
#include <nt2/exponential/functions/exprecnegc.hpp>
#include <nt2/include/functions/simd/exprecneg.hpp>
#include <nt2/include/functions/simd/exprecnegc.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>


namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT(exprecnegc_, tag::cpu_
                          , (order)(A0)
                          , (unspecified_<order>)
                           (generic_<unspecified_<A0>>)
                          )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const order&
                                            , const A0& u) const
    {
      return compute(order(), u);
    }
  private:
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                         , const A0& u) const
    {
      return exprecnegc(u);
    }
    template < long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
    {
      return -exprecneg<P>(u);
    }
  };
} }


#endif
