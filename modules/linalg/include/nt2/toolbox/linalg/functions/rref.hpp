/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_RREF_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_RREF_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_rref rref
 *
 * \par Description
 * reduced echelon
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/rref.hpp>
 * \endcode
 * 
 * 
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag rref_ of functor rref
     *        in namespace nt2::tag for toolbox algebra
    **/
    namespace factorization
    {
      struct rref_ : ext::unspecified_<factorization::rref_>
      {
        typedef ext::unspecified_<factorization::rref_> parent;
      };
    }

    struct rref_ :  ext::tieable_<rref_>
    {
      typedef ext::tieable_<rref_>  parent;
    };
  }
  
  NT2_FUNCTION_IMPLEMENTATION(tag::rref_, rref, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::rref_, rref, 2)
  namespace factorization
  {
    /**
     * @brief Initialize a rref factorization
     *
     * For any given matrix expression, initialize a rref factorization of
     * said matrix using the specified output layout for the rref method
     * and return a precomputed factorization object.
     *
     * Contrary to the rref function which performs such a factorization and
     * return a Matlab like output, factorization::rref returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     *
     * @return A unspecified type containing the precomputed elements of the
     * rref factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::rref_, rref, 1)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::rref_, rref, 2)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::rref_, rref, 3)
  }

}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::rref_,Domain,N,Expr>
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
  struct  size_of<tag::rref_,Domain,1,Expr>
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
  struct  generator<tag::rref_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename boost::dispatch::meta::semantic_of<seq_term>::type sema_t;

    // Rebuild proper expression type with semantic
    typedef expression< typename boost::remove_const<Expr>::type
                      , sema_t
                      >                                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  }; 
}}}


#endif

