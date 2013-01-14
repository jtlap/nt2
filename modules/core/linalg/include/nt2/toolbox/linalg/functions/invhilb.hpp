/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_INVHILB_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_INVHILB_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_invhilb invhilb
 *
 * \par Description
 *   invhilb(n) is the inverse of the n by n matrix with elements
 *   1/(i+j-1), which is a famous example of a badly conditioned
 *   matrix.  the result is exact for  n  less than about 15.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/invhilb.hpp>
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
// invhilb actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag invhilb_ of functor invhilb
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct invhilb_ : ext::unspecified_<invhilb_> { typedef ext::unspecified_<invhilb_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::invhilb_, invhilb, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::invhilb_, invhilb, 2)
  template < class T> container::table<T> invhilb(size_t n)
  {
    return nt2::invhilb(n, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::invhilb_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n =  boost::proto::child_c<0>(e);
      result_type sizee;
      sizee[0] = sizee[1] = n;
      return sizee;
    }
  };

  template <class Domain, class Expr,  int N>
  struct value_type < tag::invhilb_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  boost::dispatch::meta::semantic_of<tmp1_type>::type tmp2_type;
    typedef typename  tmp2_type::type                                          type;
  };
} }
#endif

