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

#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/memory/stack_buffer.hpp>

#include "fill.hpp"

template<typename Type, typename Target> inline void store_runner(bool offset = false)
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

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data, Type , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( out , Type , sz );
  for(std::size_t i=0;i<sz;++i)
  {
    fill<Type>()(data[i],65+i);
  }

  for(std::size_t i=0;i<3;++i)
  {
    Target v = load<Target>(&data[i*cd]);

    if(!offset) store(v,&out[i*cd]);
    else        store(v,&out[0], i*cd);

    NT2_TEST_EQUAL( load<Target>(&out[i*cd]), load<Target>(&data[i*cd]) );
  }
}

template<typename Type, typename Target>
inline void unaligned_store_runner(bool offset = false)
{
  using boost::simd::load;
  using boost::simd::unaligned_store;
  using boost::simd::tag::unaligned_store_;
  using boost::simd::meta::cardinal_of;
  using boost::dispatch::meta::as_;

  if(!offset)
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<unaligned_store_(Target, Type*)>::type
                      )
                    , void
                    );
  else
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<unaligned_store_(Target, Type*, int)>::type
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

    if(!offset) unaligned_store(v,&out[i*cd]);
    else        unaligned_store(v,&out[0], i*cd);

    NT2_TEST_EQUAL( load<Target>(&out[i*cd]), load<Target>(&data[i*cd]) );
  }
}

#endif
