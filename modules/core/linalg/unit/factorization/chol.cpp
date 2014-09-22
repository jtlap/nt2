//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied chol function"

#include <nt2/include/functions/chol.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/pascal.hpp>
#include <nt2/include/functions/dec.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL(chol_no_1i, NT2_REAL_TYPES )
{
  using nt2::_;
  int p;
  nt2::table<T,nt2::positive_definite_>
    a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
  nt2::table<T> u;

  std::cout << " u = chol(a) " << std::endl;
  u = nt2::chol(a);
  NT2_TEST_ULP_EQUAL(a , nt2::mtimes(nt2::trans(u),u), T(20) );

  std::cout << " tie(u,p) = chol(a) " << std::endl;
  nt2::tie(u,p) = nt2::chol(a);
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a , nt2::mtimes(nt2::trans(u),u), T(20) );
}


NT2_TEST_CASE_TPL(chol_no_2i, NT2_REAL_TYPES )
{
  using nt2::_;
  int p;
  nt2::table<T,nt2::positive_definite_>
    a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
  nt2::table<T> u, l, u1;

  std::cout << " u = chol(a, nt2::upper_) " << std::endl;
  u = nt2::chol(a, nt2::upper_);
  NT2_TEST_ULP_EQUAL(a , nt2::mtimes(nt2::trans(u),u), T(20) );

  std::cout << " tie(l,p) = chol(a, lower_) " << std::endl;
  nt2::tie(l,p) = nt2::chol(a, nt2::lower_);
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(l, nt2::trans(l)), T(20) );

  std::cout << " tie(u,p) = chol(a, raw_) " << std::endl;
  nt2::tie(u,p) = nt2::chol(a, nt2::raw_);
  u1 =  triu(u);

  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::trans(u1),u1), T(20) );
}


NT2_TEST_CASE_TPL(chol_no_3i, NT2_REAL_TYPES )
{
  using nt2::_;
  int p;
  nt2::table<T,nt2::positive_definite_>
    a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
  nt2::table<T> u, l, u1, l1;

  std::cout << " tie(u,p) = chol(a, raw_, upper_) " << std::endl;
  nt2::tie(u,p) = nt2::chol(a, nt2::raw_, nt2::upper_);
  u1 =  triu(u);
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::trans(u1),u1), T(20) );

  std::cout << " tie(l,p) = chol(a, raw_, lower_) " << std::endl;
  nt2::tie(l,p) = nt2::chol(a, nt2::raw_, nt2::lower_);
  l1 =  tril(l);
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(l1, nt2::trans(l1)), T(20) );

  std::cout << " tie(u,p) = chol(a, upper_, raw_) " << std::endl;
  nt2::tie(u,p) = nt2::chol(a, nt2::upper_, nt2::raw_);
  u1 =  triu(u);
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::trans(u1),u1), T(20) );

  std::cout << " tie(l,p) = chol(a, lower_, raw_) " << std::endl;
  nt2::tie(l,p) = nt2::chol(a, nt2::lower_, nt2::raw_);
  l1 =  tril(l);
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(l1, nt2::trans(l1)), T(20) );
}

NT2_TEST_CASE_TPL(chol_no_1i_nondef, NT2_REAL_TYPES )
{
  using nt2::_;
  int p;
  nt2::table<T> a = nt2::pascal(5, nt2::meta::as_<T>());
  a(5, 5) = nt2::dec(a(5, 5));

  nt2::table<T> u;

  std::cout << " u = chol(a) " << std::endl;
  NT2_TEST_ASSERT(u = nt2::chol(a));

  std::cout << " tie(u,p) = chol(a) " << std::endl;
  nt2::tie(u,p) = nt2::chol(a);
  NT2_TEST_EQUAL(p,5);
  NT2_TEST_ULP_EQUAL(a(_(1, 4),_(1, 4)), nt2::mtimes(nt2::trans(u),u), T(20) );
}


NT2_TEST_CASE_TPL(chol_no_2i_nondef, NT2_REAL_TYPES )
{
  using nt2::_;
  int p;
  nt2::table<T> a = nt2::pascal(5, nt2::meta::as_<T>());
  a(5, 5) = nt2::dec(a(5, 5));

  nt2::table<T> u, l, u1;

  std::cout << " u = chol(a, nt2::upper_) " << std::endl;
  NT2_TEST_ASSERT(u = nt2::chol(a, nt2::upper_));

  std::cout << " l = chol(a, nt2::lower_) " << std::endl;
  NT2_TEST_ASSERT(l = nt2::chol(a, nt2::lower_));

  std::cout << " tie(l,p) = chol(a, lower_) " << std::endl;
  nt2::tie(l,p) = nt2::chol(a, nt2::lower_);
  NT2_TEST_EQUAL(p,5);
  NT2_TEST_ULP_EQUAL(a(_(1, 4),_(1, 4)), nt2::mtimes(l, nt2::trans(l)), T(20) );

  std::cout << " tie(u,p) = chol(a, raw_) " << std::endl;
  nt2::tie(u,p) = nt2::chol(a, nt2::raw_);
  u1 =  triu(u(_(1, 4),_(1, 4)));

  NT2_TEST_EQUAL(p,5);
  NT2_TEST_ULP_EQUAL(a(_(1, 4),_(1, 4)), nt2::mtimes(nt2::trans(u1),u1), T(20) );
}


