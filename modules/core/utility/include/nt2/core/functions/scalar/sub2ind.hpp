//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_SUB2IND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_SUB2IND_HPP_INCLUDED

#include <nt2/core/functions/sub2ind.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <cstddef>

namespace nt2 { namespace ext
{
  template<class Seq>
  struct sequence_value
   : boost::dispatch::meta::
     strip< typename boost::mpl::
            eval_if_c< boost::fusion::result_of::size<Seq>::type::value == 0
                     , boost::mpl::identity<std::size_t>
                     , boost::fusion::result_of::value_at_c<Seq, 0>
                     >::type
          >
  {
  };

  //============================================================================
  // Case for no base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sub2ind_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename sequence_value<A1>::type               type;
    typedef typename meta::as_unsigned<type>::type          result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos) const
    {
      typedef typename boost::fusion::result_of::size<A1>::type dims;
      return bitwise_cast<result_type>(
             eval ( size, pos
                  , boost::mpl::int_<0>()
                  , boost::mpl::int_<dims::value-1>()
                  )
             );
    }

    template<class Idx, class Sz>
    BOOST_DISPATCH_FORCE_INLINE type
    eval(const A0& s, const A1& p, const Idx&, const Sz& sz) const
    {
      return  boost::fusion::at_c<Idx::value>(p) - 1
            + boost::fusion::at_c<Idx::value>(s)
            * eval(s,p,boost::mpl::int_<Idx::value+1>(),sz);
    }

    template<class Sz>
    BOOST_DISPATCH_FORCE_INLINE type
    eval(const A0& s,const A1& p,const boost::mpl::int_<0>&,const Sz& sz) const
    {
      return  boost::fusion::at_c<0>(p) - 1
            + boost::fusion::at_c<0>(s)
            * eval(s,p,boost::mpl::int_<1>(),sz);
    }

    template<class Sz>
    BOOST_DISPATCH_FORCE_INLINE type
    eval(const A0&, const A1& p, const Sz&, const Sz&) const
    {
      return splat<type>(  boost::fusion::at_c<Sz::value>(p)
                         -  One<type>()
                        );
    }

    BOOST_DISPATCH_FORCE_INLINE type
    eval( const A0&, const A1& p
        , const boost::mpl::int_<0>&, const boost::mpl::int_<0>&
        ) const
    {
      return splat<type>(  boost::fusion::at_c<0>(p)
                         -  One<type>()
                        );
    }

    BOOST_DISPATCH_FORCE_INLINE type
    eval( const A0&, const A1&
        , const boost::mpl::int_<0>&, const boost::mpl::int_<-1>&
        ) const
    {
      return Zero<type>();
    }
  };

  //============================================================================
  // Case for specific base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sub2ind_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                              (fusion_sequence_<A2>)
                            )
  {
    typedef typename sequence_value<A1>::type               type;
    typedef typename meta::as_unsigned<type>::type          result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos, const A2& base) const
    {
      typedef typename boost::fusion::result_of::size<A1>::type dims;
      return bitwise_cast<result_type>(
             eval ( size,pos,base
                  , boost::mpl::int_<0>()
                  , boost::mpl::int_<dims::value-1>()
                  )
             );
    }

    template<class Idx, class Sz>
    BOOST_DISPATCH_FORCE_INLINE type
    eval(const A0& s, const A1& p, const A2& b, const Idx&, const Sz& sz) const
    {
      return  boost::fusion::at_c<Idx::value>(p)
            - boost::fusion::at_c<Idx::value>(b)
            + boost::fusion::at_c<Idx::value>(s)
            * eval(s,p,b,boost::mpl::int_<Idx::value+1>(),sz);
    }

    template<class Sz>
    BOOST_DISPATCH_FORCE_INLINE type
    eval( const A0& s, const A1& p, const A2& b
        , const boost::mpl::int_<0>&, const Sz& sz
        ) const
    {
      return  boost::fusion::at_c<0>(p) - boost::fusion::at_c<0>(b)
            + boost::fusion::at_c<0>(s)
            * eval(s,p,b,boost::mpl::int_<1>(),sz);
    }

    template<class Sz>
    BOOST_DISPATCH_FORCE_INLINE type
    eval(const A0&, const A1& p, const A2& b, const Sz&, const Sz&) const
    {
      return splat<type>(  boost::fusion::at_c<Sz::value>(p)
                         -  boost::fusion::at_c<Sz::value>(b)
                        );
    }

    BOOST_DISPATCH_FORCE_INLINE type
    eval( const A0&, const A1& p, const A2& b
        , const boost::mpl::int_<0>&, const boost::mpl::int_<0>&
        ) const
    {
      return splat<type>(  boost::fusion::at_c<0>(p)
                         -  boost::fusion::at_c<0>(b)
                        );
    }

    BOOST_DISPATCH_FORCE_INLINE type
    eval( const A0&, const A1&, const A2&
        , const boost::mpl::int_<0>&, const boost::mpl::int_<-1>&
        ) const
    {
      return Zero<type>();
    }
  };
} }

#endif
