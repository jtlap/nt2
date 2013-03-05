//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 function prod"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/toolbox/exponential/include/functions/exp2.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( prod_1D )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::prod;
  typedef double T;
  using nt2::_;

  std::size_t M = 5;

  table<T> r, r1;
  table<T> a(of_size(M));
  table<T> b(of_size(M));

  for(std::size_t i = 1; i <= M; ++i)
    a(i) = b(i)= 2;


  r = prod(a);
  NT2_TEST_EQUAL(r(1),1 <<nt2::numel(a)) ;

  r1 = prod(a,1);
  NT2_TEST_EQUAL(r(1), r1(1)) ;

  for(int j = 2; j <= NT2_MAX_DIMENSIONS; ++j){
    r = prod(a,j);
    for(std::size_t i = 1; i <= M; ++i)
      NT2_TEST_EQUAL(r(i), a(i));
  }

  r = prod(a+b);
  NT2_TEST_EQUAL(r(1),1<<(nt2::numel(a)) << nt2::numel(a)) ;

  r = prod(a(nt2::_));
  NT2_TEST_EQUAL(r(1),1<<nt2::numel(a)) ;


}

NT2_TEST_CASE( prod_2D )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::prod;
  typedef double T;
  using nt2::_;


  std::size_t M = 5;
  std::size_t N = 4;

  table<T> r, r1;
  table<T> a(of_size(M,N));
  table<T> b(of_size(M,N));

  for(std::size_t j = 1; j <= N; ++j){
    for(std::size_t i = 1; i <= M; ++i){
      a(i,j) = b(i,j) = 2;
    }
  }

  r1 = prod(a,1);
  for(std::size_t j = 1; j <= N; ++j){
    NT2_TEST_EQUAL(r1(1,j),1<<M) ;
  }

  r = prod(a);
  for(std::size_t j = 1; j <= N; ++j)
    NT2_TEST_EQUAL(r(1,j), 1<<M) ;


  for(std::size_t j = 1; j <= N; ++j)
    NT2_TEST_EQUAL(r(1,j), r1(1,j)) ;

  r1 = prod(a,2);

  for(std::size_t i = 1; i <= M; ++i)
    NT2_TEST_EQUAL(r1(i,1),1<<N) ;


  for(int j = 3; j <= NT2_MAX_DIMENSIONS; ++j){
    r = prod(a,j);
    for(std::size_t j = 1; j <= N; ++j)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r(i,j), a(i,j));
  }

  r = prod(a+b);
  for(std::size_t j = 1; j <= N; ++j)
    NT2_TEST_EQUAL(r(1,j), 1<<M<<M) ;

  r = prod(a(nt2::_));
  NT2_TEST_EQUAL(r(1),1<<nt2::numel(a)) ;

}

NT2_TEST_CASE( prod_3D )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::prod;
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
        a(i,j,k) = b(i,j,k) = 2;
      }
    }
  }

  r1 = prod(a,1);
  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      NT2_TEST_EQUAL(r1(1,j,k),1<<M) ;

  r = prod(a);
  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      NT2_TEST_EQUAL(r(1,j,k),1<<M) ;

  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      NT2_TEST_EQUAL(r(1,j,k), r1(1,j,k)) ;


  r = prod(a+b);
  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      NT2_TEST_EQUAL(r(1,j,k), 1<<M<<M) ;


  r = prod(a(nt2::_));
  NT2_TEST_EQUAL(r(1),nt2::exp2(nt2::numel(a))) ;

  r1 = prod(a,2);
  for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r1(i,1,k),1<<N) ;

  r1 = prod(a,3);
  for(std::size_t j = 1; j <= N; ++j)
    for(std::size_t i = 1; i <= M; ++i)
      NT2_TEST_EQUAL(r1(i,j,1),1<<O) ;


  for(int j = 4; j <= NT2_MAX_DIMENSIONS; ++j){
    r = prod(a,j);
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        for(std::size_t i = 1; i <= M; ++i)
          NT2_TEST_EQUAL(r(i,j,k), a(i,j,k));
  }

}

NT2_TEST_CASE( prod_4D )
{

  using nt2::table;
  using nt2::of_size;
  using nt2::prod;
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
          a(i,j,k,l) = 2;
          b(i,j,k,l) = 2;
          w(i,j,k,l) = x(i,j,k,l) = y(i,j,k,l) = z(1,j,k,l) = 2;
        }
      }
    }
  }

  r1 = prod(a,1);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        NT2_TEST_EQUAL(r1(1,j,k,l),1<<M) ;


  r = prod(a);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        NT2_TEST_EQUAL(r(1,j,k,l),1<<M) ;


  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        NT2_TEST_EQUAL(r(1,j,k,l), r1(1,j,k,l)) ;


  r = prod(a+b,1);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t j = 1; j <= N; ++j)
        NT2_TEST_EQUAL(r(1,j,k,l),1<<M<<M) ;


  r = prod(a(nt2::_));
  NT2_TEST_EQUAL(r(1),(nt2::exp2(nt2::numel(a)))) ;


  r = prod(a,4);
  for(std::size_t k = 1; k <= O; ++k)
    for(std::size_t j = 1; j <= N; ++j)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r(i,j,k,1),1<<P) ;



  r = prod(a,3);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t j = 1; j <= N; ++j)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r(i,j,1,l),1<<O) ;



  r = prod(a,2);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      for(std::size_t i = 1; i <= M; ++i)
        NT2_TEST_EQUAL(r(i,1,k,l),1<<N) ;



  w = prod(x+y,1) + z;
  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= N; ++j){
        NT2_TEST_EQUAL(w(1,j,k,l),(1<<M<<M) +2) ;
      }
    }
  }



}

NT2_TEST_CASE( prod )
{

  using nt2::table;
  using nt2::of_size;
  using nt2::prod;
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
          a(i,j,k,l) = 2;
          c2(1,j,k,l) = 2;
          c3(1,1,k,l) = 2;
          c4(1,1,1,l) = 2;
        }
      }
    }
  }

  r = prod(prod(a));
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      NT2_TEST_EQUAL(r(1,1,k,l),nt2::exp2(N*M)) ;


  r = prod(prod(prod(a)));
  for(std::size_t l = 1; l <= P; ++l)
    NT2_TEST_EQUAL(r(1,1,1,l),nt2::exp2(N*M*O)) ;


  r = prod(prod(prod(prod(a))));
  NT2_TEST_EQUAL(r(1,1,1,1),nt2::exp2(nt2::numel(a))) ;



  r = prod(c2);
  for(std::size_t l = 1; l <= P; ++l)
    for(std::size_t k = 1; k <= O; ++k)
      NT2_TEST_EQUAL(r(1,1,k,l),1<<N) ;

  r = prod(c3);
  for(std::size_t l = 1; l <= P; ++l)
    NT2_TEST_EQUAL(r(1,1,1,l),1<<O) ;

  r = prod(c4);
  NT2_TEST_EQUAL(r(1,1,1,1),1<<P) ;

}
