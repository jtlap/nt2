/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_CHEBVAND_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_CHEBVAND_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/mpl/if.hpp>
/*!
 * \ingroup algebra
 * \defgroup algebra_chebvand chebvand
 *
 * \par Description
 * function C = chebvand(m,p)
 * compute a vandermonde-like matrix for the chebyshev polynomials.
 *   c = chebvand(p), where p is a vector, produces the
 *   (primal) chebyshev vandermonde matrix based on the points p:
 *      c(i,j) = t_{i-1}(p(j)), where t_{i-1} is the chebyshev
 *      polynomial of degree i-1.
 *   chebvand(m,p) is a rectangular version of
 *   chebvand(p) with m rows.
 *   special case: if p is a scalar, then p equally spaced points on
 *      [0,1] are used.

 *   Reference:
 *   [1] N. J. Higham, Stability analysis of algorithms for solving confluent
 *       Vandermonde-like systems, SIAM J. Matrix Anal. Appl., 11 (1990),
 *       pp. 23-41.
 *
 *   Nicholas J. Higham, Dec 1999.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/chebvand.hpp>
 * \endcode
 *
 **/
//==============================================================================
// chebvand actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag chebvand_ of functor chebvand
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct chebvand_ : ext::unspecified_<chebvand_> { typedef ext::unspecified_<chebvand_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::chebvand_, chebvand, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::chebvand_, chebvand, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::chebvand_, chebvand, 3)

  template < class T > container::table<T> chebvand(size_t n,  size_t k)
  {
    return nt2::chebvand(n, k, meta::as_<T>());
  }
  template < class T > container::table<T> chebvand(size_t n)
  {
    return nt2::chebvand(n, meta::as_<T>());
  }

}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::chebvand_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t m =  boost::proto::child_c<0>(e);
      size_t n =  boost::proto::child_c<1>(e);
      result_type sizee;
      sizee[0] = m; sizee[1] = n;
      return sizee;
    }
  };

  template <class Domain, class Expr,  int N>
  struct value_type < tag::chebvand_, Domain,N,Expr>
  {
    typedef double type;
  };

  template <class Domain, class Expr>
  struct value_type < tag::chebvand_, Domain,5,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,2>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename t_type::type                                             type;
  };
} }
#endif

