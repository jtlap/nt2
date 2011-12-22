//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_MAKE_BLOCK_HPP_INCLUDED
#define NT2_SDK_META_MAKE_BLOCK_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <nt2/core/settings/shape.hpp>
#include <nt2/core/settings/option.hpp>
//#include <nt2/core/settings/location.hpp>

namespace nt2 { namespace container
{
  template<class Type, class Settings>
  struct make_block
  {
    typedef typename meta::option<Settings, tag::shape_>::type shape_type;
    typedef typename boost::mpl::apply<shape_type,Type,Settings>::type type;
  };
} }

#endif
