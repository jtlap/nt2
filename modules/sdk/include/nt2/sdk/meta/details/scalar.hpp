//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_SCALAR_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_SCALAR_HPP_INCLUDED

#include <nt2/sdk/meta/details/generic.hpp>

namespace nt2 { namespace meta
{
  template<class T> struct scalar_ : scalar_< typename T::parent >
  {
    typedef scalar_< typename T::parent > parent;
    typedef typename T::origin            origin;
    typedef T                             base;
  };

  template<class T>
  struct  scalar_< unspecified_<T> >
        : generic_< typename unspecified_<T>::origin >
  {
    typedef generic_< typename unspecified_<T>::origin >  parent;
    typedef typename unspecified_<T>::origin              origin;
    typedef unspecified_<T>                               base;
  };
} }

#endif
