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
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-10> , MTen  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-9 > , MNine )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-8 > , MEight)
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-7 > , MSeven)
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-6 > , MSix  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-5 > , MFive )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-4 > , MFour )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-3 > , MThree)
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-2 > , MTwo  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<-1 > , MOne  )
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
        : details::integral_constant< boost::mpl::int_<N>, Category>
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Invalidate integral value greater than their static limits
  //////////////////////////////////////////////////////////////////////////////
  template<int N, class Category,class Info>
  struct  validate<constants::digit_<N>,Category,Info>
  {
    template<class T, bool EnableIf= boost::is_signed<T>::value>
    struct  inner
          : boost::mpl::bool_ <   ((1LL << (sizeof(T)*CHAR_BIT)) > N )
                              &&  ( N >= 0  )
                              > {};

    template<class T>
    struct  inner<T,true>
          : boost::mpl::bool_ <   (((1LL << (sizeof(T)*CHAR_BIT-1))-1) >=  N )
                              &&  ( (1LL << (sizeof(T)*CHAR_BIT-1))    >= -N )
                              > {};


    template<class Sig> struct result;
    template<class This,class Target>
    struct result<This(nt2::meta::as_<Target>)>
      : boost::mpl::bool_<  inner<Target>::value
                            || boost::is_floating_point<Target>::value
                          >
    {};
  };

} }

/*
NT2_CONSTANT(not_one_ , Notone  ) // ~1

*/

#endif
