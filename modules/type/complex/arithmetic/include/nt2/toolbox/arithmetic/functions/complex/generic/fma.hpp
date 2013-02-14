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
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{


  //0 ccc
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(-nt2::imag(a1), nt2::imag(a0), fma(nt2::real(a0), nt2::real(a1), nt2::real(a2)));
      r_type i = fma(nt2::real(a1), nt2::imag(a0), fma(nt2::real(a0), nt2::imag(a1), nt2::imag(a2)));
      return checkr(a0, a1, a2, result_type(r, i));
    }

    static inline result_type checkr(const A0& a0,  const A1& a1,  const A2& a2, const result_type& res)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return res;
#else
      if(nt2::any(is_invalid(res)))
      {
        result_type z = nt2::multiplies(a0, a1);
        z+=a2;
        return if_else(is_invalid(res), z, res);
      }
      return res;
#endif

    }
  };

  //1 cci
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(-nt2::imag(a1), nt2::imag(a0), nt2::real(a1)*nt2::real(a0));
      r_type i = fma(nt2::real(a1), nt2::imag(a0), fma(nt2::real(a0), nt2::imag(a1), nt2::imag(a2)));
      return checkr(a0, a1, a2, r, i);
    }

    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(testi, nt2::logical_and(nt2::logical_and(nt2::is_real(a0), nt2::is_real(a1)), nt2::is_invalid(i)));
      BOOST_AUTO_TPL(testr, nt2::logical_and(nt2::logical_and(nt2::is_real(a0), nt2::is_imag(a1)), nt2::is_invalid(r)));
      return result_type(nt2::if_zero_else(testr, r), nt2::if_else(testi, nt2::imag(a2), i));
#endif

    }
  };

  //2 cic
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(-nt2::imag(a1), nt2::imag(a0), nt2::real(a2));
      r =  nt2::seladd(nt2::is_eqz(a1), r, nt2::Zero<r_type>()*real(a0));
      r_type i = fma(nt2::real(a0), nt2::imag(a1), nt2::imag(a2));
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(nt2::is_real(a0), nt2::is_invalid(i)));
      return result_type(r, nt2::if_else(test, imag(a2), i));
#endif

    }
  };
  //3 icc
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > >)
                              (generic_<complex_<arithmetic_<A1> > >)
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  // 4 cii
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_ <arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = -nt2::imag(a0)*nt2::imag(a1);
      r_type i = fma(nt2::real(a0), nt2::imag(a1), nt2::imag(a2));
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, r_type& r, r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(nt2::logical_and(nt2::logical_and(nt2::is_real(a0), nt2::is_real(a1)), nt2::is_real(a2)), nt2::is_nez(i)));
      r = if_zero_else(nt2::logical_or(nt2::is_eqz(a0), nt2::is_eqz(a1)), r);
      return result_type(r, nt2::if_zero_else(test, i));
#endif

    }
  };

  // 5 iic
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A2 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(-nt2::imag(a1), nt2::imag(a0), nt2::real(a2));
      r_type i = nt2::imag(a2);
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, r_type& r, r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(logical_or(nt2::is_real(a1), is_real(a0)), nt2::is_invalid(r)));
      i =  nt2::seladd(nt2::is_eqz(a1), i, nt2::Zero<r_type>()*imag(a0));
      i =  nt2::seladd(nt2::is_eqz(a0), i, nt2::Zero<r_type>()*imag(a1));
      r = if_else(test, real(a2), r);
      return result_type(r, i);
#endif

    }
  };

  // 6 ici
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<imaginary_ <arithmetic_<A2> > > )
    )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  // 7 iii
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
    )
  {
    typedef typename meta::as_real<A0>::type r_type;
    typedef typename meta::as_complex<r_type>::type result_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = -nt2::imag(a0)*nt2::imag(a1);
      r_type i = imag(a2);
      return checkr(a0, a1, a2, r, i);
    }

    static inline result_type checkr(const A0& a0,const A1& a1, const A2& a2, r_type& r, r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(logical_or(nt2::is_real(a1), is_real(a0)), nt2::is_invalid(r)));
      i =  nt2::seladd(nt2::is_eqz(a1), r, nt2::Zero<r_type>()*imag(a0));
      i =  nt2::seladd(nt2::is_eqz(a0), r, nt2::Zero<r_type>()*imag(a1));
      r = if_zero_else(nt2::logical_or(nt2::is_eqz(a0), nt2::is_eqz(a1)), r);
      return result_type(r, nt2::if_else(test, i, nt2::imag(a2)));
