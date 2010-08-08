/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DIGITS_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DIGITS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// List all basic -10,-9,...,0,...,10,100,1000 constants
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/constant.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <nt2/sdk/constant/details/integral_constant.hpp>

////////////////////////////////////////////////////////////////////////////////
// Constant tag
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace constants
{
  template<int N> struct digit_ { BOOST_STATIC_CONSTANT(int, value = N); };
} }

////////////////////////////////////////////////////////////////////////////////
// Natural numbers between -10 and 10
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-10> , Mten  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-9 > , Mnine )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-8 > , Meight)
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-7 > , Mseven)
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-6 > , Msix  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-5 > , Mfive )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-4 > , Mfour )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-3 > , Mthree)
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-2 > , Mtwo  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-1 > , Mone  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 0 > , Zero  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 1 > , One   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 2 > , Two   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 3 > , Three )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 4 > , Four  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 5 > , Five  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 6 > , Six   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 7 > , Seven )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 8 > , Eight )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 9 > , Nine  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 10> , Ten   )

  ////////////////////////////////////////////////////////////////////////////////
  // Larger values
  ////////////////////////////////////////////////////////////////////////////////
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 100> , Hundred  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<1000> , Thousand )

  ////////////////////////////////////////////////////////////////////////////////
  // Values sueful for trigo and what not
  ////////////////////////////////////////////////////////////////////////////////
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 45> , FortyFive         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 90> , Ninety            )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<180> , OneHundredEighty  )
}

////////////////////////////////////////////////////////////////////////////////
// Functor integration
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<int N, class Category,class Info>
  struct  call<constants::digit_<N>,Category,Info>
        : details::integral_constant< boost::mpl::int_<N>, Category >
  {};
} }

/*
NT2_CONSTANT(not_one_ , Notone  ) // ~1

*/

#endif
