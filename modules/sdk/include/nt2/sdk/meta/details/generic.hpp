//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_GENERIC_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_GENERIC_HPP_INCLUDED

#include <nt2/sdk/meta/details/hierarchy_base.hpp>

namespace nt2 { namespace meta
{
  template<class T> struct generic_ : generic_< typename T::parent >
  {
    typedef generic_< typename T::parent >  parent;
    typedef typename T::origin              origin;
  };

  template<class T> struct generic_< unspecified_<T> > : unspecified_<T>
  {
    typedef unspecified_<T> parent;
    typedef T               origin;
  };

  template<class T> struct generic_< unknown_<T> > : unknown_<T>
  {
    typedef unknown_<T> parent;
    typedef T           origin;
  };
} }

#endif
