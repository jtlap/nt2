//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 optimize toolbox - levenberg"

#include <iostream>
#include <nt2/include/functions/levenberg.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/table.hpp>

template < class Tabout > 
struct fpp 
{
  template < class Tabin> inline
  Tabout operator()(const Tabin & x ) const
  {
    typedef typename Tabin::value_type value_type; 
//    Tabout r = (nt2::sqr(x)-value_type(3))*x+nt2::_(value_type(1), value_type(numel(x)));
    Tabout r = (nt2::sqr((x-nt2::_(value_type(1), value_type(numel(x))))));
    return r; 
  }
};

template<class Tabout, class Tabin >  Tabout f1(const Tabin & x )
{
    typedef typename Tabin::value_type value_type;
    Tabout r = (nt2::sqr(x)-value_type(3))*x;
    return r; 
}

// NT2_TEST_CASE_TPL( levenberg_function_ptr, NT2_REAL_TYPES )
// {
//   using nt2::levenberg;
//   using nt2::optimization::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   typedef nt2::table<T> ltab_t;  
//   tab_t x0 = nt2::zeros(nt2::of_size(1, 3), nt2::meta::as_<T>());
//   ltab_t h = nt2::is_nez(nt2::ones (nt2::of_size(1, 3), nt2::meta::as_<T>())*nt2::Half<T>());
//   tab_t r = nt2::ones (nt2::of_size(1, 3), nt2::meta::as_<T>()); 
//   output<tab_t,T> res = levenberg(&f1<tab_t, tab_t>, x0, h);

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(res.minimum()-r)), nt2::Sqrteps<T>()); 
// }

NT2_TEST_CASE_TPL( levenberg_functor, NT2_REAL_TYPES )
{
  using nt2::levenberg;
  using nt2::options;
  using nt2::optimization::output;
  typedef nt2::table<T> tab_t;
  typedef typename nt2::meta::as_logical<T>::type lT;
  typedef nt2::table<T> ltab_t;  
  tab_t x0 = nt2::zeros(nt2::of_size(1, 3), nt2::meta::as_<T>());
  ltab_t h = nt2::is_nez(nt2::ones (nt2::of_size(1, 3), nt2::meta::as_<T>())*nt2::Half<T>());
  tab_t r = nt2::_(T(1), T(3)); 
  output<tab_t,T> res = levenberg(fpp<tab_t>(), x0, h,
                                  options [ nt2::iterations_ = 100, 
                                            nt2::tolerance::absolute_ = nt2::Eps<T>()
                                    ]);

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(res.minimum()-r)), nt2::Four<T>()*nt2::Sqrteps<T>());

}

// NT2_TEST_CASE_TPL( levenberg_function, (double)(float) )
// {
//   using nt2::levenberg;
//   using nt2::optimization::output;

//   output<T,T> res = levenberg<T>( f1, 0, 0.5, 2 );

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - 1.f), nt2::Sqrteps<float>());
// }

// NT2_TEST_CASE_TPL( levenberg_functor, (double)(float) )
// {
//   using nt2::levenberg;
//   using nt2::optimization::output;

//   output<T,T> res = levenberg<T>( f2(), 0, 0.5, 2 );

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( levenberg_bind, (double)(float) )
// {
//   using nt2::levenberg;
//   using nt2::optimization::output;

//   output<T,T> res = levenberg<T>( boost::bind(f3, _1, 3., 4.), 0, 0.5, 2 );

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( levenberg_lambdda, (double)(float) )
// {
//   using nt2::levenberg;
//   using nt2::optimization::output;
//   namespace bl = boost::lambda;

//   output<T,T> res = levenberg<T>( bl::_1*bl::_1*bl::_1 - 3*bl::_1 + 4
//                             , 0, 0.5, 2
//                             );

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - T(1)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( levenberg_tie, (double)(float) )
// {
//   using nt2::levenberg;
//   using boost::fusion::tie;
//   using boost::fusion::ignore;

//   std::size_t i;
//   T x,y,fx;
//   bool convergence_successful;

//   tie(x,fx,i,convergence_successful) = levenberg<T>( &f0<T>, 0, 0.5, 2 );
//   std::cout << "Minimum : f(" << x << ") = " << fx
//             << " after " << i <<  " iterations\n";

//   NT2_TEST(convergence_successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(x - T(1)), nt2::Sqrteps<T>());

//   tie(y,ignore,ignore,ignore) = levenberg<T>( &f0<T>, 0, 0.5, 2 );
//   std::cout << "Minimum is at y = " << y << "\n";

//   NT2_TEST_LESSER_EQUAL(nt2::abs(y - T(1)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( levenberg_option, (double)(float) )
// {
//   using nt2::levenberg;
//   using nt2::options;
//   using nt2::optimization::output;

//   output<T,T> res = levenberg<T>( f1, 0, 0.5, 2
//                             , options [ nt2::iterations_ = 10
//                                       , nt2::tolerance::absolute_ = T(1e-3)
//                                       ]
//                             );

//   std::cout << "Minimum : f(" << res.minimum << ") = "  << res.value
//             << " after "      << res.iterations_count   <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::abs(res.minimum - 1.f), 1e-3);

//   res = levenberg<T>( f1, 0,0.5,2, options [ nt2::iterations_ = 1 ] );
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
//   levenberg < matrix < double > > hjm; 
//   cout << hjm.optimize(fff, b, h) << endl; ; 
//   cout << b << endl;
//   cout << "minimum " << hjm.optimize(fff, b, h) <<  " au point " <<  b << " en " << hjm.getNbIteration() <<  " iterations" << endl; 

// }
