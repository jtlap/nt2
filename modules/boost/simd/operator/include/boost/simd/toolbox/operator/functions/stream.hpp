//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_STREAM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_STREAM_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_stream stream
 *
 * \par Description
 * Stream data from a0 to the memory zone given by a1 and offset a2
 * and return a0. 
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/stream.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1, class A2>
 *   typename meta::call<tag::stream_(A0 const&, A1 const&, A2 const&)>::type
 *   stream(A0 const& a0, A1 const& a1, A2 const& a2 = 0);
 * }
 * \endcode
 *
 * \param a0 the object to stream
 * \param a1 the base address
 * \param a2 offset to stream at
 * 
 * \return a0
 *  
**/

namespace boost { namespace simd
{
  namespace tag { struct stream_ : ext::elementwise_<stream_> { typedef ext::elementwise_<stream_> parent; }; }
    /*!
     * \brief Define the tag stream_ of functor stream 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
  template<class A0, class A1, class A2>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::stream_(A0 const&, A1 const&, A2 const&)>::type
  stream(A0 const& a0, A1 const& a1, A2 const& a2)
  {
    return typename boost::dispatch::make_functor<tag::stream_, A0>::type()(a0, a1, a2);
  }
  
  template<class A0, class A1>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::stream_(A0 const&, A1 const&, int const&)>::type
  stream(A0 const& a0, A1 const& a1)
  {
    return typename boost::dispatch::make_functor<tag::stream_, A0>::type()(a0, a1, 0);
  }
  
} }

#endif
