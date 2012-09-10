//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - unaligned_store/simd Mode"

#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL(unaligned_store, BOOST_SIMD_SIMD_TYPES )
{
   using boost::simd::unaligned_store;
   using boost::simd::unaligned_load;
   using boost::simd::native;
   using boost::simd::meta::cardinal_of;

   typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
   typedef native<T,ext_t>             n_t;

   static const std::size_t card = cardinal_of<n_t>::value;
   
   T data[2*card];
   for(std::size_t i=0;i<card;++i)
     data[i] = T(1+i);

   std::cout << ((nt2::int64_t)(&data[0]))%32 << std::endl;

   n_t v = unaligned_load<n_t>(&data[0]);
   unaligned_store(v,&data[0],card);

   for(std::size_t j=0;j<card;++j)
   {
     NT2_TEST_EQUAL( data[j], data[j+card] );
   }
}

struct foo { double d; float f; char c; };
BOOST_FUSION_ADAPT_STRUCT(foo,(double,d)(float,f)(char,c))

NT2_TEST_CASE( unaligned_store_sequence )
{
  using boost::simd::unaligned_store;
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_store_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  char   cdata[ cardinal_of< native<char  ,ext_t> >::value ];
  float  fdata[ cardinal_of< native<float ,ext_t> >::value ];
  double ddata[ cardinal_of< native<double,ext_t> >::value ];
  char   scdata[ cardinal_of< native<char  ,ext_t> >::value ];
  float  sfdata[ cardinal_of< native<float ,ext_t> >::value ];
  double sddata[ cardinal_of< native<double,ext_t> >::value ];

  for(size_t i=0;i<cardinal_of< native<char  ,ext_t> >::value;++i) 
  { cdata[i] = char(1+i); }
  for(size_t i=0;i<cardinal_of< native<float ,ext_t> >::value;++i) 
  { fdata[i] = float(1+i); }
  for(size_t i=0;i<cardinal_of< native<double ,ext_t> >::value;++i) 
  { ddata[i] = double(1+i); }

  typedef native<foo, ext_t> seq_t;

  seq_t v = unaligned_load<seq_t>(boost::fusion::make_vector(&ddata[0], &fdata[0], &cdata[0]), 0);
  unaligned_store(v, boost::fusion::make_vector(&sddata[0], &sfdata[0], &scdata[0]), 0);

  for(size_t j=0;j<cardinal_of< native<double,ext_t> >::value;++j)  
    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v)[j] , sddata[j]);
  for(size_t j=0;j<cardinal_of< native<float,ext_t> >::value;++j)    
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v)[j] , sfdata[j]);
  for(size_t j=0;j<cardinal_of< native<char,ext_t> >::value;++j)  
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v)[j] , scdata[j]);
}