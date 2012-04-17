//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_EXTRACTIVE_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_META_EXTRACTIVE_HIERARCHY_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
    //==========================================================================
    // Extarctive node hierarchy
    //==========================================================================
    template<class Tag> struct extractive_ : elementwise_<Tag>
    {
      typedef elementwise_<Tag> parent;
    };
} } }

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::extractive_;
} }

#endif
