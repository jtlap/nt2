//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the find function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the find functor
    **/
    struct find_ : ext::tieable_<find_>
    {
      typedef ext::tieable_<find_> parent;
    };
  }

  /*!
    @brief

    @param
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 1)

  /*!
    @brief

    @param
    @param
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 4)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::find_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};


  template<class Domain, int N, class Expr>
  struct  value_type<tag::find_,Domain,N,Expr>
  {
    typedef std::ptrdiff_t      type;

  };
} }
    


#endif
