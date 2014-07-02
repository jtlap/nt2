//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_VECNORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_VECNORM_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_vecnorm vecnorm
 *
 * \par Description
 * norm of a vector with static or dynamic choice of the norm
 * the input parameter is always considered as a big column vector.
 * second parameter can be a positive floating number p or -inf
 * in which case the lp norm is computed
 *
 * Note that if 0 < p < 1 or p = -inf, the functor does not share the
 * properties that define a mathematical norm.
 *
 * vecnorm(v) is the same as vecnorm(v,tag::Two).
 * vecnorm(v,p) returns the lp-norm of v defined as sum(abs(v).^p)^(1/p).
 * vecnorm(v,Inf<T>()) returns the largest element of abs(v).
 * vecnorm(v,-Minf<T>())) returns the smallest element of abs(v)
 * nan is returned if v contains nans.
 *
 * vecnorm can also be invoked with a static choice of the second parameter
 * using a templated version:
 * vecnorm<T>(v)
 * T can be nt2::tag::Inf, nt2::tag::Minf, nt2::tag::One or nt2::tag::Two,
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/vecnorm.hpp>
 * \endcode
 *
 *
 * \param v the expresion vector, even if matricial it is always considered as a
 *          big column vector
 *
 * \param the type of norm required
 *
 *

 * \par Notes
 *   Call norm to obtain the Matlab behaviour on matrices.
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag vecnorm_ of functor vecnorm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct vecnorm_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(nt2::tag::vecnorm_, vecnorm, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(nt2::tag::vecnorm_, vecnorm, 2)

  template < class T, class A>
  BOOST_FORCEINLINE typename meta::as_real<typename A::value_type>::type
  vecnorm(const A& a)
  {
    return vecnorm(a, nt2::meta::as_<T>());
  }

}

#endif
