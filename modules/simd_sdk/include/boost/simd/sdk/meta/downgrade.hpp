//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_DOWNGRADE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the \ref boost::simd::meta::downgrade \metafunction
 */

#include <boost/mpl/apply.hpp>
#include <boost/simd/sdk/meta/strip.hpp>
#include <boost/simd/sdk/meta/sign_of.hpp>
#include <boost/simd/sdk/meta/factory_of.hpp>
#include <boost/simd/sdk/meta/make_integer.hpp>
#include <boost/simd/sdk/meta/primitive_of.hpp>
#include <boost/simd/sdk/meta/is_fundamental.hpp>
#include <boost/simd/sdk/meta/details/downgrade.hpp>

namespace boost { namespace simd {  namespace meta
{
  //============================================================================
  /*!
   * Returns the input type rebound with a type that is twice as small as
   * its primitive, with optional sign change.\
   *
   * \tparam Type Hierarchizable type to downgrade.
   * \tparam Sign Optional sign to use while downgrading \c Type. If unspecified,
   * \c Sign is equals to the sign of \c Type.
   *
   * \par Models:
   *
   * \metafunction
   *
   * \semantic
   *
   * \code
   * typedef boost::simd::meta::downgrade<T, Sign>::type r;
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   * typedef make_real< max< sizeof(primitive_of<T>::type)/2
   *                       , sizeof(float)
   *                       >::value
   *                  , factory_of<T>::type
   *                  >::type                                  r;
   * \endcode
   *
   * if \c primitive_of<T> is of hierarchy \ref boost::simd::tag::real_ and to:
   *
   * \code
   * typedef make_integer< max<sizeof(primitive_of<T>::type)/2, 1>::value
   *                     , Sign
   *                     , factory_of<T>::type
   *                     >::type                                r;
   * \endcode
   *
   * otherwise.
   *
   * \usage
   *
   * \include downgrade.cpp
   */
  //============================================================================
  template< class Type, class Sign>
  struct  downgrade
        : details::downgrade_impl
          < typename meta::primitive_of<typename meta::strip<Type>::type>::type
          , sizeof(typename meta::primitive_of
                            < typename meta::strip<Type>::type >::type
                  )
          , Sign
          , typename meta::factory_of<typename meta::strip<Type>::type>::type
          >
  {
    BOOST_SIMD_STATIC_ASSERT
    ( ( is_fundamental
        < typename meta::primitive_of<typename meta::strip<Type>::type>::type
        >::value
      )
    , BOOST_SIMD_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_DOWNGRADE
    , "A type with a non-fundamental primitive is used in boost::simd::meta::downgrade"
    );
  };

} } }

#endif

