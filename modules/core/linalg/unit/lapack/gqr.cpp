//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/qp3.hpp>
#include <nt2/include/functions/qrf.hpp>
#include <nt2/include/functions/gqr.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(gqr_square, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;
  t_t tau_q3,tau_rf, r_q3, r_rf,qr_q3, qr_rf;
  t_i jpvt;

  t_t q  = T(10)* nt2::ones (10, 10, nt2::meta::as_<T>())
           - T(4)*nt2::eye  (10, 10, nt2::meta::as_<T>());
  t_t q_p3(q);
  t_t q_rf(q);

  nt2::qrf(q_rf,tau_rf);
  nt2::qp3(q_p3, jpvt, tau_q3);


  r_q3 = nt2::triu ( q_p3 );
  r_rf = nt2::triu ( q_rf );

  nt2::gqr(q_rf,tau_rf);
  nt2::gqr(q_p3,tau_q3);

  qr_q3 = nt2::mtimes(q_p3,r_q3);
  qr_rf = nt2::mtimes(q_rf,r_rf);


  std::size_t d = nt2::numel(jpvt);
  t_t p = nt2::zeros(d);

  for(std::size_t i = 1; i<= d;++i)
   p(jpvt(i),i) = 1;

  NT2_TEST_ULP_EQUAL(nt2::mtimes(q,p), qr_q3, T(10));
  NT2_TEST_ULP_EQUAL(q, qr_rf , T(10));
}

NT2_TEST_CASE_TPL(gqr_non_square, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;
  t_t tau_q3,tau_rf, r_q3, r_rf;
  t_i jpvt;

  t_t q  = T(10)* nt2::ones (6, 3, nt2::meta::as_<T>())
           - T(4)*nt2::eye  (6, 3, nt2::meta::as_<T>());
  t_t q_p3(q);
  t_t q_rf(q);

  nt2::qrf(q_rf,tau_rf);
  nt2::qp3(q_p3, jpvt, tau_q3);


  r_q3 = nt2::triu ( q_p3( _(1,3), _) );
  r_rf = nt2::triu ( q_rf(_(1,3), _) );


  nt2::gqr(q_rf,tau_rf);
  nt2::gqr(q_p3,tau_q3);

  t_t qr_q3 = nt2::mtimes(q_p3,r_q3);
  t_t qr_rf = nt2::mtimes(q_rf,r_rf);


  std::size_t d = nt2::numel(jpvt);
  t_t p = nt2::zeros(d);

  for(std::size_t i = 1; i<= d;++i)
   p(jpvt(i),i) = 1;


  NT2_TEST_ULP_EQUAL(nt2::mtimes(q,p), qr_q3, T(10));
  NT2_TEST_ULP_EQUAL(q, qr_rf , T(10));

}



