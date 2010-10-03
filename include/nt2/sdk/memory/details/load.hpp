/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_LOAD_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for scalar types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/category.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class T, int Offset, class Category, class Hierarchy, class Info>
  struct  call<load_<T,Offset>,tag::scalar_(Category), Hierarchy, Info>
        : callable
  {
    typedef T result_type;
    NT2_FUNCTOR_CALL(2) { return a0[a1+Offset]; }
  };
} }

#endif
