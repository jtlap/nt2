/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_IEEE_SPEC_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_IEEE_SPEC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class Category,class Info>
  struct  call<constants::nb_mantissa_bits_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
				:	 meta::as_integer<typename meta::strip<A0>::type,signed> {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , ( 2 , ( double, float) )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1,float)
		{
			typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;
			return splat<typename A0::type>(23);
		}
		
    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
		{
			typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;
			return splat<typename A0::type>(52);
		}
  };

	template<class Category,class Info>
  struct  call<constants::nb_exponent_bits_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
				:	 meta::as_integer<typename meta::strip<A0>::type,signed> {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , ( 2 , ( double, float) )
                              )

		NT2_FUNCTOR_CALL_EVAL_IF(1,float)
		{
			typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;
			return splat<typename A0::type>(8);
		}
		
    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
		{
			typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;
			return splat<typename A0::type>(11);
		}
  };
	
	template<class Category,class Info>
  struct  call<constants::max_exponent_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
				:	 meta::as_integer<typename meta::strip<A0>::type,signed> {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , ( 2 , ( double, float) )
                              )

		NT2_FUNCTOR_CALL_EVAL_IF(1,float)
		{
			typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;
			return splat<typename A0::type>(127);
		}
		
    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
		{
			typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;
			return splat<typename A0::type>(1023);
		}
  };


	template<class Category,class Info>
  struct  call<constants::min_exponent_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
				:	 meta::as_integer<typename meta::strip<A0>::type,signed> {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , ( 2 , ( double, float) )
                              )

		NT2_FUNCTOR_CALL_EVAL_IF(1,float)
		{
			typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;
			return splat<typename A0::type>(-126);
		}
		
    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
		{
			typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;
			return splat<typename A0::type>(-1022);
		}
  };	
} }

#endif
