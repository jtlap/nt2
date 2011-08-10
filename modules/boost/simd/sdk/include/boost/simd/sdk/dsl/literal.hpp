/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_DSL_LITTERAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_DSL_LITTERAL_HPP_INCLUDED

#include <boost/dispatch/dsl/category.hpp>
#include <boost/simd/sdk/constant/category.hpp>
#include <boost/simd/include/functions/splat.hpp>

////////////////////////////////////////////////////////////////////////////////
// Litteral as usually splatted w/e the target
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::terminal_,tag::cpu_
                            , (Value)(State)(Data)
                            , (scalar_< arithmetic_<Value> >)
                              ((target_<unspecified_<State> >))
                              (scalar_< integer_<Data> >)
                            )
  {
    typedef typename State::type result_type;

    inline result_type operator()( Value const& v, State const&, Data const& ) const
    {
      return boost::simd::splat<result_type>(v);
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::terminal_,tag::cpu_
                            , (Id)(State)(Data)
                            , (constant_<Id>)
                              ((target_<unspecified_<State> >))
                              (scalar_< integer_<Data> >)
                            )
  {
    typedef typename State::type result_type;

    inline result_type operator()( Id const& v, State const&, Data const& ) const
    {
      typename dispatch::make_functor<typename Id::type,Id>::type callee;
      return callee( dispatch::meta::as_<result_type>() );
    }
  };
} } }


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_TPL( tag::terminal_,tag::cpu_
                                , (class Value)(class State)
                                  (class Data)(std::size_t N)
                                , (scalar_< arithmetic_<Value> >)
                                  ((target_< scalar_< array_<arithmetic_<State>,N> > >))
                                  (scalar_< integer_<Data> >)
                                )
{
  typedef typename State::type::value_type result_type;

  inline result_type operator()( Value const& v, State const&, Data const& ) const
  {
    return static_cast<result_type>(v);
  }
};
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_TPL( tag::terminal_,tag::cpu_
                                , (class Id)(class State)
                                  (class Data)(std::size_t N)
                                , (constant_<Id>)
                                  ((target_< scalar_< array_<arithmetic_<State>,N> > >))
                                  (scalar_< integer_<Data> >)
                                )
{
  typedef typename State::type::value_type result_type;

  inline result_type operator()( Id const& v, State const&, Data const& ) const
  {
    typename dispatch::make_functor<typename Id::type,Id>::type callee;
    return callee( dispatch::meta::as_<result_type>() );
  }
};
} } }

#endif
