//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_RAT_SIGMOID_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_RAT_SIGMOID_HPP_INCLUDED
#include <nt2/statistics/functions/rat_sigmoid.hpp>

#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( rat_sigmoid_, tag::cpu_
                              , (A0)
                              , (generic_< single_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      const A0 _289  = single_constant< A0, 0x43908000> ();
      A0 x2 = sqr(a0);
      return average(
        if_else(ge(x2, _289),
                signnz(a0),
                a0*horner< NT2_HORNER_COEFF_T(stype, 4,
                                              (0xaf1fc6d2,
                                               0xb4c34d4c,
                                               0xb8a9f321,
                                               0xbb2dea54
                                              ) ) > (x2)/
                   horner< NT2_HORNER_COEFF_T(stype, 4,
                                              (0xb23d50b6,
                                               0xb6e66086,
                                               0xba1e6d8a,
                                               0xbbadea5f
                                              ) ) > (x2)
               )
        , One<A0>()
      );

    }
  };
  BOOST_DISPATCH_IMPLEMENT  ( rat_sigmoid_, tag::cpu_
                              , (A0)
                              , (generic_< double_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      const A0 _289  = double_constant< A0, 0x4072100000000000ll> ();
      A0 x2 = sqr(a0);
      return average(
        if_else(ge(x2, _289),
                signnz(a0),
                a0*horner< NT2_HORNER_COEFF_T(stype, 4,
                                              (
                                                0xbde3f8da4c506a28ll,
                                                0xbe9869a971d4a30cll,
                                                0xbf153e641c5c0898ll,
                                                0xbf65bd4a7046af9dll
                                              ) ) > (x2)/
                   horner< NT2_HORNER_COEFF_T(stype, 4,
                                              (
                                                0xbe47aa16b28bb73dll,
                                                0xbedccc10b9d25998ll,
                                                0xbf43cdb13effaf64ll,
                                                0xbf75bd4bd665c758ll
                                              ) ) > (x2)
               )
        , One<A0>()
      );

    }
  };
} }

// p =

//     -1.940498733720220e-10    -4.671971413119245e-07    -1.022851039147061e-04    -3.334794689789135e-03
//   0xaf555c2f,
//   0xb4fad316,
//   0xb8d681e6,
//   0xbb5a8c92

// q =

//     -1.438780662693109e-08    -8.721679967449728e-06    -7.603587145259541e-04    -6.669593918493321e-03
//   0xb2772e3e,
//   0xb7125355,
//   0xba4752cf,
//   0xbbda8c9c



#endif




// p =

//     -1.453160145661359e-10    -3.637782003013016e-07    -8.103834178644004e-05    -2.653737438057703e-03
// 0xbde3f8da4c506a28ll,
// 0xbe9869a971d4a30cll,
// 0xbf153e641c5c0898ll,
// 0xbf65bd4a7046af9dll,


// q =

//     -1.101959908172314e-08    -6.865770868411113e-06    -6.043544253748587e-04    -5.307480087468473e-03
// 0xbe47aa16b28bb73dll,
// 0xbedccc10b9d25998ll,
// 0xbf43cdb13effaf64ll,
// 0xbf75bd4bd665c758ll,


