//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRANS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRANS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::trans function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct trans_ : ext::elementwise_<trans_>
    {
      typedef ext::elementwise_<trans_> parent;
    };
  }

  //============================================================================
  /*!
   * transpose a matrix
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trans_, trans, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct size_of<tag::trans_,Domain,N,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      //BOOST_ASSERT(ndims(boost::proto::child_c<0>(e)) <= 2);
      return _2D( boost::fusion::at_c<1>(boost::proto::child_c<0>(e).extent())
                , boost::fusion::at_c<0>(boost::proto::child_c<0>(e).extent())
                );
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::trans_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
