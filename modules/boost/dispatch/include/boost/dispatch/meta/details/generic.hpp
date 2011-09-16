//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_GENERIC_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_GENERIC_HPP_INCLUDED

#include <boost/dispatch/meta/details/hierarchy_base.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct generic_ : generic_< typename T::parent >
  {
    typedef generic_< typename T::parent >  parent;
  };

  template<class T> struct generic_< unspecified_<T> > : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  template<class T> struct generic_< unknown_<T> > : unknown_<T>
  {
    typedef unknown_<T> parent;
  };
} } }

#endif
