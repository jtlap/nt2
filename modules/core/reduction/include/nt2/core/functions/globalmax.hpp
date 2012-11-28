//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALMAX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALMAX_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/global.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/globalfind.hpp>
/*!
 * \ingroup core
 * \defgroup core globalmax
 *
 * \par Description
 * sentimentaly bool(max(a0(_)))
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/globalmax.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::globalmax_(A0)>::type
 *     globalmax(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of globalmax
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
    struct globalmax_ : tag::formal_ { typedef tag::formal_ parent; };
  }

  //============================================================================
  /*!
   * max of absolute squares of a table
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmax_       , globalmax, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmax_       , g_max, 1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::globalmax_, globalmax,(A0 const&)(A1&),2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::globalmax_, g_max ,(A0 const&)(A1&),2)

}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalmax_, tag::cpu_,
                              (A0),
                              (unspecified_<A0>)
    )
  {
    typedef typename meta::call<tag::global_(nt2::functor<tag::maximum_>
                                             , const A0&
      )>::type                           result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::global(nt2::functor<tag::maximum_>(), a0);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalmax_, tag::cpu_,
                              (A0)(A1),
                              (unspecified_<A0>)(scalar_<integer_<A1> > )
    )
  {
    typedef typename meta::call<tag::global_(nt2::functor<tag::maximum_>, const A0&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 & a1) const
    {
       result_type tmp =  global(nt2::functor<tag::maximum_>(), a0);
       A1 k = nt2::globalfind(eq(a0, tmp));
       a1 = k;
       return tmp;
    }
  };


} }
#endif
