//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPAND_TO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPAND_TO_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the expand_to function
 **/

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <boost/assert.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/include/functions/repnum.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for expand_to functor
     **/
    struct expand_to_ : ext::elementwise_<expand_to_>
    {
      typedef ext::elementwise_<expand_to_> parent;
    };
  }

  /*!
    @brief expand expression to a given size enabling singleton expansion

    expand_to(a,siz) is coceptually equivalent (for additive element types) to
    bsxfun(plus, a, zeros(siz))
   
    size(a)  and @c siz must be such that for every involved dimension  @c i
    size(a, i) == siz(i) or 1
        Whenever a dimension of @c a or @c b is singleton (i.e equal
    to one), expand_to virtually replicates the array along that dimension to match
    the given dimension in siz.

    @param a expression to process
    @param b size to expand to
  **/
#define M0(z,n,t)                                                 \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::expand_to_, expand_to, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}
namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<nt2::tag::expand_to_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  template<class Domain, class Expr,int N>
  struct  size_of<nt2::tag::expand_to_,Domain,N,Expr>
        : meta::boxed_size<Expr,1>
  {};
} }



#endif
