/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 function sum"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/max.hpp>

#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( sum_1D )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::sum;
  typedef double T;
  using nt2::_;

  std::size_t M = 5;

  table<T> r, r1;
  table<T> a(of_size(M));
  table<T> b(of_size(M));
  table<T> c;
  r =  sum(c);
  NT2_TEST_EQUAL(r(1), 0);

  for(std::size_t i = 1; i <= M; ++i)
    a(i) = b(i)= 1;


  r = sum(a);
  NT2_TEST_EQUAL(r(1),M) ;

  r1 = sum(a,1);
  NT2_TEST_EQUAL(r(1), r1(1)) ;

  for(int j = 2; j <= NT2_MAX_DIMENSIONS; ++j){
    r = sum(a,j);
    for(std::size_t i = 1; i <= M; ++i)
      NT2_TEST_EQUAL(r(i), a(i));
  }

  r = sum(a+b);
  NT2_TEST_EQUAL(r(1),2*M) ;

  r = sum(a(nt2::_));
  NT2_TEST_EQUAL(r(1),M) ;
  T rs = sum(a(nt2::_));
  NT2_TEST_EQUAL(rs,M) ;

}

NT2_TEST_CASE( sum_2D )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::sum;
  typedef double T;
  using nt2::_;


  std::size_t M = 5;
  std::size_t N = 4;

  table<T> r, r1;
  table<T> a(of_size(M,N));
  table<T> b(of_size(M,N));

  for(std::size_t j = 1; j <= N; ++j){
    for(std::size_t i = 1; i <= M; ++i){
      a(i,j) = b(i,j) = T(1);
    }
  }

  r1 = sum(a,1);
  for(std::size_t j = 1; j <= N; ++j){
    NT2_TEST_EQUAL(r1(1,j),M) ;
  }

  r = sum(a);
  for(std::size_t j = 1; j <= N; ++j)
    NT2_TEST_EQUAL(r(1,j), M) ;


  for(std::size_t j = 1; j <= N; ++j)
    NT2_TEST_EQUAL(r(1,j), r1(1,j)) ;

  r1 = sum(a,2);

  for(std::size_t i = 1; i <= M; ++i)
    NT2_TEST_EQUAL(r1(i,1),N) ;


  for(int j = 3; j <= NT2_MAX_DIMENSIONS; ++j){
    r = sum(a,j);
    for(std::size_t j = 1; j <= N; ++j)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r(i,j), a(i,j));
  }

  r = sum(a+b);
  for(std::size_t j = 1; j <= N; ++j)
    NT2_TEST_EQUAL(r(1,j), 2*M) ;

  r = sum(a(nt2::_));
  NT2_TEST_EQUAL(r(1),nt2::numel(a)) ;

}

NT2_TEST_CASE( sum_3D )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::sum;
  typedef double T;
  using nt2::_;


  std::size_t M = 5;
  std::size_t N = 4;
  std::size_t O = 4;


  table<T> r, r1;
  table<T> a(of_size(M,N,O));
  table<T> b(of_size(M,N,O));

  for(std::size_t k = 1; k <= O; ++k){
    for(std::size_t j = 1; j <= N; ++j){
      for(std::size_t i = 1; i <= M; ++i){
        a(i,j,k) = b(i,j,k) = T(1);
      }
    }
  }

  r1 = sum(a,1);
  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      NT2_TEST_EQUAL(r1(1,j,k),M) ;

  r = sum(a);
  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      NT2_TEST_EQUAL(r(1,j,k),M) ;

  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      NT2_TEST_EQUAL(r(1,j,k), r1(1,j,k)) ;


  r = sum(a+b);
  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      NT2_TEST_EQUAL(r(1,j,k), 2*M) ;


  r = sum(a(nt2::_));
  NT2_TEST_EQUAL(r(1),nt2::numel(a)) ;

  r1 = sum(a,2);
  for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r1(i,1,k),N) ;

  r1 = sum(a,3);
  for(std::size_t j = 1; j <= N; ++j)
    for(std::size_t i = 1; i <= M; ++i)
      NT2_TEST_EQUAL(r1(i,j,1),O) ;


  for(int j = 4; j <= NT2_MAX_DIMENSIONS; ++j){
    r = sum(a,j);
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        for(std::size_t i = 1; i <= M; ++i)
          NT2_TEST_EQUAL(r(i,j,k), a(i,j,k));
  }

}

