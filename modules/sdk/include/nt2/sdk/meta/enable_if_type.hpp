/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_ENABLE_IF_TYPE_HPP_INCLUDED
#define NT2_SDK_META_ENABLE_IF_TYPE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// enable SFINAE on type definition
// Documentation: http://nt2.lri.fr/sdk/meta/helper/enable_if_type.html
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class T, class R=void>  struct enable_if_type { typedef R type; };
} }

#endif
