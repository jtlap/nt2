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
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/constant/constant.hpp>

////////////////////////////////////////////////////////////////////////////////
// Constant tag
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace constants
{
  template<nt2::int64_t N> struct digit_ { BOOST_STATIC_CONSTANT(int, value = N); };
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
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 20> , Twenty)

  ////////////////////////////////////////////////////////////////////////////////
  // Larger values
  ////////////////////////////////////////////////////////////////////////////////
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 100> , Hundred  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<1000> , Thousand )

  ////////////////////////////////////////////////////////////////////////////////
  // Values useful for trigo and what not
  ////////////////////////////////////////////////////////////////////////////////
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 45> , Fortyfive         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_< 90> , Ninety            )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<180> , Onehundredeighty  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::digit_<180> , C_180             )

  ////////////////////////////////////////////////////////////////////////////////
  // Local digit based constant generator
  ////////////////////////////////////////////////////////////////////////////////
  template<class Target, nt2::int64_t N> inline
  typename meta::enable_call<constants::digit_<N>(meta::as_<Target>)>::type
  integral_constant()
  {
    nt2::functors::functor< constants::digit_<N> > callee;
    return callee( nt2::meta::as_<Target>() );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Functor integration
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<nt2::int64_t N, class Category,class Hierarchy,class Info>
  struct  call<constants::digit_<N>,tag::constant_(Category),Hierarchy,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    template<class Target> inline typename Target::type const
    operator()( Target const& ) const
    {
      typename Target::type that = splat<typename Target::type>(N);
      return that;
    }
  };
} }

#endif
