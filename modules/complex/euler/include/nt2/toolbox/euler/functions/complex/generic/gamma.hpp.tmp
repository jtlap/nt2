//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_COMPLEX_GENERIC_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_COMPLEX_GENERIC_GAMMA_HPP_INCLUDED
#include <nt2/toolbox/euler/functions/gamma.hpp>

#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/include/functions/is_ltz.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamma_, tag::cpu_
                            , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        typedef typename meta::as_real<A0>::type rtype;
        typedef typename meta::as_integer<rtype, signed>::type itype; 
        typedef typename meta::as_logical<rtype>::type ltype; 
        const rtype Log2pi = nt2::log(Two<rtype>()*Pi<rtype>()); //TODO
        const rtype a[] = {
          8.333333333333333e-02,
          -2.777777777777778e-03,
          7.936507936507937e-04,
          -5.952380952380952e-04,
          8.417508417508418e-04,
          -1.917526917526918e-03,
          6.410256410256410e-03,
          -2.955065359477124e-02,
          1.796443723688307e-01,
          -1.39243221690590};
        
        ltype ltz_x =  is_ltz(real(a0));
        rtype x = nt2::abs(real(a0));
        rtype y = negif(ltz_x, imag(a0));
        
        rtype x0 = x;
        ltype ltx7 = lt(x, Seven<rtype>()); 
        rtype na = if_else_zero(ltx7, nt2::trunc(Seven<rtype>()-x)); 
        x0 = x+na;
        rtype q1 = hypot(x0, y);
        rtype th = atan(y/x0);
        rtype logq1 = nt2::log(q1); 
        rtype gr = (x0-Half<rtype>())*logq1-th*y-x0+Half<rtype>()*Log2pi;
        rtype gi = th*(x0-Half<rtype>())+y*logq1-y;
        rtype  tkp1th = th;
        th2 =  th+th; 
        for (int32_t k=0;k<10;k++){
          t = nt2::pow(q1,-1-2*k);
          rtype s, c;
          sincos(tkp1th, s, c); 
          gr += (a[k]*t*c);
          gi -= (a[k]*t*s);
          tkp1th+= th2;             
        }
        rtype gr1 = Zero<rtype>;
        rtype gi1 = Zero<rtype>;
        int32_t max_na = maximum(na); 
        for (j=0;j<max_na;j++)
          {
            rtype rj =  nt2::splat<rtype>(j);
            ltnaj = lt(rj, na); 
            gr1 = seladd(ltnaj, gr1, (Half<rtype>()*log((x+j)*(x+j)+y*y))); 
            gi1 = seladd(ltnaj, gi1, atan(y/(x+rj)));
          }
        gr -= gr1;
        gi -= gi1;
        //case real(a0) < 0
        //    if (x1 <= 0.0) {
        q1 =  nt2::abs(a0);
        th1 = nt2::arg(a0); 
        result_type r = -sinpi(a0); 
        rtype  q2 = nt2::abs(r);
        rtype  th2= nt2::arg(r);
        
        gr = if_else(ltz_x, log(PI<rtype>()/(q1*q2))-gr, gr);
        gi = if_else(ltz_x, -th1-th2-gi, gi);
        result_type g = result_type(gr,gi);
        
        //    g =  if_else( gt(x, Max_gamma<rtype>()), Inf<result_type>(), g); 
        //     if ((y == 0.0) && (x == (int)x) && (x <= 0.0))
        return g; 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamma_, tag::cpu_
                            , (A0)
                            , (generic_< imaginary_<floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type             rtype; 
    typedef typename meta::as_complex<rtype>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::gamma(result_type(Zero<rtype>, imag(a0)); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamma_, tag::cpu_
                            , (A0)
                            , (generic_< dry_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::gamma(real(a0))); 
    }
  };  
} }


#endif
