/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_VALMAX_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_VALMAX_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating valmax constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

NT2_REGISTER_DISPATCH(tag::val_max_,tag::cpu_,(A0), (target_< double_<A0>    > ) )
NT2_REGISTER_DISPATCH(tag::val_max_,tag::cpu_,(A0), (target_< float_<A0>     > ) )
NT2_REGISTER_DISPATCH(tag::val_max_,tag::cpu_,(A0), (target_< unsigned_<A0>  > ) )
NT2_REGISTER_DISPATCH(tag::val_max_,tag::cpu_,(A0), (target_< signed_<A0>    > ) )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::val_max_(tag::target_<tag::double_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<double>::type const that = {0x7fefffffffffffffLL};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Dummy>
  struct  call< tag::val_max_(tag::target_<tag::float_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<float>::type const that = {0x7f7fffff};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Dummy>
  struct  call< tag::val_max_(tag::target_<tag::unsigned_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type base;
      return splat<typename A0::type>(static_cast<base>(~0));
    }
  };

  template<class Dummy>
  struct  call< tag::val_max_(tag::target_<tag::signed_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type base;
      typedef typename meta::as_unsigned<base>::type base_u;
      BOOST_STATIC_CONSTANT(base_u, value = base_u(1) << (sizeof(base_u)*CHAR_BIT-1) );
      return splat<typename A0::type>(base(~value));
    }
  };
} }

#endif
