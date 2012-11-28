//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_FMA_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_FMA_HPP_INCLUDED
#include <nt2/toolbox/arithmetic/functions/fma.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

// This file must be rewritten
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A0> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      result_type z = result_type(fma(-nt2::imag(a1), nt2::imag(a2), fma(nt2::real(a1), nt2::real(a2), nt2::real(a0))),
                         fma(nt2::real(a1), nt2::imag(a2), fma(nt2::real(a2), nt2::imag(a1), nt2::imag(a0))));

      return if_else(logical_and(logical_and(is_real(a0), is_real(a1)), is_real(a2)), result_type(real(z)), z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
       result_type z = result_type(fma(-nt2::imag(a1), nt2::imag(a2), nt2::real(a0)),
                         fma(nt2::real(a1), nt2::imag(a2), nt2::imag(a0)));
      return if_else(logical_and(logical_and(is_real(a0), is_real(a1)), is_real(a2)), result_type(real(z)), z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      result_type z = result_type(fma(nt2::real(a1), nt2::real(a2), nt2::real(a0)),
                         fma(nt2::real(a2), nt2::imag(a1), nt2::imag(a0)));
      return if_else(logical_and(logical_and(is_real(a0), is_real(a1)), is_real(a2)), result_type(real(z)), z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<imaginary_<arithmetic_<A0> > >)
                              (generic_<complex_<arithmetic_<A1> > >)
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      result_type z = result_type(fma(-nt2::imag(a1), nt2::imag(a2), (nt2::real(a1)*nt2::real(a2))),
                         fma(nt2::real(a1), nt2::imag(a2), fma(nt2::real(a2), nt2::imag(a1), nt2::imag(a0))));
      return if_else(logical_and(logical_and(is_real(a0), is_real(a1)), is_real(a2)), result_type(real(z)), z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_ <arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return result_type(fma(-nt2::imag(a1), nt2::imag(a2), nt2::real(a0)),
                         fma(nt2::real(a1), nt2::imag(a2), nt2::imag(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A2 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return result_type(-nt2::imag(a1)*nt2::imag(a2),
                         fma(nt2::real(a2), nt2::imag(a1), nt2::imag(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<imaginary_ <arithmetic_<A2> > > )
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return result_type(-nt2::imag(a1)*nt2::imag(a2),
                         fma(nt2::real(a1), nt2::imag(a2), nt2::imag(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_complex<rA0>::type result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return result_type(-nt2::imag(a1)*nt2::imag(a2), nt2::imag(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<arithmetic_<A0> > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(fma(-nt2::imag(a1), nt2::imag(a2), fma(nt2::real(a1), nt2::real(a2), a0)),
                         fma(nt2::real(a1), nt2::imag(a2), nt2::real(a2)*nt2::imag(a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(fma(a1, nt2::real(a2), nt2::real(a0)),
                         fma(a1, nt2::imag(a2), nt2::imag(a0)));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(fma(nt2::real(a1), a2, nt2::real(a0)),
                         fma(a2, nt2::imag(a1), nt2::imag(a0)));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_< arithmetic_<A1>  > )
                              (generic_< arithmetic_<A2>  > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(fma(a1, a2, nt2::real(a0)),
                         nt2::imag(a0));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< arithmetic_<A0>  > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_< arithmetic_<A2>  > )
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(fma(nt2::real(a1), a2, a0),
                         a2*nt2::imag(a1));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<arithmetic_<A0>  > )
                              (generic_<arithmetic_<A1>  > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A2 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(fma(a1, nt2::real(a2), a0),
                         a1*nt2::imag(a2));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<arithmetic_<A0> > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<complex_  <arithmetic_<A2> > > )
                            )
  {
    typedef A2 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(fma(-nt2::imag(a1), nt2::imag(a2), a0),
                         nt2::real(a2)*nt2::imag(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<arithmetic_<A0> > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(fma(-nt2::imag(a1), nt2::imag(a2), a0),
                         nt2::real(a1)*nt2::imag(a2));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(nt2::real(a0),
                         fma(a2, nt2::imag(a1), nt2::imag(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(nt2::real(a1)*a2,
                         fma(a2, nt2::imag(a1), nt2::imag(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(nt2::real(a0),
                         fma(a1, nt2::imag(a2), nt2::imag(a0)));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A2 result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(a1*nt2::real(a2),
                         fma(a1, nt2::imag(a2), nt2::imag(a0)));
    }
  };

} }

#endif
