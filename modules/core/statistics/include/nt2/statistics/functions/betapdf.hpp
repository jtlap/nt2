//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_BETAPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_BETAPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief betapdf generic tag

     Represents the betapdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct betapdf_ : ext::elementwise_<betapdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<betapdf_> parent;
    };
  }
  /*!
    beta distribution

    @par Semantic:

    For every table expression

    @code
    auto r = betapdf(x, a, b);
    @endcode

    computes

    \f$ r = (x^{a-1}(1-x)^{b-1}1_{[0, 1[}(x))/\B(x, a, b)\f$

    where B is the beta function
            \f$ B(a,b)=\int_0^1 t^{a-1}(1-t)^{b-1}\mbox{d}t\f$


    @see @funcref{beta}
    @param x
    @param a first distribution parameter
    @param b second  distribution parameter

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::betapdf_, betapdf, 3)

}

#endif
