//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SATURATE_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_saturate saturate
 *
 * \par Description
 * saturate the value a0 in the template parameter type T,
 * but the value returned is of type A0
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/saturate.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::saturate_(A0)>::type
 *     saturate(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of saturate
 * 
 * \param T template parameter of saturate
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
     * \brief Define the tag saturate_ of functor saturate 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    template <class T>
    struct saturate_ : ext::elementwise_<saturate_<T> > {};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::saturate_<A0>, saturate, (A1 const&), 2)
} }

#endif
