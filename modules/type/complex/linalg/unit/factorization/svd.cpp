//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied svd function"

#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <algorithm>

NT2_TEST_CASE_TPL(svd_scalar, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::_;
  typedef nt2::table<T>           t_t;
  t_t a =  nt2::svd(cT(-3, 4));
  NT2_TEST_EQUAL(a, T(5));
  a =  nt2::svd(cT(-3, 4), nt2::econ_);
  NT2_TEST_EQUAL(a, T(5));
  a =  nt2::svd(cT(-3, 4), 0);
  NT2_TEST_EQUAL(a, T(5));

}


NT2_TEST_CASE_TPL(svd1o_ni, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::_;
  using nt2::meta::as_;
  typedef nt2::table<T>           t_t;
  typedef nt2::table<cT>           ct_t;
  int i[3] = {4, 4, 5};
  int j[3] = {4, 5, 4};
  for(int k = 0; k < 3; ++k)
  {
    nt2::table<cT> a = nt2::reshape(nt2::_(T(1), T(i[k]*j[k])), i[k], j[k]);
    size_t d = std::min(i[k], j[k]);
    a(_(1, d), _(1, d))+= nt2::from_diag(_(T(101), T(100+d)))*nt2::I<cT>();
    std::cout << "11 a " << i[k] << "X" << j[k] << ", s =  nt2::svd(a);" << std::endl;
    t_t s =  nt2::svd(a);
    ct_t a2 = nt2::mtimes(a, nt2::ctrans(a));
    t_t w =  nt2::sqrt(nt2::symeig(a2));
    NT2_TEST_ULP_EQUAL(nt2::sort(s, 'd'), nt2::sort(w, 'd')(_(1,d)), 10);
    std::cout << "12 a " << i[k] << "X" << j[k] << ", s1 =  nt2::svd(a, nt2::vector_);" << std::endl;
    t_t s1 =  nt2::svd(a, nt2::vector_);
    NT2_TEST_EQUAL(s, s1);
    std::cout << "13 a " << i[k] << "X" << j[k] << ", s1 =  nt2::svd(a, nt2::raw_);" << std::endl;
    s1 =  nt2::svd(a, nt2::vector_);
    NT2_TEST_EQUAL(s, s1);
    std::cout << "14 a " << i[k] << "X" << j[k] << ", ds =  nt2::svd(a, nt2::matrix_);" << std::endl;
    t_t ds =  nt2::svd(a, nt2::matrix_);
    NT2_TEST_EQUAL(s, nt2::diag_of(ds));
  }

}

NT2_TEST_CASE_TPL(svd3o_ni, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::_;
  using nt2::meta::as_;
  typedef nt2::table<T>           t_t;
  typedef nt2::table<cT>         ct_t;
  int i[3] = {4, 4, 5};
  int j[3] = {4, 5, 4};
  for(int k = 0; k < 3; ++k)
  {
    nt2::table<cT> a = nt2::reshape(nt2::_(T(1), T(i[k]*j[k])), i[k], j[k]);
    size_t d = std::min(i[k], j[k]);
    a(_(1, d), _(1, d))+= nt2::from_diag(_(T(101), T(100+d)))*nt2::I<cT>();
    ct_t u, v, tv;
    t_t s, ds;

    std::cout << "31 a " << i[k] << "X" << j[k] << ", nt2::tie(u, ds, v)=  nt2::svd(a);" << std::endl;
    nt2::tie(u, ds, v)=  nt2::svd(a);
    NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u, nt2::mtimes(ds, ctrans(v))), 1024);

    std::cout << "32 a " << i[k] << "X" << j[k] << ", nt2::tie(u, ds, v)=  nt2::svd(a, nt2::matrix_);" << std::endl;
    nt2::tie(u, ds, v)=  nt2::svd(a, nt2::matrix_);
    NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u, nt2::mtimes(ds, ctrans(v))), 1024);

    std::cout << "33 a " << i[k] << "X" << j[k] << ", nt2::tie(u, s, v)=  nt2::svd(a, nt2::vector_);" << std::endl;
    nt2::tie(u, s, v)=  nt2::svd(a, nt2::vector_);
    NT2_TEST_EQUAL(s, diag_of(ds));
    NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u, nt2::mtimes(ds, ctrans(v))), 1024);

    std::cout << "34 a " << i[k] << "X" << j[k] << ", nt2::tie(u, s, tv)=  nt2::svd(a, nt2::raw_);" << std::endl;
    nt2::tie(u, s, tv)=  nt2::svd(a, nt2::raw_);
    NT2_TEST_EQUAL(s, diag_of(ds));
    NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u, nt2::mtimes(ds, tv)), 1024);

    std::cout << "35 a " << i[k] << "X" << j[k] << ", nt2::tie(u, ds, v)=  nt2::svd(a, nt2::econ_);" << std::endl;
    nt2::tie(u, ds, v)=  nt2::svd(a, nt2::econ_);
    NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u,  nt2::mtimes(ds, ctrans(v))), 1024);

    std::cout << "36 a " << i[k] << "X" << j[k] << ", nt2::tie(u, ds, v)=  nt2::svd(a, 0);" << std::endl;
    nt2::tie(u, ds, v)=  nt2::svd(a, 0);
    NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u,  nt2::mtimes(ds, ctrans(v))), 1024);

  }
}

