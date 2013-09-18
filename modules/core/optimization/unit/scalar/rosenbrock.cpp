//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 optimize toolbox - rosenbrock"

#include <nt2/include/functions/rosenbrock.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/globalasum2.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/table.hpp>
#include <iostream>

template < class Tabout >
struct fpp
{
  template < class Tabin> inline
  Tabout operator()(const Tabin & x ) const
  {
    typedef typename Tabin::value_type value_type;
    Tabout r = globalsum(nt2::sqr((x-nt2::_(value_type(1), value_type(numel(x))))));
    return r;
  }
};
template < class Tabout >
struct gpp
{
  template < class Tabin> inline
  Tabout operator()(const Tabin & x ) const
  {
    Tabout r=Tabout(100)*nt2::sqr(x(2)-nt2::sqr(x(1)))+nt2::sqr(1-x(1));
    return r;
  }
};

// template<class Tabout, class Tabin >  Tabout f1(const Tabin & x )
// {
//     typedef typename Tabin::value_type value_type;
//     Tabout r =  globalasum2(nt2::sqr(x)-value_type(3));
//     return r;
// }


// NT2_TEST_CASE_TPL( rosenbrock_function_ptr, NT2_REAL_TYPES )
// {
//   using nt2::rosenbrock;
//   using nt2::optimization::output;
//   typedef nt2::table<T> tab_t;
//   tab_t x0 = nt2::ones(nt2::of_size(1, 3), nt2::meta::as_<T>());
//   NT2_DISPLAY(x0);
//   tab_t r = nt2::sqrt(T(3))*nt2::ones (nt2::of_size(1, 3), nt2::meta::as_<T>());
//   NT2_DISPLAY(r);
//   output<tab_t,T> res = rosenbrock(&f1<T, tab_t>, x0);

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(res.minimum()-r)), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( rosenbrock_functor, NT2_REAL_TYPES )
// {
//   using nt2::rosenbrock;
//   using nt2::options;
//   using nt2::optimization::output;
//   typedef nt2::table<T> tab_t;
//   tab_t x0 = nt2::zeros(nt2::of_size(1, 3), nt2::meta::as_<T>());
//   tab_t r = nt2::_(T(1), T(3));
//   output<tab_t,T> res = rosenbrock(fpp<tab_t>(), x0,
//                                   options [ nt2::iterations_ = 100,
//                                             nt2::tolerance::absolute_ = nt2::Eps<T>()
//                                     ]);

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(res.minimum()-r)), nt2::Four<T>()*nt2::Sqrteps<T>());
// }

NT2_TEST_CASE_TPL( rosenbrock_functor2, NT2_REAL_TYPES )
{
  using nt2::rosenbrock;
  using nt2::options;
  using nt2::optimization::output;
  typedef nt2::table<T> tab_t;
  tab_t x0 = T(5)*nt2::ones(nt2::of_size(1, 2), nt2::meta::as_<T>());
  tab_t r = nt2::cons(nt2::of_size(1, 2), T(1),T(1));
  output<tab_t,T> res = rosenbrock(gpp<tab_t>(), x0,
                                  options [ nt2::iterations_ = 10000,
                                            nt2::tolerance::absolute_ = T(100)*nt2::Eps<T>()
                                    ]);

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
}

NT2_TEST_CASE_TPL( rosenbrock_functor3, (float) )
{
  using nt2::rosenbrock;
  using nt2::options;
  using nt2::optimization::output;
  typedef nt2::table<T> tab_t;
  tab_t x0 = T(5)*nt2::ones(nt2::of_size(1, 2), nt2::meta::as_<T>());
  tab_t r = nt2::cons(nt2::of_size(1, 2), T(1),T(1));
  output<tab_t,T> res = rosenbrock(gpp<tab_t>(), x0,
                                  options [ nt2::iterations_ = 10000,
                                            nt2::tolerance::absolute_ = 1.0e-5
                                    ]);

  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  typedef nt2::table<double> tab_d;
  tab_d x0d = nt2::cast<double>(res.minimum);
  output<tab_d,double> resd = rosenbrock(gpp<tab_d>(), x0d,
                                  options [ nt2::iterations_ = 10000,
                                            nt2::tolerance::absolute_ = 1.0e-8
                                    ]);
   std::cout << "Minimum : f(" << resd.minimum << ") = " << resd.value
            << " after " << resd.iterations_count <<  " iterations\n";

}
