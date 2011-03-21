//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SATURATE_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SATURATE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/ieee/include.hpp>

namespace nt2
{
  
#define NT2_FUNCTION_IMPLEMENTATION_TPL(NAME,ARITY)		\
  template <class T, class A0>						\
  inline typename nt2::meta::enable_call<tag::NAME##_<T>(A0&)>::type \
  NAME(A0 const& a0){NT2_FUNCTION_BODY(tag::NAME##_<T>,ARITY)} \
    /**/
  
#define NT2_INNER_STRUCT(T, NAME, SUF)			\
  template<class A0> struct inner_##NAME < A0, T>		\
  {								\
    static inline typename NT2_RETURN_TYPE(1)::type		\
      eval(A0 const& a0,T const&){ return NAME##_##SUF(a0);}	\
  };								\
  /**/
}


namespace nt2 {
  namespace tag
  {
    template <class T> struct saturate_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION_TPL(saturate, 1)
}

#include <nt2/toolbox/ieee/function/scalar/saturate.hpp>
#include NT2_IEEE_INCLUDE(saturate.hpp) 

#endif
