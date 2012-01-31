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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_INSERT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_INSERT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_insert insert
 *
 * \par Description
 * insert scalar \c a0 into a SIMD vector \c a1 at position \c a2.
 * This is semantically equivalent to:
 * <tt>a1[a2] = a0;</tt>
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/insert.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1, class A2>
 *   typename meta::call<tag::insert_(A0 const&, A1 const&, A2 const&)>::type
 *   insert(A0 const& a0, A1 const& a1, A2 const& a2);
 * }
 * \endcode
 *
 * \param a0 the object to insert
 * \param a1 the SIMD vector
 * \param a2 offset to insert at
 * 
 * \return a0
 *  
**/

namespace boost { namespace simd
{
  namespace tag { struct insert_ : ext::unspecified_<insert_> {}; }
    /*!
     * \brief Define the tag insert_ of functor insert 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
  template<class A0, class A1, class A2>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::insert_(A0 const&, A1&, A2 const&)>::type
  insert(A0 const& a0, A1& a1, A2 const& a2)
  {
    return typename boost::dispatch::make_functor<tag::insert_, A0>::type()(a0, a1, a2);
  }
  
} }

#endif
