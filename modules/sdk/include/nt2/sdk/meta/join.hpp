/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_JOIN_HPP_INCLUDED
#define NT2_SDK_META_JOIN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Compute the lazy union of two types set
// See: http://nt2.metascale.org/sdk/meta/set/join.hpp
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/has_key.hpp>

namespace nt2 { namespace meta
{
  template<class H1,class H2> struct join
  {
    typedef void is_set_type;
    template<class T>
    static boost::mpl::bool_<   has_key<H1,T>::value
                            ||  has_key<H2,T>::value
                            >
    key(T*);
  };
} }

#endif
