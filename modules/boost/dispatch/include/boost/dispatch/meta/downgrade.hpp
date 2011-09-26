//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_DISPATCH_META_DOWNGRADE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the \ref boost::dispatch::meta::downgrade \metafunction
 */

#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/sign_of.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/make_integer.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>
#include <boost/dispatch/meta/details/downgrade.hpp>

namespace boost { namespace dispatch { namespace meta
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
   * typedef boost::dispatch::meta::downgrade<T, Sign>::type r;
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   * typedef make_floating< max< sizeof(primitive_of<T>::type)/2
   *                       , sizeof(float)
   *                       >::value
   *                  , factory_of<T>::type
   *                  >::type                                  r;
   * \endcode
   *
   * if \c primitive_of<T> is of hierarchy \ref boost::dispatch::tag::floating_ and to:
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
  template< class T, class Sign>
  struct  downgrade
        : details::downgrade_impl
          < typename meta::primitive_of<typename meta::strip<T>::type>::type
          , sizeof(typename meta::primitive_of
                            < typename meta::strip<T>::type >::type
                  )
          , Sign
          , typename meta::factory_of<typename meta::strip<T>::type>::type
          >
  {
    //==========================================================================
    /*
     * A type with a non-fundamental primitive is used in 
     * boost::dispatch::meta::downgrade.
     */    
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (is_fundamental < typename
                        meta::primitive_of<typename meta::strip<T>::type>::type
                      >::value
      )
    , BOOST_DISPATCH_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_DOWNGRADE
    , (T&)
    );
  };
} } }

#endif

