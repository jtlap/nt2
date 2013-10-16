//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/simd/preprocessor/stack_buffer.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../common/store_runner.hpp"
#include "../common/foo.hpp"
#include "fill.hpp"

#define NT2_TEST_STORE(r, data, elem) BOOST_PP_CAT(nt2_test_run_, data)<T, elem>::call();

template<class T, class U>
struct nt2_test_run_store
{
  static void call(bool offset = false)
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::logical;
    using boost::simd::native;
    using boost::simd::pack;

    typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

    store_runner< U           , native<T,ext_t>           >(offset);
    store_runner< logical<U>  , native<logical<T>,ext_t>  >(offset);
    store_runner< U           , pack<T>                   >(offset);
  }
};

template<class T, class U>
struct nt2_test_run_store_offset
{
  static void call() { nt2_test_run_store<T,U>::call(true); }
};

NT2_TEST_CASE_TPL( store,  BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_STORE, store, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( store_offset,  BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_STORE, store_offset, BOOST_SIMD_TYPES)
}

template<class T, class U>
struct nt2_test_run_store_scatter
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::store;
    using boost::simd::load;
    using boost::simd::tag::store_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;

    typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
    typedef native<T,ext_t>               vT;
    typedef typename boost::dispatch::meta::as_integer<vT>::type viT;
    typedef typename boost::dispatch::meta::as_integer<T>::type  iT;

    typedef typename boost::dispatch::meta::call<store_(vT,U*,viT)>::type  rT;

    NT2_TEST_TYPE_IS( rT, void );

    static const std::size_t card = cardinal_of<vT>::value;

    T data[card*3];
    U out[card*3];

    for(size_t i=0;i<cardinal_of<vT>::value*3;++i)
    {
      data[i] = T(1+i);
      out[i]  = U(0);
    }

    viT index;

    // Spread out the scatter values
    index[0] = cardinal_of<vT>::value*3 -1;
    index[cardinal_of<viT>::value-1] = 0;

    for(std::size_t i=1;i<cardinal_of<viT>::value-1;++i)
    {
      index[i] = iT(i*(cardinal_of<vT>::value*3)/(cardinal_of<vT>::value-1));
    }

    vT v = load<vT>(&data[0]);
    store(v,&out[0],index);
    vT ref = load<vT>(&out[0],index);

    NT2_TEST_EQUAL( ref, v );
  }
};

NT2_TEST_CASE_TPL(store_scatter, BOOST_SIMD_SIMD_TYPES )
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_STORE, store_scatter, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE( store_sequence_pointer )
{
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  store_runner< foo, native<foo,ext_t> >();
  store_runner< foo, native<foo,ext_t> >(true);
}

NT2_TEST_CASE( store_sequence )
{
  using boost::simd::store;
  using boost::simd::load;
  using boost::simd::tag::store_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::fusion::make_vector;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo, ext_t> seq_t;

  static const size_t sz = cardinal_of< seq_t >::value;
  short  sdata[ sz ];
  float  fdata[ sz ];
  char   cdata[ sz ];

  short  ssdata[ sz ];
  float  sfdata[ sz ];
  char   scdata[ sz ];

  for(size_t i=0;i<sz;++i)
  {
    sdata[i] = short(10+i);
    fdata[i] = float(1+i);
    cdata[i] = char(65+i);
  }

  seq_t v = load<seq_t>(make_vector(&sdata[0], &fdata[0], &cdata[0]), 0);
  store(v, make_vector(&ssdata[0], &sfdata[0], &scdata[0]));

  for(size_t j=0;j<sz;++j)
  {
    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v)[j] , ssdata[j]);
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v)[j] , sfdata[j]);
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v)[j] , scdata[j]);
  }
}
