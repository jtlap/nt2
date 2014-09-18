//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied lu function"

#include <nt2/table.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/tri1l.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/from_diag.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( lu_no_1i,  NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  int i[3] = {4, 4, 5};
  int j[3] = {4, 5, 4};
  for(int k = 0; k < 3; ++k)
  {
    nt2::table<T> l, u, p, lu;
    nt2::table<nt2_la_int> ip;
    nt2::table<T> b = nt2::reshape(nt2::_(T(1), T(i[k]*j[k])), i[k], j[k]);
    size_t d = std::min(i[k], j[k]);
    b(_(1, d), _(1, d))+= nt2::from_diag(_(T(1001), T(1000+d)));

    std::cout << "b " << i[k] << "X" << j[k] << ",  tie(l, u)= nt2::qr(b);" << std::endl;
    nt2::tie(l, u) = nt2::lu(b);
    NT2_TEST_ULP_EQUAL( b,  nt2::mtimes(l, u), T(200));


    std::cout << "b " << i[k] << "X" << j[k] << ",  tie(l, u, p)= nt2::qr(b);" << std::endl;
    nt2::tie(l, u, p) = nt2::lu(b, nt2::matrix_);
    NT2_TEST_ULP_EQUAL( nt2::mtimes(p, b), nt2::mtimes(l, u), T(200));

    std::cout << "b " << i[k] << "X" << j[k] << ",  lu = nt2::qr(b);" << std::endl;
    lu = nt2::lu(b);
    //note the use of p that is not computed in the previous call
    NT2_TEST_ULP_EQUAL( nt2::mtimes(p, b), nt2::mtimes(nt2::tri1l(lu)(nt2::_, nt2::_(1, d) )
                                                      , nt2::triu(lu( nt2::_(1, d), nt2::_))), T(200));
  }
}


NT2_TEST_CASE_TPL ( lu_no_1i_sub,  NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> l, u, p, lu;
  l =  nt2::ones(4, 8, as_<T>());
  u =  nt2::ones(4, 8, as_<T>());
  p =  nt2::ones(4, 8, as_<T>());
  lu=  nt2::ones(4, 8, as_<T>());
  nt2::table<T> b = nt2::reshape(nt2::_(T(1), T(16)), 4, 4)+ nt2::from_diag(_(T(1001), T(1004)));

  std::cout <<  ",  tie(l(_, _(1, 2, 8)), u(_, _(1, 2, 8)))= nt2::qr(b);" << std::endl;
  nt2::tie(l(_, _(1, 2, 8)), u(_, _(1, 2, 8))) = nt2::lu(b);
  NT2_TEST_ULP_EQUAL( b,  nt2::mtimes(l(_, _(1, 2, 8)), u(_, _(1, 2, 8))), T(200));


  std::cout <<  ",  tie(l(_, _(1, 2, 8)), u(_, _(1, 2, 8)), p(_, _(1, 2, 8)))= nt2::qr(b);" << std::endl;
  nt2::tie(l(_, _(1, 2, 8)), u(_, _(1, 2, 8)), p(_, _(1, 2, 8))) = nt2::lu(b, nt2::matrix_);
  NT2_TEST_ULP_EQUAL( nt2::mtimes(p(_, _(1, 2, 8)), b), nt2::mtimes(l(_, _(1, 2, 8)), u(_, _(1, 2, 8))), T(200));

  std::cout << ",  lu(_, _(1, 2, 8)) = nt2::qr(b);" << std::endl;
  lu(_, _(1, 2, 8)) = nt2::lu(b);
  //note the use of p that is not computed in the previous call
  NT2_TEST_ULP_EQUAL( nt2::mtimes(p(_, _(1, 2, 8)), b), nt2::mtimes(nt2::tri1l(lu(_, _(1, 2, 8)))
                                                                   , nt2::triu(lu(_, _(1, 2, 8)))), T(200));
                                                                    }


