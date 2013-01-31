//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COLVECT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLVECT_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the colvect function
**/

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/reshaping.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for colvect functor
    **/
    struct colvect_ : ext::reshaping_<colvect_>
    {
      typedef ext::reshaping_<colvect_> parent;
    };
  }

  /*!
    @brief Column reshaping

    Reshape an expression into a column shaped table.

    @param a0 Expression to reshape

    @return The reshaped expression
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::colvect_       , colvect, 1)
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::colvect_  , colvect, 1)
}

#endif
