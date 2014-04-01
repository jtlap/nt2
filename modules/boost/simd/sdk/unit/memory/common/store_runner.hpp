//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef STORE_RUNNER_HPP_INCLUDED
#define STORE_RUNNER_HPP_INCLUDED

#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/splat.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>

#include "fill.hpp"

template<typename Type, typename Target>
inline void aligned_store_runner(bool offset = false)
{
  using boost::simd::aligned_load;
  using boost::simd::aligned_store;
  using boost::simd::allocator;
  using boost::simd::tag::aligned_store_;
  using boost::simd::meta::cardinal_of;
  using boost::dispatch::meta::as_;

  if(!offset)
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<aligned_store_(Target, Type*)>::type
                      )
                    , void
                    );
  else
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<aligned_store_(Target, Type*, int)>::type
                      )
                    , void
                    );

  static const std::size_t cd = cardinal_of<Target>::value;
  static const std::size_t sz = cd*3;

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data, Type  , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( out , Type  , sz );

  for(std::size_t i=0;i<sz;++i)
  {
    fill<Type>()(data[i],65+i);
  }

  for(std::size_t i=0;i<3;++i)
  {
    Target v = aligned_load<Target>(&data[i*cd]);

    if(!offset) aligned_store(v,&out[i*cd]);
    else        aligned_store(v,&out[0], i*cd);

    NT2_TEST_EQUAL( aligned_load<Target>(&out[i*cd]), aligned_load<Target>(&data[i*cd]) );
  }
}

template<typename Type, typename Target>
inline void store_runner(bool offset = false)
{
  using boost::simd::load;
  using boost::simd::store;
  using boost::simd::tag::store_;
  using boost::simd::meta::cardinal_of;
  using boost::dispatch::meta::as_;

  if(!offset)
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<store_(Target, Type*)>::type
                      )
                    , void
                    );
  else
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<store_(Target, Type*, int)>::type
                      )
                    , void
                    );

  static const std::size_t cd = cardinal_of<Target>::value;
  static const std::size_t sz = cd*3;

  Type  data[sz];
  Type  out[sz];

  for(std::size_t i=0;i<sz;++i) fill<Type>()(data[i],65+i);

  for(std::size_t i=0;i<3;++i)
  {
    Target v = load<Target>(&data[i*cd]);

    if(!offset) store(v,&out[i*cd]);
    else        store(v,&out[0], i*cd);

    NT2_TEST_EQUAL( load<Target>(&out[i*cd]), load<Target>(&data[i*cd]) );
  }
}

template<typename Type, typename Target, typename Mask>
inline void mask_store_runner(Mask mask, bool offset = false)
{
  using boost::simd::load;
  using boost::simd::store;
  using boost::simd::tag::store_;
  using boost::simd::meta::cardinal_of;
  using boost::dispatch::meta::as_;
  using boost::simd::splat;
  using boost::simd::if_else;
  if(!offset)
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<store_(Target, Type*, Mask)>::type
                      )
                    , void
                    );
  else
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<store_(Target, Type*, int, Mask)>::type
                      )
                    , void
                    );

  static const std::size_t cd = cardinal_of<Target>::value;
  static const std::size_t sz = cd*3;

  Type  data[sz];
  Type  out[sz];

  for(std::size_t i=0;i<sz;++i) fill<Type>()(data[i],65+i);

  for(std::size_t i=0;i<3;++i)
  {
    Target v = load<Target>(&data[i*cd]);
    if(!offset) store(v,&out[i*cd],mask);
    else        store(v,&out[0], i*cd,mask);
    Target old = splat<Target>(42);
    Target ref = if_else(mask,v,old);
    NT2_TEST_EQUAL( load<Target>(&out[i*cd],old,mask), ref);
  }
}
#endif
