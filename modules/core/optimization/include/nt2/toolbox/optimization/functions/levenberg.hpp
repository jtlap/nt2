//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPTIMIZATION_FUNCTIONS_LEVENBERG_HPP_INCLUDED
#define NT2_TOOLBOX_OPTIMIZATION_FUNCTIONS_LEVENBERG_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::levenberg function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/toolbox/optimization/options.hpp>

namespace nt2
{
  namespace tag
  {
    struct levenberg_ : ext::unspecified_<levenberg_>
    {
      typedef ext::unspecified_<levenberg_> parent;
    };
  }

  //============================================================================
  /*!
   * Apply levenberg algorithm to find local minimum of a function
   *
   * \param func     Function to optimize
   * \param init     Initial value
   * \param which    Which are the unknowns we want to optimize
   * \param opt      Options pack related to the minimization handling
   *
   * \return  a tuple containing the result of the minimization, the value of the
   *          function at minimum, the number of required iteration and a boolean
   *          notifying success of convergence.
   */
  //============================================================================
  template<class F, class A, class H> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::levenberg_( F
                                  , A, H
                                    , details::optimization_settings<typename A::value_type> const&
                                  )
                      >::type
  levenberg(F f, A init, H which)
  {
    typename boost::dispatch::make_functor<tag::levenberg_, F>::type callee;
    return callee ( f
                  , init
                  , which
                  , details::optimization_settings<typename A::value_type>()
                  );
  }

  template<class F, class A, class H, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::levenberg_( F
                                  , A, H
                                  , details::optimization_settings<typename A::value_type> const&
                                  )
                      >::type
  levenberg(F f, A init, H which, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::levenberg_, F>::type callee;
    return callee ( f
                  , init
                  , which
                  , details::optimization_settings<typename A::value_type>(opt)
                  );
  }
}



#endif
