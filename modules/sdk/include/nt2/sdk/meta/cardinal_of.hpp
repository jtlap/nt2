/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_CARDINAL_OF_HPP_INCLUDED
#define NT2_SDK_META_CARDINAL_OF_HPP_INCLUDED

#include <boost/mpl/int.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
{
  template<class Type,class Hierarchy>
  struct cardinal_of_impl : boost::mpl::int_<1> {};
} }

namespace nt2 { namespace meta
{
  template<class T>
  struct  cardinal_of
        : details::cardinal_of_impl < typename meta::strip<T>::type
                                    , typename hierarchy_of<T>::type
                                    > {};
} }

#endif
