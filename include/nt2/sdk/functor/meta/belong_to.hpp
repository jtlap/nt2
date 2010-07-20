/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_META_BELONG_TO_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_BELONG_TO_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Check if a type "belong to" another aka is the first a key in the second one
// if it's an AssociativeSequence, or are they the same otherwise
// Documentation: http://nt2.lri.fr/sdk/functor/meta/belong_to.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/meta/is_set.hpp>

namespace nt2 { namespace details
{
  template<class T, class S, bool Enable>
  struct belong_to_impl;

  template<class T, class S>
  struct belong_to_impl<T,S,false> : boost::mpl::false_ {};

  template<class T>
  struct belong_to_impl<T,T,false> : boost::mpl::true_ {};

  template<class T, class S>
  struct belong_to_impl<T,S,true> : meta::has_key<S,T> {};
} }

namespace nt2 { namespace meta
{
  template<class T, class S>
  struct  belong_to
        : details::belong_to_impl<T,S,meta::is_set<S>::value> {};
} }

#endif
