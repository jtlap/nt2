//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_AS_SIGNED_HPP_INCLUDED
#define NT2_SDK_META_AS_SIGNED_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements \ref nt2::meta::as_signed
 */

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_signed.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template<class T, class Enable = void>
  struct  as_signed;
} }

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   *
   * Returns the input type rebound the signed equivalent type to its primitive
   * type.
   *
   * \tparam T Type to modify
   *
   * \par Models:
   *
   * \metafunction
   *
   * \par Semantic:
   *
   * For any type \c T,
   *
   * \code
   * typedef as_signed<T>::type type;
   * \endcode
   *
   * is equivalent to
   *
   * \code
   * typedef T  type;
   * \endcode
   *
   * if \c primitive<T>::type is \c signed and to
   *
   * \code
   *  typedef apply< meta::factory_of<T>::type
   *               , boost::make_signed< meta::primitive_of<T>::type >::type
   *               >::type                                                type;
   * \endcode
   *
   * if \c primitive<T>::type is unsigned.
   *
   * \par Example usage:
   *
   * \include as_signed.cpp
   */
  //============================================================================
  template<class T>
  struct  as_signed
        : details::as_signed < typename meta::strip<T>::type >
  {
    NT2_STATIC_ASSERT
    ( (is_fundamental < typename
                        meta::primitive_of<typename meta::strip<T>::type>::type
                      >::value
      )
    , NT2_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_SIGNED
    , "A type with a non-fundamental primitive is used in nt2::meta::as_signed."
    );
  };
} }

namespace nt2 { namespace details
{
  template<class T, class Enable>
  struct  as_signed
        : boost::mpl::apply < typename meta::factory_of<T>::type
                            , typename meta::
                              as_signed< typename meta::primitive_of<T>::type
                                       >::type
                            >
  {};

  template<class T>
  struct  as_signed < T
                    , typename boost::enable_if < typename meta::
                                                  is_fundamental<T>::type
                                                >::type
                    >
       : boost::mpl::eval_if< boost::mpl::
                              bool_ <   boost::is_integral<T>::value
                                    &&  !boost::is_same<bool,T>::value
                                    >
                            , boost::make_signed<T>
                            , boost::mpl::identity<T>
                            > {};
} }

#endif
