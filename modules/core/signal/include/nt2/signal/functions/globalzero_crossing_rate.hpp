//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_GLOBALZERO_CROSSING_RATE_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_GLOBALZERO_CROSSING_RATE_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/zero_crossing_rate.hpp>
#include <nt2/include/functions/global.hpp>

/*!
 * \ingroup core
 * \defgroup core globalzero_crossing_rate
 *
 * \par Description
 * Returns the globalzero_crossing_rate of the elements of the SIMD vector
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/globalzero_crossing_rate.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::globalzero_crossing_rate_(A0)>::type
 *     globalzero_crossing_rate(const A0 & a0);
 * }
 * \endcode
**/


namespace nt2
{
  namespace tag
  {
    struct globalzero_crossing_rate_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * rate of sign changes along a signal
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalzero_crossing_rate_, globalzero_crossing_rate, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalzero_crossing_rate_, globalzcr, 1)
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalzero_crossing_rate_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::zero_crossing_rate_>
                                            , const A0&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::zero_crossing_rate_>(), a0);
    }
  };
} }

#endif
