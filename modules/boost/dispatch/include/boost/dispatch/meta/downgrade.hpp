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
#include <boost/mpl/always.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/sign_of.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/make_integer.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/make_floating.hpp>

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
   * if \c primitive_of<T> is of hierarchy \ref boost::dispatch::tag::floating_ 
   * and to:
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
  template< class T, class Sign = void> struct  downgrade;
} } }

namespace boost { namespace dispatch { namespace ext
{
  template<typename Type, typename Sign, typename Enable = void>
  struct downgrade
  {
    typedef typename meta::factory_of<Type>::type    lambda;
    typedef typename meta::primitive_of<Type>::type  base;
    typedef typename meta::downgrade<base,Sign>::type  up;
    typedef typename mpl::apply1<lambda, up>::type   type;   
  };
  
  template<typename T, typename Sign>
  struct downgrade< T, Sign
                  , typename enable_if<typename is_integral<T>::type>::type
                  >
  {
    typedef typename meta::factory_of<T>::type    lambda;
    typedef typename meta::primitive_of<T>::type  base;

    BOOST_MPL_ASSERT_MSG( (sizeof(base) > 1)
                        , TYPE_CAN_NOT_BE_DOWNGRADED
                        , (T)
                       );

    typedef typename mpl::eval_if < is_void<Sign>
                                  , meta::sign_of<T>
                                  , mpl::identity<Sign>
                                  >::type         sign;

    typedef typename meta::make_integer<sizeof(base)/2,sign,lambda>::type type;
  };

  template<typename T, typename Sign>
  struct downgrade< T, Sign
                  , typename enable_if<typename is_floating_point<T>::type>::type
                  >
  {
    typedef typename meta::factory_of<T>::type    lambda;
    typedef typename meta::primitive_of<T>::type  base;

    BOOST_MPL_ASSERT_MSG( (sizeof(base) > 4)
                        , TYPE_CAN_NOT_BE_DOWNGRADED
                        , (T)
                        );

    typedef typename meta::make_floating<sizeof(base)/2,lambda>::type  type;
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T,class Sign>
  struct  downgrade               : ext::downgrade<T, Sign> {};

  template<class T, class Sign> 
  struct downgrade<T&,Sign>       : downgrade<T,Sign> {};

  template<class T, class Sign> 
  struct downgrade<T const,Sign>  : downgrade<T,Sign> {};
} } }

#endif
