/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_META_SCALAR_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_SCALAR_OF_HPP_INCLUDED

#include <boost/simd/sdk/meta/strip.hpp>
#include <boost/simd/sdk/meta/hierarchy_of.hpp>

namespace boost { namespace simd {  namespace details
{
  template<class T, class Hierarchy> struct scalar_of_impl { typedef T type; };
} } }

namespace boost { namespace simd {  namespace meta
{
  template<class T>
  struct  scalar_of
        : details::scalar_of_impl < typename strip<T>::type
                                  , typename hierarchy_of<
                                                        typename strip<T>::type
                                                        >::type
                                  >
          {};
} } }

#endif
