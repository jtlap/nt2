//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - qr factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/complexify.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

 NT2_TEST_CASE_TPL(qr_factorization, NT2_REAL_TYPES)
 {
   using nt2::tag::factorization::qr_;

   typedef nt2::table<T> t_t;
   t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
     + T(15)*nt2::eye  (4, 4, nt2::meta::as_<T>());

   typedef typename nt2::meta::call<qr_(t_t const&, char)>::type result_type;

   result_type res = nt2::factorization::qr(b, 'N');

   NT2_DISPLAY(res.p());
   NT2_DISPLAY(res.q());
   NT2_DISPLAY(res.r());
   NT2_TEST_EQUAL(res.status(), 0);
   t_t c =  nt2::ones (4, 1, nt2::meta::as_<T>());
   NT2_DISPLAY(c);
   res.inplace_solve(c);
   NT2_DISPLAY(c);
 }
 NT2_TEST_CASE_TPL(qr_factorization2, NT2_REAL_TYPES)
 {
   using nt2::tag::factorization::qr_;

   typedef nt2::table<T> t_t;
   t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
     + T(15)*nt2::eye  (4, 4, nt2::meta::as_<T>());

   typedef typename nt2::meta::call<qr_(t_t const&, char)>::type result_type;

   result_type res = nt2::factorization::qr(b, 'N');

   NT2_DISPLAY(res.p());
   NT2_DISPLAY(res.q());
   NT2_DISPLAY(res.r());
   NT2_TEST_EQUAL(res.status(), 0);
   t_t c =  nt2::ones (4, 1, nt2::meta::as_<T>());
   t_t d = b;
   t_t e = c;
   NT2_DISPLAY(c);
   res.inplace_solve(c);
   NT2_DISPLAY(c);
   NT2_DISPLAY(nt2::mtimes(d, c));
   NT2_TEST_ULP_EQUAL(nt2::mtimes(d, c), e, 2.5);
 }

NT2_TEST_CASE_TPL(qr_factorizationc, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::qr_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  ct_t b =       nt2::ones (4, 4, nt2::meta::as_<cT>())
    + T(15)*nt2::eye  (4, 4, nt2::meta::as_<cT>());

  typedef typename nt2::meta::call<qr_(ct_t const&, char)>::type result_type;

  result_type res = nt2::factorization::qr(b, 'N');

  NT2_DISPLAY(res.p());
  NT2_DISPLAY(res.q());
  NT2_DISPLAY(res.r());
  NT2_TEST_EQUAL(res.status(), 0);
  ct_t c =  nt2::ones (4, 1, nt2::meta::as_<cT>());
  ct_t e = c;
  ct_t d = b;
  NT2_DISPLAY(c);
  res.inplace_solve(c);
  NT2_DISPLAY(c);
  NT2_DISPLAY(nt2::mtimes(d, c));
  NT2_TEST_ULP_EQUAL(nt2::mtimes(d, c), e, 2.5);

  {
    ct_t cc =  nt2::reshape(nt2::complexify(nt2::_(T(1),  T(8))), 4, 2);
    NT2_DISPLAY(cc);
    ct_t bb = cc;
    bb(2, nt2::_) = cc(1, nt2::_);
    NT2_DISPLAY(bb);
  }
}
