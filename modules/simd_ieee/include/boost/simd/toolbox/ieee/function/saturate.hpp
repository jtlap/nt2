//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SATURATE_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/simd/toolbox/ieee/include.hpp>

namespace boost { namespace simd
{
  
#define BOOST_SIMD_FUNCTION_IMPLEMENTATION_TPL(NAME,ARITY)		\
  template <class T, class A0>						\
  inline typename meta::call< tag::NAME##_<T> (A0 const &)>::type \
  NAME(A0 const& a0){BOOST_SIMD_FUNCTION_BODY(tag::NAME##_<T>,ARITY)} \
    /**/
  
#define BOOST_SIMD_INNER_STRUCT(T, NAME, SUF)			\
  template<class A0> struct inner_##NAME < A0, T>		\
  {								\
    static inline result_type		\
      eval(A0 const& a0,T const&){ return NAME##_##SUF(a0);}	\
  };								\
  /**/
} }


namespace boost { namespace simd {
  namespace tag
  {
    template <class T> struct saturate_ {};
  }
  BOOST_SIMD_FUNCTION_IMPLEMENTATION_TPL(saturate, 1)
} }

#include <boost/simd/toolbox/operator.hpp>
#include <boost/simd/toolbox/ieee/function/scalar/saturate.hpp>
#include <boost/simd/toolbox/ieee/function/simd/all/saturate.hpp> 

#endif
