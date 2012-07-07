//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LINE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LINE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>
#include <nt2/sdk/meta/add_settings.hpp>

/*!
 * \ingroup core
 * \defgroup core line
 *
 * \par Description
 * Returns the sum of absolute values of the elements matrix along the selected direction,
 * i.e. the 1-norm line(a0, n))
 * by default n is the first non-singleton dimension of a0
 *
 * \alias norm1,  asum
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/line.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::line_(A0)>::type
 *     line(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of line
 *
 * \return always a scalar value
 *
 * \par Notes
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *
**/


namespace nt2
{
  namespace tag
  {
    struct line_ : ext::elementwise_<line_>
    {
      typedef ext::elementwise_<line_> parent;
    };
  }

  //============================================================================
  /*!
   * sum of absolute squares of a table
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::line_       , line, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::line_       , line, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::line_       , line, 3)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::line_,Domain,4,Expr>
        : boxed_size_of<Expr,3>
  {};

  template<class Domain, int N, class Expr>
  struct  generator<nt2::tag::line_,Domain,N,Expr>
  {
    // We behave as our child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type  c_sema_t;
    typedef typename boost::dispatch::meta::semantic_of<c_sema_t>::type sema_t;

    // .. except we have a special size
    typedef typename boxed_size_of<Expr, 3>::result_type               sizes_t;

    // Rebuild proper expression type with semantic using the new size
    // and revoking any shape settings
    typedef expression< typename boost::remove_const<Expr>::type
                      , typename meta::
                        add_settings< sema_t
                                    , settings(rectangular_,sizes_t)
                                    >::type
                      >                                             result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }
#endif
