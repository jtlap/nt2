//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ROWVECT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ROWVECT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::rowvect function
 */

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/reshaping.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2
{
  namespace tag
  {
    struct rowvect_ : ext::reshaping_<rowvect_>
    {
      typedef ext::reshaping_<rowvect_> parent;
    };
  }

  //============================================================================
  /*!
   * superior triangular part of a 2D table.
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::rowvect_       , rowvect, 1)
}

//==============================================================================
// Setup rowvect generator traits
//==============================================================================
namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::rowvect_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of
                          ::child_c<Expr&, 0>::value_type::extent_type ext_t;
    typedef typename meta::call<tag::numel_(ext_t const&)>::type num;

    typedef of_size_< 1, mpl_value<num>::value > result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(1,nt2::numel(boost::proto::child_c<0>(e)));
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::rowvect_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
