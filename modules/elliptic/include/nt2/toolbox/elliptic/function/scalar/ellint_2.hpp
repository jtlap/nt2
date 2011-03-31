//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SCALAR_ELLINT_2_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SCALAR_ELLINT_2_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/toolbox/polynomials/function/scalar/impl/horner.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellint_2_, tag::cpu_,
                          (A0),
                          (arithmetic_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ellint_2_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::ellint_2(type(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellint_2_, tag::cpu_,
                          (A0),
                          (real_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ellint_2_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      type x = nt2::abs(a0);
      if (x>One<A0>())    return Nan<A0>();
      if (x == One<A0>()) return x;
      return boost::math::ellint_2(a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::ellint_2_, tag::cpu_,
//                           (A0),
//                           (float_<A0>)
//                          )

// namespace nt2 { namespace ext
// {
//   template<class Dummy>
//   struct call<tag::ellint_2_(tag::float_),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0)> :
//       std::tr1::result_of<meta::floating(A0)>{};

//     NT2_FUNCTOR_CALL(1)
//     {
//       A0 x = nt2::abs(a0);
//       if (x>One<A0>()) return Nan<A0>();
//       if (x == One<A0>()) return x;
//       const A0 a = nt2::sqrt(oneminus(x));
//       return horner< NT2_HORNER_COEFF_T(A0, 11,
//                               (0x392102f5,
//                                0x3b246c1b,
//                                0x3c0e578f,
//                                0x3c2fe240,
//                                0x3bfebca9,
//                                0x3bf882cf,
//                                0x3c3d8b3f,
//                                0x3cb2d89a,
//                                0x3d68ac90,
//                                0x3ee2e430,
//                                0x3f800000) ) > (a)
//                 -log(a)*a*horner< NT2_HORNER_COEFF_T(A0, 10,
//                                     (0x38098de4,
//                                      0x3a84557e,
//                                      0x3bd53114,
//                                      0x3c8a54f6,
//                                      0x3cd67118,
//                                      0x3d0925e1,
//                                      0x3d2ef92b,
//                                      0x3d6fffe9,
//                                      0x3dc00000,
//                                      0x3e800000
//                                      ) ) > (a);
//     }
//   };
// } }

#endif
// modified by jt the 26/12/2010
