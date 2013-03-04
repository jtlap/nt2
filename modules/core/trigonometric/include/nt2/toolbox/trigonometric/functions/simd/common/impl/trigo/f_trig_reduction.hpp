//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/inrad.hpp>
#include <nt2/include/functions/simd/round.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/is_not_less.hpp>
#include <nt2/include/functions/simd/is_not_greater.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/bitwise_andnot.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_invalid.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/split.hpp>
#include <nt2/include/functions/simd/group.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      // This class exposes the public static member:
      // reduce:                to provide range reduction
      //
      // unit_tag allows to choose statically the scaling  among radian_tag, pi_tag, degree_tag
      // meaning that the cosa function will (for example) define respectively
      // x-->cos(x)          (radian_tag),
      // x-->cos(pi*x)       (pi_tag)
      // x-->cos((pi/180)*x) (degree_tag)
      //

      // trigonometric reduction strategies to the [-pi/4, pi/4] range.
      // these reductions are used in the accurate and fast
      // trigonometric functions with different policies

      template<class A0, class mode>
      struct trig_reduction < A0, radian_tag,  tag::simd_type, mode, float>
      {
        typedef typename meta::as_logical<A0>::type              bA0;
        typedef typename meta::as_integer<A0, signed>::type int_type;
        static inline bA0 isalreadyreduced(const A0&a0) { return is_ngt(a0, Pio_4<A0>()); }
        static inline bA0 ismedium (const A0&a0)  { return le(a0,single_constant<A0,0x43490fdb>()); }
        static inline bA0 issmall  (const A0&a0)  { return le(a0,single_constant<A0,0x427b53d1>()); }
        static inline bA0 islessthanpi_2  (const A0&a0)  { return le(a0,Pio_2<A0>()); }
        typedef typename boost::mpl::not_<boost::is_same<A0,typename meta::upgrade<A0>::type> >::type conversion_allowed;

        static inline bA0 cot_invalid(const A0&) { return False<bA0>(); }
        static inline bA0 tan_invalid(const A0&) { return False<bA0>(); }
        static inline int_type reduce(const A0& x, A0& xr, A0& xc){ return inner_reduce(x, xr, xc, mode()); }
      private:
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const big_& b)
        {
          const A0 x = x_n;
          // x is always positive here
          if (nt2::all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>();
            }
          else if (nt2::all(islessthanpi_2(x))) // all of x are in [pi/4, pi/2],  straight algorithm is sufficient for 1 ulp
              return rem_pio2_straight(x, xr, xc);
          else if (nt2::all(issmall(x))) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
              return rem_pio2_cephes(x, xr, xc);
          else if (nt2::all(ismedium(x))) // all of x are in [0, 2^7*pi/2],  fdlibm medium_ way
              return rem_pio2_medium(x, xr, xc);
          else
              return inner_reduce_big(x, xr, xc, b, conversion_allowed());
        }

        template<class m>
        static inline int_type inner_reduce_big(const A0& x, A0& xr, A0& xc, const m&, boost::mpl::true_)
        {
          //if (nt2::all(isnotsobig(x))) // all of x are in [0, 2^18*pi],  conversion to double is used to reduce
          typedef typename meta::upgrade<A0>::type uA0;
          typedef typename meta::upgrade<int_type>::type uint_type;
          typedef trig_reduction< uA0, radian_tag,  tag::simd_type, mode, double> aux_reduction;
          uA0 ux1, ux2, uxr1, uxr2, uxc1, uxc2;
          nt2::split(x, ux1, ux2);
          uint_type n1 = aux_reduction::reduce(ux1, uxr1, uxc1);
          uint_type n2 = aux_reduction::reduce(ux2, uxr2, uxc2);
          xr = nt2::group(uxr1, uxr2);
          nt2::split(xr, ux1, ux2);
          xc = nt2::group((uxr1-ux1)+uxc1, (uxr2-ux2)+uxc2);
          return nt2::group(n1, n2);
        }

        static inline int_type inner_reduce_big(const A0& x, A0& xr, A0& xc, const big_&, boost::mpl::false_)
        {
          // all of x are in [0, inf],  standard big_ way
          return rem_pio2(x, xr, xc);
        }

        static inline int_type inner_reduce_big(const A0& x, A0& xr, A0& xc, const direct_big_&, boost::mpl::false_)
        {
          return rem_pio2_big(x, xr, xc);
        }

        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const medium_&)
        {
          const A0 x = x_n;
          // x is always positive here
          if (nt2::all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>();
            }
          else if (nt2::all(islessthanpi_2(x))) // all of x are in [pi/4, pi/2],  straight algorithm is sufficient for 1 ulp
              return rem_pio2_straight(x, xr, xc);
          else if (nt2::all(issmall(x))) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
              return rem_pio2_cephes(x, xr, xc);
          else // correct only if all of x are in [0, 2^7*pi/2],  fdlibm medium_ way
              return rem_pio2_medium(x, xr, xc);
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const small_&)
        {
          const A0 x = x_n;
          // x is always positive here
          if (nt2::all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>();
            }
          else if (nt2::all(islessthanpi_2(x))) // all of x are in [pi/4, pi/2],  straight algorithm is sufficient for 1 ulp
              return rem_pio2_straight(x, xr, xc);
          else //  correct only if all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
              return rem_pio2_cephes(x, xr, xc);
         }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const direct_small_&)
        {
          const A0 x = x_n;
          return rem_pio2_cephes(x, xr, xc);
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const direct_medium_&)
        {
          const A0 x = x_n;
          return rem_pio2_medium(x, xr, xc);
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const direct_big_& b)
        {
          const A0 x = x_n;
          inner_reduce_big(x, xr, xc, b);
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const clipped_pio4_&)
        {
          const A0 x = x_n;
          xr = sel(isalreadyreduced(nt2::abs(x)), x, Nan<A0>());
          xc = Zero<A0>();
          return Zero<int_type>();
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const clipped_small_&)
        {
          const A0 x = x_n;
          xr = sel(issmall(nt2::abs(x)), x, Nan<A0>());
          return inner_reduce(xr, xr, xc, small_());
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const clipped_medium_&)
        {
          const A0 x = x_n;
          xr = sel(ismedium(nt2::abs(x)), x, Nan<A0>());
          return inner_reduce(xr, xr, xc, medium_());
        }

      };


      template<class A0>
      struct trig_reduction<A0,degree_tag, tag::simd_type,big_, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::as_logical<A0>::type              bA0;

        static inline bA0 cot_invalid(const A0& x) { return logical_and(is_nez(x), is_flint(x/_180<A0>())); }
        static inline bA0 tan_invalid(const A0& x) { return is_flint((x-_90<A0>())/_180<A0>()); }

        static inline int_type reduce(const typename A0::native_type x_n, A0& xr, A0& xc)
        {
          const A0 x = x_n;
          A0 xi = round(x*single_constant<A0,0x3c360b61>()); //  1.111111111111111e-02f
          A0 x2 = x - xi * _90<A0>();//90.0f
          xr =  x2*single_constant<A0,0x3c8efa35>(); //0.0174532925199432957692f
          xc = Zero<A0>();
          return toint(xi);
        }
      };

      // TODO put a medium_ case with a fast_round ?
       template < class A0>
       struct trig_reduction < A0, pi_tag,  tag::simd_type, big_, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::as_logical<A0>::type              bA0;

        static inline bA0 cot_invalid(const A0& x) { return logical_and(is_nez(x), is_flint(x)); }
        static inline bA0 tan_invalid(const A0& x) { return is_flint(x-Half<A0>()) ; }

        static inline int_type reduce(const typename A0::native_type x_n,  A0& xr, A0&xc)
        {
          const A0 x = x_n;
          A0 xi = round(x*Two<A0>());
          A0 x2 = x - xi * Half<A0>();
          xr = x2*Pi<A0>();
          xc = Zero<A0>();
          return toint(xi);
        }
      };
    }
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_trig_reduction.hpp
// /////////////////////////////////////////////////////////////////////////////
