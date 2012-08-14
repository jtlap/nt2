//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HORZCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HORZCAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/sdk/meta/add_settings.hpp>
#include <nt2/core/settings/shape.hpp>

namespace nt2
{
  namespace tag
  {
    struct  horzcat_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, horzcat, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, horzcat, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, cath, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, cath, 2)
}

#endif
