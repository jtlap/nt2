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
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <nt2/sdk/meta/is_unspecified.hpp>

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn any type into its integral equivalent
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct as_real;
} }

namespace nt2 { namespace details
{
  template<class T, class Enable = void>
  struct  as_real
        : boost::mpl::apply < typename meta::factory_of<T>::type
                            , typename meta::
                              as_real< typename meta::primitive_of<T>::type >::type
                            >
  {};

  template<class T>
  struct  as_real < T
                  , typename boost::enable_if < typename meta::
                                                is_fundamental<T>::type
                                              >::type
                  >
       : meta::make_real<sizeof(T)> {};
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn any type into its integral equivalent
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  as_real
        : details::as_real < typename meta::strip<T>::type >
  {
    NT2_STATIC_ASSERT ( (!is_unspecified<T>::value)
                      , NT2_UNHIERARCHIZED_TYPE_USED_IN_META_AS_REAL
                      , "An unhierarchized type is used in nt2::meta::as_real."
                      );
  };
} }

#endif
