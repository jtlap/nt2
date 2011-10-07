//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_CATEGORY_HPP_INCLUDED
#define NT2_CORE_CONTAINER_CATEGORY_HPP_INCLUDED

#include <boost/dispatch/meta/property_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Layout>
  struct container_ : container_< typename T::parent, Layout >
  {
    typedef container_<typename T::parent, Layout> parent;
  };

  template<class T, class Layout>
  struct container_< unspecified_<T>, Layout > : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

} } }

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::container_;
} }

#endif
