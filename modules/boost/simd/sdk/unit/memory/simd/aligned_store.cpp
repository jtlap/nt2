//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/insert.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/cat.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../common/store_runner.hpp"
#include "../common/foo.hpp"

#define NT2_TEST_ALIGNED_STORE(r, data, elem) BOOST_PP_CAT(nt2_test_run_, data)<T, elem>::call();

template<class T, class U>
struct nt2_test_run_mask_aligned_store
{
  static void call(bool offset = false)
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::logical;
    using boost::simd::native;
    using boost::simd::pack;

    typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

    masked_aligned_store_runner< U           , native<T,ext_t>          , native<logical<T>,ext_t>  >(offset);
    masked_aligned_store_runner< logical<U>  , native<logical<T>,ext_t> , native<logical<T>,ext_t>  >(offset);
    masked_aligned_store_runner< U           , pack<T>                  , pack<logical<T > >  >(offset);
  }
};

template<class T, class U>
struct nt2_test_run_aligned_store
{
  static void call(bool offset = false)
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::logical;
    using boost::simd::native;
    using boost::simd::pack;

    typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

    aligned_store_runner< U           , native<T,ext_t>           >(offset);
    aligned_store_runner< logical<U>  , native<logical<T>,ext_t>  >(offset);
    aligned_store_runner< U           , pack<T>                   >(offset);
  }
};

template<class T, class U>
struct nt2_test_run_aligned_store_offset
{
  static void call() { nt2_test_run_aligned_store<T,U>::call(true); }
};

NT2_TEST_CASE_TPL( mask_store,  BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_ALIGNED_STORE, mask_aligned_store, BOOST_SIMD_TYPES)
}


NT2_TEST_CASE_TPL( store,  BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_ALIGNED_STORE, aligned_store, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( store_offset,  BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_ALIGNED_STORE, aligned_store_offset, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE( store_sequence_pointer )
{
  using boost::simd::pack;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  aligned_store_runner< bar, native<bar,ext_t> >();
  aligned_store_runner< bar, pack<bar> >();
  aligned_store_runner< bar, native<bar,ext_t> >(true);
  aligned_store_runner< bar, pack<bar> >(true);
}

NT2_TEST_CASE( store_sequence )
{
  using boost::simd::aligned_store;
  using boost::simd::tag::aligned_store_;
  using boost::simd::aligned_load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::fusion::make_vector;
  using boost::fusion::result_of::value_at;

  typedef BOOST_SIMD_DEFAULT_EXTENSION            ext_t;
  typedef native<foo,ext_t>                       vT;
  typedef value_at<vT,boost::mpl::int_<0> >::type foo0_t;
  typedef value_at<vT,boost::mpl::int_<1> >::type foo1_t;
  typedef value_at<vT,boost::mpl::int_<2> >::type foo2_t;

  static const size_t sz = cardinal_of< vT >::value;

  BOOST_SIMD_ALIGNED_STACK_BUFFER( cdata, char  , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( fdata, float , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( sdata, short , sz );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( scdata, char  , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( sfdata, float , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ssdata, short , sz );

  for(std::size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    sdata[i] = short(1+i);
  }

  vT v = aligned_load<vT>(boost::fusion::make_vector(&sdata[0], &fdata[0], &cdata[0]), 0);
  aligned_store(v, boost::fusion::make_vector(&ssdata[0], &sfdata[0], &scdata[0]), 0);

  typedef value_at<vT,boost::mpl::int_<0> >::type foo0_t;
  typedef value_at<vT,boost::mpl::int_<1> >::type foo1_t;
  typedef value_at<vT,boost::mpl::int_<2> >::type foo2_t;

  foo0_t sref = aligned_load<foo0_t>(&ssdata[0]);
  foo1_t fref = aligned_load<foo1_t>(&sfdata[0]);
  foo2_t cref = aligned_load<foo2_t>(&scdata[0]);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sref);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fref);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cref);
}

