//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - svd_result factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(svd_result, NT2_REAL_TYPES)
{
  using nt2::_; 
  using nt2::tag::factorization::svd_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t; 
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t; 
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
  b(_, 1) = b(_, 3); 
  nt2::details::svd_result<t_t> f(b);

//   nt2::disp("b     ", b); 
  nt2::disp("values", f.values());
  t_t u  = f.u();
  nt2::disp("u    ", u);
  t_t vt = f.vt();
  nt2::disp("vt    ", vt);
  t_t w  = f.w(); 
  nt2::disp("w    ", w);
  t_t sg = f.singular();
  nt2::disp("sg   ", sg);
  t_t nul = f.null();
  nt2::disp("null   ", nul);
  t_t zer = f.zerosolve(); 
  nt2::disp("zer    ", zer);
  T condition =  f.cond();
  std::cout << "cond " << condition << std::endl; 
  T norm =  f.norm();
  std::cout << "norm " << norm << std::endl; 
  T norminv =  f.norminv();
  std::cout << "norminv " << norminv << std::endl; 
  std::cout << "rank         " << f.rank()  << std::endl; 
  t_t ort = f.orth();                                     
  nt2::disp("orth ", ort);
  std::cout << nt2::details::svd_result<t_t>(b,'N','N').norm() << std::endl;
  // the solvers still don't work because of matricial product lack

}
NT2_TEST_CASE_TPL(svd_result, NT2_REAL_TYPES)
{
  using nt2::_; 
  using nt2::tag::factorization::svd_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t; 
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t; 
  nt2::details::svd_result<t_t> f(nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>()));

//   nt2::disp("b     ", b); 
  nt2::disp("values", f.values());
  t_t u  = f.u();
  nt2::disp("u    ", u);
  t_t vt = f.vt();
  nt2::disp("vt    ", vt);
  t_t w  = f.w(); 
  nt2::disp("w    ", w);
  t_t sg = f.singular();
  nt2::disp("sg   ", sg);
  t_t nul = f.null();
  nt2::disp("null   ", nul);
  t_t zer = f.zerosolve(); 
  nt2::disp("zer    ", zer);
  T condition =  f.cond();
  std::cout << "cond " << condition << std::endl; 
  T norm =  f.norm();
  std::cout << "norm " << norm << std::endl; 
  T norminv =  f.norminv();
  std::cout << "norminv " << norminv << std::endl; 
  std::cout << "rank         " << f.rank()  << std::endl; 
  t_t ort = f.orth();                                     
  nt2::disp("orth ", ort);
  std::cout << nt2::details::svd_result<t_t>(b,'N','N').norm() << std::endl;
  // the solvers still don't work because of matricial product lack

}
