//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SATURATE_AT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SATURATE_AT_HPP_INCLUDED

/*!
 * \file
**/

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_saturate_at saturate_at
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/saturate_at.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::saturate_at_(A0)>::type
 *     saturate_at(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of saturate_at
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag saturate_at_ of functor saturate_at
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    template <class T>
    struct saturate_at_ : ext::elementwise_< saturate_at_<T> >
    {
      typedef ext::elementwise_< saturate_at_<T> > parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::saturate_at_<A0>
                                            , saturate_at
                                            , (A1 const&)
                                            , 2
                                            )
} }

#endif
