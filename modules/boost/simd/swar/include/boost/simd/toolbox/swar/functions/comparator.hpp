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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_COMPARATOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_COMPARATOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_comparator comparator
 *
 * \par Description
 * Compute the min and the max of the first two inputs if the third non zero,
 *  or by the max and the min if the third is zero.The function returns a value indicating if anything has changed
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/comparator.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class A0,class A1> inline
 *   typename boost::dispatch::meta::call<tag::comparator_(A0 const&,A0 const&,A1 const&)
 *                                       >::type
 *   comparator(A0 const& a0,A0 const& a1,A1 const& a2);
 *    
 *   template<class A0,class A1> inline
 *   bool comparator(A0 const& a0,A0 const& a1,A1& a2,A0& a3,A0& a4);
 * }
 * \endcode
 *
 * \param a0 the first parameter of comparator
 * \param a1 the second parameter of comparator
 * \param a2 the third parameter of comparator, a scalar integer value
 * \param a3 the fourth parameter of comparator, min or max of a0 and a1, according a2 is non zero
 * \param a4 the fith parameter of comparator, max or min of a0 and a1, according a2 is non zero
 * 
 * \return a bool value or a fusion vector of the bool and the two other results
 *  
 * \par Notes
 * \par
 * This is a swar operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation is a transform of an SIMD vector, that will return
 * vectors obtained on a non necessarily elementwise basis from the inputs
 * elements
 * \par
 * If usable and used in scalar mode, it reduces to the operation
 * on a one element vector.
 *  
**/

namespace boost { namespace simd {
  struct ascending_ {};
  struct descending_{};
  namespace tag
  {         
    /*!
     * \brief Define the tag comparator_ of functor comparator 
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct comparator_ : ext::unspecified_<comparator_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::comparator_, comparator, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::comparator_, comparator, (A0 const&)(A0 const&)(A1 const&)(A0&)(A0&), 2)
} }

#endif

// modified by jt the 25/12/2010
