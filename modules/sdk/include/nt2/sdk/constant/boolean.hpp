/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_BOOLEAN_HPP_INCLUDED
#define NT2_SDK_CONSTANT_BOOLEAN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Make True and False
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/constant/constant.hpp>

namespace nt2 { namespace tag
{
  struct true_  {};
  struct false_ {};
} }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::true_ , True  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::false_, False )
}

NT2_REGISTER_DISPATCH(tag::true_ ,tag::cpu_,(A0),(target_< fundamental_<A0> >))
NT2_REGISTER_DISPATCH(tag::false_,tag::cpu_,(A0),(target_< fundamental_<A0> >))

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::true_(tag::target_<tag::fundamental_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type type;
      return splat<typename A0::type>(true);
    }
  };

  template<class Dummy>
  struct  call< tag::false_(tag::target_<tag::fundamental_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type type;
      return splat<typename A0::type>(false);
    }
  };
} }

#endif
