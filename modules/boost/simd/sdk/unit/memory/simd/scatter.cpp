//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014   MetaScale SAS
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
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

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

#include <stdlib.h>
#include <time.h>

#define NT2_TEST_STORE(r, data, elem) BOOST_PP_CAT(nt2_test_run_, data)<T, elem>::call();

template<class T, class U>
struct nt2_test_run_store_scatter
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::store;
    using boost::simd::tag::store_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;

    typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
    typedef native<T,ext_t>               vT;
    typedef typename boost::simd::meta::vector_of<int32_t, vT::static_size>::type viT;

    typedef typename boost::dispatch::meta::call<store_(vT,U*,viT)>::type  rT;

    NT2_TEST_TYPE_IS( rT, void );

    static const std::size_t card = cardinal_of<vT>::value;
    std::vector<T, boost::simd::allocator<T> > out(card*10+1);
    vT data;
    for(size_t i=0;i<cardinal_of<vT>::value;++i)
      data[i] = T(1+i);

    srand(time(NULL));

    viT index;
    vT actual;
    for (std::size_t i=0;i<card;i++)
      index[i] = rand()%10 + i*10;

    store(data,&out[0],index);

    for (std::size_t i=0;i<card;i++)
      actual[i]=out[index[i]];

    NT2_TEST_EQUAL(actual,data );
  }
};

template<class T, class U>
struct nt2_test_run_mask_store_scatter
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::store;
    using boost::simd::tag::store_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;
    using boost::simd::insert;
    using boost::simd::logical;
    using boost::simd::if_else;

    typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;
    typedef native<T,ext_t>               vT;
    typedef native<logical<T>, ext_t>     vlT;
    typedef typename boost::simd::meta::vector_of<int32_t, vT::static_size>::type viT;

    typedef typename boost::dispatch::meta::call<store_(vT,U*,viT,vlT)>::type  rT;

    NT2_TEST_TYPE_IS( rT, void );

    static const std::size_t card = cardinal_of<vT>::value;

    vlT mask;
    vT v;

    srand(time(NULL));

    viT index;
    vT actual;
    for (std::size_t i=0;i<card;i++)
    {
      index[i] = rand()%10 + i*10;
      insert(logical<T>(rand()%2), mask, i);
    }
    index[0]=8;

    std::vector<T, boost::simd::allocator<T> > out(card*10+1);
    vT data;
    for(size_t i=0;i<cardinal_of<vT>::value;++i)
      data[i] = if_else(mask[i],T(1+i),T(-42));

    store(data,&out[0],index,mask);

    for (std::size_t i=0;i<card;i++)
      actual[i]=if_else(mask[i],out[index[i]],T(-42));

    NT2_TEST_EQUAL(actual,data);
  }
};

NT2_TEST_CASE_TPL(store_scatter, BOOST_SIMD_SIMD_TYPES )
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_STORE,store_scatter,BOOST_SIMD_TYPES);
}

NT2_TEST_CASE_TPL(mask_store_scatter, BOOST_SIMD_SIMD_TYPES )
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_STORE,mask_store_scatter,BOOST_SIMD_TYPES);
}
