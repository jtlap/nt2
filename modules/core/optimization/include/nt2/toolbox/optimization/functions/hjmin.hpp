/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_OPTIMIZATION_FUNCTIONS_HJMIN_HPP_INCLUDED
#define NT2_TOOLBOX_OPTIMIZATION_FUNCTIONS_HJMIN_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::hjmin function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/toolbox/optimization/options.hpp>

namespace nt2
{
  namespace tag
  {
    struct hjmin_ : ext::unspecified_<hjmin_>
    {
      typedef ext::unspecified_<hjmin_> parent;
    };
  }

  //============================================================================
  /*!
   * Apply hjmin (Hooke-Jeeves) algorithm to find local minimum of a function
   *
   * \param func  Function to optimize
   * \param init  Initial value
   * \param stps  Initial step(s) in every (each) direction
   * \param opt   Options pack related to the minimization handling
   *
   * \return  a tuple containing the result of the minimization, the value of the
   *          function at minimum, the number of required iteration and a boolean
   *          notifying success of convergence.
   *
   * Hooke-Jeeves Pattern Moves is in a sense the simplest of all optimization
   * algorithms. At each iteration, this method first defines a pattern of
   * points by moving each parameter one by one, so as to optimize the
   * current loss function. The entire pattern of points is then shifted or
   * moved to a new location; this new location is determined by
   * extrapolating the line from the old base point in the m dimensional
   * parameter space to the new base point. The step sizes in this process
   * are constantly adjusted to "zero in" on the respective optimum. This
   * method is usually quite effective, and should be tried if both the
   * quasi-Newton and Simplex methods fail to produce reasonable estimates.
   */
  //============================================================================
  template<class F, class A, class H> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::hjmin_( F
                                  , A, H
                                    , details::optimization_settings<typename A::value_type> const&
                                  )
                      >::type
  hjmin(F f, A init, H stps)
  {
    typename boost::dispatch::make_functor<tag::hjmin_, F>::type callee;
    return callee ( f
                  , init
                  , stps
                  , details::optimization_settings<typename A::value_type>()
                  );
  }

  template<class F, class A, class H, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::hjmin_( F
                                  , A, H
                                  , details::optimization_settings<typename A::value_type> const&
                                  )
                      >::type
  hjmin(F f, A init, H stps, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::hjmin_, F>::type callee;
    return callee ( f
                  , init
                  , stps
                  , details::optimization_settings<typename A::value_type>(opt)
                  );
  }
}



#endif
