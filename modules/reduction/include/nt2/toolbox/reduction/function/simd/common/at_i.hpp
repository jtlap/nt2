//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_AT_I_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_AT_I_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ati_, tag::cpu_,
                     (A0)(A1)(X),
                     ((simd_<arithmetic_<A0>,X>))
                     (integer_<A1>)
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ati_(tag::simd_<tag::arithmetic_, X> ,
                       tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0, A1)>
          : meta::scalar_of<typename meta::strip<A0>::type>
    {};

    NT2_FUNCTOR_CALL(2) { return a0[a1]; }

  };
} }

#endif
