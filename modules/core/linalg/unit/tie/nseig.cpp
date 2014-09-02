//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/nseig.hpp>

#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/nseig.hpp>
#include <nt2/include/constants/one.hpp>

#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/triu.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/linalg/options.hpp>


NT2_TEST_CASE_TPL(nseig_sca, NT2_REAL_TYPES)
{
  using nt2::nseig;
  typedef nt2::table<T> t_t;
  t_t w =   nseig(T(2));
  NT2_TEST_ULP_EQUAL(w, T(2), 0);
  w =   nseig(T(2), nt2::matrix_);
  NT2_TEST_ULP_EQUAL(w, T(2), 0);
  w =   nseig(T(2), nt2::vector_);
  NT2_TEST_ULP_EQUAL(w, T(2), 0);
 }

NT2_TEST_CASE_TPL(nseig, NT2_REAL_TYPES)
{
  using nt2::nseig;
  using nt2::mtimes;
  using nt2::_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  typedef nt2::table<itype_t> it_t;
  t_t b =      nt2::triu(nt2::from_diag(nt2::_(T(1), T(4)))
                     + nt2::ones  (4, 4, nt2::meta::as_<T>()));
  //  b(_, 1) = b(_, 3);
  ct_t w, w1;
  ct_t wr = nt2::_(T(2), T(5));
  display("b", b);
  w = nseig(b);
  display("w", w);
  w = nseig(nt2::triu(nt2::from_diag(nt2::_(T(1), T(4)))
                      + nt2::ones  (4, 4, nt2::meta::as_<T>())));
  display("w", w);
  NT2_TEST_EQUAL(w, wr);
  ct_t z = nt2::ones(8, 1, nt2::meta::as_<T>());

  z(nt2::_(1, 2, 8)) = nseig(b);
  display("z", z);
  NT2_TEST_EQUAL(w, z(nt2::_(1, 2, 8)));

  ct_t cb = b;
  NT2_TEST_EQUAL(height(w), height(b));
  display("cb", cb);
  w1 = nseig(cb);
  display("w1", w1);
  NT2_TEST_ULP_EQUAL(w, w1, 2);
  w = nseig(b, nt2::matrix_);
  display("w", w);
  w1 = nseig(cb, nt2::matrix_);
  display("w1", w1);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(w, w1, 2);

  w = nseig(b, nt2::matrix_, nt2::balance_);
  display("w", w);
  w1 = nseig(cb, nt2::matrix_, nt2::balance_);
  display("w1", w1);
  std::cout << "- -1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(w, w1, 2);

  ct_t v;
  nt2::tie(v, w) = nseig(b);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 0 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(b, nt2::matrix_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 2 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb, nt2::matrix_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 3 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(b, nt2::vector_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 4 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, nt2::from_diag(w)), mtimes(b, v), 8);


  nt2::tie(v, w) = nseig(cb, nt2::vector_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 5 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);

  ct_t vl;

  nt2::tie(v, w, vl) = nseig(b);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 6 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w, vl) = nseig(cb);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 7 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(b, nt2::matrix_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 8 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);
  std::cout << "- 9 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::matrix_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 10 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 11 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(b, nt2::vector_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 12 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 13 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::vector_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 14 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 15 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w) = nseig(cb, nt2::vector_, nt2::balance_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 16 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb, nt2::matrix_, nt2::balance_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 17 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::vector_, nt2::balance_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 18 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 19 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::matrix_, nt2::balance_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 20 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 21 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 22-" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 23 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

//   ct_t vv = nt2::ones(10, 10, nt2::meta::as_<T>());
//   nt2::tie(vv(nt2::_(1, 2, 8), nt2::_(1, 2, 8))
//           , z(nt2::_(1, 2, 8))
//           , vl) = nseig(cb, nt2::vector_);
//   nt2::display("z     ", z);
//   nt2::display("vv    ", vv);
//   nt2::display("vl    ", vl);


}


NT2_TEST_CASE_TPL(nseigc, NT2_REAL_TYPES)
{
  using nt2::nseig;
  using nt2::mtimes;
  using nt2::_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  typedef nt2::table<itype_t> it_t;
  ct_t b =      nt2::triu(nt2::from_diag(nt2::_(T(1), T(4)))
                     + nt2::ones  (4, 4, nt2::meta::as_<T>()));
  //  b(_, 1) = b(_, 3);
  ct_t w, w1;

  display("b", b);
  w = nseig(b);
  display("w", w);
  ct_t cb = b;

  display("cb", cb);
  w1 = nseig(cb);
  display("w1", w1);
  NT2_TEST_ULP_EQUAL(w, w1, 2);
  w = nseig(b, nt2::matrix_);
  display("w", w);
  w1 = nseig(cb, nt2::matrix_);
  display("w1", w1);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(w, w1, 2);

  w = nseig(b, nt2::matrix_, nt2::balance_);
  display("w", w);
  w1 = nseig(cb, nt2::matrix_, nt2::balance_);
  display("w1", w1);
  std::cout << "- -1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(w, w1, 2);

  ct_t v;
  nt2::tie(v, w) = nseig(b);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 0 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(b, nt2::matrix_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 2 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb, nt2::matrix_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 3 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(b, nt2::vector_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 4 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, nt2::from_diag(w)), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb, nt2::vector_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 5 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);

  ct_t vl;

  nt2::tie(v, w, vl) = nseig(b);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 6 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w, vl) = nseig(cb);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 7 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(b, nt2::matrix_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 8 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);
  std::cout << "- 9 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::matrix_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 10 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 11 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(b, nt2::vector_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 12 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 13 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::vector_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 14 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 15 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w) = nseig(cb, nt2::vector_, nt2::balance_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 16 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb, nt2::matrix_, nt2::balance_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  std::cout << "- 17 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::vector_, nt2::balance_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 18 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 19 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::matrix_, nt2::balance_);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 20 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 21 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  nt2::display("vl    ", vl);
  std::cout << "- 22-" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 23 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);
}


// NT2_TEST_CASE_TPL(nseig2, NT2_REAL_TYPES)
// {
//   using nt2::tag::nseig_;
//   using nt2::mtimes;
//   using nt2::_;
//   typedef std::complex<T> cT;
//   typedef nt2::table<T> t_t;
//   typedef nt2::table<cT> ct_t;
//   t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::One<T>(), nt2::One<T>(), -nt2::One<T>(), nt2::One<T>());
//   ct_t w, v, vl;
//   nt2::display("a     ", a);
//   nt2::tie(v, w, vl) = nseig(a);
//   nt2::display("w     ", w);
//   nt2::display("v     ", v);
//   nt2::display("vl    ", vl);
//   ct_t ca = a;
//   nt2::display("ca     ", ca);
//   nt2::tie(v, w, vl) = nseig(ca);
//   nt2::display("w     ", w);
//   nt2::display("v     ", v);
//   nt2::display("vl    ", vl);
// }

