/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_GLOBAL_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_GLOBAL_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <boost/tr1/functional.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/memory/details/no_padding.hpp>

////////////////////////////////////////////////////////////////////////////////
// Various pre-made padding strategies
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Global padding: global size is aligned_on
  //////////////////////////////////////////////////////////////////////////////
  struct global_padding
  {
    typedef boost::mpl::pair<tag::padding,global_padding> nt2_settings_type;
  };
} }

////////////////////////////////////////////////////////////////////////////////
// slice Functor implementation
// We use the align_on<N> to check if we're computing on level 1 or not
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Info>
  struct call<slice_<memory::global_padding>,tag::fusion_,Info>
  {
    template<class Sig> struct result;

    template<class This,class Seq,int N,int S>
    struct  result<This(Seq,boost::mpl::int_<N>,boost::mpl::int_<S>)>
          :   std::tr1
            ::result_of < result
              ::align_on( typename std::tr1
                          ::result_of < details
                                        ::times ( typename boost::fusion
                                                          ::result_of::value_at_c < Seq const
                                                                                  , N-1
                                                                                  >::type
                                                , typename
                                                  result < This ( Seq
                                                                , boost::mpl::int_<N+1>
                                                                , boost::mpl::int_<S>
                                                                )
                                                          >::type
                                                )
                                      >::type
                        , boost::mpl::int_<((N==1)?NT2_CONFIG_ALIGNMENT:1)>
                        )
                        >
    {};

    template<class This,class Seq, int N>
    struct  result< This(Seq,boost::mpl::int_<N>,boost::mpl::int_<N>)>
          :   std::tr1
            ::result_of < result
                          ::align_on( typename  boost::fusion
                                                ::result_of::value_at_c < Seq const
                                                                        , N-1
                                                                        >::type
                                    , boost::mpl::int_<((N==1)?NT2_CONFIG_ALIGNMENT:1)>
                                    )
                        >
    {};

    template<class Seq,int N, int S>
    typename result<call(Seq,boost::mpl::int_<N>,boost::mpl::int_<S>)>::type
    operator()( Seq const& s
              , boost::mpl::int_<N> const&
              , boost::mpl::int_<S> const&
              ) const
    {
      details::times callee;
      return memory::align_on<((N==1)?NT2_CONFIG_ALIGNMENT:1)>
                              ( callee( slice<memory::no_padding,N+1>(s)
                                      , boost::fusion::at_c<N-1>(s)
                                      )
                              );
    }

    template<class S,int N>
    typename result<call(S, boost::mpl::int_<N>, boost::mpl::int_<N>)>::type
    operator()( S const& s
              , boost::mpl::int_<N> const&
              , boost::mpl::int_<N> const&
              ) const
    {
      return  memory::align_on<((N==1)?NT2_CONFIG_ALIGNMENT:1)>
                              (boost::fusion::at_c<N-1>(s));
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
  struct  call<stride_<memory::global_padding>,tag::fusion_,Info>
        : call<stride_<memory::no_padding>,tag::fusion_,Info>
  {};
} }

#endif
