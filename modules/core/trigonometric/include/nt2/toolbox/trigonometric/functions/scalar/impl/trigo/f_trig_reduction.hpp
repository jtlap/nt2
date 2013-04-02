//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/round.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_else_allbits.hpp>
#include <nt2/include/functions/is_not_less.hpp>
#include <nt2/include/functions/is_not_greater.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace details { namespace internal
{
  template< class A0
            , class unit_tag
            , class style
            , class mode
            , class base_A0 = typename meta::scalar_of<A0>::type
  >
  struct trig_reduction;

  // This class exposes the public static member:
  // reduce:                to provide range reduction
  //
  // unit_tag allows to choose statically the scaling  among radian_tag, pi_tag, degree_tag
  // meaning that the cosa function will (for example) define respectively
  // x-->cos(x)          (radian_tag),
  // x-->cos(p*x)        (pi_tag)
  // x-->cos((pi/180)*x) (degree_tag)
  //
  // precision_tag allows to choose policies among accuracy and speed
  // are defined:
  //   trig_tag
  //   fast_tag
  // fast_tag doe not mean that functions are returning stupid values
  //    but that the range is very restricted.
  // accu_tag does not mean that functions are ever slow,  but that they are
  //    slower and slower with increased range, but they are speedier than
  //    standard ones except for really big_ parameters values, because they return
  //    quite accurate values even in these cases
  //
  // for each trigonometric function, xxx
  //   xxx_
  //   fast_xxx_
  // NT2 functors are provided.

  // trigonometric reduction strategies to the [-pi/4, pi/4] range.
  // these reductions are used in the normal and fast
  // trigonometric functions with different policies

  template<class A0, class mode>
  struct trig_reduction < A0, radian_tag,  tag::not_simd_type, mode, float>
  {
    typedef typename meta::as_integer<A0, signed>::type int_type;

    static inline bool isalreadyreduced(const A0&a0) { return nt2::le(a0, nt2::Pio_4<A0>()); }
    static inline bool ismedium (const A0&a0)        { return nt2::le(a0,single_constant<A0,0x43490fdb>()); }
    static inline bool issmall  (const A0&a0)        { return nt2::le(a0,single_constant<A0,0x427b53d1>()); }
    static inline bool islessthanpi_2  (const A0&a0) { return nt2::le(a0,nt2::Pio_2<A0>()); }
    static inline bool conversion_allowed(){
      typedef typename meta::upgrade<A0>::type uA0;
      return boost::mpl::not_<boost::is_same<A0,uA0> >::value;
    }

    static inline bool cot_invalid(const A0& ) { return false; }
    static inline bool tan_invalid(const A0& ) { return false; }

    static inline int_type reduce(const A0& x, A0& xr){ return inner_reduce(x, xr, mode()); }
  private:
    static inline int_type inner_reduce(const A0& x, A0& xr, const big_&)
    {
      // x is always positive here
      if (isalreadyreduced(x)) // all of x are in [0, pi/4], no reduction
      {
        xr = x;
        return Zero<int_type>();
      }
      else if (islessthanpi_2(x)) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
        return nt2::rem_pio2_straight(x, xr);
      else if (issmall(x)) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
        return nt2::rem_pio2_cephes(x, xr);
      else if (ismedium(x)) // all of x are in [0, 2^7*pi/2],  fdlibm medium_ way
        return nt2::rem_pio2_medium(x, xr);
      else if (conversion_allowed())  // all of x are in [0, 2^18*pi],  conversion to double is used to reduce if available
      {
        typedef typename meta::upgrade<A0>::type uA0;
        typedef trig_reduction< uA0, radian_tag,  tag::not_simd_type, mode, double> aux_reduction;
        uA0 ux = x, uxr;
        int_type n = static_cast<int_type>(aux_reduction::reduce(ux, uxr));
        xr = static_cast<A0>(uxr);
        return n;
      }
      else  // all of x are in [0, inf],  standard big_ way // too long
      {
        return nt2::rem_pio2(x, xr);
      }

    }

    static inline int_type inner_reduce(const A0& x, A0& xr, const medium_&)
    {
      // x is always positive here
      if (isalreadyreduced(x)) // all of x are in [0, pi/4], no reduction
      {
        xr = x;
        return nt2::Zero<int_type>();
      }
      else if (islessthanpi_2(x)) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
        return nt2::rem_pio2_straight(x, xr);
      else if (issmall(x)) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
        return nt2::rem_pio2_cephes(x, xr);
      else  // correct only if all of x are in [0, 2^7*pi/2],  fdlibm medium_ way
        return nt2::rem_pio2_medium(x, xr);
    }

    static inline int_type inner_reduce(const A0& x, A0& xr, const small_&)
    {
      // x is always positive here
      if (isalreadyreduced(x)) // all of x are in [0, pi/4], no reduction
      {
        xr = x;
        return Zero<int_type>();
      }
      else if (islessthanpi_2(x)) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
        return nt2::rem_pio2_straight(x, xr);
      else  // correct only if all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
        return nt2::rem_pio2_cephes(x, xr);
    }

    static inline int_type inner_reduce(const A0& x, A0& xr, const direct_small_&)
    {
      return nt2::rem_pio2_cephes(x, xr);
    }

    static inline int_type inner_reduce(const A0& x, A0& xr, const direct_medium_&)
    {
      return nt2::rem_pio2_medium(x, xr);
    }

    static inline int_type inner_reduce(const A0& x, A0& xr, const direct_big_&)
    {
      if (conversion_allowed()) // conversion to double is used to reduce time, if available
      {
        typedef typename meta::upgrade<A0>::type uA0;
        typedef trig_reduction< uA0, radian_tag,  tag::not_simd_type, mode, double> aux_reduction;
        uA0 ux = x, uxr;
        int_type n = aux_reduction::reduce(ux, uxr);
        xr = uxr;
        return n;
      }
      else
      {
        return nt2::rem_pio2(x, xr);
      }
    }

    static inline int_type inner_reduce(const A0& x, A0& xr, const clipped_pio4_&)
    {
      xr = nt2::if_else(isalreadyreduced(x), x, Nan<A0>());
      return nt2::Zero<int_type>();
    }

    static inline int_type inner_reduce(const A0& x, A0& xr, const clipped_small_&)
    {
      xr = nt2::if_else(issmall(x), x, nt2::Nan<A0>());
      return inner_reduce(xr, xr, small_());
    }
    static inline int_type inner_reduce(const A0& x, A0& xr, const clipped_medium_&)
    {
      xr = nt2::if_else(ismedium(x), x, Nan<A0>());
      return inner_reduce(xr, xr, medium_());
    }
  };

  template<class A0>
  struct trig_reduction<A0,degree_tag, tag::not_simd_type,big_, float>
  {
    typedef typename meta::as_integer<A0, signed>::type int_type;

    static inline bool cot_invalid(const A0& x) { return nt2::is_nez(x)&&is_flint(x/_180<A0>()); }
    static inline bool tan_invalid(const A0& x) { return nt2::is_flint((x-nt2::_90<A0>())/nt2::_180<A0>()); }

    static inline int_type reduce(const A0& x, A0& xr)
    {
      A0 xi = nt2::round(x*single_constant<A0,0x3c360b61>()); //  1.111111111111111e-02f
      A0 x2 = x - xi * nt2::_90<A0>();

      xr =  x2*single_constant<A0,0x3c8efa35>(); //0.0174532925199432957692f
      return nt2::toint(xi);
    }

    static inline int_type inner_reduce(const A0& x, A0& xr, const clipped_pio4_&)
    {
      xr = nt2::if_else_nan(isalreadyreduced(nt2::abs(x)), x);
      return nt2::Zero<int_type>();
    }
    static inline int_type inner_reduce(const A0& x, A0& xr, const clipped_small_&)
    {
      x = nt2::if_else_nan(issmall(nt2::abs(x)), x);
      return inner_reduce(x, xr, small_());
    }
    static inline int_type inner_reduce(const A0& x, A0& xr, const clipped_medium_&)
    {
      x = nt2::if_else_nan(ismedium(nt2::abs(x)), x);
      return inner_reduce(x, xr, medium_());
    }
  };

  template < class A0>
  struct trig_reduction < A0, pi_tag,  tag::not_simd_type, big_, float>
  {
    typedef typename meta::as_integer<A0, signed>::type int_type;

    static inline bool cot_invalid(const A0& x) { return nt2::is_nez(x)&&nt2::is_flint(x); }
    static inline bool tan_invalid(const A0& x) { return nt2::is_flint(x-nt2::Half<A0>()) ; }

    static inline int_type reduce(const A0& x,  A0& xr)
    {
      A0 xi = nt2::round(x*nt2::Two<A0>());
      A0 x2 = x - xi * nt2::Half<A0>();
      xr = x2*nt2::Pi<A0>();
      return nt2::toint(xi);
    }
  };
} } }

#endif
