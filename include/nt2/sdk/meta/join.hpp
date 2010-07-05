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
// Documentation: http://nt2.lri.fr/sdk/meta/join.hpp
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class H1,class H2> struct join
  {
    typedef void is_set_type;
    template<class T,class X=void>
    struct  has_key
          : boost::mpl::bool_ <   H1::template has_key<T>::value
                              ||  H2::template has_key<T>::value
                              >
    {};
  };
} }

#endif
