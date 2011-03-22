//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_SELSUB_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_SELSUB_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF(tag::selsub_, tag::cpu_,
			 (A0)(A1)(X),
			 (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
			 (tag::selsub_(tag::simd_<tag::arithmetic_,X>,
					       tag::simd_<tag::arithmetic_,X>,
					       tag::simd_<tag::arithmetic_,X>)), 
			 ((simd_<arithmetic_<A0>,X>))
			 ((simd_<arithmetic_<A1>,X>))
			 ((simd_<arithmetic_<A1>,X>))
			 ); 

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::selsub_(tag::simd_<tag::arithmetic_, X> ,
                           tag::simd_<tag::arithmetic_, X> ,
                           tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1,A1)>: meta::strip<A1>{};

    NT2_FUNCTOR_CALL(3)
    {
     return a1 - b_and(a2,a0);
    }

  };
} }

#endif
// modified by jt the 04/01/2011
