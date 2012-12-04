//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_REM_PIO2_CEPHES_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_REM_PIO2_CEPHES_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/functions/rem_pio2_cephes.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
#include <nt2/toolbox/constant/include/constants/three.hpp>
#include <nt2/toolbox/constant/include/constants/zero.hpp>
#include <nt2/include/functions/simd/round.hpp>
#include <nt2/include/functions/simd/fast_toint.hpp>
#include <nt2/include/functions/simd/bitwise_and.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/fusion/tuple.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_cephes_, boost::simd::tag::simd_,
                      (A0)(X),
                      ((simd_ < floating_<A0>,X > ))
                    )
  {
    typedef typename meta::as_integer<A0>::type            itype;
    typedef boost::fusion::tuple<A0,A0,itype>        result_type;

    inline result_type operator()(A0 const& a0) const
    {
      result_type res;
      boost::fusion::at_c<2>(res) =
        nt2::rem_pio2_cephes(a0,
                             boost::fusion::at_c<0>(res),
                             boost::fusion::at_c<1>(res)
                            );
      return res;
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // reference based Implementation when real
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_cephes_, boost::simd::tag::simd_,
                        (A0)(X),
                        ((simd_ < floating_<A0>, X > ))
                        ((simd_ < floating_<A0>, X > ))
                        ((simd_ < floating_<A0>, X > ))
                      )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& x, A0 & xr, A0& xc) const
    {
      A0 xi =  round(x*Twoopi<A0>());
      xr = x-xi*Pio2_1<A0>();
      xr -= xi*Pio2_2<A0>();
      xr -= xi*Pio2_3<A0>();
      xc = Zero<A0>();
      return b_and(fast_toint(xi), Three<result_type>());
    }
  };
} }
#endif
