//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_DET_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_DET_HPP_INCLUDED

#include <nt2/linalg/functions/det.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/getrf.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/diag_of.hpp>
<<<<<<< Updated upstream
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
=======
>>>>>>> Stashed changes
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/globalprod.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::det_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
<<<<<<< Updated upstream
    typedef typename A0::value_type result_type;
=======
    typedef typename A0::value_type                 type_t;
    typedef typename boost::dispatch::meta::as_floating<type_t>
                                          ::type  result_type;
>>>>>>> Stashed changes

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG( issquare(a0)
                      , "DET: Argument must be a square matrix"
                      );

      nt2::container::table<typename A0::value_type>  lu(a0);
      nt2::container::table<nt2_la_int>               ip;
      // Factorize A as L/U
      nt2_la_int  info = nt2::getrf( boost::proto::value(lu)
                                   , boost::proto::value(ip));
      boost::dispatch::ignore_unused(info);
      // DET(A) is the product of LU(A) diagonal by -1 at the power of
      // the number of non-permutations done in LU(A)
      nt2_la_int n = nt2::numel(ip);
<<<<<<< Updated upstream
      result_type d = nt2::globalprod(nt2::diag_of(lu));
      return nt2::negif((inbtrue(eq(ip, colvect(nt2::_(nt2_la_int(1), n))))&1), d);
    }
  };



  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::det_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 & a1) const
    {
      BOOST_ASSERT_MSG( issquare(a0)
                      , "DET: Argument must be a square matrix"
                      );
      // compute e and return m for matrix determinant such that det = ldexp(m, e)
      // if no overflow or underflow can occur,  with 0.5 < abs(m) < 1 or m == 0
      // The exponent result is enough to know the order of magnitude of the determinant
      // (between 0.5*2^e and 2^e if the mantissa is non zero)
      // The mantissa result give the sign of the determinant.
      // This routine is inspired from linpack http://www.netlib.org/linpack/dgedi.f
      // that use ten power factor instead
      typedef typename meta::as_integer<result_type>::type itype_t;
      nt2::container::table<result_type> lu(a0);
      nt2::container::table<nt2_la_int> ip;
      // Factorize A as L/U
      nt2_la_int  info = nt2::getrf( boost::proto::value(lu)
                                   , boost::proto::value(ip));
      boost::dispatch::ignore_unused(info);
      nt2::container::table<result_type> tmp = diag_of(lu);
      nt2::container::table<A1> e;
      itype_t e1;
      result_type m1 = nt2::frexp(nt2::globalprod(nt2::frexp(tmp, e)), e1);
      a1 = if_else_zero(is_nez(m1), globalsum(e)+e1);
      nt2_la_int n = nt2::numel(ip);
      return nt2::negif((inbtrue(eq(ip, colvect(nt2::_(nt2_la_int(1), n))))&1), m1);
=======
      result_type sign = inbtrue(eq(ip, colvect(nt2::_(nt2_la_int(1), n))))&1 ? Mone<result_type>() : One<result_type>();
      return nt2::globalprod(nt2::diag_of(lu))*sign;
>>>>>>> Stashed changes
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::det_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::det_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 & a1) const
    {
      return nt2::frexp(a0, a1);
    }
  };
} }

#endif
