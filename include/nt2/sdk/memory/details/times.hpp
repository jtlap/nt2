/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_TIMES_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_TIMES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// CT/RT hybrid times functor
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/times.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace details
{
  struct times
  {
    template<class Sig> struct result;

    template<class This, class A, class B>
    struct result<This(A,B)>
    {
      template<bool As, bool Bs, int Dummy = 0 >
      struct inner
  	  {
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, A() * B() );
        typedef typename nested::type type;
      };

      template<int Dummy>
      struct inner<false,false,Dummy>
      {
        typedef typename boost::mpl::times<A,B>::type type;
      };

      typedef typename meta::strip<A>::type arg0_;
      typedef typename meta::strip<B>::type arg1_;
      typedef typename inner< boost::is_arithmetic<arg0_>::value
                            , boost::is_arithmetic<arg1_>::value
                            >::type type;
    };

    template<bool A0, bool A1> struct status {};

    template<class A0, class A1> inline
    typename result<times(A0,A1)>::type
    operator()( A0 const& a0, A1 const& a1 )
    {
      typedef status< boost::is_arithmetic<A0>::value
                    , boost::is_arithmetic<A1>::value
                    > status_t;

      return eval(a0,a1,status_t());
    }

    template<class A0, class A1> inline
    typename result<times(A0,A1)>::type
    eval( A0 const& a0, A1 const& a1, status<true,true> const& )
    {
      return a0*a1;
    }

    template<class A0, class A1> inline
    typename result<times(A0,A1)>::type
    eval( A0 const& , A1 const& , status<false,false> const& )
    {
      return typename result<times(A0,A1)>::type();
    }

    template<class A0, class A1> inline
    typename result<times(A0,A1)>::type
    eval( A0 const& , A1 const& a1, status<false,true> const& )
    {
      return A0::value * a1;
    }

    template<class A0, class A1> inline
    typename result<times(A0,A1)>::type
    eval( A0 const& a0, A1 const&, status<true,false> const& )
    {
      return a0 * A1::value;
    }
  };
} }

#endif
