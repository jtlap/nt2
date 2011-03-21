//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SATURATE_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SATURATE_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/include/functions/select.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::saturate_<T>, tag::cpu_,
		      (A0)(T)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class T, class X, class Dummy>
  struct call<tag::saturate_<T>(tag::simd_<tag::arithmetic_,X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<T>::type stype;
      const A0 vma = splat<A0>(Valmax<stype>());
      const A0 vmi = splat<A0>(Valmin<stype>()); 
      return sel(gt(a0, vma), vma, sel(lt(a0, vmi), vmi, a0)); 
    }
  };
} }

#endif
