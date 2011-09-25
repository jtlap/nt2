//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SPLAT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>

#include <boost/dispatch/meta/as.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_operator
 * \defgroup splat splat function
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/splat.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::splat_(A0)>::type
 *     splat(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of splat
 * 
 * \return a value of the same type as the parameter
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag splat_ of functor splat 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct splat_  {};
  }

  template<class T, class A0> inline
  typename boost::dispatch::meta::call<tag::splat_(A0, boost::dispatch::meta::as_<T>)>::type
  splat(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::splat_, A0>::type callee;
    return callee(a0, boost::dispatch::meta::as_<T>() );
  }
} }

#endif
