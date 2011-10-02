//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_COMPILE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_COMPILE_HPP_INCLUDED

#include <nt2/sdk/dsl/compile.hpp>
#include <nt2/sdk/dsl/run.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// Compilation of expressions
//==============================================================================
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::compile_, tag::formal_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef functor<tag::run_> result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const&) const
    {
      return result_type();
    }
  };
} }

#endif