NT2_TEST_CASE_TPL(svd1o_ni_sub, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::_;
  using nt2::meta::as_;
  typedef nt2::table<T>           t_t;
  typedef nt2::table<cT>         ct_t;

  t_t s1, s;
  s = s1 = nt2::ones(8, 1, as_<T>());
  t_t ds = nt2::ones(8, 4, as_<T>());
  nt2::table<cT> a = nt2::reshape(nt2::_(T(1), T(16)), 4, 4) + nt2::from_diag(_(T(101), T(104)))*nt2::I<cT>();
  std::cout << "11 s(_(1, 2, 8)) =  nt2::svd(a);" << std::endl;
  s(_(1, 2, 8)) =  nt2::svd(a);

  ct_t a2 = nt2::mtimes(a, nt2::ctrans(a));
  t_t w =  nt2::sqrt(nt2::symeig(a2));

  NT2_TEST_ULP_EQUAL(nt2::sort(s(_(1, 2, 8)), 'd'), nt2::sort(w, 'd'), 10);

  std::cout << "12 s1(_(1, 2, 8)) =  nt2::svd(a, nt2::vector_);" << std::endl;
  s1(_(1, 2, 8)) =  nt2::svd(a, nt2::vector_);
  NT2_TEST_EQUAL(s(_(1, 2, 8)), s1(_(1, 2, 8)));

  std::cout << "13 s1(_(1, 2, 8)) =  nt2::svd(a, nt2::raw_);" << std::endl;
  s1(_(1, 2, 8)) =  nt2::svd(a, nt2::vector_);
  NT2_TEST_EQUAL(s(_(1, 2, 8)), s1(_(1, 2, 8)));

  std::cout << "14 ds(_(1, 2, 8), _) =  nt2::svd(a, nt2::matrix_);" << std::endl;
  ds(_(1, 2, 8), _) =  nt2::svd(a, nt2::matrix_);
  NT2_TEST_EQUAL(s(_(1, 2, 8)), nt2::diag_of(ds(_(1, 2, 8), _)));

}

NT2_TEST_CASE_TPL(svd3o_ni_sub, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::_;
  using nt2::meta::as_;
  typedef nt2::table<T>           t_t;
  typedef nt2::table<cT>         ct_t;

  t_t s = nt2::ones(8, 1, as_<T>());
  t_t ds = nt2::ones(8, 4, as_<T>());
  nt2::table<cT> a = nt2::reshape(nt2::_(T(1), T(16)), 4, 4) + nt2::from_diag(_(T(101), T(104)))*nt2::I<cT>();
  ct_t u, v, tv;
  u = v = tv = ds;

  std::cout << "31 nt2::tie(u(_(1, 2, 8), _), ds(_(1, 2, 8), _), v(_(1, 2, 8), _))=  nt2::svd(a);" << std::endl; //ok
  nt2::tie(u(_(1, 2, 8), _), ds(_(1, 2, 8), _), v(_(1, 2, 8), _))=  nt2::svd(a);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u(_(1, 2, 8), _), mtimes(ds(_(1, 2, 8), _), ctrans(v(_(1, 2, 8), _)))), 1024);

  std::cout << "32 nt2::tie(u(_(1, 2, 8), _), ds(_(1, 2, 8), _), v(_(1, 2, 8), _))=  nt2::svd(a, nt2::matrix_);" << std::endl; //ok
  nt2::tie(u(_(1, 2, 8), _), ds(_(1, 2, 8), _), v(_(1, 2, 8), _))=  nt2::svd(a, nt2::matrix_);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u(_(1, 2, 8), _), mtimes(ds(_(1, 2, 8), _), ctrans(v(_(1, 2, 8), _)))), 1024);

  std::cout << "33 nt2::tie(u(_(1, 2, 8), _), s(_(1, 2, 8), _), v(_(1, 2, 8), _))=  nt2::svd(a, nt2::vector_);" << std::endl;
  nt2::tie(u(_(1, 2, 8), _), s(_(1, 2, 8)), v(_(1, 2, 8), _))=  nt2::svd(a, nt2::vector_);
  NT2_TEST_EQUAL(s(_(1, 2, 8)), diag_of(ds(_(1, 2, 8), _)));
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u(_(1, 2, 8), _), mtimes(ds(_(1, 2, 8), _), ctrans(v(_(1, 2, 8), _)))), 1024);

  std::cout << "34 nt2::tie(u, s(_(1, 2, 8)), tv)=  nt2::svd(a, nt2::raw_);" << std::endl;
  nt2::tie(u(_(1, 2, 8), _), s(_(1, 2, 8)), tv(_(1, 2, 8), _))=  nt2::svd(a, nt2::raw_);
  NT2_TEST_EQUAL(s(_(1, 2, 8)), diag_of(ds(_(1, 2, 8), _)));
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u(_(1, 2, 8), _), mtimes(ds(_(1, 2, 8), _), tv(_(1, 2, 8), _))), 1024);

  std::cout << "35 nt2::tie(u, ds, v)=  nt2::svd(a, nt2::econ_);" << std::endl; //ok
  nt2::tie(u(_(1, 2, 8), _), ds(_(1, 2, 8), _), v(_(1, 2, 8), _))=  nt2::svd(a, nt2::econ_);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u(_(1, 2, 8), _), mtimes(ds(_(1, 2, 8), _), ctrans(v(_(1, 2, 8), _)))), 1024);

  std::cout << "36 nt2::tie(u(_(1, 2, 8), _), ds(_(1, 2, 8), _), v(_(1, 2, 8), _))=  nt2::svd(a, 0);" << std::endl; //ok
  nt2::tie(u(_(1, 2, 8), _), ds(_(1, 2, 8), _), v(_(1, 2, 8), _))=  nt2::svd(a, 0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(u(_(1, 2, 8), _), mtimes(ds(_(1, 2, 8), _), ctrans(v(_(1, 2, 8), _)))), 1024);
}


