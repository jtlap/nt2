//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_FAST_SINCOSD_FAST_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_FAST_SINCOSD_FAST_HPP_INCLUDED
#include <nt2/trig_derivatives/functions/d_fast_sincosd.hpp>

#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/simd/fast_sincosd.hpp>
#include <nt2/include/constants/deginrad.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_fast_sincosd_
                            , tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & a2) const
    {
      A0 c;
      a2 = -fast_sincosd(a0, c)*Deginrad<A0>();
      return c*Deginrad<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( d_fast_sincosd_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef std::pair<A0, A0>                      result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 c;
      A0 const s = fast_sincosd(a0, c);
      return result_type(c*Deginrad<A0>(), -s*Deginrad<A0>());
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( d_fast_sincosd_, tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      fast_sincosd(a0, a2, a1);
      a2 = -a2*Deginrad<A0>();
      a1 *= Deginrad<A0>();
    }
  };
} }


#endif
