//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_IF_ELSE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_IF_ELSE_HPP_INCLUDED

#include <nt2/toolbox/operator/functions/if_else.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/pure.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>

namespace nt2 { namespace ext
{
  //complex/complex 1 -1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                            , (generic_< logical_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return result_type(if_else(a0, nt2::real(a1), nt2::real(a2)),
                         if_else(a0, nt2::imag(a1), nt2::imag(a2)));
    }
  };

  //complex/complex 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                            , (generic_< fundamental_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return if_else( is_nez(a0), a1, a2 );
    }
  };

  //imaginary/imaginary 1 -2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                            , (generic_< logical_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return bitwise_cast<result_type>(if_else(a0, nt2::imag(a1), nt2::imag(a2)));
    }
  };

  //imaginary/imaginary 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                            , (generic_< fundamental_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return if_else(is_nez(a0), a1, a2 );
    }
  };

  //complex/imaginary 1 -3
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                              (generic_< imaginary_< arithmetic_<A2> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      typedef typename meta::as_real<result_type>::type rtype;
      return if_else(a0, a1, result_type(Zero<rtype>(), nt2::imag(a2)));
    }
  };

  //complex/imaginary 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                              (generic_< imaginary_< arithmetic_<A2> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2 );
    }
  };

  //imaginary/complex/ 1 -4
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                              (generic_< complex_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      typedef typename meta::as_real<result_type>::type rtype;
      return if_else(a0, result_type(Zero<rtype>(), nt2::imag(a1)), a2);
    }
  };

  //imaginary/complex/ 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                              (generic_< complex_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      typedef typename meta::as_real<result_type>::type rtype;
      return if_else(is_nez(a0), result_type(Zero<rtype>(), nt2::imag(a1)), a2 );
    }
  };

  //dry/dry 1 -5
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                            , (generic_< logical_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              (generic_< dry_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return result_type(if_else(a0, nt2::real(a1), nt2::real(a2)));
    }
  };

  //dry/dry 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                            , (generic_< fundamental_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              (generic_< dry_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //dry/complex 1 -6
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              (generic_< complex_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, result_type(nt2::real(a1)), a2);
    }
  };

  //dry/complex 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              (generic_< complex_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //complex/dry/ 1 -7
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                              (generic_< dry_< arithmetic_<A2> > >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, a1, result_type(nt2::real(a2)));
    }
  };

  //complex/dry/ 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                              (generic_< dry_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //dry/imaginary 1 -8
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              (generic_< imaginary_< arithmetic_<A2> > >)
                            )
  {
    typedef typename meta::as_real<A2>::type rtype;
    typedef typename meta::as_complex<rtype>::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, result_type(nt2::real(a1)), result_type(Zero<rtype>(), nt2::imag(a2)));
    }
  };

  //dry/imaginary 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              (generic_< imaginary_< arithmetic_<A2> > >)
                            )
  {
    typedef typename meta::as_real<A2>::type rtype;
    typedef typename meta::as_complex<rtype>::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //imaginary/dry/ 1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                              (generic_< dry_< arithmetic_<A2> > >)
                            )
  {
    typedef typename meta::as_real<A1>::type rtype;
    typedef typename meta::as_complex<rtype>::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, result_type(Zero<rtype>(), nt2::imag(a1)), result_type(nt2::real(a2)));
    }
  };

  //imaginary/dry/ 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                              (generic_< dry_< arithmetic_<A2> > >)
                            )
  {
    typedef typename meta::as_real<A1>::type rtype;
    typedef typename meta::as_complex<rtype>::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //arithmetic/dry 1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< arithmetic_<A1> >)
                              (generic_< dry_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return result_type(if_else(a0, a1, nt2::real(a2)));
    }
  };

  //arithmetic/dry 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< arithmetic_<A1> >)
                              (generic_< dry_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //arithmetic/complex 1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< arithmetic_< arithmetic_<A1> > >)
                              (generic_< complex_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, result_type(a1), a2);
    }
  };

  //arithmetic/complex 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< arithmetic_< arithmetic_<A1> > >)
                              (generic_< complex_< arithmetic_<A2> > >)
                            )
  {
    typedef A2 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //arithmetic/imaginary 1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< arithmetic_<A1> >)
                              (generic_< imaginary_< arithmetic_<A2> > >)
                            )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, result_type(a1), result_type(Zero<A1>(), nt2::imag(a2)));
    }
  };

  //arithmetic/imaginary 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< arithmetic_<A1> >)
                              (generic_< imaginary_< arithmetic_<A2> > >)
                            )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };


  //dry/arithmetic/   1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              (generic_< arithmetic_<A2> >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return result_type(if_else(a0, nt2::real(a1), a2));
    }
  };

  //dry/arithmetic_ 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              (generic_< arithmetic_<A2> >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //complex/arithmetic/   1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                              (generic_< arithmetic_<A2> >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return result_type(if_else(a0, a1, result_type(a2)));
    }
  };

  //complex/arithmetic_ 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                              (generic_< arithmetic_<A2> >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //imaginary/arithmetic/   1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< logical_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                              (generic_< arithmetic_<A2> >)
                            )
  {
    typedef typename meta::as_complex<A2>::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return result_type(if_else(a0, result_type(Zero<A2>(), nt2::imag(a1)), result_type(a2)));
    }
  };

  //imaginary/arithmetic_ 2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< fundamental_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                              (generic_< arithmetic_<A2> >)
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };


} }

#endif
