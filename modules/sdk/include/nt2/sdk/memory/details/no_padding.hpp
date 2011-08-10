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
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// slice implementation for no_padding strategy
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class A0, class A2, class Dummy>
  struct implement< tag::slice_
                  ( fusion_sequence_<A0>, padding_<memory::no_padding>
                  , mpl_integral_<scalar_<integer_<A2> > >
                  )
                , tag::cpu_, Dummy
                >
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
    typedef A0                  arg0;
    typedef memory::no_padding  arg1;
    typedef A2                  arg2;

    typedef boost::fusion::result_of::at_c<arg0 const,arg2::value-1>  true_case;

    static arg0 const& s; static arg1 const&  p;

    BOOST_TYPEOF_NESTED_TYPEDEF_TPL
    ( false_case
    ,   slice<arg2::value+1>(s,p)
      * boost::fusion::at_c<arg2::value-1>(s)
    );

    typedef typename boost::mpl::eval_if< same_size<arg0,arg2>
                                        , true_case
                                        , false_case
                                        >::type                   result_type;

    inline result_type
    operator()( A0 const& a0, memory::no_padding const&, A2 const& ) const
    {
      return eval(a0, typename same_size<A0,A2>::type() );
    }
    ////////////////////////////////////////////////////////////////////////////
    // Implementation when size<A0> == A2
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval( A0 const& a0, boost::mpl::true_ const& ) const
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when size<A0> != A2
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval( A0 const& a0, boost::mpl::false_ const& ) const
    {
      return   slice<A2::value+1> (a0, memory::no_padding() )
             * boost::fusion::at_c<A2::value-1>(a0);
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // stride Functor implementation
  //////////////////////////////////////////////////////////////////////////////
  template<class A0, class A1, class A2, class Dummy>
  struct implement< tag::stride_
                    ( fusion_sequence_<A0> , padding_<A1>
                    , mpl_integral_<scalar_<integer_<A2> > >
                    )
                  , tag::cpu_, Dummy
                  >
  {
    typedef typename  boost::fusion::result_of::
                      at_c< A0 const
                          , A2::value-1
                          >::type                                 result_type;

    inline result_type
    operator()( A0 const& a0, A1 const&, A2 const& ) const
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };
} }

#endif
