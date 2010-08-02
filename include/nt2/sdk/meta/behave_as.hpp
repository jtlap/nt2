/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_BEHAVE_AS_HPP_INCLUDED
#define NT2_SDK_META_BEHAVE_AS_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <nt2/sdk/meta/category_of.hpp>

namespace nt2 { namespace details
{
  template<class Lambda,class Type,class Tag>
  struct behave_as_impl : boost::mpl::apply1<Lambda,Type>::type {};
} }

namespace nt2 { namespace meta
{
  template<class Lambda,class Type>
  struct behave_as : details::behave_as_impl<Lambda
                                            ,Type
                                            ,typename category_of<Type>::type
                                            > {};
} }

#endif
