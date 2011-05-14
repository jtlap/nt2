/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_IMPL_DIVIDES_FLOAT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_IMPL_DIVIDES_FLOAT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  //////////////////////////////////////////////////////////////////////////////
  // a/b use the reciprocal estimate and one pass of Newton-Raphson refinement
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct  call< tag::divides_( tag::simd_<tag::float_,tag::altivec_>
                             , tag::simd_<tag::float_,tag::altivec_>
                             )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type erb   = { vec_re(a1()) };
      type rec_b = { vec_madd ( vec_nmsub(erb(), a1(), One<type>()())
                              , erb()
                              , erb()
                              ) 
                   };
      type that  = { vec_madd(a0(),rec_b(),Zero<type>()()) };
      return that;
    }
  };
} }

#endif
