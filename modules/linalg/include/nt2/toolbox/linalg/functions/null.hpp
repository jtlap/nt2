/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_NULL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_NULL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * @brief null  null space of a matrix expression.
 *    z = null(a) is an orthonormal basis for the null space of a obtained
 *    from the singular value decomposition.  that is,  a*z has negligible
 *    elements, size(z,2) is the nullity of a,
 *    and transconj(z)*z = eye(size(transconj(z)*z)).
 * 
 *    z = null(a,'r') is a "rational" basis for the null space obtained
 *    from the reduced row echelon form.  a*z is zero, size(z,2) is an
 *    estimate for the nullity of a, and, if a is a small matrix with 
 *    integer elements, the elements of r are ratios of small integers.  
 * 
 *    the orthonormal basis is preferable numerically, while the rational
 *    basis may be preferable pedagogically.
 * 
 *    example:
 * 
 *        a =
 * 
 *            1     2     3
 *            1     2     3
 *            1     2     3
 * 
 *       z = null(a); 
 * 
 *        computing the 1-norm of the matrix a*z will be 
 *        within a small tolerance
 * 
 *        norm(a*z,1)< 1e-12
 *        ans =
 *          1
 * 
 *        null(a,'r') = 
 *
 *           -2    -3
 *            1     0
 *            0     1
 *
 **/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag null_ of functor null
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct null_ :  ext::unspecified_<null_> { typedef ext::unspecified_<null_> parent; };
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::null_, null, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::null_, null, 2)

}
namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N> //N == 1 only
  struct  size_of<tag::null_, Domain, N, Expr> 
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename c0_t::extent_type                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      // TODO
      // I don't know if this is fully correct
      // I know that the size returned here is always greater or equal to the final
      // result actual size and that calculating the final size is determined
      // by the full result computation as we suppress the matrix columns that
      // don't verify a test.
      result_type sizee = boost::proto::child_c<0>(e).extent();
      std::swap(sizee[0], sizee[1]); 
      return sizee; 
    }
  };

 template <class Domain, class Expr,  int N>
 struct value_type < tag::null_, Domain,N,Expr>
  : meta::value_as<Expr,0>
 {};
} }
#endif
