//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_DIGITS_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_DIGITS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines natural number constants
 */

#include <nt2/include/simd.hpp>
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/toolbox/constant/include.hpp>
#include <nt2/sdk/constant/common.hpp>

namespace nt2 { namespace tag
{
  //============================================================================
  /*!
   * This tag represents the constant \c N
   * \tparam N Value to generate
   */
  //============================================================================
  template<nt2::int64_t N> struct digit_ {};
} }

namespace nt2
{
  //============================================================================
  // Constant functions from -10 to 10 and 20
  //============================================================================
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-10> , Mten  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-9 > , Mnine )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-8 > , Meight)
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-7 > , Mseven)
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-6 > , Msix  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-5 > , Mfive )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-4 > , Mfour )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-3 > , Mthree)
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-2 > , Mtwo  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<-1 > , Mone  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 0 > , Zero  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 1 > , One   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 2 > , Two   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 3 > , Three )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 4 > , Four  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 5 > , Five  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 6 > , Six   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 7 > , Seven )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 8 > , Eight )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 9 > , Nine  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 10> , Ten   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 20> , Twenty)

  //============================================================================
  // Hundred and Thousand
  //============================================================================
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 100> , Hundred  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<1000> , Thousand )

  //============================================================================
  // Values useful for trigonometric and angle related computations
  //============================================================================
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 45> , Fortyfive         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 90> , Ninety            )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<180> , Onehundredeighty  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<180> , C_180             )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 45> , _45               )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_< 90> , _90               )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::digit_<180> , _180              )

  //============================================================================
  // Custom integral constant genertor function
  //============================================================================
  template<class Target, nt2::int64_t N> inline
  typename meta::call<tag::digit_<N >(meta::as_<Target>)>::type
  integral_constant()
  {
    typename nt2::make_functor< tag::digit_<N>, Target >::type callee;
    return callee( nt2::meta::as_<Target>() );
  }
}

#include <nt2/toolbox/constant/constants/scalar/digits.hpp>
#include <nt2/toolbox/constant/constants/simd/all/digits.hpp>

#endif
