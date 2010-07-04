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

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Check if a type T is a member of set H
  //////////////////////////////////////////////////////////////////////////////
  template<class H,class K> struct has_key : H::template has_key<K> {};
} }

#endif
