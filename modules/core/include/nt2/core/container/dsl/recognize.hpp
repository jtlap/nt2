//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_RECOGNIZE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_RECOGNIZE_HPP_INCLUDED

#include <nt2/sdk/dsl/recognize.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/functor/preprocessor/dispatch.hpp>

//==============================================================================
// Recognition of expressions (no-op for now)
//==============================================================================
namespace nt2 { namespace ext
{
  NT2_REGISTER_DISPATCH_TO( nt2::tag::recognize_, tag::formal_
                          , (A0)
                          , (unspecified_<A0>)
                          , tag::identity_
                          )
} }

#endif
