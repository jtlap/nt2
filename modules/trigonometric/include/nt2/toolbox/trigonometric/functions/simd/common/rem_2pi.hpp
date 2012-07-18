//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_REM_2PI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_REM_2PI_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/functions/rem_2pi.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/twopi.hpp>
#include <nt2/include/constants/inv2pi.hpp>
#include <nt2/include/constants/pix2_1.hpp>
#include <nt2/include/constants/pix2_2.hpp>
#include <nt2/include/constants/pix2_3.hpp> 

#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/trigo/selection_tags.hpp>

/////////////////////////////////////////////////////////////////////////////
// reference based Implementation
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_2pi_, boost::simd::tag::simd_,
                      (A0)(X),
                      ((simd_ < floating_<A0>,X > ))
                    )
  {
    typedef boost::fusion::tuple<A0,A0>        result_type;

    inline void operator()(A0 const& a0) const
    {
      result_type res;
      boost::fusion::at_c<2>(res) =
        nt2::rem_2pi(a0,
                      boost::fusion::at_c<0>(res),
                      boost::fusion::at_c<1>(res)
                     );
      return res;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::rem_2pi_, boost::simd::tag::simd_,(A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0,A0 & xr,A0 & xc) const
    {
      nt2::int32_t n = rem_pio2(a0, xr, xc); 
      xr = xr+n*Pio_2<A0>(); 
      xr =  if_else(gt(xr, Pi<A0>()), xr-Twopi<A0>(), xr);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_2pi_, boost::simd::tag::simd_,
                             (A0)(A1)(X),
                             ((simd_ <floating_<A0>,X  > ))
                             ((simd_ <floating_<A0>,X  > ))
                             ((simd_ <floating_<A0>,X  > ))
                             ((target_ <unspecified_<A1> >))                          
                 )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& a0, A0 & xr, A0& xc, A1 const&) const
    {
      typedef typename A1::type selector;
      return rem2pi<selector, void>::rem(a0, xr, xc); 
    }
  private:
    template < class T, class dummy = void> struct rem2pi
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        BOOST_ASSERT_MSG(false, "wrong target for rem_2pi"); 
      }
    };
    template < class dummy> struct rem2pi < big, dummy>
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        nt2::rem_2pi(x, xr, xc);
      }
    }; 
    template < class dummy> struct rem2pi < verysmall, dummy > // |a0| <2*pi
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        xr = if_else(gt(x, Pi<A0>()) x-Twopi<A0>(),
                     if_else(lt(x, -Pi<A0>()), x+Twopi<A0>(), x); 
        xc = Zero<A0>();
      }
    }; 
    template < class dummy> struct rem2pi < small, dummy >// |a0| <= 20*pi
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        A0 xi =  nt2::round2even(x*Inv2pi<A0>()); 
        xr = x-xi*Pix2_1<A0>();
        xr -= xi*Pix2_2<A0>();
        xr -= xi*Pix2_3<A0>();
        xc = Zero<A0>();
       }
    };
    
    template < class dummy> struct rem2pi < medium, dummy >
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        nt2::int32_t n = rem_pio2_medium(x, xr, xc); 
        xr = xr+n*Pio_2<A0>(); 
        xr = if_else(gt(xr, Pi<A0>()), xr-Twopi<A0>(), xr);
      }
    }; 
  }; 
  
} }
#endif
