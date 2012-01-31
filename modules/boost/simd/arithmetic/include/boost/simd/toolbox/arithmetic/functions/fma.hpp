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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FMA_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FMA_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_fma fma
 *
 * \par Description
 * computes \c a0*a1+a2, but the computation with only one rounding operation
 * is only done on architectures possessing this hard wired capability
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/fma.hpp>
 * \endcode
 * 
 * \par Aliases 
 * \arg madd
 * \arg fam
 * \arg amul
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::fma_(A0,A0,A0)>::type
 *     fma(const A0 & a0,const A0 & a1,const A0 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of fma
 * \param a1 the second parameter of fma
 * \param a2 the third parameter of fma
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag fma_ of functor fma 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct fma_ : ext::elementwise_<fma_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fma_, fma, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fma_, madd, 3)

  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::fma_, fam, 3)
  {
    typename boost::dispatch::make_functor<tag::fma_, A0>::type callee;
    return callee(a1, a2, a0);
  }

  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::fma_, amul, 3)
  {
    typename boost::dispatch::make_functor<tag::fma_, A0>::type callee;
    return callee(a1, a2, a0);
  }

} }

#endif
