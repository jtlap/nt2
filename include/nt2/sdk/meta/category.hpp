/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_CATEGORY_HPP_INCLUDED
#define NT2_SDK_META_CATEGORY_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// tag type for defining new category
// Documentation: http://nt2.lri.fr/sdk/meta/category/category.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/cstdint.hpp>

namespace nt2 { namespace tag
{
  template<class T, boost::uint32_t Family, boost::uint32_t Grain>
  struct category
  {
    typedef T type;
    static const boost::uint32_t rank = (  ( (Family << 24) & 0xFF000000  )
                                        | (Grain         & 0x00FFFFFF  )
                                        );
  };

  //////////////////////////////////////////////////////////////////////////////
  // Required to prevent spurrious link errors
  //////////////////////////////////////////////////////////////////////////////
  template<class T, boost::uint32_t Family, boost::uint32_t Grain>
  const boost::uint32_t category<T,Family,Grain>::rank;
} }

#endif
