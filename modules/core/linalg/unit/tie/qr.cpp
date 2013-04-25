//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied qr function"

#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/rand.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


template<typename T>
 nt2::table<T> extract_p(nt2::table<T>& jpvt)
  {
   std::size_t d = nt2::numel(jpvt);
   nt2::table<T> p = nt2::zeros(d);

   for(std::size_t i = 1; i<= d;i++)
     p(static_cast<int>(jpvt(i)),i) = 1;

   return p;
  }

NT2_TEST_CASE_TPL ( direct_qr, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> x, q, r, p,ux,u;
  nt2::table<T> a = nt2::rand(6 , 6, as_<T>());
  nt2::table<T> b = nt2::ones(4, 4, as_<T>());
  u = nt2::zeros(4);
  u(1,1) = u(1,2) = u(1,3) = u(1,4) = -2;

  /// Interface tests

  // X = QR(A)
  x = nt2::qr(b);
  ux = triu(x);
  NT2_TEST_ULP_EQUAL(ux,u,T(200));

  // [Q,R] = QR(A)
  nt2::tie(q, r) = nt2::qr(a);
  NT2_TEST_ULP_EQUAL( a, nt2::mtimes(q, r), T(200));

  // [Q,R,P] = QR(A)
  nt2::tie(q, r, p) = nt2::qr(a);
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,p), nt2::mtimes(q, r), T(200));
}


NT2_TEST_CASE_TPL ( option_qr_square, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;
  using nt2::pivot_;
  using nt2::matrix_;
  using nt2::vector_;
  using nt2::no_pivot_;

  typedef  nt2::table<T> t_t;
  nt2::table<T> x, q, q1, r, r1, p, p1;
  nt2::table<T> a = nt2::rand(6 , 6, as_<T>());

  /// Interface tests

  // [Q,R] = QR(A,0)
  nt2::tie(q, r) = nt2::qr(a,0);
  NT2_TEST_ULP_EQUAL( a, nt2::mtimes(q, r), T(200));

  x = nt2::qr(a, no_pivot_);
  t_t u = triu(x);
  NT2_TEST_ULP_EQUAL( u, r, T(200));

 // [Q,R,P] = QR(A,matrix_,vector_,0)
  nt2::tie(q, r, p) = nt2::qr(a, matrix_    );
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,p), nt2::mtimes(q, r), T(250));

  x = nt2::qr(a, pivot_);
  u = triu(x);
  NT2_TEST_ULP_EQUAL(u, r, T(200));

  x = nt2::qr(a, 0);
  u = triu(x);
  NT2_TEST_ULP_EQUAL(u, r, T(200));

  nt2::tie(q, r, p1) = nt2::qr(a, vector_    );
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,extract_p(p1)), nt2::mtimes(q, r), T(250));
  nt2::tie(q1, r1, p1) = nt2::qr(a, 0);
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,extract_p(p1)), nt2::mtimes(q, r), T(250));

}


NT2_TEST_CASE_TPL ( option_qr_not_square_m_superior_n, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;
  using nt2::pivot_;
  using nt2::matrix_;
  using nt2::vector_;
  using nt2::no_pivot_;

  typedef  nt2::table<T> t_t;
  nt2::table<T> x, q, q1, r, r1, p, p1;
  nt2::table<T> a = nt2::rand(9 , 6, as_<T>());

  /// Interface tests

  // [Q,R] = QR(A,0)
  nt2::tie(q, r) = nt2::qr(a,0);
  NT2_TEST_ULP_EQUAL( a, nt2::mtimes(q, r), T(200));

  x = nt2::qr(a, no_pivot_);
  t_t u = triu(x(_(1,6), _ ));

  NT2_TEST_ULP_EQUAL( u, r, T(200));

 // [Q,R,P] = QR(A,matrix_,vector_,0)
  nt2::tie(q, r, p) = nt2::qr(a, matrix_    );
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,p), nt2::mtimes(q, r), T(200));

  x = nt2::qr(a, pivot_);
  u = triu(x);
  NT2_TEST_ULP_EQUAL(u, r, T(200));

  x = nt2::qr(a, 0);
  u = triu(x);
  NT2_TEST_ULP_EQUAL(u, r, T(200));

  nt2::tie(q, r, p1) = nt2::qr(a, vector_    );
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,extract_p(p1)), nt2::mtimes(q, r), T(200));
  nt2::tie(q1, r1, p1) = nt2::qr(a, 0);
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,extract_p(p1)), nt2::mtimes(q, r), T(200));

}

NT2_TEST_CASE_TPL ( option_qr_not_square_m_inferior_n, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;
  using nt2::pivot_;
  using nt2::matrix_;
  using nt2::vector_;
  using nt2::no_pivot_;

  typedef  nt2::table<T> t_t;
  nt2::table<T> x, q, q1, r, r1, p, p1;
  nt2::table<T> a = nt2::rand(6 , 9, as_<T>());

  /// Interface tests

  // [Q,R] = QR(A,0)
  nt2::tie(q, r) = nt2::qr(a,0);
  NT2_TEST_ULP_EQUAL( a, nt2::mtimes(q, r), T(200));

  x = nt2::qr(a, no_pivot_);
  t_t u = triu(x);
  NT2_TEST_ULP_EQUAL( u, r, T(200));

  // [Q,R,P] = QR(A,matrix_,vector_,0)
  nt2::tie(q, r, p) = nt2::qr(a, matrix_    );
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,p), nt2::mtimes(q, r), T(200));

  x = nt2::qr(a, pivot_);
  u = triu(x);
  NT2_TEST_ULP_EQUAL(u, r, T(200));

  x = nt2::qr(a, 0);
  u = triu(x);
  NT2_TEST_ULP_EQUAL(u, r, T(200));

  nt2::tie(q, r, p1) = nt2::qr(a, vector_    );
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,extract_p(p1)), nt2::mtimes(q, r), T(200));
  nt2::tie(q1, r1, p1) = nt2::qr(a, 0);
  NT2_TEST_ULP_EQUAL( nt2::mtimes(a,extract_p(p1)), nt2::mtimes(q, r), T(200));

}
