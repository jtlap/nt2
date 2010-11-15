//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for group
  // TODO no float no int8_


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<group_,tag::simd_(tag::arithmetic_),int16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                           type1;
      typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                 type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packs_epi16(a0, a1));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<group_,tag::simd_(tag::arithmetic_),uint16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                           type1;
      typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                 type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packus_epi16(a0, a1));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<group_,tag::simd_(tag::arithmetic_),int32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                           type1;
      typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                 type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packs_epi32(a0, a1));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<group_,tag::simd_(tag::arithmetic_),uint32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                           type1;
      typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                 type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packs_epi32(a0, a1)); //_mm_packus_epi32 pas existe avant sse4.1
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<group_,tag::simd_(tag::arithmetic_),int64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                           type1;
      typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                 type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      rtype b = {_mm_slli_si128(simd::native_cast<rtype>(a1),4)};// works only for int64 that are int32 representable
      b = b_or(b, a0);
      return simd::native_cast<rtype>(_mm_shuffle_epi32(b, NT2_SH(0, 2, 1, 3)));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<group_,tag::simd_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                           type1;
      typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                 type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };


  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<group_,tag::simd_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                           type1;
      typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                 type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      typedef typename meta::as_integer<rtype>::type itype;
      rtype r = simd::native_cast<rtype>(_mm_slli_si128(simd::native_cast<itype >(_mm_cvtpd_ps(a1)), 8));
      return b_or(r, simd::native_cast<rtype>(_mm_cvtpd_ps(a0)));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
