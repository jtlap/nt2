/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_TRIG_BASE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_TRIG_BASE_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/functions/scalar/impl/selection_tags.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/trigo/f_trig_reduction.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/trigo/d_trig_reduction.hpp>
#include <nt2/include/functions/simd/is_invalid.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/shli.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/bitwise_or.hpp>
#include <nt2/sdk/simd/tags.hpp>

// trigonometric functions are implemented using the classical cephes/fdlibm/libc principles
// however the formal reduce/eval/return is properly divided to allow choices versus
// speed, accuracy and  SIMD vectorisation
//
// On small ranges performance can be obtained with almost full accuracy (1 ulp) at 1.5
// cycles per element for a cosine computation using SIMD. But if one require full accuracy
// on the full float or double range, the prize can grow up to few hundreds of cycle for
// some big values of input.
// See the NT2 technical documentation for more insights


namespace nt2
{
  namespace details
  {
    // in the class defined below:
    // A0 is the argument type of the trigonometric functions
    //
    // Up to now, only floating real based on IEEE 754 float or double are supported
    // (sorry no long double yet for lack of portability)
    // The possible conversion of integer types to floating ones
    // is already addressed in the primary functors invocations namely cos_, sin_ etc.

    namespace internal
    {
      template < class A0, class unit_tag> struct trig_ranges; 
//       {
//      //      static inline A0    max_range() {return Zero<A0>(); }
//       }; 
      template < class A0>  struct trig_ranges<A0, radian_tag>
      {
        static inline A0    max_range() {return Pio_4<A0>(); }
        static inline A0    scale()     {return One<A0>(); }
      }; 
      template < class A0>  struct trig_ranges<A0, pi_tag>
      {
        static inline A0    max_range() {return Quarter<A0>(); }
        static inline A0    scale()     {return Pi<A0>(); }
      }; 
      template < class A0>  struct trig_ranges<A0, degree_tag>
      {
        static inline A0    max_range() {return _45<A0>(); }
        static inline A0    scale()     {return Pio_180<A0>(); }
      }; 


      // This class expose the public static members:
      // cosa     x -> cos(a*x)
      // sina     x -> sin(a*x)
      // tana     x -> tan(a*x)
      // cota     x -> cot(a*x)
      // sincosa  x -> cos(a*x) and sin(a*x)
      // "a" is not a run time parameter !
      // It stands as a remainder that according the Tag it can be considered
      // as a scale factor for the input of values:
      //   1           radian_tag,
      //   pi          pi_tag
      //   pi/180      degree_tag,
      // but the scaling is internal to the algorithm to provide better accuracy
      // and better performance.

      // It heritates of a reduction and an evaluation class to perform
      // the appropriate range reductions and function evaluations.

      // In this file stands the scalar version !
      // Some definitions are useless but provide facilities of comparaison with
      // the SIMD implementation
      //
      template < class A0,
                 class unit_tag,
                 class style,
                 class mode =  big> 
      struct trig_base{};

      template < class A0,
                 class unit_tag,
                 class mode>
      struct trig_base<A0,unit_tag,tag::not_simd_type,mode>
      {
        typedef trig_reduction<A0,unit_tag,tag::not_simd_type, mode>    redu_t;
        typedef trig_evaluation<A0,tag::not_simd_type>            eval_t;
        typedef typename meta:: scalar_of<A0>::type                           sA0; // scalar version of A0
        typedef typename meta::as_integer<A0, signed>::type              int_type; // signed integer type associated to A0
        typedef typename meta::scalar_of<int_type>::type                sint_type; // scalar version of the associated type
        typedef typename mode::type                                         style;

        // for all functions the scalar algorithm is:
        // * quick return (or exception raising TODO) for inf and nan or specific invalid cases inputs
        // * range reduction
        // * computation of sign and evaluation selections flags
        // * evaluations
        // * return with flag based corrections

        static inline A0 cosa(const A0& a0){ return cosa(a0, style()); }
        static inline A0 sina(const A0& a0){ return sina(a0, style()); }
        static inline A0 tana(const A0& a0){ return tana(a0, style()); }
        static inline A0 cota(const A0& a0){ return cota(a0, style()); }
        static inline A0 sincosa(const A0& a0, A0& c){ return sincosa(a0,c,style()); }

        static inline A0 cosa(const A0& a0, const regular&)
        {
          static const sint_type de = static_cast<sint_type>(sizeof(sint_type)*8-1);   // size in bits of the scalar types minus one
          if (is_invalid(a0)) return Nan<A0>(); //Nan or Inf input
          const A0 x =  nt2::abs(a0);
          A0 xr = Nan<A0>(), xc;
          const int_type n = redu_t::reduce(x, xr, xc);
          const int_type swap_bit = n&One<int_type>();
          const int_type sign_bit = shli(b_xor(swap_bit, (n&2)>>1), de);
          A0 z = sqr(xr);
          if (swap_bit)
            {
              z = eval_t::sin_eval(z, xr, xc);
            }
          else
            {
              z = eval_t::cos_eval(z, xr, xc);
            }
          return b_xor(z,sign_bit);
        }

