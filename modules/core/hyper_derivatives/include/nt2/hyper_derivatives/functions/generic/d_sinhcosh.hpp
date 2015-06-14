//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPER_DERIVATIVES_FUNCTIONS_GENERIC_D_SINHCOSH_HPP_INCLUDED
#define NT2_HYPER_DERIVATIVES_FUNCTIONS_GENERIC_D_SINHCOSH_HPP_INCLUDED
#include <nt2/hyper_derivatives/functions/d_sinhcosh.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/simd/sinhcosh.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_sinhcosh_
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
      a2 = sinhcosh(a0, c);
      return c;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( d_sinhcosh_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef std::pair<A0, A0>                      result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 c;
      A0 const s = sinhcosh(a0, c);
      return result_type(c, s);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( d_sinhcosh_, tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      sinhcosh(a0, a2, a1);
    }
  };
} }


#endif
