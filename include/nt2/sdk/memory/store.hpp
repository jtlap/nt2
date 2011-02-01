/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_STORE_HPP_INCLUDED
#define NT2_SDK_MEMORY_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Store a value in memory functor and function
// Documentation: http://nt2.lri.fr/sdk/memory/function/store.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2
{
  namespace tag { struct store_ {}; }
  NT2_FUNCTION_IMPLEMENTATION(tag::store_,store,3)
}

#include <nt2/sdk/memory/details/store.hpp>

#endif
