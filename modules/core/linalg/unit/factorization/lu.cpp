//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL ( lu_lapack_output, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> y, l, u, p;
  nt2::table<nt2_la_int> sp;
  nt2::table<int> ip;
  nt2::table<T> a = nt2::trans(nt2::reshape(nt2::_(T(1), T(9)), 3, 3));
  a(3, 3) = 0;
  nt2::table<T> b = a(nt2::_, nt2::cons(3, 2, 1));
  a = b;
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  y =  nt2::lu(a);
  NT2_DISPLAY(y);
  nt2::tie(y, sp) = nt2::lu(a, nt2::lapack_);
  NT2_DISPLAY(y);
  NT2_DISPLAY(sp);
  nt2::tie(l, u) = nt2::lu(a);
  NT2_DISPLAY(l);
  NT2_DISPLAY(u);
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(l, u)), a, 0.5 );
  std::cout << " ==================== " << std::endl;
  nt2::tie(l, u, ip) = nt2::lu(a, nt2::vector_);
  NT2_DISPLAY(l);
  NT2_DISPLAY(u);
  NT2_DISPLAY(ip);
  std::cout << "---------------------" << std::endl;
  nt2::tie(l, u, p) = nt2::lu(a, nt2::matrix_);
  NT2_DISPLAY(l);
  NT2_DISPLAY(u);
  NT2_DISPLAY(p);
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(p, a)), (nt2::mtimes(l, u)), 0.5           );



}

NT2_TEST_CASE_TPL ( square_lu, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> lu, l, u, p;
  nt2::table<T> a = nt2::ones(4, 4, as_<T>()) + T(10)*nt2::eye(4, 4, as_<T>());
  nt2::table<T> b = a(nt2::_, nt2::cons(4, 3, 2, 1));
  a = b;
  NT2_DISPLAY(a);
  /// Interface tests
  lu = nt2::lu(a);

  lu = nt2::lu(a) - a;
  nt2::tie(lu) = nt2::lu(a);
  lu = nt2::zeros(4, 4, nt2::meta::as_<T>());
  nt2::tie(lu(_(2,3),_(2,3))) = nt2::lu( a(_(1,2),_(1,2)) );

  // [L,U] = LU(A) <=> A = L*U
  nt2::tie(l, u) = nt2::lu(a);
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(l, u)), a, 0.5 );


  NT2_DISPLAY(b);
  lu = nt2::lu(b);
  nt2::tie(l, u) = nt2::lu(b);

  // [L,U,P] = LU(A) <=> P*A = L*U
  nt2::tie(l, u, p) = nt2::lu(a);
  NT2_TEST_EQUAL    ( p                  , (nt2::fliplr(nt2::eye(4, nt2::meta::as_<T>()))) );
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(p, a)), (nt2::mtimes(l, u)), 0.5           );

  // [L,U,IP] = LU(A) <=> A(IP, _)= L*U
  nt2::table<int> ip;
  nt2::tie(l, u, ip) = nt2::lu(a, nt2::vector_);
  NT2_DISPLAY(ip);
  NT2_TEST_ULP_EQUAL( a(ip, nt2::_), (nt2::mtimes(l, u)), 0.5           );

}

NT2_TEST_CASE_TPL ( square_lu_complex, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  typedef std::complex<T>          cT;
  nt2::table<cT> lu, l, u;
  nt2::table<T> p;
  nt2::table<cT> a = nt2::ones(4, 4, as_<cT>()) + T(10)*nt2::eye(4, 4, as_<cT>());

  /// Interface tests
  lu = nt2::lu(a);

  lu = nt2::lu(a) - a;
  nt2::tie(lu) = nt2::lu(a);
  lu = nt2::zeros(4, 4, nt2::meta::as_<cT>());
  nt2::tie(lu(_(2,3),_(2,3))) = nt2::lu( a(_(1,2),_(1,2)) );

  // [L,U] = LU(A) <=> A = L*U
  nt2::tie(l, u) = nt2::lu(a);
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(l, u)), a, 0.5 );

  // [L,U,P] = LU(A) <=> P*A = L*U
  nt2::tie(l, u, p) = nt2::lu(a);
  NT2_TEST_EQUAL    ( p                  , (nt2::eye(4, nt2::meta::as_<T>())) );
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(p, a)), (nt2::mtimes(l, u)), 0.5           );
}

NT2_TEST_CASE_TPL ( non_square_lu, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> lu, l, u, p;
  nt2::table<T> a = nt2::ones(4, 7, as_<T>()) + T(10)*nt2::eye(4, 7, as_<T>());
  NT2_DISPLAY(a);

  /// Interface tests
  lu = nt2::lu(a);

  lu = nt2::lu(a) - a;
  nt2::tie(lu) = nt2::lu(a);

  lu = nt2::zeros(4, 7, nt2::meta::as_<T>());
  nt2::tie(lu(_(2,3),_(2,5))) = nt2::lu( a(_(1,2),_(1,4)) );

  // [L,U] = LU(A) <=> A = L*U
  nt2::tie(l, u) = nt2::lu(a);
  NT2_DISPLAY(l);
  NT2_DISPLAY(u);
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(l, u)), a, 0.5 );

  NT2_DISPLAY(trans(a));
  NT2_DISPLAY(l);
  NT2_DISPLAY(u);
  nt2::tie(l, u) = nt2::lu(trans(a));
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(l, u)), trans(a), 0.5 );

  //[L,U,P] = LU(A) <=> P*A = L*U
  nt2::tie(l, u, p) = nt2::lu(a);
  NT2_TEST_EQUAL    ( p                  , (nt2::eye(4, nt2::meta::as_<T>())) );
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(p, a)), (nt2::mtimes(l, u)), 0.5           );
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
