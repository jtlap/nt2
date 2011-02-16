/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_BEHAVE_AS_HPP_INCLUDED
#define NT2_SDK_META_BEHAVE_AS_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/error/static_assert.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>

namespace nt2 { namespace meta
{
  template<class Lambda,class T>
  struct  behave_as
        : boost::mpl::apply1< Lambda
                            , typename primitive_of<typename strip<T>::type>::type
                            >::type
  {
    NT2_STATIC_ASSERT ( (is_fundamental<typename meta::primitive_of<typename meta::strip<T>::type>::type>::value)
                      , NT2_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_BEHAVE_AS
                      , "A type with a non-fundamental primitive is used in nt2::meta::behave_as."
                      );
  };
} }

#endif
