//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_COMBINATORIAL_FUNCTIONS_FIBONACCI_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_FIBONACCI_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_fibonacci fibonacci
 *
 * \par Description
 * returns the selected values by n of a fibonacci sequence starting by a and b
 * the values are computed by the Binet formula.
 * \par
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fibonacci.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0, class A1>
 *     meta::call<tag::fibonacci_(A0, A0, A1)>::type
 *     fibonacci(const A0 & a, const A0 & b,  const A1& n);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fibonacci
 *
 * \param T template parameter of fibonacci
 *
 * \return a value of the template parameter type T.
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on n vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag fibonacci_ of functor fibonacci
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct fibonacci_ : ext::unspecified_<fibonacci_> { typedef ext::unspecified_<fibonacci_> parent; };
//    struct fibonacci_ : ext::elementwise_<fibonacci_> { typedef ext::elementwise_<fibonacci_> parent; };
//    struct fibonacci_ : tag::formal_{ typedef tag::formal_ parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fibonacci_,fibonacci, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::fibonacci_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee =  nt2::extent(boost::proto::child_c<2>(e));
      return sizee;
    }
  };


  template <class Domain, class Expr, int N>
  struct value_type < tag::fibonacci_, Domain,N,Expr>
    : meta::value_as<Expr,2>
  { };
} }

#endif

