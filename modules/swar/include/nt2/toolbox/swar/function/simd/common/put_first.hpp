//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_PUT_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_PUT_FIRST_HPP_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0)(A1)(X),
                            ((simd_<arithmetic_<A0>,X>))
                            ((integer_<A1>))
                           );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::put_first_(tag::simd_<tag::arithmetic_, X> ,
                              tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      
      NT2_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
      tmp[0] = a0[a1];
      for(A1 i = 1; i != meta::cardinal_of<A0>::value; ++i)
        tmp[i] = a0[i];
      
      return load<A0>(&tmp[0], 0);
    }
  };
} }

#endif
