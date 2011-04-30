//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_ADDS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_ADDS_HPP_INCLUDED
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/select.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<real_<A0>,X>))
                          ((simd_<real_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::adds_(tag::simd_<tag::real_, X>,
			 tag::simd_<tag::real_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::add(a0, a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<uint_<A0>,X>))
                          ((simd_<uint_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::adds_(tag::simd_<tag::uint_, X>,
			 tag::simd_<tag::uint_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 a0pa1 = a0+a1;
      return b_or(a0pa1, lt(a0pa1, a0)); 
     //      return sel(lt(a0pa1, nt2::max(a0, a1)), Valmax<A0>(), a0pa1); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<int_<A0>,X>))
                          ((simd_<int_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::adds_(tag::simd_<tag::int_, X>,
			 tag::simd_<tag::int_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 gtza0 = is_gtz(a0);
      A0 gtza1 = is_gtz(a1);
      A0 a0pa1 = a0+a1;
      A0 test1 = b_and(gtza0, b_and(gtza1, (lt(a0pa1, nt2::max(a0, a1))))); 
      A0 test2 = b_andnot(b_andnot(b_or(is_gtz(a0pa1),gt(a0pa1, nt2::min(a0, a1))),gtza0),gtza1);
      return sel(test1,Valmax<A0>(),sel(test2,Valmin<A0>(),a0pa1)); 
    }
  };
} }

#endif
