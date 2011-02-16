/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_AS_UNSIGNED_HPP_INCLUDED
#define NT2_SDK_META_AS_UNSIGNED_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Returns the input type rebound with the equivalent unsigned type of its primitive type.
// See: http://nt2.metascale.org/sdk/meta/traits/as_unsigned.html
//////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>

namespace nt2 { namespace meta
{
  template<class T> struct as_unsigned;
} }

namespace nt2 { namespace details
{
  template<class T, class Enable = void>
  struct  as_unsigned
        : boost::mpl::apply < typename meta::factory_of<T>::type
                            , typename meta::
                              as_unsigned < typename meta::primitive_of<T>::type
                                          >::type
                            >
  {};

  template<class T>
  struct  as_unsigned < T
                      , typename boost::enable_if < typename meta::
                                                    is_fundamental<T>::type
                                                  >::type
                      >
       : boost::mpl::eval_if< boost::mpl::
                              bool_ <   boost::is_integral<T>::value
                                    &&  !boost::is_same<bool,T>::value
                                    >
                            , boost::make_unsigned<T>
                            , boost::mpl::identity<T>
                            > {};
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn any type into its integral equivalent
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  as_unsigned
        : details::as_unsigned < typename meta::strip<T>::type >
  {
    NT2_STATIC_ASSERT ( (is_fundamental<typename meta::primitive_of<typename meta::strip<T>::type>::type>::value)
                      , NT2_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_UNSIGNED
                      , "A type with a non-fundamental primitive is used in nt2::meta::as_unsigned."
                      );
  };
} }

#endif
