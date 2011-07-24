/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_LOCALGEN_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_LOCALGEN_HPP_INCLUDED


namespace nt2 { namespace tag
{
  //////////////////////////////////////////////////////////////////////////////
  // Small type to gather real value bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<nt2::uint64_t D, nt2::uint32_t F> struct pattern {};
} }

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Small type to gather real value bit patterns depending on target type
  //////////////////////////////////////////////////////////////////////////////
  template< class Target
          , nt2::uint64_t Value
          , class Select = typename meta::scalar_of<Target>::type
          >
  struct  pattern;

  template<class Target, nt2::uint64_t Value>
  struct pattern<Target, Value, float >
  {
    typedef tag::pattern<0,Value> type;
  };

  template<class Target, nt2::uint64_t Value>
  struct pattern<Target, Value, double >
  {
    typedef tag::pattern<Value,0> type;
  };
}}

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, nt2::uint64_t D, nt2::uint32_t F> inline
  typename meta::call<tag::pattern<D,F >(meta::as_<Target>)>::type
  real_constant()
  {
    nt2::functor< tag::pattern<D,F> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of float
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, nt2::uint32_t F> inline
  typename meta::call<tag::pattern<0,F >(meta::as_<Target>)>::type
  single_constant()
  {
    nt2::functor< tag::pattern<0,F> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of double
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, nt2::uint64_t D> inline
  typename meta::call<tag::pattern<D,0 >(meta::as_<Target>)>::type
  double_constant()
  {
    nt2::functor< tag::pattern<D,0> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns dependant on target type
  //////////////////////////////////////////////////////////////////////////////
  template<class T, uint64_t V> inline
  typename meta::call<typename details::pattern<T,V>::type(meta::as_<T>)>::type
  Const()
  {
    nt2::functor< typename details::pattern<T,V>::type > callee;
    return callee( nt2::meta::as_<T>() );
  }
}

//==============================================================================
// Custom local real functor
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_TPL( (tag::pattern<D,F>) , tag::cpu_
                                , (nt2::uint64_t D)(nt2::uint32_t F)(class A0)
                                , (target_< scalar_<double_<A0> > >)
                                )
  {
    typedef typename strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const that = {D};
      return splat<result_type>(that.value);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_TPL( (tag::pattern<D,F>) , tag::cpu_
                                , (nt2::uint64_t D)(nt2::uint32_t F)(class A0)
                                , (target_< scalar_<float_<A0> > >)
                                )
  {
    typedef typename strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const that = {F};
      return splat<result_type>(that.value);
    }
  };
} }
  
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of localgen.hpp
// /////////////////////////////////////////////////////////////////////////////
