//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_BOOST_MATH_SPECIFIC_INTERFACE_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_SPECIFIC_INTERFACE_HPP_INCLUDED

namespace nt2
{

#define NT2_BOOST_MATH_FUNCTION_IMPLEMENTATION_TPL(NAME,ARITY)    \
  template <class T, class A0>            \
  inline typename nt2::meta::call<boost_math::tag::NAME##_<T>(A0 const&)>::type \
  NAME(A0 const& a0){NT2_FUNCTION_BODY(boost_math::tag::NAME##_<T>,ARITY)} \
    /**/

#define NT2_BOOST_MATH_INNER_STRUCT(T, NAME, SUF)      \
  template<class A0> struct inner_##NAME < A0, T>    \
  {                \
    static inline result_type    \
      eval(A0 const& a0,T const&){ return NAME##_##SUF(a0);}  \
  };                \
  /**/
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of interface.hpp
// /////////////////////////////////////////////////////////////////////////////
