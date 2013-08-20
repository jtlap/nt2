//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef LOAD_RUNNER_HPP_INCLUDED
#define LOAD_RUNNER_HPP_INCLUDED

#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/memory/allocator.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>

#include <vector>
#include "fill.hpp"

template<typename Type, typename Target>
inline void aligned_load_runner(bool offset = false)
{
  using boost::simd::aligned_load;
  using boost::simd::tag::aligned_load_;
  using boost::simd::meta::cardinal_of;
  using boost::dispatch::meta::as_;
  using boost::simd::allocator;

  if(!offset)
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<aligned_load_( Type*, as_<Target>)>::type
                      )
                    , Target
                    );
  else
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<aligned_load_( Type*, int, as_<Target>)>::type
                      )
                    , Target
                    );

  static const std::size_t cd = cardinal_of<Target>::value;
  static const std::size_t sz = cd*3;

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data, Type   , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ref , Target , sz );

  for(std::size_t i=0;i<sz;++i)
  {
    fill<Type>()(data[i],i);
    fill<Target>()(ref[i/cd],i/cd);
  }

  for(std::size_t i=0;i<3;++i)
  {
    if(!offset) NT2_TEST_EQUAL(aligned_load<Target>(&data[i*cd])  , ref[i]);
    else        NT2_TEST_EQUAL(aligned_load<Target>(&data[0],i*cd), ref[i]);
  }
}

template<typename Type, typename Target>
inline void load_runner(bool offset = false)
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::meta::cardinal_of;
  using boost::dispatch::meta::as_;

  if(!offset)
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<load_( Type*, as_<Target>)>::type
                      )
                    , Target
                    );
  else
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<load_( Type*, int, as_<Target>)>::type
                      )
                    , Target
                    );

  static const std::size_t cd = cardinal_of<Target>::value;
  static const std::size_t sz = cd*3;

  Type    data[sz];
  Target  ref[sz];

  for(std::size_t i=0;i<sz;++i)
  {
    fill<Type>()(data[i],i);
    fill<Target>()(ref[i/cd],i/cd);
  }

  for(std::size_t i=0;i<3;++i)
  {
    if(!offset) NT2_TEST_EQUAL(load<Target>(&data[i*cd])  , ref[i]);
    else        NT2_TEST_EQUAL(load<Target>(&data[0],i*cd), ref[i]);
  }
}

template<typename Type, typename Target, typename Misalignment>
inline void misaligned_load_runner(Misalignment const&, bool offset = false)
{
  using boost::simd::aligned_load;
  using boost::simd::tag::aligned_load_;
  using boost::simd::meta::cardinal_of;
  using boost::dispatch::meta::as_;

  static const int ms = Misalignment::value;
  std::cout << "Misaligned load test with Misalignment = " << ms << "\n";

  if(!offset)
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<aligned_load_( Type*, as_<Target>
                                          , Misalignment
                                          )
                                    >::type
                      )
                    , Target
                    );
  else
    NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                              ::call<aligned_load_( Type*, int, as_<Target>
                                          , Misalignment
                                          )
                                    >::type
                      )
                    , Target
                    );

  static const std::size_t cd = cardinal_of<Target>::value;
  static const std::size_t sz = cd*3;

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data, Type   , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ref , Target , sz );

  for(std::size_t i=0;i<sz;++i)
  {
    fill<Type>()(data[i],i);
    fill<Target>()(ref[i/cd],i/cd,ms);
  }

  std::size_t mn = Misalignment::value < 0 ? 1 : 0;
  std::size_t mx = Misalignment::value < 0 ? 3 : 2;

  for(std::size_t i=mn;i<mx;++i)
  {
    if(!offset) NT2_TEST_EQUAL((aligned_load<Target,ms>(&data[ms+i*cd])), ref[i]);
    else        NT2_TEST_EQUAL((aligned_load<Target,ms>(&data[0],ms+i*cd)), ref[i]);
  }

  std::cout << "\n";
}

#endif
