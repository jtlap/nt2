/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_AS_REAL_HPP_INCLUDED
#define NT2_SDK_META_AS_REAL_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/make_real.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
{
  template<class T, class Hierarchy>
  struct as_real : meta::make_real<sizeof(T)> {};
} }

namespace nt2 { namespace meta
{
  template<class T>
  struct as_real : details::as_real < typename meta::strip<T>::type
                                    , typename hierarchy_of<T>::type
                                    > {};
} }

#endif
