/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DETAILS_MEMORY_NO_PADDING_HPP_INCLUDED
#define NT2_SDK_DETAILS_MEMORY_NO_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// slice Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Info>
  struct call<slice_,tag::fusion_(memory::no_padding),Info>
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder,class N,class S>
    struct  result<This(Seq,Padder,N,S)>
    {
      static Seq    const&  s;
      static Padder const&  p;
      static details::times callee;

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( different
      , callee( slice<N::value+1>(s,p), boost::fusion::at_c<N::value-1>(s) )
      );

      typedef boost::fusion::result_of::at_c<Seq const, N::value-1> same;

      typedef typename boost::mpl::eval_if_c< (N::value==S::value)
                                            , same
                                            , different
                                            >::type type;
    };

    NT2_FUNCTOR_CALL_DISPATCH ( 4
                              , boost::mpl::bool_<(A2::value == A3::value)>
                              , ( 2,( boost::mpl::true_
                                    , boost::mpl::false_
                                    )
                                )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(4, boost::mpl::true_ )
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(4, boost::mpl::false_ )
    {
      details::times callee;
      return callee( slice<A2::value+1>(a0,a1), boost::fusion::at_c<A2::value-1>(a0));
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// stride Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Info>
  struct call<stride_,tag::fusion_(memory::no_padding),Info>
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder, class N>
    struct  result<This(Seq,Padder,N)>
          : boost::fusion::result_of::at_c<Seq const,N::value-1>
    {};

    NT2_FUNCTOR_CALL(3)
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };
} }

#endif
