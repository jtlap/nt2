//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_BALANCE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_BALANCE_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/linalg/functions/details/balance.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct balance_ : ext::unspecified_<factorization::balance_>
      {
        typedef ext::unspecified_<factorization::balance_> parent;
      };
    }

    struct balance_ : ext::unspecified_<balance_>
    {
      typedef ext::unspecified_<balance_>  parent;
    };
  }

  /**
   * @brief Perform Balance factorization
   *
   * For any given matrix expression, performs a Balance factorization of
   * said matrix using the specified output layout for the Balance method.
   *
   * Contrary to the nt2::factorization::balance function which performs a partial evaluation of
   * said decomposition, nt2::balance returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::balance_, balance, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::balance_, balance, 2)

  // Those variant are used for the tied(x...) = balance(..) syntax
  NT2_FUNCTION_IMPLEMENTATION_TPL ( tag::balance_
                                  , balance
                                  , (A0 const&)(A1 const&)(A2&)(A3&)(A4&)
                                  , 5
                                  )

  namespace factorization
  {
    /**
     * @brief Initialize a Balance factorization
     *
     * For any given matrix expression, initialize a Balance factorization of
     * said matrix using the specified output layout for the Balance method
     * and return a precomputed factorization object.
     *
     * Contrary to the balance function which performs such a factorization and
     * return a Matlab like output, factorization::balance returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  ip   Notify if balance should be performed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Balance factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::balance_, balance, 1)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::balance_, balance, 2)
  }
}

namespace nt2 { namespace container { namespace ext
{
  // TODO
} } }

#endif
