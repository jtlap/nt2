/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_SPLAT_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_SPLAT_HPP_INCLUDED

namespace nt2 { namespace functors
{
  template<class T, class X, class Info>
  struct  call<splat_<T>,tag::simd_(tag::ast_,X), fundamental_, Info>
        : callable
  {
    typedef T result_type;
    NT2_FUNCTOR_CALL(1) { T that(a0); return that; }
  };
} }

#endif
