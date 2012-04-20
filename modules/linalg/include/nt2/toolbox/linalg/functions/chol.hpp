//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_CHOL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_CHOL_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/linalg/functions/details/chol.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct chol_ : ext::unspecified_<factorization::chol_>
      {
        typedef ext::unspecified_<factorization::chol_> parent;
      };
    }

    struct chol_ : ext::unspecified_<chol_>
    {
      typedef ext::unspecified_<chol_>  parent;
    };
  }

  /**
   * @brief Perform Cholesky factorization
   *
   * For any given matrix expression, performs a Cholesky factorization of
   * said matrix using the specified output layout for the Cholevsky method.
   *
   * Contrary to the cholesky function which performs a partial evalaution of
   * said decomposition, chol returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   * @param  low  Notify if chol should return a lower triangular matrix
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 2)

  // Those variant are used for the tied(x...) = chol(..) syntax
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 4)

  namespace factorization
  {
    /**
     * @brief Initialize a Cholevsky factorization
     *
     * For any given matrix expression, initialize a Cholevsky factorization of
     * said matrix using the specified output layout for the Cholevsky method
     * and return a precomputed factorization object.
     *
     * Contrary to the chol function which performs such a factorization and
     * return a Matlab like output, factorization::chol returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  uplo Notify if chol should return a lower or upper result
     * @param  ip   Notify if chol should be performaed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Cholesky factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::chol_, chol, 2)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::chol_, chol, 3)
  }
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::chol_,Domain,N,Expr>
        ////: reduction_size_of<tag::sum_, 1, Expr>{};
  {
    // The size is contained in the first child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename meta::strip<seq_term>::type::extent_type        result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Domain, class Expr>
  struct  size_of<tag::chol_,Domain,1,Expr>
        ////: reduction_size_of<tag::sum_, 1, Expr>{};
  {
    // The size is contained in the first child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename meta::strip<seq_term>::type::extent_type        result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Domain, int N, class Expr>
  struct  generator<tag::chol_,Domain,N,Expr>
        ////: reduction_generator<tag::chol_,N,Expr> {};
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename boost::dispatch::meta::semantic_of<seq_term>::type sema_t;

    // Rebuidl proper expression type with semantic
    typedef expression< typename boost::remove_const<Expr>::type
                      , sema_t
                      >                                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }

#endif
