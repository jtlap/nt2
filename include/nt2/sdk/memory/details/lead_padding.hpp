/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_LEAD_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_LEAD_PADDING_HPP_INCLUDED

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
  struct call<slice_,tag::fusion_(memory::lead_padding),Info>
  {
    ////////////////////////////////////////////////////////////////////////////
    // Template status for selecting between {N,S} state space
    ////////////////////////////////////////////////////////////////////////////
    template<bool Same, bool One> struct status {};

    ////////////////////////////////////////////////////////////////////////////
    // result_of protocol
    ////////////////////////////////////////////////////////////////////////////
    template<class Sig> struct result;

    template<class This,class Seq,class Padder,class N>
    struct  result<This(Seq const&,Padder const&,N const&)>
    {
      typedef boost::fusion::result_of::size<Seq> seq_size;
      typedef status<(N::value==seq_size::value),(N::value==1)> status_type;

      template<class Status, class Dummy=void> struct inner;

      // N!=S
      template<class Dummy>
      struct  inner<status<false,false>,Dummy>
      {
        static Seq const& s;
        static details::times callee;
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL
        ( nested
        , callee( slice<N::value+1>(s,memory::lead_padding())
                , boost::fusion::at_c<N::value-1>(s)
                )
        );
        typedef typename nested::type type;
      };

      // N==S but N!=1
      template<class Dummy>
      struct  inner<status<true,false>,Dummy>
            : boost::fusion::result_of::at_c<Seq const,N::value-1>
      {};

      // N==1 but N!=S
      template<class Dummy>
      struct  inner<status<false,true>,Dummy>
      {
        static Seq const& s;
        static details::times callee;
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL
        ( nested
        , callee( memory::align_on( boost::fusion::at_c<0>(s) )
                , slice<2>(s,memory::lead_padding())
                )
        );
        typedef typename nested::type type;
      };

      // N==1 and S==1
      template<class Dummy>
      struct  inner<status<true,true>,Dummy>
      {
        static Seq const& s;
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL
        ( nested
        , memory::align_on( boost::fusion::at_c<0>(s) )
        );
        typedef typename nested::type type;
      };

      typedef typename inner<status_type>::type type;
    };

    NT2_FUNCTOR_CALL_DISPATCH ( 3
                              , (status<(     A2::value
                                          ==  boost::fusion
                                            ::result_of::size<A0>::value
                                        )
                                        ,(A2::value==1)
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
      details::times callee;
      return callee ( slice<A2::value+1>(a0,memory::lead_padding())
                    , boost::fusion::at_c<A2::value-1>(a0)
                    );
    }

    NT2_FUNCTOR_CALL_EVAL_IF(3, (status<true , false>) )
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(3, (status<false , true>) )
    {
      details::times callee;
      return callee ( memory::align_on( boost::fusion::at_c<0>(a0) )
                    , slice<2>(a0,memory::lead_padding())
                    );
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
  struct  call<stride_,tag::fusion_(memory::lead_padding),Info>
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder, class N>
    struct  result<This(Seq const&,Padder const&,N const&)>
    {
      typedef boost::fusion::result_of::at_c<Seq const,N::value-1> non_leading;
      static Seq const& s;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( leading
      , memory::align_on( boost::fusion::at_c<0>(s) )
      );

      typedef typename  boost::mpl::eval_if_c < (N::value==1)
                                              , leading
                                              , non_leading
                                              >::type             type;
    };

    NT2_FUNCTOR_CALL_DISPATCH ( 3
                              , boost::mpl::bool_<(A2::value==1)>
                              , ( 2,( boost::mpl::true_
                                    , boost::mpl::false_
                                    )
                                )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(3, boost::mpl::true_   )
    {
      return memory::align_on( boost::fusion::at_c<0>(a0) );
    }

    NT2_FUNCTOR_CALL_EVAL_IF(3, boost::mpl::false_  )
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };
} }

#endif
