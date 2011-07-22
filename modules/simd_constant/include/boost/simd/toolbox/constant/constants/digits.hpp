//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DIGITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DIGITS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines natural number constants
 */

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include.hpp>

namespace boost { namespace dispatch { namespace tag
{
  //============================================================================
  /*!
   * This tag represents the constant \c N
   * \tparam N Value to generate
   */
  //============================================================================
  template<boost::simd::int64_t N> struct digit_ {};
} } }

namespace boost { namespace simd
{
  //============================================================================
  // Constant functions from -10 to 10 and 20
  //============================================================================
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-10> , Mten  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-9 > , Mnine )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-8 > , Meight)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-7 > , Mseven)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-6 > , Msix  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-5 > , Mfive )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-4 > , Mfour )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-3 > , Mthree)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-2 > , Mtwo  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<-1 > , Mone  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 0 > , Zero  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 1 > , One   )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 2 > , Two   )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 3 > , Three )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 4 > , Four  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 5 > , Five  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 6 > , Six   )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 7 > , Seven )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 8 > , Eight )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 9 > , Nine  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 10> , Ten   )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 20> , Twenty)

  //============================================================================
  // Hundred and Thousand
  //============================================================================
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 100> , Hundred  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<1000> , Thousand )

  //============================================================================
  // Values useful for trigonometric and angle related computations
  //============================================================================
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 45> , Fortyfive         )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 90> , Ninety            )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<180> , Onehundredeighty  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<180> , C_180             )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 45> , _45               )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_< 90> , _90               )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::digit_<180> , _180              )

  //============================================================================
  // Custom integral constant genertor function
  //============================================================================
  template<class Target, boost::simd::int64_t N> inline
  typename boost::dispatch::meta::call<boost::dispatch::tag::digit_<N >(boost::dispatch::meta::as_<Target>)>::type
  integral_constant()
  {
    typename boost::dispatch::make_functor< tag::digit_<N>, Target >::type callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }
} }

#include <boost/simd/toolbox/constant/constants/scalar/digits.hpp>
#include <boost/simd/toolbox/constant/constants/simd/all/digits.hpp>

#endif
