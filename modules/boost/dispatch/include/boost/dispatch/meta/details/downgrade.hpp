//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_DOWNGRADE_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_DOWNGRADE_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/sign_of.hpp>
#include <boost/dispatch/meta/make_integer.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template< class Type
          , class Sign  = typename meta::
                          sign_of < typename meta::strip<Type>::type >::type
          >
  struct  downgrade;
} } }

namespace boost { namespace dispatch { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Scalar arithmetic types are downgraded using make_integer unless they're
  // floating point types
  //////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t Size, class Sign, class Lambda>
  struct downgrade_impl : meta::make_integer<Size/2,Sign,Lambda>
  {};

  template<class Sign, class Lambda>
  struct downgrade_impl<double,sizeof(double),Sign, Lambda>
  {
    typedef typename boost::mpl::apply1<Lambda, float>::type type;
  };

  template<class Sign, class Lambda>
  struct downgrade_impl<float,sizeof(float),Sign, Lambda>
  {
    typedef typename boost::mpl::apply1<Lambda, float>::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // If type size is 1, return the type itself for any category
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Sign, class Lambda>
  struct  downgrade_impl<T,1,Sign, Lambda>
        : meta::make_integer<1,Sign, Lambda> {};
} } }


#endif

