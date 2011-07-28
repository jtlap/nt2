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
#include <nt2/sdk/constant/common.hpp>
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/toolbox/constant/include.hpp>
#include <nt2/include/functions/splat.hpp>

namespace nt2 { namespace tag
{
  //============================================================================
  /*!
   * This tag represents the constant \c N
   * \tparam N Value to generate
   */
  //============================================================================
  template<nt2::int64_t N> struct Digit{};
} }

#define NT2_CONSTANT_DIGITS_IMPLEMENTATION(VAL,NAME)		\
namespace nt2							\
{								\
  template<class Target> inline				        \
  typename meta::call<nt2::tag::Digit<VAL>(nt2::meta::as_<Target>)>::type \
  NAME()							\
  {								\
    typename nt2::make_functor<nt2::tag::Digit<VAL>, Target>::type callee; \
    return callee( nt2::meta::as_<Target>() );			\
  }								\
}								\
/**/

  //============================================================================
  // Constant functions from -10 to 10 and 20
  //============================================================================
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-10, Mten  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-9 , Mnine )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-8 , Meight)
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-7 , Mseven)
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-6 , Msix  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-5 , Mfive )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-4 , Mfour )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-3 , Mthree)
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-2 , Mtwo  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(-1 , Mone  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 0 , Zero  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 1 , One   )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 2 , Two   )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 3 , Three )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 4 , Four  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 5 , Five  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 6 , Six   )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 7 , Seven )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 8 , Eight )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 9 , Nine  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 10, Ten   )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 20, Twenty)
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 24, Twentyfour)
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 120,_120)
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 720,_720)
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(5040,_5040)
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(40320,_40320)

  //============================================================================
  // Hundred and Thousand
  //============================================================================
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 100 , Hundred  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(1000 , Thousand )

  //============================================================================
  // Values useful for trigonometric and angle related computations
  //============================================================================
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 45, Fortyfive         )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 90, Ninety            )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(180, Onehundredeighty  )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(180, C_180             )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 45, _45               )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION( 90, _90               )
  NT2_CONSTANT_DIGITS_IMPLEMENTATION(180, _180              )

  //============================================================================
  // Custom integral constant genertor function
  //============================================================================
namespace nt2 {
  template<class Target, nt2::int64_t N> inline
  typename meta::call<tag::Digit<N >(meta::as_<Target>)>::type
  integral_constant()
  {
    typename nt2::make_functor< tag::Digit<N>, Target >::type callee;
    return callee( nt2::meta::as_<Target>() );
  }
}

//==============================================================================
// Register dispatch over digits<N>
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_TPL( tag::Digit<N> , tag::cpu_
                                , (nt2::int64_t N)(class A0)
                                , (target_< scalar_< fundamental_<A0> > >)
                                )
  {
    typedef typename A0::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return  splat<result_type>(N);
    }
  };
} }

//#include <nt2/toolbox/constant/constants/scalar/digits.hpp>
#include <nt2/toolbox/constant/constants/simd/all/digits.hpp>

#endif
