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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/sdk/details/type_id.hpp>


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

  table<T,nt2::_1D> a00(of_size(M));
  table<T>          a01(of_size(M));

  table<T> a1;
  table<T> a2_4(of_size(M,N,O,P));
  table<T> b2_4(of_size(M,N,O,P));
  table<T, nt2::_3D> a2_3(of_size(M,N,O));
  table<T, nt2::_2D> a2_2(of_size(M,N));

  table<T> w(of_size(M,N,O,P));
  table<T> x(of_size(M,N,O,P));
  table<T> y(of_size(M,N,O,P));
  table<T> z(of_size(1,N,O,P));

  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= N; ++j){
        for(std::size_t i = 1; i <= M; ++i){
          a2_4(i,j,k,l) = T(1);
          b2_4(i,j,k,l) = T(1);
          a2_3(i,j,k) = T(1);
          a2_2(i,j) = T(1);
          a00(i) = T(1);
          a01(i) = T(1);
          w(i,j,k,l) = x(i,j,k,l) = y(i,j,k,l) = z(1,j,k,l) = T(1);
        }
      }
    }
  }
  
  a1 = sum(a2_4,1);
  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= N; ++j){
        NT2_TEST_EQUAL(T(a1(1,j,k,l)),T(M)) ;
      }
    }
  }



  a1 = sum(a2_4 + b2_4,1);
  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= N; ++j){
        NT2_TEST_EQUAL(T(a1(1,j,k,l)),2*T(M)) ;
      }
    }
  }

  a1 = sum(a2_3,1);
  for(std::size_t k = 1; k <= O; ++k){
    for(std::size_t j = 1; j <= N; ++j){
      NT2_TEST_EQUAL(T(a1(1,j,k)),T(M)) ;
    }
  }

  a1 = sum(a2_2,1);
  for(std::size_t j = 1; j <= N; ++j){
    NT2_TEST_EQUAL(T(a1(1,j)),T(M)) ;
  }


  a1 = sum(a00);
  NT2_TEST_EQUAL(T(a1(1)),T(M)) ;

  // a1 = sum(a2_4(nt2::_));
  // NT2_TEST_EQUAL(T(a1(1)),T(nt2::numel(a2_4))) ;

  a1 = sum(a01);
  NT2_TEST_EQUAL(T(a1(1)),T(M)) ;
  
  a1 = sum(a2_4,4);
  for(std::size_t k = 1; k <= O; ++k){
    for(std::size_t j = 1; j <= N; ++j){
      for(std::size_t i = 1; i <= M; ++i){
        NT2_TEST_EQUAL(T(a1(i,j,k,1)),T(P)) ;
      }
    }
  }

  a1 = sum(a2_3,3);
  for(std::size_t j = 1; j <= N; ++j){
    for(std::size_t i = 1; i <= M; ++i){
      NT2_TEST_EQUAL(T(a1(i,j,1)),T(O)) ;
    }
  }

  a1 = sum(a2_2,2);
  for(std::size_t i = 1; i <= M; ++i){
    NT2_TEST_EQUAL(T(a1(i,1)),T(N)) ;
  }


  a1 = sum(a2_4,3);
  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t j = 1; j <= N; ++j){
      for(std::size_t i = 1; i <= M; ++i){
        NT2_TEST_EQUAL(T(a1(i,j,1,l)),T(O)) ;
      }
    }
  }


  a1 = sum(a2_4,2);
  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t i = 1; i <= M; ++i){
        NT2_TEST_EQUAL(T(a1(i,1,k,l)),T(N)) ;
      }
    }
  }

  a1 = sum(a2_3,2);
  for(std::size_t k = 1; k <= O; ++k){
    for(std::size_t i = 1; i <= M; ++i){
      NT2_TEST_EQUAL(T(a1(i,1,k)),T(N)) ;
    }
  }

  w = sum(x+y,1) + z;
  for(std::size_t l = 1; l <= P; ++l){
    for(std::size_t k = 1; k <= O; ++k){
      for(std::size_t j = 1; j <= N; ++j){
        NT2_TEST_EQUAL(T(w(1,j,k,l)),T(2)*T(M)+T(1)) ;
      }
    }
  }
  

}
