//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALMIN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALMIN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/minimum.hpp>
#include <nt2/include/functions/global.hpp>
/*!
 * \ingroup core
 * \defgroup core globalmin
 *
 * \par Description
 * sentimentaly bool(min(a0(_)))
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/globalmin.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::globalmin_(A0)>::type
 *     globalmin(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of globalmin
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
    struct globalmin_ : tag::formal_
    {
      typedef tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * min of absolute squares of a table
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmin_       , globalmin, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmin_       , g_min, 1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::globalmin_, globalmin,(A0 const&)(A1&),2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::globalmin_, g_min ,(A0 const&)(A1&),2)
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalmin_, tag::cpu_, (A0), (unspecified_<A0>) )
  {
    typedef typename meta::call<tag::global_(nt2::functor<tag::minimum_>, const A0&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::minimum_>(), a0);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalmin_, tag::cpu_, (A0)(A1), (unspecified_<A0>)(scalar_<integer_<A1> > ))
  {
    typedef typename meta::call<tag::global_(nt2::functor<tag::minimum_>, const A0&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 & a1) const
    {
       result_type tmp =  global(nt2::functor<tag::minimum_>(), a0);
       A1 k = nt2::globalfind(a0 == tmp)(1);
       a1 = k;
       return tmp;
    }
  };

} }
#endif
