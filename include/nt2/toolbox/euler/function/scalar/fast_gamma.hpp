//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_FAST_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_FAST_GAMMA_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/polevl.hpp>
#include <nt2/include/functions/stirling.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/is_eqz.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for fast_gamma

  /////////////////////////////////////////////////////////////////////////////
  // Compute fast_gamma(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<fast_gamma_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (real_,arithmetic_))
    )
//     NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
//     {
//       static boost::array< A0, 8> P = {{
// 	  1.536830450601906E-003,
// 	  5.397581592950993E-003,
// 	  4.130370201859976E-003,
// 	  7.232307985516519E-002,
// 	  8.203960091619193E-002,
// 	  4.117857447645796E-001,
// 	  4.227867745131584E-001,
// 	  9.999999822945073E-001
// 	}};
//       A0 x = a0, p, q;
//       int32_t sgngamf = 1;
//       bool negative = x < Zero<A0>();
//       A0 nz = Zero<A0>();
//       if( negative )
// 	{
//       //	  std::cout << "icitte " << std::endl; 
// 	  negative = 1;
// 	  q = -x;
// 	  p = floor(q);
// 	  if( p == q ) return Nan<A0>(); 
// 	  int32_t i = (int32_t)p;
// 	  if( is_even(i) ) sgngamf = -1;
// 	  nz = q - p;
// 	  if( nz > Half<A0>() )
// 	    {
// 	      p += One<A0>();
// 	      nz = q - p;
// 	    }
// 	  nz = q*sinpi(nz);
// 	  if( iseqz(nz) ) return Nan<A0>()*sgngamf;
// 	  nz =  nt2::abs(nz); 
// 	  x = q;
// 	}
//       A0 z; 
//          std::cout << "1--x "<< x << std::endl; 
//        if( x >= Ten<A0>() )  return stirling(x);
//       int direction = x < Two<A0>(); 
//       z = One<A0>();
//       //      int i = 0; 
//           std::cout << "1--x "<< x << std::endl; 
//       while( x >= Three<A0>() )
// 	{
//       //	  std::cout << "premier while : " << ++i << std::endl; 
// 	  x -= One<A0>();
// 	  z *= x;
// 	}
//       //      i = 0; 
//       //      std::cout << "2--x "<< x << std::endl; 
//       while( x < Two<A0>() )
// 	{
//       //	  std::cout << "second while : " << ++i << std::endl; 
// 	  if( iseqz(x)) return Nan<A0>(); 
// 	  if( x < 1.e-4 )
// 	    {
// 	      A0 p = z / ((One<A0>() + Euler<A0>() * x) * x);
// 	      return (negative) ? sgngamf * Pi<A0>()/(nz * p ) : p; 
// 	    }
// 	  z *=x;
// 	  x += One<A0>();
// 	}
//        //       std::cout << "3--x "<< x << std::endl; 
      
//       if( direction ) z = rec(z);
//       if( x == Two<A0>() ) return z;
//       x -= Two<A0>();
//       p = z * polevl( x, P);
//       //      std::cout << "4--p "<< p << " nz " <<  nz << std::endl; 
//       //      std::cout << "4--p "<< p << " negative " <<  negative << std::endl; 
      
     
//       return (negative) ? sgngamf * Pi<A0>()/(nz * p ) : p; 
//     }

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      static boost::array<A0, 7> P = {{
	  1.60119522476751861407E-4,
	  1.19135147006586384913E-3,
	  1.04213797561761569935E-2,
	  4.76367800457137231464E-2,
	  2.07448227648435975150E-1,
	  4.94214826801497100753E-1,
	  9.99999999999999996796E-1
	}};
      static boost::array<A0, 8>  Q = {{
	  -2.31581873324120129819E-5,
	  5.39605580493303397842E-4,
	  -4.45641913851797240494E-3,
	  1.18139785222060435552E-2,
	  3.58236398605498653373E-2,
	  -2.34591795718243348568E-1,
	  7.14304917030273074085E-2,
	  1.00000000000000000320E0
        }};
      A0 x = a0, p, z;
      int32_t sgngam = 1;
      if( isnan(x) || (x == Minf<A0>()) ) return Nan<A0>();
      if (x == Inf<A0>()) return x;
      A0 q = nt2::abs(x);	  
      if( q > 33.0 )
	{
	  if( isltz(x))
	    {
	      if (((p = floor(q)) == q)) return Nan<A0>(); 
	      int32_t i = (int32_t)p;
	      if( is_even(i) ) sgngam = -1;
	      z = q - p;
	      if( z > Half<A0>() )
		{
		  p += One<A0>();
		  z = q - p;
		}
	      z = q*sinpi(z);
	      if( iseqz(z) ) return Nan<A0>()*sgngam;
	      z = nt2::abs(z);
	      z = Pi<A0>()/(z * stirling(q) );
	    }
	  else
	    {
	      z = stirling(x);
	    }
	  return( sgngam * z );
	}
      
      z = One<A0>();
      while( x >= Three<A0>() )
	{
	  x -= One<A0>();
	  z *= x;
	}
      
      while( isltz(x) )
	{
	  if( x > -1.E-9 )
	    {
	     return z / ((One<A0>() + Euler<A0>() * x) * x);
	    }
	  z /= x;
	  x += One<A0>();
	}
      
      while( x < Two<A0>() )
	{
	  if( iseqz(x)) return Nan<A0>(); 
	  if( x < 1.e-9 )
	    {
	      return z / ((One<A0>() + Euler<A0>() * x) * x);
	    }
	  z /= x;
	  x +=  One<A0>();
	}
      
      if( x == Two<A0>() ) return(z);
      
      x -= Two<A0>();
      p = polevl(x,P);
      q = polevl(x,Q);
      return z*p/q;
    }
    
    
    
    
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      return fast_gamma(type(a0));
    }
//   private :
//     template < class A0 >  static inline A0
//     finalize(const A0 & x, const A0& negative, const A0& nz, const A0& sgngam, float)
//     {
//       static boost::array< A0, 8> P = {{
// 	  1.536830450601906E-003,
// 	  5.397581592950993E-003,
// 	  4.130370201859976E-003,
// 	  7.232307985516519E-002,
// 	  8.203960091619193E-002,
// 	  4.117857447645796E-001,
// 	  4.227867745131584E-001,
// 	  9.999999822945073E-001
// 	}};      
//       p = z * polevl( x, P);
//       return (negative) ? sgngamf * Pi<A0>()/(nz * p ) : p; 
//      }
//     template < class A0 >  static inline A0
//     finalize(const A0 & x, const A0& negative, const A0& nz, const A0& sgngam, double)
//     {
//       x -= Two<A0>();
//       p = polevl(x,P);
//       q = polevl(x,Q);
//       return z*p/q;
//     }
  };
} }


      
#endif
