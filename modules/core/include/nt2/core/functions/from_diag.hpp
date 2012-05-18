//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FROM_DIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FROM_DIAG_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::from_diag function
 */

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

namespace nt2
{
  namespace tag
  {
    struct from_diag_ : ext::elementwise_<from_diag_>
    {
      typedef ext::elementwise_<from_diag_> parent;
    };
    struct offset_from_diag_ : ext::elementwise_<offset_from_diag_>
    {
      typedef ext::elementwise_<offset_from_diag_> parent;
    };
  }

  //============================================================================
  /*!
   * Builds a matrix from a vector suign it as the matrix's diagonal
   *
   * \param xpr A vector
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::from_diag_, from_diag, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_from_diag_, from_diag, 2)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct generator<nt2::tag::from_diag_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr,0>::type expr_t;
    typedef typename meta::strip<expr_t>::type::value_type          value_type;

    typedef expression< typename boost::remove_const<Expr>::type
                      , memory::container<value_type,_2D>
                      >                                          result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };

  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::from_diag_,Domain,N,Expr> : boxed_size_of<Expr,1> {};


  template<class Domain, int N, class Expr>
  struct generator<nt2::tag::offset_from_diag_,Domain,N,Expr>

  {
    typedef typename boost::proto::result_of::child_c<Expr,0>::type expr_t;
    typedef typename meta::strip<expr_t>::type::value_type          value_type;

    typedef expression< typename boost::remove_const<Expr>::type
                        , memory::container<value_type,_2D>
                      >                                          result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };

  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::offset_from_diag_,Domain,N,Expr> : boxed_size_of<Expr,2> {};
} } }

#endif
