//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 optimize toolbox - nedlermead"

#include <iostream>
#include <nt2/include/functions/neldermead.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/eps.hpp>  
#include <nt2/include/constants/oneo_10.hpp>
#include <nt2/table.hpp> 
struct ffp 
{
  template < class Tab > inline
  typename Tab::value_type operator()(const Tab & x ) const
  {
    typedef typename Tab::value_type value_type; 
    return nt2::globalsum((nt2::sqr((nt2::rowvect(x)-nt2::_(value_type(1), value_type(numel(x)))))));
    //   NT2_DISPLAY(r)
  }
};

template<class Tab > typename Tab::value_type f1(const Tab & x )
{
    typedef typename Tab::value_type value_type; 
    return nt2::globalsum((nt2::sqr((nt2::rowvect(x)-nt2::_(value_type(1), value_type(numel(x)))))));
}


// NT2_TEST_CASE_TPL( nedlermead_function_ptr, NT2_REAL_TYPES )
// {
//   using nt2::nedlermead;
//   using nt2::optimization::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   typedef nt2::table<T> ltab_t;  
//   tab_t x0 = nt2::zeros(nt2::of_size(1, 3), nt2::meta::as_<T>());
//   ltab_t h = nt2::is_nez(nt2::ones (nt2::of_size(1, 3), nt2::meta::as_<T>())*nt2::Half<T>());
//   tab_t r = nt2::ones (nt2::of_size(1, 3), nt2::meta::as_<T>()); 
//   output<tab_t,T> res = nedlermead(&f1<tab_t, tab_t>, x0, h);

//   std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
//             << " after " << res.iterations_count <<  " iterations\n";

//   NT2_TEST(res.successful);
//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(res.minimum()-r)), nt2::Sqrteps<T>()); 
// }
 
NT2_TEST_CASE_TPL( nedlermead_functor, NT2_REAL_TYPES ) 
{
  using nt2::neldermead; 
  using nt2::options;   
  using nt2::optimization::output;   
  typedef nt2::table<T> tab_t;
  typedef typename nt2::meta::as_logical<T>::type lT;
  tab_t x0 = nt2::zeros(nt2::of_size(1, 2), nt2::meta::as_<T>());
  tab_t h = nt2::ones (nt2::of_size(1, 2), nt2::meta::as_<T>())*nt2::Oneo_10<T>();
  tab_t r = nt2::_(T(1), T(2));
  NT2_DISPLAY(x0);   
  NT2_DISPLAY(h);   
  output<tab_t,T> res = neldermead(ffp(), x0, h,
                                  options [ nt2::iterations_ = 100, 
                                            nt2::tolerance::absolute_ = T(0.001) 
                                    ]); 
 
  std::cout << "Minimum : f(" << res.minimum << ") = " << res.value
            << " after " << res.iterations_count <<  " iterations\n";

  NT2_TEST(res.successful);
  NT2_DISPLAY(res.minimum());
  NT2_DISPLAY(r); 
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(res.minimum()-r)), T(0.001));

}
  