        static inline A0 sina(const A0& a0, const regular&)
        {
          static const sint_type de = static_cast<sint_type>(sizeof(sint_type)*8-1);
          if (is_invalid(a0)) return Nan<A0>();
          const A0 x =  nt2::abs(a0);
          A0 xr = Nan<A0>(), xc;
          const int_type n = redu_t::reduce(x, xr, xc);
          const int_type swap_bit = n&One<int_type>();
          const A0 sign_bit = b_xor(bitofsign(a0), shli(n&Two<int_type>(), de-1));
          A0 z = sqr(xr);
          if (swap_bit)
            {
              z = eval_t::cos_eval(z, xr, xc);
            }
          else
            {
              z = eval_t::sin_eval(z, xr, xc);
            }
          return b_xor(z,sign_bit);
        }

        static inline A0 tana(const A0& a0, const regular&)
        {
          if (is_invalid(a0)||redu_t::tan_invalid(a0)) return Nan<A0>();
          if (is_eqz(a0)) return a0;
          const A0 x =  nt2::abs(a0);
          A0 xr = Nan<A0>(), xc, y;
          const int_type n = redu_t::reduce(x, xr, xc);
          y = eval_t::tan_eval(xr, xc, 1-((n&1)<<1));
          // 1 -- n even
          //-1 -- n odd
          return b_xor(y, bitofsign(a0));
        }

        static inline A0 cota(const A0& a0, const regular&)
        {
          if (nt2::is_invalid(a0)||redu_t::cot_invalid(a0)) return Nan<A0>();
          const A0 x = nt2::abs(a0);
          const A0 bos =  bitofsign(a0);
          if (!a0) return b_or(Inf<A0>(), bos);
          A0 xr = Nan<A0>(), xc;
          const int_type n = redu_t::reduce(x, xr, xc);
          const A0 y = eval_t::cot_eval(xr, xc, 1-((n&1)<<1));
          return b_xor(y, bos);
        }

        static inline A0 sincosa(const A0& a0,  A0& c, const regular&)
        {
          A0 s; 
          if (is_invalid(a0)) { c = Nan<A0>(); return c; }
          const A0 x =  nt2::abs(a0);
          static const sint_type de = static_cast<sint_type>(sizeof(sint_type)*8-1);
          A0 xr, xc;
          const int_type n = redu_t::reduce(x, xr, xc);
          const int_type swap_bit = n&One<int_type>();
          const A0 z = sqr(xr);
          const int_type cos_sign_bit = shli(b_xor(swap_bit, (n&Two<int_type>())>>1), de);
          const A0 sin_sign_bit = b_xor(bitofsign(a0), shli(n&Two<int_type>(), de-1));
          
          if (is_nez(swap_bit))
            {
              c = eval_t::sin_eval(z, xr, xc);
              s = eval_t::cos_eval(z, xr, xc);
            }
          else
            {
              c = eval_t::cos_eval(z, xr, xc);
              s = eval_t::sin_eval(z, xr, xc);
            }
          c = b_xor(c,cos_sign_bit);
          return b_xor(s,sin_sign_bit);
        }

        static inline A0 cosa(const A0& a0, const fast &)
        {
          A0 x =  scale(a0); 
          if(not_in_range(a0))
            return Nan<A0>();
          else
            return eval_t::cos_eval(sqr(x), x, Zero<A0>());
        }

        
        static inline A0 sina(const A0& a0, const fast&)
        {
          A0 x =  scale(a0); 
          if(not_in_range(a0))
            return Nan<A0>();
          else
            return eval_t::sin_eval(sqr(x), x, Zero<A0>());
        }

        static inline A0 tana(const A0& a0, const fast&)
        {
          A0 x =  scale(a0); 
          if(not_in_range(a0))
            return Nan<A0>();
          else
            return eval_t::base_tan_eval(x);
        }         
        static inline A0 cota(const  A0& a0, const fast&)
        {
          A0 x =  scale(a0); 
          if(not_in_range(a0))
            return Nan<A0>();
          else
            return rec(eval_t::base_tan_eval(x));
        }


        static inline A0 sincosa(const A0& a0, A0& c, const fast&)
        {
          if(not_in_range(a0)){c = Nan<A0>(); return c; }
          A0 x =  scale(a0);
          A0 z =  sqr(x); 
          c = eval_t::cos_eval(z, x, Zero<A0>());
          return eval_t::sin_eval(z, x, Zero<A0>());  
        }
        
        static inline bool not_in_range(const A0& a0)
        {
          return nt2::abs(a0) > trig_ranges<A0,unit_tag>::max_range();
        }
        static inline A0 scale (const A0& a0)
        {
          return a0*trig_ranges<A0,unit_tag>::scale();
        }
        
      };
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of trig_base.hpp
// /////////////////////////////////////////////////////////////////////////////
