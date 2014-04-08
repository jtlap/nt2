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
struct nt2_test_run_aligned_store_scatter
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::aligned_store;
    using boost::simd::aligned_load;
    using boost::simd::tag::aligned_store_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;

    typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
    typedef native<T,ext_t>               vT;
    typedef typename boost::dispatch::meta::as_integer<vT>::type viT;
    typedef typename boost::dispatch::meta::as_integer<T>::type  iT;

    typedef typename boost::dispatch::meta::call<aligned_store_(vT,U*,viT)>::type  rT;

    NT2_TEST_TYPE_IS( rT, void );

    std::size_t card = cardinal_of<vT>::value;
    BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, card*3 );
    BOOST_SIMD_ALIGNED_STACK_BUFFER( out ,  U, card*3 );

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

    vT v = aligned_load<vT>(&data[0]);
    aligned_store(v,&out[0],index);
    vT ref = aligned_load<vT>(&out[0],index);

    NT2_TEST_EQUAL( ref, v );
  }
};

template<class T, class U>
struct nt2_test_run_mask_aligned_store_scatter
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::aligned_store;
    using boost::simd::tag::aligned_store_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;
    using boost::simd::insert;
    using boost::simd::logical;
    using boost::simd::if_else;

    typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;
    typedef native<T,ext_t>               vT;
    typedef native<logical<T>, ext_t>     vlT;
    typedef typename boost::simd::meta::vector_of<int32_t, vT::static_size>::type viT;

    typedef typename boost::dispatch::meta::call<aligned_store_(vT,U*,viT,vlT)>::type  rT;


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

    aligned_store(data,&out[0],index,mask);

    for (std::size_t i=0;i<card;i++)
      actual[i]=if_else(mask[i],out[index[i]],T(-42));

    NT2_TEST_EQUAL(actual,data);
  }
};

NT2_TEST_CASE_TPL(mask_store_scatter, BOOST_SIMD_SIMD_TYPES )
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_ALIGNED_STORE, mask_aligned_store_scatter, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL(store_scatter, BOOST_SIMD_SIMD_TYPES )
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_ALIGNED_STORE, aligned_store_scatter, BOOST_SIMD_TYPES)
}

template<class T, class U>
struct nt2_test_run_aligned_store_scatter_pack
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::aligned_store;
    using boost::simd::aligned_load;
    using boost::simd::tag::aligned_store_;
    using boost::simd::pack;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;

    typedef pack<T>               vT;
    typedef BOOST_SIMD_DEFAULT_EXTENSION            ext_t;

    typedef typename boost::dispatch::meta::as_integer<T>::type  iT;
    typedef native<iT,ext_t> viT;

    typedef typename boost::dispatch::meta::call<aligned_store_(vT,U*,viT)>::type  rT;

    NT2_TEST_TYPE_IS( rT, void );

    std::size_t card = cardinal_of<vT>::value;
    BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, card*3 );
    BOOST_SIMD_ALIGNED_STACK_BUFFER( out ,  U, card*3 );

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

    vT v = aligned_load<vT>(&data[0]);
    aligned_store(v,&out[0],index);
    vT ref = aligned_load<vT>(&out[0],index);

    NT2_TEST_EQUAL( ref, v );
  }
};

NT2_TEST_CASE_TPL(store_scatter_pack, BOOST_SIMD_SIMD_TYPES )
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_ALIGNED_STORE, aligned_store_scatter_pack, BOOST_SIMD_TYPES)
}
