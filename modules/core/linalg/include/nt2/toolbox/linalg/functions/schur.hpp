//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_SCHUR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_SCHUR_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/toolbox/linalg/functions/details/schur.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct schur_ : ext::unspecified_<factorization::schur_>
      {
        typedef ext::unspecified_<factorization::schur_> parent;
      };
    }

    struct schur_ : ext::tieable_<schur_>
    {
      typedef ext::tieable_<schur_>  parent;
    };
  }

  /**
   * @brief Perform Schur factorization
   *
   * For any given matrix expression, performs a Schur factorization of
   * said matrix using the specified output layout for the Schurevsky method.
   *
   * Contrary to the nt2::factorization::schur function which performs a partial evaluation of
   * said decomposition, nt2::schur returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::schur_, schur, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::schur_, schur, 2)

  namespace factorization
  {
    /**
     * @brief Initialize a Schur factorization
     *
     * For any given matrix expression, initialize a Schur factorization of
     * said matrix using the specified output layout for the Schur method
     * and return a precomputed factorization object.
     *
     * Contrary to the schur function which performs such a factorization and
     * return a Matlab like output, factorization::schur returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  econ Notify if schur should return an economy size decomposition
     *
     * @return A unspecified type containing the precomputed elements of the
     * Schur factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::schur_, schur, 4)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::schur_, schur, 5)
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::schur_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::schur_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  template<class Domain, class Expr>
  struct  value_type<tag::schur_,Domain,2,Expr>
  {
// input 2 must be as_ < std::complex < T > >
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::type  in1_t;
    typedef typename meta::strip<in1_t>::type   sin1_t;
    typedef typename sin1_t::value_type          type;
  };
} }

#endif
