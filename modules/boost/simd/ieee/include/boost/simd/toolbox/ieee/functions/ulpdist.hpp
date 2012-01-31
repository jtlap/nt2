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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_ULPDIST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_ULPDIST_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_ulpdist ulpdist
 *
 * \par Description
 * Returns ulp distance of the two values.
 * \par
 * \arg If the common type is integer it is the same as \c dist
 * \arg If the common type is floating point the ulpdist is is computed,
 * by the above described method
 * \par
 * It is often difficult to  answer to the following question:
 * \arg are these two floating computations results similar enough?
 * \par
 * The ulpdist is a way to answer which is tuned for relative errors estimations
 * and peculiarly adapted to cope with the limited bits accuracy of floating point
 * representations.
 * The method is the following:
 * \par
 * Properly normalize the two numbers by the same factor in a way that 
 * the largest of the two numbers exponents will be brought to zero
 * Return the absolute difference of these normalized numbers
 * divided by the rounding error Eps
 * \par
 * The roundind error is the ulp (unit in the last place) value, i.e. the
 * floating number, the exponent of which is 0 and the mantissa is all zeros
 * but a 1 in the last digit (it is not hard coded that way however).
 * This means 2^-23 for floats and 2^-52 for double
 * \arg For instance if two floating numbers (of same type) have an ulpdist of 
 * zero that means that their floating representation are identical.
 * \arg Generally equality up to 0.5 ulp is the best that one can wish beyond
 * strict equality.
 * \arg Typically if a double is compared to the float representation of
 * its floating conversion (they are exceptions as for fully representable
 * reals) the ulpdist will be around 2^26.5 (~10^8)
 * \par
 * The ulpdist is also roughly equivalent to the number of representable
 * floating points values between two given floating points values.
 * \par
 * \arg  \c ulpdist(1.0,1+Eps\<double\>())==0.5
 * \arg  \c ulpdist(1.0,1+Eps\<double\>()/2)==0.0
 * \arg  \c ulpdist(1.0,1-Eps\<double\>()/2)==0.25
 * \arg  \c ulpdist(1.0,1-Eps\<double\>())==0.5 
 * \arg  \c ulpdist(double(Pi\<float\>()),Pi\<double\>())==9.84293e+07
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/ulpdist.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::ulpdist_(A0,A0)>::type
 *     ulpdist(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of ulpdist
 * \param a1 the second parameter of ulpdist
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
     * \brief Define the tag ulpdist_ of functor ulpdist 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct ulpdist_ : ext::elementwise_<ulpdist_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ulpdist_, ulpdist, 2)
} }

#endif

// modified by jt the 25/12/2010
