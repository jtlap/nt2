//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALSUM_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/global.hpp>
/*!
 * \ingroup core
 * \defgroup core globalsum
 *
 * \par Description
 * sentimentaly bool(sum(a0(_)))
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/globalsum.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::globalsum_(A0)>::type
 *     globalsum(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of globalsum
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
    struct globalsum_ : tag::formal_
    {
      typedef tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * sum of absolute squares of a table
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalsum_       , globalsum, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalsum_       , g_sum, 1)
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalsum_, tag::cpu_, (A0), (unspecified_<A0>) )
  {
    typedef typename meta::call<tag::global_(nt2::functor<tag::sum_>, const A0&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const 
    {
       return global(nt2::functor<tag::sum_>(), a0); 
    }
  };
} }
#endif
