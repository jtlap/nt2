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

//////////////////////////////////////////////////////////////////////////////
// Turn any type into its real equivalent
// See: http://nt2.metascale.org/sdk/meta/traits/as_real.html
//////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/make_real.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/is_unspecified.hpp>

namespace nt2 { namespace meta
{
  template<class T>
  struct  as_real
        : meta::make_real< sizeof(typename meta::primitive_of<typename meta::strip<T>::type>::type)
                         , typename meta::factory_of<typename meta::strip<T>::type>::type
                         >
  {
    NT2_STATIC_ASSERT ( (!is_unspecified<T>::value)
                      , NT2_UNHIERARCHIZED_TYPE_USED_IN_META_AS_REAL
                      , "An unhierarchized type is used in nt2::meta::as_real."
                      );
  };
} }

#endif
