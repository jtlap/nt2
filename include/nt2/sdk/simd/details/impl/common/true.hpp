//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_TRUE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_TRUE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// in SIMD, True is not !0 but ~0 whatever the type
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
  struct  call< tag::true_( tag::target_<tag::simd_<tag::real_,X> >)
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
      typedef typename meta::as_integer<type>::type    int_type;
      typename meta::from_bits<type>::type that = { ~int_type(0) };
      return splat<result_type>(that.value);
    }
  };

  template<class X, class Dummy>
  struct  call< tag::true_(tag::target_<tag::simd_<tag::integer_,X> >)
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
