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
// Documentation: http://nt2.lri.fr/sdk/meta/has_key.hpp
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class S,class K> struct has_key : S::template has_key<K> {};
} }

#endif
