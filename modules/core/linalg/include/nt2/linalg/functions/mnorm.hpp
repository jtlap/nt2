//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>

namespace nt2 { namespace tag
  {
    /*!
     @brief globalnorm generic tag

      Represents the mnorm function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct mnorm_ :  tag::formal_
    {
      /// INTERNAL ONLY
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Matricial norm

    Computes the matricial norms of a matrix expression with static or dynamic choice from
    by the optional second parameter or the template parameter
    that can be 1,  2, inf or fro_

    @par Semantic:
    1, 2 and inf can be given dynamically or statically as template parameter ie:

    For any expression @c a0 of type @c A0, the following call:

    @code
    as_real<A0::value_type>::type x = mnorm(a0);
    @endcode

    is equivalent to:

    @code
    as_real<A0::value_type>::type x = svd(a0)(1);
    @endcode

    For any expression @c a0 of type @c A0 and any value x in {1, 2, inf, fro}
    following call:

    @code
    as_real<A0::value_type>::type x = mnorm(a0,p);
    @endcode

    or

    @code
    as_real<A0::value_type>::type x = mnorm<x>(a0);
    @endcode
    is equivalent to:

    @code
    as_real<A0::value_type>::type x = mnormx(a0);
    @endcode

    @param a0 Expression to compute the norm of
    @param a1 Type of norm to compute
  **/



  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm_, mnorm, 1)

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm_, mnorm, 2)

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm_, mnorm2, 1)

  /// @overload
  template < class T, class A>
  BOOST_FORCEINLINE
  typename meta::as_real<typename A::value_type>::type
  mnorm(const A& a)
  {
    return mnorm(a, nt2::meta::as_<T>());
  }
  /// @overload
  template < int Value, class A>
  BOOST_FORCEINLINE
  typename meta::as_real<typename A::value_type>::type
  mnorm(const A& a)
  {
    return mnorm(a, boost::mpl::int_<Value>());
  }
}

namespace nt2
{
  namespace tag
  {
    struct fro_   {};
    struct inf_   {};
  }
  nt2::meta::as_<tag::fro_>     const fro_ = {};
  nt2::meta::as_<tag::inf_>     const inf_ = {};
}

#endif

