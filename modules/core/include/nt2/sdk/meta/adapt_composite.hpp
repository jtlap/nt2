//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_ADAPT_COMPOSITE_HPP_INCLUDED
#define NT2_SDK_META_ADAPT_COMPOSITE_HPP_INCLUDED

#include <boost/fusion/include/adapt_struct.hpp>
#include <nt2/sdk/meta/is_composite.hpp>

////////////////////////////////////////////////////////////////////////////////
// Adapt a structure to be a NT2 composite type
////////////////////////////////////////////////////////////////////////////////
#define NT2_ADAPT_COMPOSITE(Name,Fields)                        \
BOOST_FUSION_ADAPT_STRUCT(Name,Fields);                         \
namespace nt2 { namespace meta                                  \
{                                                               \
  template<> struct  is_composite<Name> : boost::mpl::true_ {}; \
} }                                                             \
/**/

#endif
