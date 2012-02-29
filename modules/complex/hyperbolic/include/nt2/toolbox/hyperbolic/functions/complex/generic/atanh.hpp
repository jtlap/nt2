//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_ATANH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_ATANH_HPP_INCLUDED
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/none.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/if_else.hpp> 
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/safe_max.hpp>
#include <nt2/include/functions/safe_min.hpp>

#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/smallestposval.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atanh_, tag::cpu_, (A0)
                            , (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      typedef typename meta::as_logical<rtype>::type ltype;
      typedef typename meta::as_integer<rtype>::type irtype;
        //
      // This implementation is a simd (i.e. no branch) transcription and adaptation of the 
      // boost_math code which itself is a transcription of the pseudo-code in:
      //
      // Eric W. Weisstein. "Inverse Hyperbolic Tangent." 
      // From MathWorld--A Wolfram Web Resource. 
      // http://mathworld.wolfram.com/InverseHyperbolicTangent.html
      //
      // Also: The Wolfram Functions Site,
      // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/
      //
      // Also "Abramowitz and Stegun. Handbook of Mathematical Functions."
      // at : http://jove.prohosting.com/~skripty/toc.htm
      //
      const rtype alpha_crossover = nt2::splat<rtype>(0.3);
      ltype  ltzra0 = is_ltz(real(a0));
      ltype  ltzia0 = is_ltz(imag(a0)); 
      rtype s_max = safe_max(Two<rtype>());
      rtype s_min = safe_min(Two<rtype>());
      rtype two =  Two<rtype>();
      rtype one =  One<rtype>();
      rtype inf =  Inf<rtype>();    
      rtype x = nt2::abs(real(a0));
      rtype y = nt2::abs(imag(a0));
     
      rtype r = Zero<rtype>();
      rtype i = Zero<rtype>(); 
      ltype gtxmax = gt(x,s_max);
      ltype ltxmin = lt(x,s_min);
      ltype gtymax = gt(y,s_max);
      ltype ltymin = lt(y,s_min);
      rtype xx = sqr(x);
      rtype yy = sqr(y);
      rtype sqrabs = xx + yy; 

      ltype not_in_safe_zone = logical_or(logical_or(gt(x,s_max), lt(x,s_min)),
                                          logical_or(gt(y,s_max), lt(y,s_min)));
      ltype invalid = is_invalid(a0);
      if(any(not_in_safe_zone))
        {
          //treat underflow or overflow
          // one or both of x and y are small, calculate divisor carefully:
          rtype div =  One<rtype>();
          div = if_else(ltxmin, div, div+xx);
          div = if_else(ltymin, div, div+yy);
          rtype alpha = x/div;
          alpha =  alpha+alpha; 
          
          ltype test =  gtymax;
          // Big y, medium x, divide through by y:
          rtype tmp_alpha = (two*x/y) / (y + xx/y);
          // Small x and y, whatever alpha is, it's too small to calculate:
          tmp_alpha = if_else_zero(gt(x, one), tmp_alpha); 
          alpha = if_else(logical_and(test, gt(x, one)), tmp_alpha, alpha);  
          
          test =  logical_andnot(gtxmax, test);
          
          // Big x small y, as above but neglect y^2/x:
          tmp_alpha =  two/x; 
          // Big x: divide through by x:
          tmp_alpha =  if_else(gt(y, one),  two / (x + y*y/x), tmp_alpha);
          // Big x and y: divide alpha through by x*y:
          tmp_alpha =  if_else(gtymax, (two/y) / (x/y + y/x), tmp_alpha);
          // Big x or y are infinite: the result is 0 
          tmp_alpha = if_zero_else(logical_or(eq(y,inf), eq(x, inf)), tmp_alpha);
          
          alpha = if_else(test, tmp_alpha, alpha);  
          r = if_else(lt(alpha, alpha_crossover),
                      nt2::log1p(alpha) - nt2::log1p(-alpha), 
                      nt2::log(one + two*x + xx) - std::log(sqr(x-one))
                      )/Four<rtype>();
          //compute the imaginary part
          // y^2 is negligible:
          i =  std::atan2(two*y, one - xx);
          i =  if_else(logical_or(gtymax, gtxmax), Pi<rtype>(), i);
          rtype tmp_i = if_else(ltymin, atan2(two*y, one),
                                nt2::atan2(two*y, one - yy));
          i =  if_else(ltxmin, tmp_i, i); 
        }
      ltype test = logical_and(eq(inf, x), eq(inf, y));
      if(any(test))
        {
          //inf x, inf y
          r = if_zero_else(test, r);
          i = if_else(test, Pi<rtype>(), r);
        }      
      test = is_nan(a0);
      
      if(any(test))
        {
          //nan x, inf y
          r = if_zero_else(logical_and(is_nan(x), eq(y, inf)), r);
          i = if_else(logical_and(is_nan(x), eq(y, inf)), Pi<rtype>(), r);
          
          r = if_zero_else(logical_and(is_nan(y), eq(x, inf)), r); 
          i = if_else(logical_and(is_nan(y), eq(x, inf)), y, i);

          r = if_zero_else(logical_and(is_nan(y), is_eqz(x)), r); 
          i = if_allbits_else(logical_and(is_nan(y), is_eqz(x)), i); 
       }
      //compute for safe zone
      // The real part is given by:
      // 
      // real(atanh(z)) == log((1 + x^2 + y^2 + 2x) / (1 + x^2 + y^2 - 2x))
      // 
      // However, when x is either large (x > 1/E) or very small
      // (x < E) then this effectively simplifies
      // to log(1), leading to wildly inaccurate results.  
      // By dividing the above (top and bottom) by (1 + x^2 + y^2) we get:
      //
      // real(atanh(z)) == log((1 + (2x / (1 + x^2 + y^2))) / (1 - (-2x / (1 + x^2 + y^2))))
      //
      // which is much more sensitive to the value of x, when x is not near 1
      // (remember we can compute log(1+x) for small x very accurately).
      //
      // The cross-over from one method to the other has to be determined
      // experimentally, the value used below appears correct to within a 
      // factor of 2 (and there are larger errors from other parts
      // of the input domain anyway).
      //
      rtype alpha = x*Two<rtype>() / (oneplus(sqrabs));
      rtype sqrxm1 = sqr(minusone(x));
      rtype tmp_r = if_else(lt(alpha, alpha_crossover), 
                             log1p(alpha) - log1p(-alpha), 
                             log1p(x+x + sqrabs) - log(sqrxm1 + yy)
                             )/Four<rtype>();
      r = if_else(not_in_safe_zone, r, tmp_r);

      // compute the imaginary part
      i =if_else(not_in_safe_zone,
                 i,
                 nt2::atan2(y+y, (oneminus(sqrabs)))
                 )*Half<rtype>();
      
      r = negif( ltzra0,r);
      i = negif( ltzia0,i); 
      return result_type(r, i); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atanh_, tag::cpu_, (A0)
                              , (generic_< imaginary_< arithmetic_<A0> > >)
                              )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<A0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        rtype y = oneplus(sqr(imag(a0)));
        A0 res = nt2::log(A0(nt2::sqrt(y))+a0);
        return res;     
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atanh_, tag::cpu_, (A0)
                              , (generic_< dry_< arithmetic_<A0> > >)
                              )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<A0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
      {
      if (nt2::all(is_real(a0)) && nt2::all(le(nt2::abs(a0), One<rtype>())))
        return result_type(nt2::atanh(real(a0))); 
      return nt2::atanh(result_type(real(a0), Zero<rtype>()));
      }
  };
  
} }
                           
#endif
                           
