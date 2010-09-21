//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_MANTISSA_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_MANTISSA_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>


namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<mantissa_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
             meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute mantissa(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<mantissa_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> {typedef A0 type; }; 


    NT2_FUNCTOR_CALL(1)
    {
	//TO DO incorrect
	if(!a0) return a0; 
        typedef typename meta::as_integer<A0, unsigned>::type int_type;
        static const int_type n1 = (((Maxexponent<A0>()<<1)+1)<< Nbmantissabits<A0>());
	static const int_type n2 = (sizeof(int_type)-2);
	static const int_type mask0 = ((n1<<2)>>2);
	static const int_type mask1 = ((~n1)|n2);
        return b_or(b_and(a0, mask1),mask0);
    }
  };
} }


      
#endif
