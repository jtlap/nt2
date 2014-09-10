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
#include <iomanip>

NT2_TEST_CASE_TPL ( direct_qr, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  int i[3] = {4, 4, 5};
  int j[3] = {4, 5, 4};
  for(int k = 0; k < 3; ++k)
  {
    nt2::table<T> x, q, r, p, u, tau;
    nt2::table<T> b = nt2::ones(i[k], j[k], as_<T>());
    b(2, 3) = T(2);
    nt2::table<nt2_la_int> ip;
    /// Interface tests
      std::cout << "b " << i[k] << "X" << j[k] << ", r = qr(b, upper_)" << std::endl;
      r = nt2::qr(b, nt2::upper_);

      std::cout << "b " << i[k] << "X" << j[k] << ", x = qr(b)" << std::endl;
      x = nt2::qr(b);
      NT2_TEST_ULP_EQUAL( triu(x), r, T(200));

      std::cout << "b " << i[k] << "X" << j[k] << ",  x = qr(b, raw_)" << std::endl;
      x = nt2::qr(b), nt2::raw_;
      NT2_TEST_ULP_EQUAL( triu(x), r, T(200));

      std::cout << "b " << i[k] << "X" << j[k] << ",  x = qr(b, 0)" << std::endl;
      x = nt2::qr(b, 0);
      NT2_TEST_ULP_EQUAL( triu(x), r, T(200));

      std::cout << "b " << i[k] << "X" << j[k] << ",  x = qr(b, nt2::econ_)" << std::endl;
      x = nt2::qr(b, nt2::econ_);
      NT2_TEST_ULP_EQUAL( triu(x), r, T(200));

      std::cout << "b " << i[k] << "X" << j[k] << ",  tie(x, tau)= nt2::qr(b, nt2::raw_);" << std::endl;
      tie(x, tau)= nt2::qr(b, nt2::raw_);
      NT2_TEST_ULP_EQUAL( triu(x), r, T(200));

      std::cout << "b " << i[k] << "X" << j[k] << ",  tie(x, tau, ip)= nt2::qr(b, nt2::raw_);" << std::endl;
      tie(x, tau, ip)= nt2::qr(b, nt2::raw_);

      std::cout << "b " << i[k] << "X" << j[k] << ",  tie(q, r)= nt2::qr(b, nt2::matrix_);" << std::endl;
      tie(q, r)= nt2::qr(b, nt2::matrix_);
      NT2_TEST_ULP_EQUAL( b, nt2::mtimes(q, r), T(200));

      std::cout << "b " << i[k] << "X" << j[k] << ",  tie(q, r, ip)= nt2::qr(b, nt2::vector_);" << std::endl;
      tie(q, r, ip)= nt2::qr(b, nt2::vector_);
      NT2_TEST_ULP_EQUAL( b(nt2::_, ip), nt2::mtimes(q, r), T(200));

      std::cout << "b " << i[k] << "X" << j[k] << ",   tie(q, r, p)= nt2::qr(b, nt2::matrix_);" << std::endl;
      tie(q, r, p)= nt2::qr(b, nt2::matrix_);
      NT2_TEST_ULP_EQUAL( mtimes(b, p), nt2::mtimes(q, r), T(200));

      std::cout << "b " << i[k] << "X" << j[k] << ",  tie(q, r)= nt2::qr(b, nt2::econ_);" << std::endl;
      tie(q, r)= nt2::qr(b, nt2::econ_);
      NT2_TEST_ULP_EQUAL( b, nt2::mtimes(q, r), T(200));

  }
}

NT2_TEST_CASE_TPL ( qr2, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;
    nt2::table<T> x, q, r, p, u, tau;
    nt2::table<T> b = nt2::ones(4, 4, as_<T>());
    b(2, 3) = T(2);
    nt2::table<nt2_la_int> ip;

    std::cout <<  " r = qr(b, upper_)" << std::endl;
    r = nt2::qr(b, nt2::upper_);

    std::cout << " x = qr(b)" << std::endl;
    x = nt2::ones(8, 4, as_<T>());
    x(_(1, 2, 8), _) = nt2::qr(b);
    NT2_TEST_ULP_EQUAL( triu(x(_(1, 2, 8), _)), r, T(200));

    std::cout << " x = qr(b, raw_)" << std::endl;
    x(_(1, 2, 8), _) = nt2::qr(b), nt2::raw_;
    NT2_TEST_ULP_EQUAL( triu(x(_(1, 2, 8), _)), r, T(200));

    std::cout << " x = qr(b, 0)" << std::endl;
    x(_(1, 2, 8), _) = nt2::qr(b, 0);
    NT2_TEST_ULP_EQUAL( triu(x(_(1, 2, 8), _)), r, T(200));

    std::cout << " x = qr(b, nt2::econ_)" << std::endl;
    x(_(1, 2, 8), _) = nt2::qr(b, nt2::econ_);
    NT2_TEST_ULP_EQUAL( triu(x(_(1, 2, 8), _)), r, T(200));

    std::cout << " tie(x, tau)= nt2::qr(b, nt2::raw_);" << std::endl;
    tau = nt2::ones(8, 1, as_<T>());
    tie(x(_(1, 2, 8), _), tau(_(1, 2, 8)))= nt2::qr(b, nt2::raw_);
    NT2_TEST_ULP_EQUAL( triu(x(_(1, 2, 8), _)), r, T(200));

    std::cout << " tie(x, tau, ip)= nt2::qr(b, nt2::raw_);" << std::endl;
    ip =  nt2::ones(8, 1, as_<nt2_la_int>());
    tie(x(_(1, 2, 8), _), tau(_(1, 2, 8)), ip(_(1, 2, 8)))= nt2::qr(b, nt2::raw_);

    q =  nt2::ones(8, 4, as_<T>());
    r = q;
    std::cout << " tie(q, r)= nt2::qr(b, nt2::matrix_);" << std::endl;
    tie(q(_(1, 2, 8), _), r(_(1, 2, 8), _))= nt2::qr(b, nt2::matrix_);
    NT2_TEST_ULP_EQUAL( b, nt2::mtimes(q(_(1, 2, 8), _), r(_(1, 2, 8), _)), T(200));


    std::cout << " tie(q, r, ip)= nt2::qr(b, nt2::vector_);" << std::endl;
    tie(q(_(1, 2, 8), _), r(_(1, 2, 8), _), ip(_(1, 2, 8)))= nt2::qr(b, nt2::vector_);
    NT2_TEST_ULP_EQUAL( b(nt2::_, ip(_(1, 2, 8))), nt2::mtimes(q(_(1, 2, 8), _), r(_(1, 2, 8), _)), T(200));

    p = nt2::ones(8, 4, as_<T>());
    std::cout << " tie(q, r, p)= nt2::qr(b, nt2::matrix_);" << std::endl;
    tie(q(_(1, 2, 8), _), r(_(1, 2, 8), _), p(_(1, 2, 8), _))= nt2::qr(b, nt2::matrix_);
    NT2_TEST_ULP_EQUAL( mtimes(b, p(_(1, 2, 8), _)), nt2::mtimes(q(_(1, 2, 8), _), r(_(1, 2, 8), _)), T(200));

    std::cout << " tie(q, r)= nt2::qr(b, nt2::econ_);" << std::endl;
    tie(q(_(1, 2, 8), _), r(_(1, 2, 8), _))= nt2::qr(b, nt2::econ_);
    NT2_TEST_ULP_EQUAL( b, nt2::mtimes(q(_(1, 2, 8), _), r(_(1, 2, 8), _)), T(200));

}
