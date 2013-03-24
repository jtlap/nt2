//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_RANDO_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_RANDO_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_rando rando
 *
 * rando  random matrix with elements -1, 0 or 1. or random elements from vector x
 *    a = rando(n,k) is a random n-by-n matrix with
 *    elements from one of the following discrete distributions
 *    (default k = 1):
 *       k = 1:  a(i,j) =  0 or 1    with equal probability,
 *       k = 2:  a(i,j) = -1 or 1    with equal probability,
 *       k = 3:  a(i,j) = -1, 0 or 1 with equal probability.
 *    n may be a 2-vector, in which case the matrix is n(1)-by-n(2).
 *    a = rando(x, n) where x is a vector with p elements is a matrix
 *    the elements of xhich are randomly obtained from x coordinates.
 *    rando(n, 1) is the same as rando(cons(0, 1), n)
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rando.hpp>
 * \endcode
 *
 **/
//==============================================================================
// rando actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag rando_ of functor rando
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct rando_ : ext::unspecified_<rando_>
    {
      typedef ext::unspecified_<rando_> parent;
    };
}

  NT2_FUNCTION_IMPLEMENTATION(tag::rando_, rando, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::rando_, rando, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::rando_, rando, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::rando_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = nt2::numel(boost::proto::child_c<1>(e));
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::rando_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,N-2>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                              s_type;
    typedef typename  s_type::value_type                                         type;
  };
} }

#endif

