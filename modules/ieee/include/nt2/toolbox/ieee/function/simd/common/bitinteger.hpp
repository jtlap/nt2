//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITINTEGER_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITINTEGER_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_positive.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitinteger_, tag::cpu_,
                             (A0)(X),
                             ((simd_<arithmetic_<A0>,X>))
                            );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::bitinteger_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      type a00 = simd::native_cast<type>(a0);
//       std::cout <<  "a0         " << a0                  << std::endl;
//       std::cout <<  "is_positive(a0) " << is_positive(a0)                  << std::endl;
//       std::cout << std::hex << "a00        " << a00                  << std::endl;
//       std::cout << "Signmask   " <<  Signmask<type>()    << std::endl;
//       std::cout << "S-a00      " << Signmask<type>()-a00 << std::endl;
      return simd::native_cast<type>(sel( is_positive(a0)
              , a00
              , Signmask<type>()-a00
                                ));
    }

  };
} }

#endif
// modified by jt the 04/01/2011
