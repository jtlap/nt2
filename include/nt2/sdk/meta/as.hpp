/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_AS_HPP_INCLUDED
#define NT2_SDK_META_AS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Type wrapper that acts *as* the type it boxes
//* TODO: Documentation: http://nt2.lri.fr/sdk/meta/helpers/as.html
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class T> struct as_ { typedef T type; };
} }

#endif
