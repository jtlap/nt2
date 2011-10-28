//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_UPGRADE_HPP_INCLUDED
#define BOOST_DISPATCH_META_UPGRADE_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Returns the input type rebound with a type that is twice as big
// as its primitive, with optional sign.
// If the primitive type is floating-point, sign is ignored.
// See: http://nt2.metascale.org/sdk/meta/traits/upgrade.html
//////////////////////////////////////////////////////////////////////////////

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
  template<class T,class Sign = void> struct  upgrade;
} } }

namespace boost { namespace dispatch { namespace ext
{
  template<typename Type, typename Sign, typename Enable = void>
  struct upgrade
  {
    typedef typename meta::factory_of<Type>::type    lambda;
    typedef typename meta::primitive_of<Type>::type  base;
    typedef typename meta::upgrade<base,Sign>::type  up;
    typedef typename mpl::apply1<lambda, up>::type   type;   
  };
  
  template<typename T, typename Sign>
  struct upgrade< T, Sign
                , typename enable_if<typename is_integral<T>::type>::type
                >
  {
    typedef typename meta::factory_of<T>::type    lambda;
    typedef typename meta::primitive_of<T>::type  base;

    typedef typename mpl::eval_if < is_void<Sign>
                                  , meta::sign_of<T>
                                  , mpl::identity<Sign>
                                  >::type         sign;

    BOOST_STATIC_CONSTANT ( std::size_t
                          , size = (sizeof(base) < 8) ? sizeof(base)*2 : 8    
                          );

    typedef typename 
            meta::make_integer<size,sign,lambda>::type type;
  };

  template<typename T, typename Sign>
  struct upgrade< T, Sign
                , typename enable_if<typename is_floating_point<T>::type>::type
                >
  {
    typedef typename meta::factory_of<T>::type    lambda;
    typedef typename meta::primitive_of<T>::type  base;

    BOOST_STATIC_CONSTANT ( std::size_t
                          , size = (sizeof(base) < 8) ? sizeof(base)*2 : 8    
                          );

    typedef typename meta::make_floating<size,lambda>::type  type;
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For any type, return the integer type of size equals to sizeof(T)*2
  // with an optional sign change
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Sign>
  struct  upgrade : ext::upgrade<T, Sign > {};

  template<class T, class Sign> 
  struct upgrade<T&,Sign> : upgrade<T,Sign> {};

  template<class T, class Sign> 
  struct upgrade<T const,Sign> : upgrade<T,Sign> {};
} } }

#endif
