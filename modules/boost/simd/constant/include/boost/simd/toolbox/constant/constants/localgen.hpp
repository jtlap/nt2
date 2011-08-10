/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_LOCALGEN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_LOCALGEN_HPP_INCLUDED


namespace boost { namespace simd { namespace tag
{
  //////////////////////////////////////////////////////////////////////////////
  // Small type to gather real value bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<boost::simd::uint64_t D, boost::simd::uint32_t F> struct pattern {};
} } }

namespace boost { namespace simd { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Small type to gather real value bit patterns depending on target type
  //////////////////////////////////////////////////////////////////////////////
  template< class Target
          , boost::simd::uint64_t Value
          , class Select = typename boost::dispatch::meta::scalar_of<Target>::type
          >
  struct  pattern;

  template<class Target, boost::simd::uint64_t Value>
  struct pattern<Target, Value, float >
  {
    typedef tag::pattern<0,Value> type;
  };

  template<class Target, boost::simd::uint64_t Value>
  struct pattern<Target, Value, double >
  {
    typedef tag::pattern<Value,0> type;
  };
}}}

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint64_t D, boost::simd::uint32_t F> inline
  typename boost::dispatch::meta::call<tag::pattern<D,F >(boost::dispatch::meta::as_<Target>)>::type
  real_constant()
  {
    boost::dispatch::functor< tag::pattern<D,F> > callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of float
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint32_t F> inline
  typename boost::dispatch::meta::call<tag::pattern<0,F >(boost::dispatch::meta::as_<Target>)>::type
  single_constant()
  {
    boost::dispatch::functor< tag::pattern<0,F> > callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of double
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint64_t D> inline
  typename boost::dispatch::meta::call<tag::pattern<D,0 >(boost::dispatch::meta::as_<Target>)>::type
  double_constant()
  {
    boost::dispatch::functor< tag::pattern<D,0> > callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns dependant on target type
  //////////////////////////////////////////////////////////////////////////////
  template<class T, uint64_t V> inline
  typename boost::dispatch::meta::call<typename details::pattern<T,V>::type(boost::dispatch::meta::as_<T>)>::type
  Const()
  {
    boost::dispatch::functor< typename details::pattern<T,V>::type > callee;
    return callee( boost::dispatch::meta::as_<T>() );
  }
} }

//==============================================================================
// Custom local real functor
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_TPL( (boost::simd::tag::pattern<D,F>) , tag::cpu_
                                , (boost::simd::uint64_t D)(boost::simd::uint32_t F)(class A0)
                                , (target_< scalar_<double_<A0> > >)
                                )
  {
    typedef typename A0::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return boost::simd::splat<result_type>(bitwise_cast<result_type,boost::simd::uint64_t>(D)); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_TPL( (boost::simd::tag::pattern<D,F>) , tag::cpu_
                                , (boost::simd::uint64_t D)(boost::simd::uint32_t F)(class A0)
                                , (target_< scalar_<float_<A0> > >)
                                )
  {
    typedef typename A0::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return boost::simd::splat<result_type>(bitwise_cast<result_type,boost::simd::uint32_t>(F)); 
    }
  };
} } }
  
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of localgen.hpp
// /////////////////////////////////////////////////////////////////////////////
