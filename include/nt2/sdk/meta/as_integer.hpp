/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_AS_INTEGER_HPP_INCLUDED
#define NT2_SDK_META_AS_INTEGER_HPP_INCLUDED

#include <nt2/sdk/meta/sign_of.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/make_integer.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <nt2/sdk/meta/is_unspecified.hpp>

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn any type into its integral equivalent
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Sign = typename meta::sign_of<T>::type >
  struct as_integer;
} }

namespace nt2 { namespace details
{
  template<class T, class Sign, class Enable = void>
  struct  as_integer
        : boost::mpl::apply < typename meta::factory_of<T>::type
                            , typename meta::
                              as_integer< typename meta::primitive_of<T>::type
                                        , Sign
                                        >::type
                            >
  {};

  template<class T, class Sign>
  struct  as_integer< T
                    , Sign
                    , typename boost::enable_if < typename meta::
                                                  is_fundamental<T>::type
                                                >::type
                    >
       : meta::make_integer<sizeof(T),Sign> {};
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn any type into its integral equivalent
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Sign>
  struct  as_integer
        : details::as_integer < typename meta::strip<T>::type
                              , Sign
                              >
  {
    NT2_STATIC_ASSERT ( (!is_unspecified<T>::value)
                      , NT2_UNHIERARCHIZED_TYPE_USED_IN_META_AS_INTEGER
                      , "An unhierarchized type is used in nt2::meta::as_integer."
                      );
  };
} }

#endif

