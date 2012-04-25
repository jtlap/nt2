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

#include <nt2/core/functions/ind2sub.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/modulo.hpp>
#include <nt2/include/functions/divides.hpp>
#include <boost/dispatch/meta/as_signed.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/int.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Case for no base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (generic_< unspecified_<A1> >)
                            )
  {
    typedef typename meta::strip<A1>::type                          base_t;
    typedef typename boost::dispatch::meta::as_signed<base_t>::type type_t;
    typedef boost::fusion::result_of::size<A0>                      dims_t;
    typedef boost::array<type_t,dims_t::value>                      result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos) const
    {
      type_t p;
      result_type sub;

      p = pos;
      eval(sub,p,size,boost::mpl::int_<0>(),boost::mpl::int_<dims_t::value>());
      return sub;
    }

    template<class N, class M>
    BOOST_DISPATCH_FORCE_INLINE result_type
    eval(result_type& sub,const A1& p, const A0& s, const N&, const M& m) const
    {
      type_t ls     = splat<type_t>(boost::fusion::at_c<N::value>(s));
      sub[N::value] = p % ls + One<type_t>();
      eval( sub, p/ls, s, boost::mpl::int_<N::value+1>(), m );

      return sub;
    }

    BOOST_DISPATCH_FORCE_INLINE void
    eval( result_type& sub, const A1& p, const A0& s
        , const boost::mpl::int_<0>&, const boost::mpl::int_<1>&
        ) const
    {
      sub[0] = p + One<type_t>();
    }

    template<class N>
    BOOST_DISPATCH_FORCE_INLINE void
    eval(result_type&, const A1&, const A0&, const N&, const N&) const {}
  };

  //============================================================================
  // Case for specific base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              (generic_< unspecified_<A1> >)
                              (fusion_sequence_<A2>)
                            )
  {
    typedef typename meta::strip<A1>::type                          base_t;
    typedef typename boost::dispatch::meta::as_signed<base_t>::type type_t;
    typedef boost::fusion::result_of::size<A0>                      dims_t;
    typedef boost::array<type_t,dims_t::value>                      result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos, const A2& base) const
    {
      type_t p;
      result_type sub;

      p = pos;
      eval(sub,p,size,base,boost::mpl::int_<0>(),boost::mpl::int_<dims_t::value>());

      return sub;
    }

    template<class N, class M>
    BOOST_DISPATCH_FORCE_INLINE result_type
    eval( result_type& sub,const A1& p, const A0& s, const A2& b
        , const N&, const M& m
        ) const
    {
      type_t ls     = splat<type_t>(boost::fusion::at_c<N::value>(s));
      sub[N::value] = p % ls + splat<type_t>(boost::fusion::at_c<N::value>(b));
      eval( sub, p/ls, s, b, boost::mpl::int_<N::value+1>(), m );

      return sub;
    }

    BOOST_DISPATCH_FORCE_INLINE void
    eval( result_type& sub, const A1& p, const A0& s, const A2& b
        , const boost::mpl::int_<0>&, const boost::mpl::int_<1>&
        ) const
    {
      sub[0] = p + splat<type_t>(boost::fusion::at_c<0>(b));
    }

    template<class N>
    BOOST_DISPATCH_FORCE_INLINE void
    eval(result_type&,const A1&,const A0&,const A2&,const N&,const N&) const  {}
  };
} }

#endif
