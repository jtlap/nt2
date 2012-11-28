//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ELSE_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ELSE_ALLBITS_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_if_else_allbits if_else_allbits
 *
 * \par Description
 * If a0 is true returns a1 else returns allbits
 * \par
 * The first operand must be a boolean type according to
 * the SIMD architecture compatible to the  other one.
 * the result type is the same as the second parameter one.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/if_else_allbits.hpp>
 * \endcode
 *
 * \par Alias
 * \arg ifelsenan
 * \arg ifnot_nan_else
 * \arg ifnotallbitselse
 * \arg ifelseallbits
 * \arg ifnot_allbits_else
 * \arg ifnotallbitselse
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1>
 *     meta::call<tag::if_else_allbits_(A0,A1)>::type
 *     if_else_allbits(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of if_else_allbits
 * \param a1 the second parameter of if_else_allbits
 *
 * \return a value of the type of the second parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/


namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag if_else_allbits_ of functor if_else_allbits
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct if_else_allbits_ : ext::elementwise_<if_else_allbits_> { typedef ext::elementwise_<if_else_allbits_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, if_else_nan, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifelsenan,   2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifnot_nan_else, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifnotnanelse, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, if_else_allbits, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifelseallbits,   2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifnot_allbits_else, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifnotallbitselse, 2)
} }

#endif


