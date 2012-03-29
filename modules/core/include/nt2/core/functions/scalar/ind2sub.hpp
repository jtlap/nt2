//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_IND2SUB_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_IND2SUB_HPP_INCLUDED

#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <nt2/core/functions/ind2sub.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Case for no base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef typename boost::array<int, boost::fusion::result_of::size<A0>::value> result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos) const
    {
      boost::array<int, boost::fusion::result_of::size<A0>::value> sub;
      eval(sub, pos, size, boost::mpl::int_<0>(),
           boost::mpl::int_<boost::fusion::result_of::size<A0>::value>());
      return sub;
    }

    template<class N, class M>
    BOOST_DISPATCH_FORCE_INLINE result_type
    eval(boost::array<int, boost::fusion::result_of::size<A0>::value>& sub,
         const size_t& p, const A0& s, const N&, const M&) const
    {
      sub[N::value] = p % boost::fusion::at_c<N::value>(s) + 1;

      eval( sub, p / boost::fusion::at_c<N::value>(s), s
          , boost::mpl::int_<N::value+1>()
          , boost::mpl::int_<M::value>()
          );

      return sub;
    }

    BOOST_DISPATCH_FORCE_INLINE void
    eval( boost::array<int, boost::fusion::result_of::size<A0>::value>& sub
        , const size_t& p, const A0& s
        , const boost::mpl::int_<0>&, const boost::mpl::int_<1>&
        ) const
    {
      sub[0] = p + 1;
    }

    template<class N>
    BOOST_DISPATCH_FORCE_INLINE void
    eval(boost::array<int, boost::fusion::result_of::size<A0>::value>& sub,
         const size_t& p, const A0& s, const N&, const N&) const
    {
    }
  };

  //============================================================================
  // Case for specific base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              (scalar_< unspecified_<A1> >)
                              (fusion_sequence_<A2>)
                            )
  {
    typedef typename boost::array<int, boost::fusion::result_of::size<A0>::value> result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos, const A2& base) const
    {
      boost::array<int, boost::fusion::result_of::size<A0>::value> sub;
      eval( sub, pos, size, base
          , boost::mpl::int_<0>()
          , boost::mpl::int_<boost::fusion::result_of::size<A0>::value>()
          );
      return sub;
    }

    template<class N, class M>
    BOOST_DISPATCH_FORCE_INLINE result_type
    eval(boost::array<int, boost::fusion::result_of::size<A0>::value>& sub,
         const size_t& p, const A0& s, const A2& b, const N&, const M&) const
    {
      sub[N::value] = p % boost::fusion::at_c<N::value>(s)
                    + boost::fusion::at_c<N::value>(b);

      eval( sub, p / boost::fusion::at_c<N::value>(s), s, b
          , boost::mpl::int_<N::value+1>()
          , boost::mpl::int_<M::value>()
          );

      return sub;
    }

    BOOST_DISPATCH_FORCE_INLINE void
    eval( boost::array<int, boost::fusion::result_of::size<A0>::value>& sub
        , const size_t& p, const A0& s, const A2& b
        , const boost::mpl::int_<0>&, const boost::mpl::int_<1>&
        ) const
    {
      sub[0] = p + boost::fusion::at_c<0>(b);
    }

    template<class N>
    BOOST_DISPATCH_FORCE_INLINE void
    eval(boost::array<int, boost::fusion::result_of::size<A0>::value>& sub,
         const size_t& p, const A0& s, const A2& b, const N&, const N&) const
    {
    }
  };
} }

#endif
