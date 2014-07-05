//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALNORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALNORM_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/mpl/int.hpp>

/*!
 * \par Description
 * norm of a whole table expression elements with static or dynamic choice
 * of the norm computation formula.
 * The input parameter is always considered as a big column vector.
 * second parameter can be a positive floating number p or -inf
 * in which case the lp norm is computed
 *
 * Note that if 0 < p < 1 or p = -inf, the functor does not share the
 * properties that define a mathematical norm,  but only a quasi-norm
 * if  0 < p < 1 and a notation commodity in the last case.
 *
 * globalnorm(v) is the same as globalnorm2(v).
 * globalnorm(v,p) returns the lp-norm of v defined as sum(abs(v).^p)^(1/p).
 * globalnorm(v,Inf<T>()) returns the largest element of abs(v).
 * globalnorm(v,-Minf<T>())) returns the smallest element of abs(v)
 * nan is returned if v contains nans.
 *
 * globalnorm can also be invoked with a static choice of the second parameter
 * using a templated version:
 * globalnorm<T>(v)
 * T can be nt2::tag::Inf, nt2::tag::Minf, nt2::tag::One or nt2::tag::Two,
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/globalnorm.hpp>
 * \endcode
 *
 *
 * \param v the expresion vector, even if matricial it is always considered as a
 *          big column vector
 *
 * \param the type of norm required
 *
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag globalnorm_ of functor globalnorm
     *        in namespace nt2::tag for toolbox reduction
    **/
    struct globalnorm_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(nt2::tag::globalnorm_, globalnorm, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(nt2::tag::globalnorm_, globalnorm, 2)

  template < class T, class A>
  BOOST_FORCEINLINE typename meta::as_real<typename A::value_type>::type
  globalnorm(const A& a)
  {
    return globalnorm(a, nt2::meta::as_<T>());
  }

  template <int N, class A>
  BOOST_FORCEINLINE typename meta::as_real<typename A::value_type>::type
  globalnorm(const A& a)
  {
    return globalnorm(a, N);
  }

}

#endif
