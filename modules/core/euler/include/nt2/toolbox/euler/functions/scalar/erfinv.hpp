//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_ERFINV_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_ERFINV_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/erfinv.hpp>
#include <nt2/include/functions/scalar/polevl.hpp>
#include <nt2/include/functions/scalar/erf.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/constants/sqrtpio_2.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfinv_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::erfinv(result_type(a0));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfinv_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    // This is inspired from scilab
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        static const boost::array<A0, 4 > a = {{
            A0(-0.14110320437680104),
            A0(0.92661860147244357),
            A0(-1.6601283962374516),
            A0(0.88622692374517353)
          }};
        static const boost::array<A0, 5 > b = {{
            A0( 0.01197270616590528),
            A0(-0.33198239813321595),
            A0( 1.46060340345661088),
            A0(-2.13505380615258078),
            A0(1)
          }};
        
        static const boost::array<A0, 4 > c = {{
            A0(1.82365845766309853),         
            A0(3.60874665878559364), 
            A0(  -1.87267416351196),  
            A0( -1.994216456587148) 
          }};
        static const boost::array<A0, 3 >d = {{
            A0(1.81848952562894617),
            A0(3.74146294065960872),
            A0(1)
          }};
        
        A0 x =  nt2::abs(a0);
        A0 res; 
        if(is_nan(a0)||(x>One<A0>())) return Nan<A0>();
        if(x == One<A0>()) return a0*Inf<A0>();  
        if(x<= A0(0.7))
          {
            //       a1*y + a2*y^3 + a3*y^5 + a4*y^7
            //res= --------------------------------------
            //     1 + b1*y^2 + b2*y^4 + b3*y^6 + b4*y^8
            
            A0 xx =  sqr(x);
            res =  a0*polevl(xx, a)/polevl(xx, b);
          }
        else
          {
            // 0.7 < x < 1
            //       c1 + c2*z + c3*z^2 + c4*z^3
            //  x= ------------------------------ ; z = sqrt(-log(1-y)/2)
            //         1 + d1*z + d2*z^2
            // -1 < y < 0.7
            //      - c1 - c2*z - c3*z^2 - c4*z^3
            //  x= ------------------------------ ; z = sqrt(-log(1+y)/2)
            //         1 + d1*z + d2*z^2
            A0 sign = nt2::is_ltz(a0)?Mone<A0>():One<A0>(); 
            A0 z = nt2::sqrt(-nt2::log(nt2::oneminus(sign*a0)*Half<A0>()));
            res =  sign*polevl(z, c)/polevl(z, d); 
          }
         res -= (nt2::erf(res)-a0)*Sqrtpio_2<A0>()/nt2::exp(-nt2::sqr(res));
         res -= (nt2::erf(res)-a0)*Sqrtpio_2<A0>()/nt2::exp(-nt2::sqr(res));
         return res; 
      }
  };
} }
       
#endif
