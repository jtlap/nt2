//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - store/simd Mode"

#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>

NT2_TEST_CASE_TPL(store, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::store;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;
  static const std::size_t card = cardinal_of<n_t>::value;

  BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];
  for(std::size_t i=0;i<card;++i)
    data[i] = T(1+i);
  std::cout << ((nt2::int64_t)(&data[0]))%32 << std::endl;
  n_t v = load<n_t>(&data[0],0);
  store(v,&data[0],card);

  for(std::size_t j=0;j<card;++j)
  {
    NT2_TEST_EQUAL( data[j], data[j+card] );
  }

#ifdef NT2_ASSERTS_AS_EXCEPTIONS
  NT2_TEST_NO_THROW( v = store<n_t>(v,&data[0],card) );
  NT2_TEST_THROW( v = store<n_t>(v,&data[0]+1,card), nt2::assert_exception);
#endif
}

struct foo { double d; float f; char c; };
BOOST_FUSION_ADAPT_STRUCT(foo,(double,d)(float,f)(char,c))

NT2_TEST_CASE( store_sequence )
{
  using boost::simd::store;
  using boost::simd::load;
  using boost::simd::tag::store_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo, ext_t> seq_t;

  static const size_t sz = cardinal_of< seq_t >::value;
  BOOST_SIMD_ALIGNED_TYPE(char)   cdata[ sz ];
  BOOST_SIMD_ALIGNED_TYPE(float)  fdata[ sz ];
  BOOST_SIMD_ALIGNED_TYPE(double) ddata[ sz ];
  BOOST_SIMD_ALIGNED_TYPE(char)   scdata[ sz ];
  BOOST_SIMD_ALIGNED_TYPE(float)  sfdata[ sz ];
  BOOST_SIMD_ALIGNED_TYPE(double) sddata[ sz ];
  for(size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    ddata[i] = double(1+i);
  }

  seq_t v = load<seq_t>(boost::fusion::make_vector(&ddata[0], &fdata[0], &cdata[0]), 0);
  store(v, boost::fusion::make_vector(&sddata[0], &sfdata[0], &scdata[0]), 0);

  for(size_t j=0;j<sz;++j)
  {
    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v)[j] , sddata[j]);
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v)[j] , sfdata[j]);
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v)[j] , scdata[j]);
  }
}

NT2_TEST_CASE( store_pointer_of_sequence )
{
  using boost::simd::store;
  using boost::simd::load;
  using boost::simd::tag::store_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo, ext_t> seq_t;

  static const size_t sz = cardinal_of< seq_t >::value;
  BOOST_SIMD_ALIGNED_TYPE(foo) sdata[sz];
  BOOST_SIMD_ALIGNED_TYPE(foo) ddata[sz];
  for(size_t i=0;i<sz;++i)
  {
    sdata[i].d = char(1+i);
    sdata[i].f = float(2+i);
    sdata[i].c = double(3+i);
  }

  seq_t v = load<seq_t>(&sdata[0], 0);
  store(v, &ddata[0], 0);

  for(size_t j=0;j<sz;++j)
  {
    NT2_TEST_EQUAL(ddata[j].d , sdata[j].d);
    NT2_TEST_EQUAL(ddata[j].f , sdata[j].f);
    NT2_TEST_EQUAL(ddata[j].c , sdata[j].c);
  }
}