NT2_TEST_CASE_TPL(chol_no_3i_nondef, NT2_REAL_TYPES )
{
  using nt2::_;
  int p;
  nt2::table<T> a = nt2::pascal(5, nt2::meta::as_<T>());
  a(5, 5) = nt2::dec(a(5, 5));

  nt2::table<T> u, l, u1, l1;

  std::cout << " tie(u,p) = chol(a, raw_, upper_) " << std::endl;
  nt2::tie(u,p) = nt2::chol(a, nt2::raw_, nt2::upper_);
  u1 =  triu(u(_(1, 4),_(1, 4)));
  NT2_TEST_EQUAL(p,5);
  NT2_TEST_ULP_EQUAL(a(_(1, 4),_(1, 4)), nt2::mtimes(nt2::trans(u1),u1), T(20) );

  std::cout << " tie(l,p) = chol(a, raw_, lower_) " << std::endl;
  nt2::tie(l,p) = nt2::chol(a, nt2::raw_, nt2::lower_);
  l1 =  tril(l(_(1, 4),_(1, 4)));
  NT2_TEST_EQUAL(p,5);
  NT2_TEST_ULP_EQUAL(a(_(1, 4),_(1, 4)), nt2::mtimes(l1, nt2::trans(l1)), T(20) );

  std::cout << " tie(u,p) = chol(a, upper_, raw_) " << std::endl;
  nt2::tie(u,p) = nt2::chol(a, nt2::upper_, nt2::raw_);
  u1 =  triu(u(_(1, 4),_(1, 4)));
  NT2_TEST_EQUAL(p,5);
  NT2_TEST_ULP_EQUAL(a(_(1, 4),_(1, 4)), nt2::mtimes(nt2::trans(u1),u1), T(20) );

  std::cout << " tie(l,p) = chol(a, lower_, raw_) " << std::endl;
  nt2::tie(l,p) = nt2::chol(a, nt2::lower_, nt2::raw_);
  l1 =  tril(l(_(1, 4),_(1, 4)));
  NT2_TEST_EQUAL(p,5);
  NT2_TEST_ULP_EQUAL(a(_(1, 4),_(1, 4)), nt2::mtimes(l1, nt2::trans(l1)), T(20) );
}



NT2_TEST_CASE_TPL(chol_no_1i_sub, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;
  int p;
  nt2::table<T,nt2::positive_definite_>
    a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
  nt2::table<T> u =  nt2::ones(6, 3, as_<T>());

  std::cout << " u(_(1, 2, 6), _) = chol(a) " << std::endl;
  u(_(1, 2, 6), _) = nt2::chol(a);
  NT2_TEST_ULP_EQUAL(a , nt2::mtimes(nt2::trans(u(_(1, 2, 6), _)),u(_(1, 2, 6), _)), T(20) );

  std::cout << " tie(u(_(1, 2, 6), _),p) = chol(a) " << std::endl;
  nt2::tie(u(_(1, 2, 6), _),p) = nt2::chol(a);
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a , nt2::mtimes(nt2::trans(u(_(1, 2, 6), _)),u(_(1, 2, 6), _)), T(20) );
}


NT2_TEST_CASE_TPL(chol_no_2i_sub, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;
  int p;
  nt2::table<T,nt2::positive_definite_>
    a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
  nt2::table<T> u, l, u1;
  u = nt2::ones(6, 3, as_<T>());
  l = nt2::ones(6, 3, as_<T>());

  std::cout << " u(_(1, 2, 6), _) = chol(a, nt2::upper_) " << std::endl;
  u(_(1, 2, 6), _) = nt2::chol(a, nt2::upper_);
  NT2_TEST_ULP_EQUAL(a , nt2::mtimes(nt2::trans(u(_(1, 2, 6), _)),u(_(1, 2, 6), _)), T(20) );

  std::cout << " tie(l,p) = chol(a, lower_) " << std::endl;
  nt2::tie(l(_(1, 2, 6), _),p) = nt2::chol(a, nt2::lower_);
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(l(_(1, 2, 6), _), nt2::trans(l(_(1, 2, 6), _))), T(20) );

  std::cout << " tie(u,p) = chol(a, raw_) " << std::endl;
  nt2::tie(u(_(1, 2, 6), _),p) = nt2::chol(a, nt2::raw_);
  u1 =  triu(u(_(1, 2, 6), _));

  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::trans(u1),u1), T(20) );
}


NT2_TEST_CASE_TPL(chol_no_3i_sub, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;
  int p;
  nt2::table<T,nt2::positive_definite_>
    a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
  nt2::table<T> u, l, u1, l1;
  u = nt2::ones(6, 3, as_<T>());
  l = nt2::ones(6, 3, as_<T>());

  std::cout << " tie(u(_(1, 2, 6), _),p) = chol(a, raw_, upper_) " << std::endl;
  nt2::tie(u(_(1, 2, 6), _),p) = nt2::chol(a, nt2::raw_, nt2::upper_);
  u1 =  triu(u(_(1, 2, 6), _));
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::trans(u1),u1), T(20) );

  std::cout << " tie(l(_(1, 2, 6), _),p) = chol(a, raw_, lower_) " << std::endl;
  nt2::tie(l(_(1, 2, 6), _),p) = nt2::chol(a, nt2::raw_, nt2::lower_);
  l1 =  tril(l(_(1, 2, 6), _));
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(l1, nt2::trans(l1)), T(20) );

  std::cout << " tie(u(_(1, 2, 6), _),p) = chol(a, upper_, raw_) " << std::endl;
  nt2::tie(u(_(1, 2, 6), _),p) = nt2::chol(a, nt2::upper_, nt2::raw_);
  u1 =  triu(u(_(1, 2, 6), _));
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::trans(u1),u1), T(20) );

  std::cout << " tie(l(_(1, 2, 6), _),p) = chol(a, lower_, raw_) " << std::endl;
  nt2::tie(l(_(1, 2, 6), _),p) = nt2::chol(a, nt2::lower_, nt2::raw_);
  l1 =  tril(l(_(1, 2, 6), _));
  NT2_TEST_EQUAL(p,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(l1, nt2::trans(l1)), T(20) );

}

