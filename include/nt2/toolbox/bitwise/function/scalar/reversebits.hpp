//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_REVERSEBITS_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_REVERSEBITS_HPP_INCLUDED


namespace nt2 { namespace functors
{

  //  no special validate for reversebits

  /////////////////////////////////////////////////////////////////////////////
  // Compute reversebits(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<reversebits_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

      NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0, 
      (4, (int64_, int32_, int16_, int8_))
    )

      NT2_FUNCTOR_CALL_EVAL_IF(1,       int8_)
      {
	typedef union { A0 a; uint8_t b; } trick;
	trick z = {a0}; 
	z.b = ((z.b * 0x0802LU & 0x22110LU) | (z.b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
	return z.a; 
      }
      NT2_FUNCTOR_CALL_EVAL_IF(1,       int16_)
      {
	typedef union { A0 a; uint8_t b[2]; } trick;
	trick z = {a0}; 
	z.b[0] = reversebits(z.b[0]);
	z.b[1] = reversebits(z.b[1]);
	std::swap(z.b[0], z.b[1]); 
	return z.a; 
      }
      NT2_FUNCTOR_CALL_EVAL_IF(1,       int32_)
      {
	typedef union { A0 a; uint16_t b[2]; } trick;
	trick z = {a0}; 
	z.b[0] = reversebits(z.b[0]);
	z.b[1] = reversebits(z.b[1]);
	std::swap(z.b[0], z.b[1]); 
	return z.a; 
      }
      NT2_FUNCTOR_CALL_EVAL_IF(1,       int64_)
      {
	typedef union { A0 a; uint32_t b[2]; } trick;
	trick z = {a0}; 
	z.b[0] = reversebits(z.b[0]);
	z.b[1] = reversebits(z.b[1]);
	std::swap(z.b[0], z.b[1]);
	return z.a; 
      }

  };
} }


      
#endif
