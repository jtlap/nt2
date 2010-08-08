/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_SHIFT_LEFT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_SHIFT_LEFT_HPP_INCLUDED

#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // only allow shift if A1 is integral and both arguments have same size
  //////////////////////////////////////////////////////////////////////////////
  template<class C, class X,class Dummy>
  struct validate<shift_left_,tag::simd_(C,X),Dummy>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::mpl::bool_ <     meta::is_integral<A1>::value,
                          &&  (   sizeof( typename meta::scalar_of<A0>::type)
                              ==  sizeof( typename meta::scalar_of<A1>::type)
                              )
                        >{};
  };

  template<class C, class X,class Dummy>
  struct call<shift_left_,tag::simd_(C,X),Dummy>
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)> { typedef A0 type; };

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = map(functor<shift_left_>(), a0, a1);
      return that;
    }
  };
} }

#endif
