/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_COMPUTE_HPP_INCLUDED
#define NT2_SDK_DSL_COMPUTE_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/dsl/proto/transform/unpack.hpp>

////////////////////////////////////////////////////////////////////////////////
// compute actor and trasnform that evaluates some AST
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace dsl
{
  template <typename Tag> struct grammar : boost::proto::_ {};

  //////////////////////////////////////////////////////////////////////////////
  // Forward functor into compute for most tag
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag, class Locality = void>
  struct  compute
        : functors::functor<Tag,Locality>
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Terminal tag require special handling
  //////////////////////////////////////////////////////////////////////////////
  template<class Locality>
  struct compute<functors::terminal_,Locality>
  {
    template<class Sig> struct result;
    template<class This,class Value,class State,class Data>
    struct result<This(Value,State,Data)>
    {
      typedef typename meta::strip<Value>::type::value_type type;
    };

    template<class Value,class State,class Data> inline
    typename result<compute(Value,State,Data)>::type
    operator()(Value& v, State& s, Data& ) const
    {
      return v[s];
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Proto visitor for computing
  //////////////////////////////////////////////////////////////////////////////

  template<class Tag>
  struct  compute_transform;

  // typedef the complete grammar which is needed to pass to default
  typedef boost::proto::visitor<compute_transform, grammar> computer;

  template<class Tag>
  struct  compute_transform : boost::proto::unpack<compute<Tag>(computer)>
  {};

  // call compute<terminal>(value, state, data)
  template<>
  struct  compute_transform<functors::terminal_>
        : boost::proto::call<compute<functors::terminal_> ( boost::proto::_value
                                                          , boost::proto::_state
                                                          , boost::proto::_data 
                                                          )
                            >
  {};
} }

namespace boost { namespace proto
{
  template<class Tag, class Locality>
  struct is_callable<nt2::dsl::compute<Tag,Locality> > : boost::mpl::true_  {};
} }
#endif