#endif
    }
  };

  //8 acc
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0> > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A1 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(a0, real(a1), real(a2));
      r_type i = fma(a0, imag(a1), imag(a2));
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, r_type& r, r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      r =  if_else(is_invalid(a0),
                   if_else(is_real(a1),
                           r,
                           if_else(nt2::is_imag(a1), real(a2),r)),
                   r
        );
      i =  if_else(is_invalid(a0),
                   if_else(is_real(a1), imag(a2), i),
                   i);
      return result_type(r, i);
#endif
    }
  };

  //9 cac
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  //10 cca
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r =fma(-nt2::imag(a1), nt2::imag(a0), fma(nt2::real(a1), nt2::real(a0), a2));
      r_type i = fma(nt2::real(a1), nt2::imag(a0), nt2::real(a0)*nt2::imag(a1));
      return checkr(a0, a1, a2, r, i);

    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(nt2::logical_and(nt2::is_real(a1), nt2::is_real(a0)), nt2::is_nez(i)));
      BOOST_AUTO_TPL(testr, nt2::logical_and(logical_or(nt2::is_eqz(a1), is_eqz(a0)),
                                             logical_and(logical_and(is_imag(a0),
                                                                     is_imag(a1)),
                                                         nt2::is_invalid(r))));
      return result_type(if_else(testr, a2, r), nt2::if_zero_else(test, i));
#endif

    }
  };

  //11 caa
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_< arithmetic_<A1>  > )
                              (generic_< arithmetic_<A2>  > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(nt2::real(a0), a1, a2);
      r_type i = nt2::imag(a0)*a1;
      return checkr(a0, r, i);
    }
    static inline result_type checkr(const A0& a0, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(nt2::is_real(a0), nt2::is_nez(i)));
      return result_type(r, nt2::if_zero_else(test, i));
#endif
    }
  };

  //12 aca
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_< arithmetic_<A0>  > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_< arithmetic_<A2>  > )
    )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  //13 aac
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0>  > )
                              (generic_<arithmetic_<A1>  > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A2 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return result_type( fma(a0, a1, nt2::real(a2))
                          , nt2::imag(a2)
        );
    }
  };

  //14 aic
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0> > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<complex_  <arithmetic_<A2> > > )
    )
  {
    typedef A2 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = real(a2);
      r_type i = fma(a0, nt2::imag(a1), nt2::imag(a2));
      return checkr(a0, a1, a2, r, i);

    }
    static inline result_type checkr(const A0& a0,const A1& a1, const A2& a2, r_type& r, r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      r =  if_else(is_invalid(a0),
                   if_else(is_real(a1),
                           nt2::Nan<r_type>(),
                           real(a2)),
                   r
        );
      i =  if_else(is_invalid(a0),
                   if_else(is_real(a1), imag(a2), i),
                   i);
      return result_type(r, i);
#endif
    }
  };

  //15 aci
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0> > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
    )
  {
    typedef A1 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = a0*nt2::real(a1);
      r_type i = fma(a0, nt2::imag(a1), nt2::imag(a2));
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, const r_type& r, r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      i =  if_else(is_invalid(a0),
                   if_else(is_real(a1), imag(a2), i),
                   i);
      return result_type(r,i);
#endif
    }
  };

  //16 cia
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(-nt2::imag(a0), nt2::imag(a1), a2);
      r_type i = nt2::real(a0)*nt2::imag(a1);
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(nt2::is_real(a1), nt2::logical_and(nt2::is_real(a0), nt2::is_nez(i))));
      r =  nt2::seladd(nt2::is_eqz(a1), r, nt2::Zero<r_type>()*real(a0));
      BOOST_AUTO_TPL(testr, nt2::logical_and(is_eqz(a0), nt2::is_invalid(r)));
      return result_type(if_else(testr, real(a2), r), nt2::if_zero_else(test, i));
