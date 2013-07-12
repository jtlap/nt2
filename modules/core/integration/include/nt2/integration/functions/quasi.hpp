//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUNCTIONS_QUASI_HPP_INCLUDED
#define NT2_INTEGRATION_FUNCTIONS_QUASI_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \file
 * \brief Defines and implements the nt2::quasi function
 */

/*!
 * \ingroup statistics
 * \defgroup statistics_exp2 exp2
 *
 * \par Description
 * uniform pseudo random numbers generator
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/quasi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::quasi_(A0)>::type
 *     quasi(const A0 & a, const A1 & b, ... dimensions);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag quasi_ of functor quasi
     *        in namespace nt2::tag for toolbox statistics
     **/
    struct quasi_ : ext::unspecified_<quasi_> { typedef ext::unspecified_<quasi_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::quasi_, quasi, 3)
 }

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::quasi_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      size_t n = boost::proto::value(boost::proto::child_c<1>(e));
      size_t m = boost::proto::value(boost::proto::child_c<0>(e));
      sizee[1] = n;
      sizee[0] = m;
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::quasi_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,2>::type  t_t;
    typedef typename  boost::dispatch::meta::semantic_of<t_t>::type   type;
  };
} }
#endif

