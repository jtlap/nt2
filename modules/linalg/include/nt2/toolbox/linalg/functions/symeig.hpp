//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_SYMEIG_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_SYMEIG_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/toolbox/linalg/functions/details/symeig.hpp>

////////////////////////////////////////////////////////////////////////////////
// Construct the class choosing the computation model :
// float,  double or complex < float >  or complex < double > and a matrix or
// matrix expression as:
//                     symeig_result<table <double> >s(1.0/(cif(5)+rif(5)-1));
// or
//                     matrix < double >  a(1.0/(cif(5)+rif(5)-1));
//                     symeig<table < double > >s(a)
//
// then you can extract v, w and using the accessors v(), w() to
// obtain 2 matrices such that up to rounding errors :
//                     s.v()*a = s.v()*s.w()
// is the original matrix
// If you just want the eigenvalues but not the eigenvectors call s(a, 'N')
// Take care that the input expression is supposed to be hermitian
// (symetric if real),  but that by default the upper part of the expression
// is considered an even a not "really" symetric input will be taken as such.
//
// Use s(a, 'N', 'L') or  s(a, 'V', 'L') to use the lower part.
////////////////////////////////////////////////////////////////////////////////


namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct symeig_ : ext::unspecified_<factorization::symeig_>
      {
        typedef ext::unspecified_<factorization::symeig_> parent;
      };
    }

    struct symeig_ : ext::tieable_<symeig_>
    {
      typedef ext::tieable_<symeig_>  parent;
    };
  }

  /**
   * @brief Perform Symeig factorization
   *
   * For any given matrix expression, performs a Symeig factorization of
   * said matrix using the specified output layout for the Symeig method.
   *
   * Contrary to the nt2::factorization::symeig function which performs a partial evaluation of
   * said decomposition, nt2::symeig returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::symeig_, symeig, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::symeig_, symeig, 2)

  namespace factorization
  {
    /**
     * @brief Initialize a Symeig factorization
     *
     * For any given matrix expression, initialize a Symeig factorization of
     * said matrix using the specified output layout for the Symeig method
     * and return a precomputed factorization object.
     *
     * Contrary to the symeig function which performs such a factorization and
     * return a Matlab like output, factorization::symeig returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  ip   Notify if lu should be performed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Lu factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::symeig_, symeig, 3)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::symeig_, symeig, 4)
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::symeig_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::symeig_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
