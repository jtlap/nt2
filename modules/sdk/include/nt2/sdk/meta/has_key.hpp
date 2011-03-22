/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_HAS_KEY_HPP_INCLUDED
#define NT2_SDK_META_HAS_KEY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Check if a type T is a member of set S
// See: http://nt2.metascale.org/sdk/meta/set/has_key.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/typeof/typeof.hpp>

namespace nt2 { namespace meta
{
  template<class S,class K> struct has_key
  {
    static K* keyptr;
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, S::key(keyptr) )
    typedef typename nested::type type;
    BOOST_STATIC_CONSTANT( bool, value = type::value );
  };
} }

#endif