NT2_TEST_CASE( sum_4D )
{

  using nt2::table;
  using nt2::of_size;
  using nt2::sum;
  typedef double T;
  using nt2::_;


  std::size_t M = 5;
  std::size_t N = 4;
  std::size_t O = 3;
  std::size_t P = 2;

  table<T> r, r1;
  table<T> a(of_size(M,N,O,P));
  table<T> b(of_size(M,N,O,P));


  table<T> w(of_size(M,N,O,P));
  table<T> x(of_size(M,N,O,P));
  table<T> y(of_size(M,N,O,P));
  table<T> z(of_size(1,N,O,P));

  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= N; ++j){
        for(std::size_t i = 1; i <= M; ++i){
          a(i,j,k,l) = T(1);
          b(i,j,k,l) = T(1);
          w(i,j,k,l) = x(i,j,k,l) = y(i,j,k,l) = z(1,j,k,l) = T(1);
        }
      }
    }
  }

  r1 = sum(a,1);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        NT2_TEST_EQUAL(r1(1,j,k,l),M) ;


  r = sum(a);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        NT2_TEST_EQUAL(r(1,j,k,l),M) ;


  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        NT2_TEST_EQUAL(r(1,j,k,l), r1(1,j,k,l)) ;


  r = sum(a+b,1);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        NT2_TEST_EQUAL(r(1,j,k,l),2*M) ;


  r = sum(a(nt2::_));
  NT2_TEST_EQUAL(r(1),nt2::numel(a)) ;


  r = sum(a,4);
  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r(i,j,k,1),P) ;



  r = sum(a,3);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t j = 1; j <= N; ++j)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r(i,j,1,l),O) ;



  r = sum(a,2);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r(i,1,k,l),N) ;



  w = sum(x+y,1) + z;
  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= N; ++j){
        NT2_TEST_EQUAL(w(1,j,k,l),2*M+1) ;
      }
    }
  }

}

NT2_TEST_CASE( sum )
{

  using nt2::table;
  using nt2::of_size;
  using nt2::sum;
  typedef double T;
  using nt2::_;


  std::size_t M = 5;
  std::size_t N = 4;
  std::size_t O = 3;
  std::size_t P = 2;

  table<T> r, r1;

  table<T> a(of_size(M,N,O,P));

  table<T> c2(of_size(1,N,O,P));
  table<T> c3(of_size(1,1,O,P));
  table<T> c4(of_size(1,1,1,P));


  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= N; ++j){
        for(std::size_t i = 1; i <= M; ++i){
          a(i,j,k,l) = T(1);
          c2(1,j,k,l) = T(1);
          c3(1,1,k,l) = T(1);
          c4(1,1,1,l) = T(1);
        }
      }
    }
  }

  r = sum(sum(a));
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      NT2_TEST_EQUAL(r(1,1,k,l),N*M) ;


  r = sum(sum(sum(a)));
  for(std::size_t l = 1; l <= P; ++l)
    NT2_TEST_EQUAL(r(1,1,1,l),N*M*O) ;


  r = sum(sum(sum(sum(a))));
  NT2_TEST_EQUAL(r(1,1,1,1),N*M*O*P) ;


  r = sum(c2);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      NT2_TEST_EQUAL(r(1,1,k,l),N) ;

  r = sum(c3);
  for(std::size_t l = 1; l <= P; ++l)
    NT2_TEST_EQUAL(r(1,1,1,l),O) ;

  r = sum(c4);
  NT2_TEST_EQUAL(r(1,1,1,1),P) ;
}

