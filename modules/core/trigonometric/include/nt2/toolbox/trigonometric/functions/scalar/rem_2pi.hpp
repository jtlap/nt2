//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_REM_2PI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_REM_2PI_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/functions/rem_2pi.hpp>
#include <nt2/include/functions/scalar/rem_pio2.hpp>
#include <nt2/include/functions/scalar/rem_pio2_medium.hpp>
#include <nt2/include/functions/scalar/round.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/threeeps.hpp>
#include <nt2/include/constants/twopi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/inv2pi.hpp>
#include <nt2/include/constants/pix2_1.hpp>
#include <nt2/include/constants/pix2_2.hpp>
#include <nt2/include/constants/pix2_3.hpp>

#include <boost/fusion/tuple.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/trigo/selection_tags.hpp>

/////////////////////////////////////////////////////////////////////////////
// reference based Implementation when float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_2pi_, tag::cpu_,
                 (A0),
                 (scalar_ < floating_<A0> > )
                 )
  {
    typedef boost::fusion::tuple<A0,A0>           result_type;

    NT2_FUNCTOR_CALL(1)
    {
      result_type res;
      nt2::rem_2pi(a0,
                   boost::fusion::at_c<0>(res),
                   boost::fusion::at_c<1>(res)
        );
      return res;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_2pi_, tag::cpu_,
                             (A0),
                             (scalar_ < single_<A0> > )
                             (scalar_ < single_<A0> > )
                             (scalar_ < single_<A0> > )
    )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0, A0 & xr, A0& xc) const
    {
      ptrdiff_t n = rem_pio2(a0, xr, xc);
      xr = xr+n*Pio_2<A0>();
      xr = (xr > Pi<A0>()+Threeeps<A0>()) ? xr-Twopi<A0>():(xr > Pi<A0>() ? Pi<A0>() : xr);
    }

  };

  /////////////////////////////////////////////////////////////////////////////
  // reference based Implementation when double
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_2pi_, tag::cpu_,
                             (A0),
                             (scalar_ < double_<A0> > )
                             (scalar_ < double_<A0> > )
                             (scalar_ < double_<A0> > )
    )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0, A0 & xr, A0& xc) const
    {
      if (a0 ==  Inf<A0>())
      {
        xc = Zero<A0>();
        xr = Nan<A0>();
        return;
      }
      ptrdiff_t n = rem_pio2(a0, xr, xc);
      xr = xr+n*Pio_2<A0>();
      xr = (xr > Pi<A0>()) ? xr-Twopi<A0>():xr;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_2pi_, tag::cpu_,
                             (A0)(A1),
                             (scalar_ <floating_<A0> > )
                             (scalar_ <floating_<A0> > )
                             (scalar_ <floating_<A0> > )
                             (target_ <unspecified_<A1> >)
    )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0, A0 & xr, A0& xc, A1 const&) const
    {
      typedef typename A1::type selector;
      rem2pi<selector, void>::rem(a0, xr, xc);
    }
  private:
    template < class T, class dummy = void> struct rem2pi
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        BOOST_ASSERT_MSG(false, "wrong target for rem_2pi");
      }
    };
    template < class dummy> struct rem2pi < big_, dummy>
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        nt2::rem_2pi(x, xr, xc);
      }
    };
    template < class dummy> struct rem2pi < very_small_, dummy > // |a0| <2*pi
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        xr = x > Pi<A0>() ? x-Twopi<A0>() : (x < -Pi<A0>()) ? x+Twopi<A0>() : x;
        xc = Zero<A0>();
      }
    };
    template < class dummy> struct rem2pi < small_, dummy >// |a0| <= 20*pi
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        A0 xi =  nt2::round(x*Inv2pi<A0>());
        xr = x-xi*Pix2_1<A0>();
        xr -= xi*Pix2_2<A0>();
        xr -= xi*Pix2_3<A0>();
        xc = Zero<A0>();
      }
    };

    template < class dummy> struct rem2pi < medium_, dummy >
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        ptrdiff_t n = rem_pio2_medium(x, xr, xc);
        A0 volatile xr_ = xr+n*Pio_2<A0>();
        xr = (xr_ > Pi<A0>()) ? xr_-Twopi<A0>():xr_;
      }
    };
  };
} }
#endif
