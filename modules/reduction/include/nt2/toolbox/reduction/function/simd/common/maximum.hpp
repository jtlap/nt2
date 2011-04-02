//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_MAXIMUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_MAXIMUM_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::maximum_, tag::cpu_,
                          (A0)(X),
                          ((simd_<arithmetic_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::maximum_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    { typedef typename meta::scalar_of<A0>::type type; };


    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      type r = a0[0];
      for(size_t i=1; i < meta::cardinal_of<A0>::value; i++)
      r = (r < a0[i]) ? a0[i] : r;
      return r;
    }

  };
} }

#endif
// modified by jt the 05/01/2011