//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include "../common/load_runner.hpp"
#include "../common/foo.hpp"
#include "fill.hpp"


#define NT2_TEST_LOAD(r, data, elem) BOOST_PP_CAT(nt2_test_run_, data)<T, elem>::call();
#define NT2_TEST_APPLY(r, data, elem) data<elem>

template<class T, class U, std::size_t N, bool masked=false, bool zero=false>
struct nt2_test_run_load_gather
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::load;
    using boost::simd::tag::load_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;
    using boost::simd::insert;
    using boost::simd::splat;
    using boost::simd::logical;
    using boost::simd::if_else;
    using boost::simd::meta::as_logical;

    typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

    typedef native<T,ext_t>                                       vT;

    typedef typename boost::dispatch::meta::
            make_integer< N, unsigned>::type                      iT;

    typedef typename boost::simd::meta
                          ::vector_of<iT,cardinal_of<vT>::value>::type viT;
    typedef typename
            boost::dispatch::
            meta::call<load_(U*,boost::dispatch::meta::as_<vT>,viT)>::type r_t;

    typedef typename boost::simd::meta::as_logical<r_t>::type vlT;

    typedef typename boost::simd::meta::scalar_of<vlT>::type s_type;

    time_t seed = time(NULL);
    std::cout<<" Seed for random number generator "<<seed<<'\n';
    srand(seed);

    NT2_TEST( (boost::is_same<vT,r_t>::value) );

    U data[ cardinal_of<vT>::value*3 ];
    for(size_t i=0;i<cardinal_of<vT>::value*3;++i)
      data[i] = i%2 ? U(1+i) : -U(1+i);

    viT index;
    for(size_t i=0;i<cardinal_of<viT>::value;++i)
      index[i] = rand() % (cardinal_of<vT>::value*3);

    vlT mask;
    r_t old= zero ? splat<r_t>(0) : splat<r_t>(-42);

    if (masked)
      for(size_t i=0;i<cardinal_of<vlT>::value;++i)
        insert(s_type(rand()%2), mask, i);

    r_t v;

    if (zero) v = masked ? boost::simd::load<vT>(&data[0], index, mask) : boost::simd::load<vT>(&data[0], index);
    else      v = masked ? boost::simd::load<vT>(&data[0], index, mask, old) : boost::simd::load<vT>(&data[0], index);

    for(size_t j=0;j<cardinal_of<vT>::value;++j)
    {
      if(masked) NT2_TEST_EQUAL(v[j] , ( if_else(mask[j],static_cast<T>(data[index[j]]),static_cast<T>(old[j]) )));
      else       NT2_TEST_EQUAL(v[j] , static_cast<T>( data[index[j]] ));
    }
  }
};

template<class T, class U>
struct nt2_test_run_load_mask_zero_gather32 : nt2_test_run_load_gather<T,U,4,true,true>
{};


template<class T, class U>
struct nt2_test_run_load_mask_gather32 : nt2_test_run_load_gather<T,U,4,true>
{};

template<class T, class U>
struct nt2_test_run_load_gather32 : nt2_test_run_load_gather<T,U,4>
{};

template<class T, class U>
struct nt2_test_run_load_mask_zero_gather64 : nt2_test_run_load_gather<T,U,8,true,true>
{};

template<class T, class U>
struct nt2_test_run_load_mask_gather64 : nt2_test_run_load_gather<T,U,8,true>
{};

template<class T, class U>
struct nt2_test_run_load_gather64 : nt2_test_run_load_gather<T,U,8,false,false>
{};

NT2_TEST_CASE_TPL( load_mask_zero_gather32, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_mask_zero_gather32, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( load_mask_gather_32, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_mask_gather32, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( load_gather32, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_gather32, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL ( load_gather32_logical
                  , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                          , boost::simd::logical
                                          , BOOST_SIMD_SIMD_TYPES
                                          )
                  )
{
  BOOST_PP_SEQ_FOR_EACH ( NT2_TEST_LOAD
                        , load_gather32
                        , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                                , boost::simd::logical
                                                , BOOST_SIMD_TYPES
                                                )
                        )
}

NT2_TEST_CASE_TPL( load_gather64, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_gather64, BOOST_SIMD_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( load_mask_gather64, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_gather64, BOOST_SIMD_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( load_mask_zero_gather64, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_mask_zero_gather64, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL ( load_gather64_logical
                  , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                          , boost::simd::logical
                                          , BOOST_SIMD_SIMD_TYPES
                                          )
                  )
{
  BOOST_PP_SEQ_FOR_EACH ( NT2_TEST_LOAD
                        , load_gather64
                        , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                                , boost::simd::logical
                                                , BOOST_SIMD_TYPES
                                                )
                        )
}
