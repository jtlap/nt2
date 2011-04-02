/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_SCALAR_OF_HPP_INCLUDED
#define NT2_SDK_META_SCALAR_OF_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
{
  template<class T, class Hierarchy> struct scalar_of_impl { typedef T type; };
} }

namespace nt2 { namespace meta
{
  template<class T>
  struct  scalar_of
        : details::scalar_of_impl < typename strip<T>::type
                                  , typename hierarchy_of<
                                                        typename strip<T>::type
                                                        >::type
                                  >
          {};
} }

#endif
