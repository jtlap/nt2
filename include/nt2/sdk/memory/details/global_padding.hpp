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
  struct call<slice_<memory::global_padding>,tag::fusion_,Info>
  {
    template<class Sig> struct result;

    ////////////////////////////////////////////////////////////////////////////
    // Regular call slice<N> over sequence of size S
    ////////////////////////////////////////////////////////////////////////////
    template<class This,class Seq,int N,int S>
    struct  result<This(Seq,boost::mpl::int_<N>,boost::mpl::int_<S>)>
    {
      static Seq const&     s;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, (slice<memory::no_padding,N>(s)) );
      typedef typename nested::type type;
    };

    template<class Seq,int N, int S>
    typename result<call(Seq,boost::mpl::int_<N>,boost::mpl::int_<S>)>::type
    operator()( Seq const& s
              , boost::mpl::int_<N> const&
              , boost::mpl::int_<S> const&
              ) const
    {
      return slice<memory::no_padding,N>(s);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Regular call slice<N> over sequence of size N
    ////////////////////////////////////////////////////////////////////////////
    template<class This,class Seq, int N>
    struct  result< This(Seq,boost::mpl::int_<N>,boost::mpl::int_<N>)>
          : boost::fusion::result_of::at_c<Seq const, N-1>
    {};

    template<class S,int N>
    typename result<call(S, boost::mpl::int_<N>, boost::mpl::int_<N>)>::type
    operator()( S const& s
              , boost::mpl::int_<N> const&
              , boost::mpl::int_<N> const&
              ) const
    {
      return boost::fusion::at_c<N-1>(s);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Regular call slice<1> over sequence of size S
    ////////////////////////////////////////////////////////////////////////////
    template<class This,class Seq, int S>
    struct  result< This(Seq,boost::mpl::int_<1>,boost::mpl::int_<S>)>
    {
      static Seq const&     s;

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , memory::align_on( slice<memory::no_padding,1>(s) )
      );

      typedef typename nested::type type;
    };

    template<class Seq,int S>
    typename result<call(Seq,boost::mpl::int_<1>,boost::mpl::int_<S>)>::type
    operator()( Seq const& s
              , boost::mpl::int_<1> const&
              , boost::mpl::int_<S> const&
              ) const
    {
      return memory::align_on( slice<memory::no_padding,1>(s) );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Call of slcie<1> on sequence of size 1
    ////////////////////////////////////////////////////////////////////////////
    template<class This,class Seq>
    struct  result< This(Seq,boost::mpl::int_<1>,boost::mpl::int_<1>)>
    {
      static Seq const&     s;

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , memory::align_on( boost::fusion::at_c<0>(s) )
      );

      typedef typename nested::type type;
    };

    template<class S>
    typename result<call(S, boost::mpl::int_<1>, boost::mpl::int_<1>)>::type
    operator()( S const& s
              , boost::mpl::int_<1> const&
              , boost::mpl::int_<1> const&
              ) const
    {
      return  memory::align_on(boost::fusion::at_c<0>(s));
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
