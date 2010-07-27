/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_SPLAT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_SPLAT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// splat for scalar types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class T, class Category, class Info>
  struct call<splat_<T>,tag::scalar_(Category), Info>
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(1)
    {
      T that = static_cast<T>(a0);
      return that;
    }
  };
} }

#endif
