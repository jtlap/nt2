//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_AS_REAL_HPP_INCLUDED
#define NT2_SDK_META_AS_REAL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements \ref nt2::meta::as_real
 */

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/make_real.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   *
   * Returns the input type rebound with an floating-point type that has the same
   * size as its primitive type.
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
   * typedef as_real<T>::type type;
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   *  typedef make_real< sizeof(primitive_of<T>::type)
   *                   , factory_of<T>::type
   *                   >::type                           type;
   * \endcode
   *
   * \par Example usage:
   *
   * \include as_real.cpp
   */
  //============================================================================
  template<class T>
  struct  as_real
        : meta::
          make_real < sizeof( typename meta::
                              primitive_of<typename meta::strip<T>::type>::type
                            )
                   , typename meta::
                              factory_of<typename meta::strip<T>::type>::type
                   >
  {
    NT2_STATIC_ASSERT
    ( (is_fundamental < typename
                        meta::primitive_of<typename meta::strip<T>::type>::type
                      >::value
      )
    , NT2_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_REAL
    , "A type with a non-fundamental primitive is used in nt2::meta::as_real."
    );
  };
} }

#endif
