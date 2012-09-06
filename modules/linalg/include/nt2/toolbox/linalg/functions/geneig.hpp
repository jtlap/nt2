//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENEIG_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENEIG_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/toolbox/linalg/functions/details/geneig.hpp>
////////////////////////////////////////////////////////////////////////////////
// Construct the class choosing the computation model :
// float,  double or complex < float >  or complex < double > and a matrix or
// matrix expression as:
//                     geneig<table < double > >s(a, b)
//
// then you can extract v, w and using the accessors v(), w() to
// obtain 2 matrices such that up to rounding errors :
//                     a*s.v() = s.w()*b*s.v()
////////////////////////////////////////////////////////////////////////////////


namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct geneig_ : ext::unspecified_<factorization::geneig_>
      {
        typedef ext::unspecified_<factorization::geneig_> parent;
      };
    }

    struct geneig_ : ext::tieable_<geneig_>
    {
      typedef ext::tieable_<geneig_>  parent;
    };
  }

  /**
   * @brief Perform Geneig factorization
   *
   * For any given matrix expression, performs a Geneig factorization of
   * said matrix using the specified output layout for the Geneig method.
   *
   * Contrary to the nt2::factorization::geneig function which performs a partial evaluation of
   * said decomposition, nt2::geneig returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::geneig_, geneig, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::geneig_, geneig, 2)

 
  namespace factorization
  {
    /**
     * @brief Initialize a Geneig factorization
     *
     * For any given matrix expression, initialize a Geneig factorization of
     * said matrix using the specified output layout for the Geneig method
     * and return a precomputed factorization object.
     *
     * Contrary to the geneig function which performs such a factorization and
     * return a Matlab like output, factorization::geneig returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     *
     * @return A unspecified type containing the precomputed elements of the
     * Lu factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::geneig_, geneig, 4)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::geneig_, geneig, 5)
  }
}
namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  generator<tag::geneig_,Domain,N,Expr>
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
