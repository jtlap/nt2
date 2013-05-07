//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 optimize toolbox - hjmin"

#include <iostream>
#include <nt2/include/functions/hjmin.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/table.hpp>

struct ffp
{
  template < class Tab > inline
  typename Tab::value_type operator()(const Tab & x ) const
  {
    typedef typename Tab::value_type value_type;
    return nt2::globalsum((nt2::sqr(x)-value_type(3))*x)+value_type(4);
  }
};

template<class Tab > typename Tab::value_type f1(const Tab & x )
{
    typedef typename Tab::value_type value_type;
  return nt2::globalsum((nt2::sqr(x)-value_type(3))*x)+value_type(4);
}

NT2_TEST_CASE_TPL( hjmin_function_ptr, NT2_REAL_TYPES )
{
  using nt2::hjmin;
   using nt2::optimization::output;
  typedef nt2::table<T> tab_t;
  tab_t x0 = nt2::zeros(nt2::of_size(1, 3), nt2::meta::as_<T>());
  tab_t h = nt2::ones (nt2::of_size(1, 3), nt2::meta::as_<T>())*nt2::Half<T>();
  tab_t r = nt2::ones (nt2::of_size(1, 3), nt2::meta::as_<T>());
  output<tab_t,T> res = hjmin(&f1<tab_t>, x0, h);

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(res.minimum()-r)), nt2::Sqrteps<T>());
}

NT2_TEST_CASE_TPL( hjmin_functor, NT2_REAL_TYPES )
{
  using nt2::hjmin;
   using nt2::optimization::output;
  typedef nt2::table<T> tab_t;
  tab_t x0 = nt2::zeros(nt2::of_size(1, 2), nt2::meta::as_<T>());
  tab_t h = nt2::ones (nt2::of_size(1, 2), nt2::meta::as_<T>())*nt2::Half<T>();
  tab_t r = nt2::ones (nt2::of_size(1, 2), nt2::meta::as_<T>());
  output<tab_t,T> res = hjmin(ffp(), x0, h);

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(res.minimum()-r)), nt2::Sqrteps<T>());
}

// NT2_TEST_CASE_TPL( hjmin_function, (double)(float) )
// {
//   using nt2::hjmin;
//   using nt2::optimization::output;

//   output<T,T> res = hjmin<T>( f1, 0, 0.5, 2 );

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - 1.f), nt2::Sqrteps<float>());
// }

// NT2_TEST_CASE_TPL( hjmin_functor, (double)(float) )
// {
//   using nt2::hjmin;
//   using nt2::optimization::output;

//   output<T,T> res = hjmin<T>( f2(), 0, 0.5, 2 );

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( hjmin_bind, (double)(float) )
// {
//   using nt2::hjmin;
//   using nt2::optimization::output;

//   output<T,T> res = hjmin<T>( boost::bind(f3, _1, 3., 4.), 0, 0.5, 2 );

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( hjmin_lambdda, (double)(float) )
// {
//   using nt2::hjmin;
//   using nt2::optimization::output;
//   namespace bl = boost::lambda;

//   output<T,T> res = hjmin<T>( bl::_1*bl::_1*bl::_1 - 3*bl::_1 + 4
//                             , 0, 0.5, 2
//                             );

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( hjmin_tie, (double)(float) )
// {
//   using nt2::hjmin;
//   using boost::fusion::tie;
//   using boost::fusion::ignore;

//   std::size_t i;
//   T x,y,fx;
//   bool convergence_successful;

//   tie(x,fx,i,convergence_successful) = hjmin<T>( &f0<T>, 0, 0.5, 2 );
//   std::cout << "Minimum : f(" << x << ") = " << fx
//             << " after " << i <<  " iterations\n";

//   NT2_TEST(convergence_successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(x - T(1)), nt2::Sqrteps<T>());

//   tie(y,ignore,ignore,ignore) = hjmin<T>( &f0<T>, 0, 0.5, 2 );
//   std::cout << "Minimum is at y = " << y << "\n";

//   NT2_TEST_LESSER_EQUAL(nt2::abs(y - T(1)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( hjmin_option, (double)(float) )
// {
//   using nt2::hjmin;
//   using nt2::options;
//   using nt2::optimization::output;

//   output<T,T> res = hjmin<T>( f1, 0, 0.5, 2
//                             , options [ nt2::iterations_ = 10
//                                       , nt2::tolerance::absolute_ = T(1e-3)
//                                       ]
//                             );

//   std::cout << "Minimum : f(" << res.minimum << ") = "  << res.value
//             << " after "      << res.iterations_count   <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - 1.f), 1e-3);

//   res = hjmin<T>( f1, 0,0.5,2, options [ nt2::iterations_ = 1 ] );
//   NT2_TEST(!res.successful);
// }

// double f1(const matrix < double >& x )       {
//      return x*x*x-3*x+4;
// }

// int main(int argc, char* argv[])
// {
//   ffp fff;
//   matrix < double >  b =  0.5*ones(1);
//   matrix < double >  h =  ones(1);
//   hjmin < matrix < double > > hjm;
//   cout << hjm.optimize(fff, b, h) << endl; ;
//   cout << b << endl;
//   cout << "minimum " << hjm.optimize(fff, b, h) <<  " au point " <<  b << " en " << hjm.getNbIteration() <<  " iterations" << endl;

// }
