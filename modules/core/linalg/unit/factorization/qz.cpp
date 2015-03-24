//==============================================================================
//         Copyright 2015   J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/qz.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/istriu.hpp>
#include <nt2/include/functions/ishess.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL ( qz, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  {
    nt2::table<cT> a, b;
    nt2::table<T> h, r, q, z;
    a = nt2::cons<T>(nt2::of_size(4, 4),
                     2,     2,     4,     1,
                     4,     2,     2,     1,
                     4,     3,     3,     2,
                     1,     3,     3,     4);
    b = nt2::cons<T>(nt2::of_size(4, 4),
                     2,     2,     4,     2,
                     3,     3,     3,     4,
                     1,     3,     1,     2,
                     4,     4,     1,     4);
    tie(h, r, q, z) = nt2::qz(a, b, nt2::real_);

    NT2_TEST(istriu(r));
    NT2_TEST(ishess(h));

    NT2_TEST_ULP_EQUAL( a,  nt2::complexify(nt2::mtimes(q, nt2::mtimes(h, trans(z)))), T(200));
    NT2_TEST_ULP_EQUAL( b,  nt2::complexify(nt2::mtimes(q, nt2::mtimes(r, trans(z)))), T(200));
  }
  {
    nt2::table<T> a, b;
    nt2::table<cT> h, r, q, z;
    a = nt2::cons<T>(nt2::of_size(4, 4),
                     2,     2,     4,     1,
                     4,     2,     2,     1,
                     4,     3,     3,     2,
                     1,     3,     3,     4);
    b = nt2::cons<T>(nt2::of_size(4, 4),
                     2,     2,     4,     2,
                     3,     3,     3,     4,
                     1,     3,     1,     2,
                     4,     4,     1,     4);
    tie(h, r, q, z) = nt2::qz(a, b, nt2::cmplx_);
    NT2_TEST(istriu(r));
    NT2_TEST(istriu(h));

    NT2_TEST_ULP_EQUAL( nt2::complexify(a),  nt2::mtimes(q, nt2::mtimes(h, trans(z))), T(200));
    NT2_TEST_ULP_EQUAL( nt2::complexify(b),  nt2::mtimes(q, nt2::mtimes(r, trans(z))), T(200));
  }
}

// NT2_TEST_CASE_TPL ( qz2, NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::meta::as_;
//   typedef std::complex<T> cT;
//   nt2::table<T> a, b, h, r, q, z, beta;
//   nt2::table<cT> alpha;
//   a = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     1,
//                    4,     2,     2,     1,
//                    4,     3,     3,     2,
//                    1,     3,     3,     4);
//   b = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     2,
//                    3,     3,     3,     4,
//                    1,     3,     1,     2,
//                    4,     4,     1,     4);
//   tie(h, r, q, z, alpha, beta) = nt2::qz(a, b, nt2::alphabeta_);
//   NT2_TEST(ishess(r));
//   NT2_TEST(ishess(h));

//   NT2_TEST_ULP_EQUAL( a,  nt2::mtimes(q, nt2::mtimes(h, trans(z))), T(200));
//   NT2_TEST_ULP_EQUAL( b,  nt2::mtimes(q, nt2::mtimes(r, trans(z))), T(200));
// }

// NT2_TEST_CASE_TPL ( qz3, NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::meta::as_;
//   typedef std::complex<T> cT;
//   nt2::table<T> a, b, h, r, q, z;
//   nt2::table<cT> vl, vr;
//   a = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     1,
//                    4,     2,     2,     1,
//                    4,     3,     3,     2,
//                    1,     3,     3,     4);
//   b = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     2,
//                    3,     3,     3,     4,
//                    1,     3,     1,     2,
//                    4,     4,     1,     4);
//   tie(h, r, q, z, vl, vr) = nt2::qz(a, b, nt2::eigs_);
//   NT2_TEST(istriu(r));
//   NT2_TEST(ishess(h));

//   NT2_TEST_ULP_EQUAL( a,  nt2::mtimes(q, nt2::mtimes(h, trans(z))), T(200));
//   NT2_TEST_ULP_EQUAL( b,  nt2::mtimes(q, nt2::mtimes(r, trans(z))), T(200));
//  }

// NT2_TEST_CASE_TPL ( qz4, NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::meta::as_;
//   typedef std::complex<T> cT;
//   nt2::table<T> a, b, h, r, q, z, beta;
//   nt2::table<cT> vl, vr, alpha;
//   a = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     1,
//                    4,     2,     2,     1,
//                    4,     3,     3,     2,
//                    1,     3,     3,     4);
//   b = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     2,
//                    3,     3,     3,     4,
//                    1,     3,     1,     2,
//                    4,     4,     1,     4);
//   tie(h, r, q, z, vl, vr, alpha, beta) = nt2::qz(a, b);
//   NT2_TEST(istriu(r));
//   NT2_TEST(ishess(h));

