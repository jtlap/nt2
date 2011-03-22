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
// Implementation of the no_padding strategy for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/fusion.hpp>
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <nt2/sdk/memory/details/no_padding.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::slice_ ( tag::fusion_sequence_
                            , tag::padding_<memory::lead_padding>
                            , tag::mpl_integral_<tag::integer_>
                            )
              , tag::cpu_, Dummy  >
        : callable
  {
    ////////////////////////////////////////////////////////////////////////////
    // Computes the actual result type depending on A0 size and A2 value
    ////////////////////////////////////////////////////////////////////////////
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
    {
      typedef typename meta::strip<A2>::type        arg0;
      typedef typename meta::strip<A2>::type        arg2;
      typedef boost::fusion::result_of::size<arg0>  size_;
      static  typename meta::strip<A0>::type const& s;

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( true_case
      , nt2::mul( slice<2>(s,memory::no_padding())
                , memory::align_on( boost::fusion::at_c<0>(s) )
                )
      );

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( false_case, slice<arg2::value>(s,memory::no_padding())
      );

      typedef typename boost::mpl::eval_if_c< (arg2::value == 1)
                                            , true_case
                                            , false_case
                                            >::type type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when A2 == 1
    ////////////////////////////////////////////////////////////////////////////
    template<class A0, class A1, class A2> inline
    typename boost::lazy_enable_if_c< (A2::value==1), NT2_RETURN_TYPE(3)>::type
    operator()( A0 const& a0, A1 const&, A2 const& ) const
    {
      return nt2::mul ( slice<2>(a0,memory::no_padding())
                      , memory::align_on( boost::fusion::at_c<0>(a0) )
                      );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when A2 >= 1
    ////////////////////////////////////////////////////////////////////////////
    template<class A0, class A1, class A2> inline
    typename boost::lazy_enable_if_c< (A2::value!=1), NT2_RETURN_TYPE(3)>::type
    operator()( A0 const& a0, A1 const&, A2 const& ) const
    {
      return slice<A2::value>(a0,memory::no_padding());
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// stride Functor implementation - Do nothing except on inner dimension
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::stride_( tag::fusion_sequence_
                            , tag::padding_<memory::lead_padding>
                            , tag::mpl_integral_<tag::integer_>
                            )
              , tag::cpu_, Dummy  >
        : callable
  {
    ////////////////////////////////////////////////////////////////////////////
    // Computes the actual result type depending on A0 size and A2 value
    ////////////////////////////////////////////////////////////////////////////
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
    {
      typedef typename meta::strip<A2>::type        arg0;
      typedef typename meta::strip<A2>::type        arg2;
      static  typename meta::strip<A0>::type const& s;

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( true_case
      , memory::align_on( boost::fusion::at_c<0>(s) )
      );

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( false_case, boost::fusion::at_c<arg2::value-1>(s) );

      typedef typename boost::mpl::eval_if_c< (arg2::value == 1)
                                            , true_case
                                            , false_case
                                            >::type type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when A2 == 1
    ////////////////////////////////////////////////////////////////////////////
    template<class A0, class A1, class A2> inline
    typename boost::lazy_enable_if_c< (A2::value==1), NT2_RETURN_TYPE(3)>::type
    operator()( A0 const& a0, A1 const&, A2 const& ) const
    {
      return memory::align_on( boost::fusion::at_c<0>(a0) );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when A2 >= 1
    ////////////////////////////////////////////////////////////////////////////
    template<class A0, class A1, class A2> inline
    typename boost::lazy_enable_if_c< (A2::value!=1), NT2_RETURN_TYPE(3)>::type
    operator()( A0 const& a0, A1 const&, A2 const& ) const
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };
} }

#endif
