//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_FLOATING_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_FLOATING_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements \ref boost::dispatch::meta::as_floating
 */

#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/make_floating.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>

namespace boost { namespace dispatch { namespace meta
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
   * \semantic
   *
   * For any type \c T,
   *
   * \code
   * typedef as_floating<T>::type type;
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   *  typedef make_floating< sizeof(primitive_of<T>::type)
   *                   , factory_of<T>::type
   *                   >::type                           type;
   * \endcode
   *
   * \par Example usage:
   *
   * \include as_floating.cpp
   */
  //============================================================================
  template<class A0, class A1 = void, class A2 = void>
  struct  as_floating;
  
  template<class T>
  struct  as_floating<T>
        : meta::
          make_floating < sizeof( typename meta::
                              primitive_of<typename meta::strip<T>::type>::type
                            )
                   , typename meta::
                              factory_of<typename meta::strip<T>::type>::type
                   >
  {
    //==========================================================================
    /*
     * A type with a non-fundamental primitive is used in 
     * boost::dispatch::meta::as_floating.
     */    
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (is_fundamental < typename
                        meta::primitive_of<typename meta::strip<T>::type>::type
                      >::value
      )
    , BOOST_DISPATCH_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_REAL
    , (T&)
    );
  };
  
  template<class A0, class A1>
  struct  as_floating<A0, A1>
        : as_floating< typename mpl::
                       if_c< sizeof(typename meta::primitive_of<typename meta::strip<A0>::type>::type) < sizeof(typename meta::primitive_of<typename meta::strip<A1>::type>::type)
                           , A1
                           , A0
                           >::type
                     >
  {
  };
  
  template<class A0, class A1, class A2>
  struct  as_floating
        : as_floating< typename mpl::
                       if_c< sizeof(typename meta::primitive_of<typename meta::strip<A0>::type>::type) < sizeof(typename meta::primitive_of<typename meta::strip<A1>::type>::type)
                           , A1
                           , A2
                           >::type
                     , A2
                     >
  {
  };
  
} } }

#endif