//   NT2_TEST_ULP_EQUAL( a,  nt2::mtimes(q, nt2::mtimes(h, trans(z))), T(200));
//   NT2_TEST_ULP_EQUAL( b,  nt2::mtimes(q, nt2::mtimes(r, trans(z))), T(200));
//   NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), nt2::from_diag(beta))-mtimes(mtimes(b, vr), from_diag(alpha)))), 1000*nt2::Eps<T>());
//   NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), from_diag(alpha/beta)))), 1000*nt2::Eps<T>());
// }

// NT2_TEST_CASE_TPL ( qz5, NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::meta::as_;
//   typedef std::complex<T> cT;
//   nt2::table<cT> a, b, h, r, q, z, beta;
//   nt2::table<cT> vl, vr, alpha;
//   a = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     1,
//                    4,     2,     2,     1,
//                    4,     3,     3,     2,
//                    1,     3,     3,     4);
//   b = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     2,
//                    3,     3,     3,     4,
//                    1,     3,     1,     2,
//                    4,     4,     1,     4);
//   tie(h, r, q, z, vl, vr, alpha, beta) = nt2::qz(a, b);
//   NT2_TEST(istriu(r));
//   NT2_TEST(istriu(h));

//   NT2_TEST_ULP_EQUAL( a,  nt2::mtimes(q, nt2::mtimes(h, trans(z))), T(200));
//   NT2_TEST_ULP_EQUAL( b,  nt2::mtimes(q, nt2::mtimes(r, trans(z))), T(200));
//   NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), nt2::from_diag(beta))-mtimes(mtimes(b, vr), from_diag(alpha)))), 1000*nt2::Eps<T>());
//   NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), from_diag(alpha/beta)))), 1000*nt2::Eps<T>());

// }

// NT2_TEST_CASE_TPL ( qz6, NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::meta::as_;
//   typedef std::complex<T> cT;
//   nt2::table<cT> a, b, h, r, q, z, beta;
//   nt2::table<cT> alpha;
//   a = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     1,
//                    4,     2,     2,     1,
//                    4,     3,     3,     2,
//                    1,     3,     3,     4);
//   b = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     2,
//                    3,     3,     3,     4,
//                    1,     3,     1,     2,
//                    4,     4,     1,     4);
//   tie(h, r, q, z, alpha, beta) = nt2::qz(a, b, nt2::alphabeta_);
//   NT2_TEST(istriu(r));
//   NT2_TEST(istriu(h));

//   NT2_TEST_ULP_EQUAL( a,  nt2::mtimes(q, nt2::mtimes(h, trans(z))), T(200));
//   NT2_TEST_ULP_EQUAL( b,  nt2::mtimes(q, nt2::mtimes(r, trans(z))), T(200));
// }

// NT2_TEST_CASE_TPL ( qz7, NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::meta::as_;
//   typedef std::complex<T> cT;
//   nt2::table<T> a, b, h, r, q, z;
//   nt2::table<cT> vl, vr;
//   a = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     1,
//                    4,     2,     2,     1,
//                    4,     3,     3,     2,
//                    1,     3,     3,     4);
//   b = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     2,
//                    3,     3,     3,     4,
//                    1,     3,     1,     2,
//                    4,     4,     1,     4);
//   tie(h, r, q, z, vl, vr) = nt2::qz(a, b, nt2::eigs_);
//   NT2_TEST(istriu(r));
//   NT2_TEST(istriu(h));

//   NT2_TEST_LESSER(nt2::globalmax(nt2::abs(a-nt2::mtimes(q, nt2::mtimes(h, trans(z))))), T(200)*nt2::Eps<T>());
//   NT2_TEST_LESSER(nt2::globalmax(nt2::abs(b- nt2::mtimes(q, nt2::mtimes(r, trans(z))))), T(200)*nt2::Eps<T>());
// }
// NT2_TEST_CASE_TPL ( qz8, NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::meta::as_;
//   typedef std::complex<T> cT;
//   nt2::table<cT> a, b, h, r, q, z;
//   nt2::table<cT> vl, vr;
//   a = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     1,
//                    4,     2,     2,     1,
//                    4,     3,     3,     2,
//                    1,     3,     3,     4);
//   b = nt2::cons<T>(nt2::of_size(4, 4),
//                    2,     2,     4,     2,
//                    3,     3,     3,     4,
//                    1,     3,     1,     2,
//                    4,     4,     1,     4);
//   tie(h, r, q, z, vl, vr) = nt2::qz(a, b, nt2::eigs_);
//   NT2_TEST(istriu(r));
//   NT2_TEST(istriu(h));

//   NT2_TEST_LESSER(nt2::globalmax(nt2::abs(a-nt2::mtimes(q, nt2::mtimes(h, trans(z))))), T(200)*nt2::Eps<T>());
//   NT2_TEST_LESSER(nt2::globalmax(nt2::abs(b- nt2::mtimes(q, nt2::mtimes(r, trans(z))))), T(200)*nt2::Eps<T>());
// }
