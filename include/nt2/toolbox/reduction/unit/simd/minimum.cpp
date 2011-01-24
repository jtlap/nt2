//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 reduction toolbox - minimum simd Mode"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/toolbox/reduction/include/minimum.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of nt2::minimum in scalar mode
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( minimum, NT2_SIMD_TYPES )
{
  using nt2::minimum;
  using nt2::load;
  using nt2::tag::minimum_;
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
 
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<minimum_(native<T,ext_t>)>::type
                            , T 
                            >::value)
          );
  NT2_ALIGNED_TYPE(T) data[cardinal_of<n_t>::value];
  for(int i=0;i<cardinal_of<n_t>::value;++i)
    data[i] = -int(cardinal_of<n_t>::value/2)+i;
  //  data[cardinal_of<n_t>::value/2] = 2;
  
  n_t v = load<n_t>(&data[0],0);
  std::cout << v << std::endl; 
  T z = v[0];
  for(int i = 1; i<cardinal_of<n_t>::value;++i)
    if (v[i] < z) z = v[i];
  std::cout << z << std::endl;
  std::cout <<  nt2::minimum(v) << std::endl;
  NT2_TEST_EQUAL( nt2::minimum(v), z );
}
