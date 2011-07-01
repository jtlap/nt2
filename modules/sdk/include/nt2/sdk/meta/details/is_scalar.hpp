//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_IS_SCALAR_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_IS_SCALAR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
{
  template<class Hierarchy> struct is_scalar : boost::mpl::false_ {};

  template<class T>
  struct is_scalar< meta::scalar_<T> >  : boost::mpl::true_ {};
} }

#endif
