//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_POPCNT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_POPCNT_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/bitwise_notand.hpp>
#include <nt2/include/functions/rem.hpp>
#include <iostream> 

namespace nt2 { namespace functors
{
  //  no special validate for popcnt

  /////////////////////////////////////////////////////////////////////////////
  // Compute popcnt(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<popcnt_, tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

      NT2_FUNCTOR_CALL_DISPATCH(
        1,
        typename nt2::meta::scalar_of<A0>::type,
        (4, (int64_, int32_, int16_, int8_))
      )
      NT2_FUNCTOR_CALL_EVAL_IF(1,       int64_)
      {
 	typedef typename NT2_CALL_RETURN_TYPE(1)::type    result_type;
	
	const result_type m1  = integral_constant<result_type,0x5555555555555555ULL>(); //binary: 0101...
	const result_type m2  = integral_constant<result_type,0x3333333333333333ULL>(); //binary: 00110011..
	const result_type m4  = integral_constant<result_type,0x0f0f0f0f0f0f0f0fULL>(); //binary:  4 zeros,  4 ones ...
	result_type x = simd::native_cast<result_type>(a0);
	x -= (shri(x, 1)) & m1;             //put count of each 2 bits into those 2 bits
	x = (x & m2) + (shri(x, 2) & m2); //put count of each 4 bits into those 4 bits 
	x = (x + shri(x, 4)) & m4;        //put count of each 8 bits into those 8 bits 
	x += shri(x, 8);  //put count of each 16 bits into their lowest 8 bits
	x += shri(x, 16);  //put count of each 32 bits into their lowest 8 bits
	x += shri(x, 32);  //put count of each 64 bits into their lowest 8 bits
	return x & integral_constant<result_type,0x7f > ();
      }

      NT2_FUNCTOR_CALL_EVAL_IF(1,       int32_)
      {
 	typedef typename NT2_CALL_RETURN_TYPE(1)::type    result_type;
	
	const result_type m1  = integral_constant<result_type,0x55555555>(); //binary: 0101...
	const result_type m2  = integral_constant<result_type,0x33333333>(); //binary: 00110011..
	const result_type m4  = integral_constant<result_type,0x0f0f0f0f>(); //binary:  4 zeros,  4 ones ...
	result_type x = simd::native_cast<result_type>(a0);
	x -= (shri(x, 1)) & m1;             //put count of each 2 bits into those 2 bits
	x = (x & m2) + (shri(x, 2) & m2); //put count of each 4 bits into those 4 bits 
	x = (x + shri(x, 4)) & m4;        //put count of each 8 bits into those 8 bits 
	x += shri(x, 8);  //put count of each 16 bits into their lowest 8 bits
	x += shri(x, 16);  //put count of each 32 bits into their lowest 8 bits
	return x & integral_constant<result_type,0x7f > ();
      }
      NT2_FUNCTOR_CALL_EVAL_IF(1,       int16_)
      {
 	typedef typename NT2_CALL_RETURN_TYPE(1)::type    result_type;
	
	const result_type m1  = integral_constant<result_type,0x5555>(); //binary: 0101...
	const result_type m2  = integral_constant<result_type,0x3333>(); //binary: 00110011..
	const result_type m4  = integral_constant<result_type,0x0f0f>(); //binary:  4 zeros,  4 ones ...
	result_type x = simd::native_cast<result_type>(a0);
	x -= (shri(x, 1)) & m1;             //put count of each 2 bits into those 2 bits
	x = (x & m2) + (shri(x, 2) & m2); //put count of each 4 bits into those 4 bits 
	x = (x + shri(x, 4)) & m4;        //put count of each 8 bits into those 8 bits 
	x += shri(x, 8);  //put count of each 16 bits into their lowest 8 bits
	return x & integral_constant<result_type,0x7f > ();
      }
      NT2_FUNCTOR_CALL_EVAL_IF(1,       int8_)
      {
 	typedef typename NT2_CALL_RETURN_TYPE(1)::type    result_type;
	
	const result_type m1  = integral_constant<result_type,0x55>(); //binary: 0101...
	const result_type m2  = integral_constant<result_type,0x33>(); //binary: 00110011..
	const result_type m4  = integral_constant<result_type,0x0f>(); //binary:  4 zeros,  4 ones ...
	result_type x = simd::native_cast<result_type>(a0);
	x -= (shri(x, 1)) & m1;             //put count of each 2 bits into those 2 bits
	x = (x & m2) + (shri(x, 2) & m2); //put count of each 4 bits into those 4 bits 
	x = (x + shri(x, 4)) & m4;        //put count of each 8 bits into those 8 bits 
	return x & integral_constant<result_type,0x7f > ();
      }
  };
} }

      
#endif