NT2_TEST_CASE_TPL ( luno_2i, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  int i[3] = {4, 4, 5};
  int j[3] = {4, 5, 4};
  for(int k = 0; k < 3; ++k)
  {
    nt2::table<T> l, u, p, lu;
    nt2::table<nt2_la_int> ip, ls;
    nt2::table<T> b = nt2::reshape(nt2::_(T(1), T(i[k]*j[k])), i[k], j[k]);
    size_t d = std::min(i[k], j[k]);
    b(_(1, d), _(1, d))+= nt2::from_diag(_(T(1001), T(1000+d)));

    std::cout << "b " << i[k] << "X" << j[k] << ",  tie(l, u, ip)= nt2::qr(b, nt2::vector_);" << std::endl;
    nt2::tie(l, u, ip)= nt2::lu(b, nt2::vector_);
    NT2_TEST_ULP_EQUAL( b(ip, _), nt2::mtimes(l, u), T(200));

    std::cout << "b " << i[k] << "X" << j[k] << ",  tie(l, u, p)= nt2::qr(b, matrix_);" << std::endl;
    nt2::tie(l, u, p) = nt2::lu(b, nt2::matrix_);
    NT2_TEST_ULP_EQUAL( nt2::mtimes(p, b), nt2::mtimes(l, u), T(200));

    std::cout << "b " << i[k] << "X" << j[k] << ",   tie(l, u) = nt2::qr(b, raw_);" << std::endl;
    nt2::tie(lu, ls) = nt2::lu(b, nt2::raw_);
    //note the use of p that is not computed in the previous call
    //ls is in the list swap lapack format for a permutation a private routine does transform it into p
    NT2_TEST_ULP_EQUAL( nt2::mtimes(p, b), nt2::mtimes(nt2::tri1l(lu)(nt2::_, nt2::_(1, d) )
                                                      , nt2::triu(lu( nt2::_(1, d), nt2::_))), T(200));
  }
}

NT2_TEST_CASE_TPL ( luno_2i_sub, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> l, u, p, lu;
  l =  nt2::ones(4, 8, as_<T>());
  u =  nt2::ones(4, 8, as_<T>());
  p =  nt2::ones(4, 8, as_<T>());
  lu=  nt2::ones(4, 8, as_<T>());
  nt2::table<T> b = nt2::reshape(nt2::_(T(1), T(16)), 4, 4)+ nt2::from_diag(_(T(1001), T(1004)));
  nt2::table<nt2_la_int> ip, ls;
  ip =  nt2::ones(1, 8, as_<nt2_la_int>());
  ls =  nt2::ones(1, 8, as_<nt2_la_int>());

  std::cout << ",  tie(l(_, _(1, 2, 8)), u(_, _(1, 2, 8)), ip(_(1, 2, 8)))= nt2::qr(b, nt2::vector_);" << std::endl;
  nt2::tie(l(_, _(1, 2, 8)), u(_, _(1, 2, 8)), ip(_(1, 2, 8)))= nt2::lu(b, nt2::vector_);
  NT2_TEST_ULP_EQUAL( b(ip(_(1, 2, 8)), _), nt2::mtimes(l(_, _(1, 2, 8)), u(_, _(1, 2, 8))), T(200));

  std::cout << ",  tie(l(_, _(1, 2, 8)), u(_, _(1, 2, 8)), p(_, _(1, 2, 8)))= nt2::qr(b, matrix_);" << std::endl;
  nt2::tie(l(_, _(1, 2, 8)), u(_, _(1, 2, 8)), p(_, _(1, 2, 8))) = nt2::lu(b, nt2::matrix_);
  NT2_TEST_ULP_EQUAL( nt2::mtimes(p(_, _(1, 2, 8)), b), nt2::mtimes(l(_, _(1, 2, 8)), u(_, _(1, 2, 8))), T(200));

  std::cout <<  ",   tie(lu(_, _(1, 2, 8)), ls(_(1, 2, 8))) = nt2::qr(b, raw_);" << std::endl;
  nt2::tie(lu(_, _(1, 2, 8)), ls(_(1, 2, 8))) = nt2::lu(b, nt2::raw_);
  //note the use of p that is not computed in the previous call
  //ls is in the list swap lapack format for a permutation a private routine does transform it into p
  NT2_TEST_ULP_EQUAL( nt2::mtimes(p(_, _(1, 2, 8)), b), nt2::mtimes(nt2::tri1l(lu(_, _(1, 2, 8)))
                                                                   , nt2::triu(lu(_, _(1, 2, 8)))), T(200));
}

NT2_TEST_CASE_TPL(singular_lu, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> lu;
  nt2::table<T> a = nt2::ones(4, 4, as_<T>()) + T(10)*nt2::eye(4, 4, as_<T>());

  // Make it singular
  a(2,nt2::_) = T(0);

  NT2_TEST_WARNING_EXCEPT_BEGIN()
  NT2_TEST_ASSERT(lu = nt2::lu(a));
  NT2_TEST_WARNING_EXCEPT_END()
}