#endif
    }
  };

  //17 ica
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
    )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  //18 cai
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
    )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  //19 iac
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A2 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  //20 aai
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0> > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
    )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return result_type(a1*a0, nt2::imag(a2));
    }
  };

  //21 aia
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0> > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
    )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    typedef A0 r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = a2;
      r_type i =  nt2::imag(a1)*a0;
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test,  nt2::logical_and(nt2::is_eqz(imag(a1)), nt2::is_invalid(a0)));
      return result_type(if_nan_else(test,r), nt2::if_zero_else(test, i));
#endif
    }

  };

  //22 iaa
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<arithmetic_<A2> > )
   )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  //23 aii
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0> > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
    )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    typedef A0 r_type;

    NT2_FUNCTOR_CALL(3)
    {
      r_type r = Zero<r_type>();
      r_type i = fma(a0, imag(a1), imag(a2));
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(testr, nt2::logical_and(nt2::is_eqz(a1), nt2::is_invalid(a0)));
      return result_type(if_nan_else(testr,r), nt2::if_else(testr, imag(a2), i));
#endif
    }
  };

  //24 iia
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<imaginary_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
    )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    typedef A2 r_type;

    NT2_FUNCTOR_CALL(3)
    {
      r_type i = Zero<r_type>();
      r_type r = nt2::fma(nt2::imag(a0), -nt2::imag(a1), a2);
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(nt2::logical_or(nt2::is_eqz(a0), nt2::is_eqz(a1)),
                                            nt2::is_invalid(nt2::imag(a0)+nt2::imag(a1))));
      return result_type(nt2::if_else(test,a2,r), nt2::if_nan_else(test, i));
#endif
    }
  };

  //25 iai
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<imaginary_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<imaginary_<arithmetic_<A2> > > )
    )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return nt2::fma(a1, a0, a2);
    }
  };

  /// adding dry

#define NT2_FMA(T1, T2, T3, CALL)                                  \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)  \
                              , T1 T2 T3                               \
    )                                                                  \
  {                                                                    \
    typedef typename meta::as_complex<A0>::type result_type;           \
    NT2_FUNCTOR_CALL(3)                                                \
    {                                                                  \
      return CALL;                                                     \
    }                                                                  \
  }                                                                    \
/**/
#define NT2_FMAD(T1, T2, T3, CALL)                                 \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)  \
                              , T1 T2 T3                               \
    )                                                                  \
  {                                                                    \
    typedef typename meta::as_dry<A0>::type result_type;               \
    NT2_FUNCTOR_CALL(3)                                                \
    {                                                                  \
      return CALL;                                                     \
    }                                                                  \
  }                                                                    \
/**/
#define NT2_SCA(I) (generic_<arithmetic_<A##I> > )
#define NT2_DRY(I) (generic_<dry_<arithmetic_<A##I> > > )
#define NT2_COM(I) (generic_<complex_<arithmetic_<A##I> > > )
#define NT2_IMA(I) (generic_<imaginary_<arithmetic_<A##I> > > )

//   NT2_FMA(DRY(1), NT2_DRY(2), NT2_DRY(3), nt2::fma(real(a0), real(a1), real(a2)))

//   NT2_FMAD(NT2_DRY(1), NT2_SCA(2), NT2_SCA(),     nt2::fma(real(a0), a1, a2));
//   NT2_FMA (NT2_DRY(1), NT2_SCA(2), NT2_COM(),    nt2::fma(real(a0), a1, a2));
//   NT2_FMA (NT2_DRY(1), NT2_SCA(2), NT2_IMA(),  nt2::fma(real(a0), a1, a2));

//   NT2_FMA(NT2_DRY(1), NT2_COM(2),    NT2_SCA(),     nt2::fma(real(a0), a1, a2));
//   NT2_FMA(NT2_DRY(1), NT2_COM(2),    NT2_COM(),    nt2::fma(real(a0), a1, a2));
//   NT2_FMA(NT2_DRY(1), NT2_COM(2),    NT2_IMA(),  nt2::fma(real(a0), a1, a2));

//   NT2_FMA(NT2_DRY(1), NT2_IMA(2),  NT2_SCA(),     nt2::fma(real(a0), a1, a2));
//   NT2_FMA(NT2_DRY(1), NT2_IMA(2),  NT2_COM(),    nt2::fma(real(a0), a1, a2));
//   NT2_FMA(NT2_DRY(1), NT2_IMA(2),  NT2_IMA(),  nt2::fma(real(a0), a1, a2));

