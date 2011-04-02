//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_NEGIF_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_NEGIF_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/is_signed.hpp>
#include <nt2/include/functions/is_true.hpp>
#include <nt2/include/functions/select.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF(tag::negif_, tag::cpu_,
			 (A0)(A1)(X),
			 (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
			 (tag::negif_(tag::simd_<tag::arithmetic_,X>, tag::simd_<tag::signed_,X>)), 
			 ((simd_<arithmetic_<A0>,X>))
			 ((simd_<signed_<A1>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::negif_(tag::simd_<tag::arithmetic_, X> ,
                          tag::simd_<tag::signed_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)>: meta::strip<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      return  sel(is_true(a0),-a1,a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF(tag::negif_, tag::cpu_,
			 (A0)(A1)(X),
			 (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
			 (tag::negif_(tag::simd_<tag::arithmetic_,X>, tag::simd_<tag::real_,X>)), 
			 ((simd_<arithmetic_<A0>,X>))
			 ((simd_<real_<A1>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::negif_(tag::simd_<tag::arithmetic_, X> ,
                          tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)>: meta::strip<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      return b_xor(a1, b_and(is_true(a0), Signmask<A0>()));
    }
  };
} }

#endif
// modified by jt the 01/03/2011
