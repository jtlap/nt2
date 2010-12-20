/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/simd/details/impl/splat.hpp>

////////////////////////////////////////////////////////////////////////////////
// Forward all constant call to the simd version of themselves that splat
// the appropriate scalar constants into a proper SIMD vector.
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( Tag, tag::cpu_
                      , (Tag)(A0)(X)
                      , ((target_< simd_< arithmetic_<A0>,X> >))
                      )

namespace nt2 { namespace ext
{
  template<class Tag, class X, class Dummy>
  struct  call< Tag(tag::target_( tag::simd_(tag::arithmetic_,X)) )
              , tag::cpu_, Dummy
              >
          : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type result_type;
      typedef typename meta::scalar_of<result_type>::type type;
      functor<Tag> callee;
      return splat<result_type>(callee( nt2::meta::as_<type>()));
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// in SIMD, True is not !0 but ~0 whatever the type
// TODO : Move to details/impl/ ?
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::true_, tag::cpu_
                      , (A0)(X), ((target_< simd_< real_<A0> ,X> >))
                      )

NT2_REGISTER_DISPATCH ( tag::true_, tag::cpu_
                      , (A0)(X), ((target_< simd_< integer_<A0> ,X> >))
                      )

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct  call< tag::true_( tag::target_(tag::simd_(tag::real_,X)) )
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
      typedef typename NT2_RETURN_TYPE(1)::type result_type;
      typedef typename meta::scalar_of<result_type>::type type;
      typename meta::from_bits<type>::type that = { ~0LL };
      return splat<result_type>(that.value);
    }
  };

  template<class X, class Dummy>
  struct  call< tag::true_(tag::target_(tag::simd_(tag::integer_,X)) )
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
      typedef typename NT2_RETURN_TYPE(1)::type result_type;
      typedef typename meta::scalar_of<result_type>::type type;
      return splat<result_type>(~type(0));
    }
  };
} }

#endif
