/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_INFINITES_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_INFINITES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating infinites constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/constant/properties.hpp>

NT2_REGISTER_DISPATCH(tag::inf_,tag::cpu_,(A0), (target_< double_<A0>      > ) )
NT2_REGISTER_DISPATCH(tag::inf_,tag::cpu_,(A0), (target_< float_<A0>       > ) )
NT2_REGISTER_DISPATCH(tag::inf_,tag::cpu_,(A0), (target_< arithmetic_<A0>  > ) )

NT2_REGISTER_DISPATCH(tag::m_inf_,tag::cpu_,(A0), (target_< double_<A0>     > ) )
NT2_REGISTER_DISPATCH(tag::m_inf_,tag::cpu_,(A0), (target_< float_<A0>      > ) )
NT2_REGISTER_DISPATCH(tag::m_inf_,tag::cpu_,(A0), (target_< arithmetic_<A0> > ) )

NT2_REGISTER_DISPATCH(tag::nan_,tag::cpu_,(A0), (target_< double_<A0>     > ) )
NT2_REGISTER_DISPATCH(tag::nan_,tag::cpu_,(A0), (target_< float_<A0>      > ) )
NT2_REGISTER_DISPATCH(tag::nan_,tag::cpu_,(A0), (target_< arithmetic_<A0> > ) )
  
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::inf_(tag::target_<tag::double_>)
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
      meta::from_bits<double>::type const that = {0x7FF0000000000000LL};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Dummy>
  struct  call< tag::inf_(tag::target_<tag::float_> )
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
      meta::from_bits<float>::type const that = {0x7F800000};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Dummy>
  struct  call< tag::inf_(tag::target_<tag::arithmetic_> )
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
      return Valmax<typename A0::type>();
    }
  };

  template<class Dummy>
  struct  call< tag::m_inf_(tag::target_<tag::double_> )
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
      meta::from_bits<double>::type const that = {0xFFF0000000000000LL};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Dummy>
  struct  call< tag::m_inf_(tag::target_<tag::float_> )
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
      meta::from_bits<float>::type const that = {0xFF800000};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Dummy>
  struct  call< tag::m_inf_(tag::target_<tag::arithmetic_> )
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
      return Valmin<typename A0::type>();
    }
  };

  template<class Dummy>
  struct  call< tag::nan_(tag::target_<tag::double_>)
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
      meta::from_bits<double>::type const that = {0xFFFFFFFFFFFFFFFFLL};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Dummy>
  struct  call< tag::nan_(tag::target_<tag::float_> )
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
      meta::from_bits<float>::type const that = {0xFFFFFFFF};
      return splat<typename A0::type>(that.value);
    }
  };

//   template<class Dummy>
//   struct  call< tag::nan_(tag::target_<tag::arithmetic_> )
//               , tag::cpu_
//               , Dummy
//               >
//         : callable
//   {
//     template<class Sig> struct result;
//     template<class This, class Target>
//     struct result<This(Target)> : meta::strip<Target>::type {};

//     NT2_FUNCTOR_CALL(1)
//     {
//       return splat<typename A0::type>(0);
//     }
//   };

} }

#endif
