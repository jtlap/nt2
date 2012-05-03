//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_QR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_QR_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/toolbox/linalg/functions/details/qr.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct qr_ : ext::unspecified_<factorization::qr_>
      {
        typedef ext::unspecified_<factorization::qr_> parent;
      };
    }

    struct qr_ :  ext::tieable_<qr_>
    {
      typedef ext::tieable_<qr_>  parent;
    };
  }

  /**
   * @brief Perform Qr factorization
   *
   * For any given matrix expression, performs a qr factorization of
   * said matrix using the specified output layout for the qr method.
   *
   * Contrary to the nt2::factorization::qr function which performs a partial evaluation of
   * said decomposition, nt2::qr returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::qr_, qr, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::qr_, qr, 2)

  namespace factorization
  {
    /**
     * @brief Initialize a qr factorization
     *
     * For any given matrix expression, initialize a qr factorization of
     * said matrix using the specified output layout for the qr method
     * and return a precomputed factorization object.
     *
     * Contrary to the qr function which performs such a factorization and
     * return a Matlab like output, factorization::qr returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     *
     * @return A unspecified type containing the precomputed elements of the
     * qr factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::qr_, qr, 2)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::qr_, qr, 3)
  }
}

namespace nt2 { namespace container { namespace ext
{
//   template<class Domain, int N, class Expr>
//   struct  size_of<tag::qr_,Domain,N,Expr>
//         ////: reduction_size_of<tag::sum_, 1, Expr>{};
//   {
//     // The size is contained in the first child
//     typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
//     typedef typename meta::strip<seq_term>::type::extent_type        result_type;

//     BOOST_FORCEINLINE result_type operator()(Expr& e) const
//     {
//       return boost::proto::child_c<0>(e).extent();
//     }
//   };

//   template<class Domain, class Expr>
//   struct  size_of<tag::qr_,Domain,1,Expr>
//         ////: reduction_size_of<tag::sum_, 1, Expr>{};
//   {
//     // The size is contained in the first child
//     typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
//     typedef typename meta::strip<seq_term>::type::extent_type        result_type;

//     BOOST_FORCEINLINE result_type operator()(Expr& e) const
//     {
//       return boost::proto::child_c<0>(e).extent();
//     }
//   };

//   template<class Domain, int N, class Expr>
//   struct  generator<tag::qr_,Domain,N,Expr>
//         ////: reduction_generator<tag::qr_,N,Expr> {};
//   {
//     typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
//     typedef typename boost::dispatch::meta::semantic_of<seq_term>::type sema_t;

//     // Rebuidl proper expression type with semantic
//     typedef expression< typename boost::remove_const<Expr>::type
//                       , sema_t
//                       >                                     result_type;

//     BOOST_FORCEINLINE result_type operator()(Expr& e) const
//     {
//       return result_type(e);
//     }
//   };
} } }

#endif