//   NT2_FMAD(NT2_SCA(), NT2_DRY(2), NT2_SCA(),    nt2::fma(a0, real(a1, a2));
//   NT2_FMA(NT2_SCA(), NT2_DRY(2), NT2_COM(),    nt2::fma(a0, real(a1, a2));
//   NT2_FMA(NT2_SCA(), NT2_DRY(2), NT2_IMA(),  nt2::fma(a0, real(a1, a2));

//   NT2_FMA(NT2_COM(),    NT2_DRY(2), NT2_SCA(),     nt2::fma(a0, real(a1), a2));
//   NT2_FMA(NT2_COM(),    NT2_DRY(2), NT2_COM(),    nt2::fma(a0, real(a1), a2));
//   NT2_FMA(NT2_COM(),    NT2_DRY(2), NT2_IMA(),  nt2::fma(a0, real(a1), a2));

//   NT2_FMA(NT2_IMA(),  NT2_DRY(2), NT2_SCA(),     nt2::fma(a0, real(a1), a2));
//   NT2_FMA(NT2_IMA(),  NT2_DRY(2), NT2_COM(),    nt2::fma(a0, real(a1), a2));
//   NT2_FMA(NT2_IMA(),  NT2_DRY(2), NT2_IMA(),  nt2::fma(a0, real(a1), a2));

//   NT2_FMAD(NT2_SCA(), NT2_SCA(2), NT2_DRY(2),    nt2::fma(a0, a1, real(a2)));
//   NT2_FMA(NT2_SCA(), NT2_COM(2),    NT2_DRY(2), nt2::fma(a0, a1, real(a2)));
//   NT2_FMA(NT2_SCA(), NT2_IMA(2),  NT2_DRY(2), nt2::fma(a0, a1, real(a2)));

//   NT2_FMA(NT2_COM(),    NT2_SCA(),     NT2_DRY(3), nt2::fma(a0, a1, real(a2)));
//   NT2_FMA(NT2_COM(),    NT2_COM(),    NT2_DRY(3), nt2::fma(a0, a1, real(a2)));
//   NT2_FMA(NT2_COM(),    NT2_IMA(),  NT2_DRY(3), nt2::fma(a0, a1, real(a2)));

//   NT2_FMA(NT2_IMA(),  NT2_SCA(),     NT2_DRY(3), nt2::fma(a0, a1, real(a2)));
//   NT2_FMA(NT2_IMA(),  NT2_COM(),    NT2_DRY(3), nt2::fma(a0, a1, real(a2)));
//   NT2_FMA(NT2_IMA(),  NT2_IMA(),  NT2_DRY(3), nt2::fma(a0, a1, real(a2)));

//   NT2_FMAD(NT2_DRY(1), NT2_DRY(2),  NT2_SCA(),    nt2::fma(real(a0), real(a1), a2));
//   NT2_FMA(NT2_DRY(1), NT2_DRY(2),  NT2_COM(),    nt2::fma(real(a0), real(a1), a2));
//   NT2_FMA(NT2_DRY(1), NT2_DRY(2),  NT2_IMA(),  nt2::fma(real(a0), real(a1), a2));

//   NT2_FMAD(NT2_SCA(), NT2_DRY(2), NT2_DRY(3),     nt2::fma(real(a0), real(a1), a2));
//   NT2_FMA(NT2_COM(),    NT2_DRY(2), NT2_DRY(3),  nt2::fma(real(a0), real(a1), a2));
//   NT2_FMA(NT2_IMA(),  NT2_DRY(2), NT2_DRY(3),  nt2::fma(real(a0), real(a1), a2));

//   NT2_FMAD( NT2_DRY(1), NT2_SCA(),    NT2_DRY(3),    nt2::fma(real(a0), real(a1), a2));
//   NT2_FMA( NT2_DRY(1), NT2_COM(),    NT2_DRY(3), nt2::fma(real(a0), real(a1), a2));
//   NT2_FMA( NT2_DRY(1), NT2_IMA(),  NT2_DRY(3), nt2::fma(real(a0), real(a1), a2));

#undef NT2_DRY
#undef NT2_SCA
#undef NT2_COM
#undef NT2_IMA
#undef NT2_FMA
#undef NT2_FMAD

 } }

#endif
