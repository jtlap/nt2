//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 optimize toolbox - brent"

#include <iostream>
#include <nt2/include/functions/brent.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

template<class T> inline T f0( T x ) { return x*x*x-3*x+4; }

float f1( float x ) { return x*x*x-3*x+4; }

struct f2
{
  template<class T> inline T operator()( T x ) const
  {
    return x*x*x-3*x+4;
  }
};

double f3( double x, double a, double b ) { return x*x*x-a*x+b; }

NT2_TEST_CASE_TPL( brent_function_ptr, (double)(float) )
{
  using nt2::brent;
  using nt2::optimization::output;

  output<T,T> res = brent<T>( &f0<T>, 0, 0.5, 2 );

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
}

NT2_TEST_CASE_TPL( brent_function, (double)(float) )
{
  using nt2::brent;
  using nt2::optimization::output;

  output<T,T> res = brent<T>( f1, 0, 0.5, 2 );

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - 1.f), nt2::Sqrteps<float>());
}

NT2_TEST_CASE_TPL( brent_functor, (double)(float) )
{
  using nt2::brent;
  using nt2::optimization::output;

  output<T,T> res = brent<T>( f2(), 0, 0.5, 2 );

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
}

NT2_TEST_CASE_TPL( brent_bind, (double)(float) )
{
  using nt2::brent;
  using nt2::optimization::output;

  output<T,T> res = brent<T>( boost::bind(f3, _1, 3., 4.), 0, 0.5, 2 );

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
}

NT2_TEST_CASE_TPL( brent_lambdda, (double)(float) )
{
  using nt2::brent;
  using nt2::optimization::output;
  namespace bl = boost::lambda;

  output<T,T> res = brent<T>( bl::_1*bl::_1*bl::_1 - 3*bl::_1 + 4
                            , 0, 0.5, 2
                            );

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
}

NT2_TEST_CASE_TPL( brent_tie, (double)(float) )
{
  using nt2::brent;
  using boost::fusion::tie;
  using boost::fusion::ignore;

  std::size_t i;
  T x,y,fx;
  bool convergence_successful;

  tie(x,fx,i,convergence_successful) = brent<T>( &f0<T>, 0, 0.5, 2 );
  std::cout << "Minimum : f(" << x << ") = " << fx
            << " after " << i <<  " iterations\n";

  NT2_TEST(convergence_successful);
  NT2_TEST_LESSER_EQUAL(nt2::abs(x - T(1)), nt2::Sqrteps<T>());

  tie(y,ignore,ignore,ignore) = brent<T>( &f0<T>, 0, 0.5, 2 );
  std::cout << "Minimum is at y = " << y << "\n";

  NT2_TEST_LESSER_EQUAL(nt2::abs(y - T(1)), nt2::Sqrteps<T>());
}

NT2_TEST_CASE_TPL( brent_option, (double)(float) )
{
  using nt2::brent;
  using nt2::options;
  using nt2::optimization::output;

  output<T,T> res = brent<T>( f1, 0, 0.5, 2
                            , options [ nt2::iterations_ = 10
                                      , nt2::tolerance::absolute_ = T(1e-3)
                                      ]
                            );

  std::cout << "Minimum : f(" << res.minimum << ") = "  << res.value
            << " after "      << res.iterations_count   <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - 1.f), 1e-3);

  res = brent<T>( f1, 0,0.5,2, options [ nt2::iterations_ = 1 ] );
  NT2_TEST(!res.successful);
}
