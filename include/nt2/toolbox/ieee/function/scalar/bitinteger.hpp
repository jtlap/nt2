//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITINTEGER_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITINTEGER_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/include/functions/is_positive.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitinteger_, tag::cpu_,
                            (A0),
                            (fundamental_<A0>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::bitinteger_(tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_bits<A0, signed>::type type;
      typedef typename meta::as_integer<A0, signed>::type itype;
      type that = {a0};
//       std::cout <<  "a0         " << a0                  << std::endl;
//       std::cout <<  "is_positive(a0) " << is_positive(a0)                  << std::endl;
//       std::cout << "that.bits " <<  that.bits          << std::endl;
//       std::cout << "Signmask  " <<  Signmask<itype>()  << std::endl;
//       std::cout << "S-that    " << Signmask<itype>()-that.bits << std::endl;
      return is_positive(a0) ? that.bits : Signmask<itype>()-that.bits;
    }

  };
} }

#endif
// modified by jt the 26/12/2010
