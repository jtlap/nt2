//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_MEMORY_DETAILS_NO_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_NO_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Implementation of the no_padding strategy for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/meta/fusion.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// slice implementation for no_padding strategy
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::slice_ ( tag::fusion_sequence_
                            , tag::padding_<memory::no_padding>
                            , tag::mpl_integral_<tag::integer_>
                            )
              , tag::cpu_, Dummy  >
        : callable
  {
    ////////////////////////////////////////////////////////////////////////////
    // Small internal to see if the index is the same as the sequence size
    ////////////////////////////////////////////////////////////////////////////
    template<class S,class N>
    struct  same_size
          : boost::mpl::bool_<(   N::value
                              ==  boost::fusion::result_of::size<S>::value
                              )>
    {};

    ////////////////////////////////////////////////////////////////////////////
    // Computes the actual result type depending on A0 size and A2 value
    ////////////////////////////////////////////////////////////////////////////
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
    {
      typedef typename meta::strip<A0>::type arg0;
      typedef typename meta::strip<A1>::type arg1;
      typedef typename meta::strip<A2>::type arg2;

      typedef boost::fusion::result_of::at_c<arg0 const,arg2::value-1>  true_case;

      static arg0 const& s; static arg1 const&  p;

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( false_case
      , nt2::mul( slice<arg2::value+1>(s,p)
                , boost::fusion::at_c<arg2::value-1>(s)
                )
      );

      typedef typename boost::mpl::eval_if< same_size<arg0,arg2>
                                          , true_case
                                          , false_case
                                          >::type type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when size<A0> == A2
    ////////////////////////////////////////////////////////////////////////////
    template<class A0, class A1, class A2> inline
    typename boost::lazy_enable_if< same_size<A0,A2>, NT2_RETURN_TYPE(3)>::type
    operator()( A0 const& a0, A1 const&, A2 const& ) const
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when size<A0> != A2
    ////////////////////////////////////////////////////////////////////////////
    template<class A0, class A1, class A2> inline
    typename boost::lazy_disable_if< same_size<A0,A2>, NT2_RETURN_TYPE(3)>::type
    operator()( A0 const& a0, A1 const& a1, A2 const& ) const
    {
      return nt2::mul ( slice<A2::value+1>(a0,a1)
                      , boost::fusion::at_c<A2::value-1>(a0)
                      );
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// stride Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::stride_( tag::fusion_sequence_
                            , tag::padding_<memory::no_padding>
                            , tag::mpl_integral_<tag::integer_>
                            )
              , tag::cpu_, Dummy  >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
          : boost::fusion::result_of::at_c< typename meta::strip<A0>::type const
                                          , meta::strip<A2>::type::value-1
                                          >
    {};

    NT2_FUNCTOR_CALL(3)
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };
} }

#endif
