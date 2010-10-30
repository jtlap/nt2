/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_GLOBAL_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_GLOBAL_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/memory/details/no_padding.hpp>

////////////////////////////////////////////////////////////////////////////////
// slice Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Info>
  struct call<slice_,tag::fusion_(memory::global_padding),Info>
  {
    ////////////////////////////////////////////////////////////////////////////
    // Template status for selecting between {N,S} state space
    ////////////////////////////////////////////////////////////////////////////
    template<bool Same, bool One> struct status {};

    ////////////////////////////////////////////////////////////////////////////
    // result_of protocol
    ////////////////////////////////////////////////////////////////////////////
    template<class Sig> struct result;

    template<class This,class A0,class A1,class A2>
    struct  result<This(A0,A1,A2)>
    {
      typedef typename meta::strip<A0>::type Seq;
      typedef typename meta::strip<A1>::type Padder;
      typedef typename meta::strip<A2>::type N;

      typedef typename boost::fusion::result_of::size<Seq>::type seq_size;

      // N!=S
      template<bool Same, bool One, int Dummy=0> struct inner
      {
        static Seq const& s;
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL
        ( nested
        , slice<N::value>(s,memory::no_padding())
        );
        typedef typename nested::type type;
      };

      // N==S int N!=1
      template<int Dummy>
      struct  inner<true,false,Dummy>
            : boost::fusion::result_of::at_c<Seq const,N::value-1>
      {};

      // N==1 but N!=S
      template<int Dummy>
      struct inner<false,true,Dummy>
      {
        static Seq const& s;
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL
        ( nested
        , memory::align_on( slice<1>(s,memory::no_padding()) )
        );
        typedef typename nested::type type;
      };

      // N==1 and S==1
      template<int Dummy>
      struct inner<true,true,Dummy>
      {
        static Seq const& s;
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL
        ( nested
        , memory::align_on( boost::fusion::at_c<0>(s) )
        );
        typedef typename nested::type type;
      };

      typedef typename inner<(N::value==seq_size::value),(N::value==1)>::type type;
    };

    NT2_FUNCTOR_CALL_DISPATCH ( 3
                              , (status< A2::value == boost::fusion::result_of::size<A0>::value
                                       , A2::value == 1
                                       >
                                )
                              , ( 4,( (status<true  , true> )
                                    , (status<false , true> )
                                    , (status<true  , false>)
                                    , (status<false , false>)
                                    )
                                )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(3, (status<false , false>) )
    {
      return slice<A2::value>(a0,memory::no_padding());
    }

    NT2_FUNCTOR_CALL_EVAL_IF(3, (status<true , false>) )
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(3, (status<false , true>) )
    {
      return memory::align_on( slice<1>(a0,memory::no_padding()) );
    }

    NT2_FUNCTOR_CALL_EVAL_IF(3, (status<true , true>) )
    {
      return memory::align_on(boost::fusion::at_c<0>(a0));
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// stride Functor implementation
// Nothing special as the padding is after all the meaningful data
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Info>
  struct  call<stride_,tag::fusion_(memory::global_padding),Info>
        : call<stride_,tag::fusion_(memory::no_padding),Info>
  {};
} }

#endif
