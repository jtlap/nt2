/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_CIRCUL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_CIRCUL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_circul circul
 *
 * \par Description
 * circul matrix (singular toeplitz lower hessenberg matrix).
 *    a = circul(n,alpha,delta,as_<T>()) returns a such that
 *       a = h(alpha) + delta*eye, where h(i,j) = alpha^(i-j+1).
 *    h(alpha) has p = floor(n/2) zero eigenvalues, the rest being
 *    4*alpha*cos( k*pi/(n+2) )^2, k=_(1, n-p).
 *    defaults: alpha = 1, delta = 0.
 *    If alpha and delta are omited then T must be there else
 *    T can be omitted and the result is in the alpha type.
 *    If T is present the element type of the result is T
 *
 *  One can also pass T using the templated circul<T>(...) syntax
 *
 *    references:
 *    [1] T. S. Circul, A class of Hessenberg matrices with known eigenvalues
 *        and inverses, SIAM Review, 11 (1969), pp. 391-395.
 *    [2] G. Fairweather, On the eigenvalues and eigenvectors of a class of
 *        Hessenberg matrices, SIAM Review, 13 (1971), pp. 220-221.
 *    [3] I. Singh, G. Poole and T. Boullion, A class of Hessenberg matrices
 *        with known pseudoinverse and Drazin inverse, Math. Comp., 29 (1975),
 *        pp. 615-619.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/circul.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// circul actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag circul_ of functor circul
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct circul_ : ext::unspecified_<circul_> { typedef ext::unspecified_<circul_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::circul_, circul, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::circul_, circul, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::circul_, circul, 3)
  template < class T> container::table<T> circul(size_t n)
  {
    return nt2::circul(nt2::_(T(1), T(n)));
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::circul_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n =  numel(boost::proto::child_c<0>(e));
      result_type sizee;
      sizee[0] = sizee[1] = n;
      return sizee;
    }
  };


  template <class Domain, class Expr, int N>
  struct value_type < tag::circul_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type   type;
  };

} }
#endif

