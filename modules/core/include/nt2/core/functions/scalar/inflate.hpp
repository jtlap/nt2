//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_INFLATE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_INFLATE_HPP_INCLUDED

#include <nt2/core/functions/inflate.hpp>
#include <boost/fusion/include/value_at.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Case for no base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inflate_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::fusion::result_of::
                            value_at<A0,boost::mpl::int_<0> >::type dims_t;

    typedef typename boost::fusion::result_of::
                            value_at<A1,boost::mpl::int_<0> >::type index_t;

    typedef boost::mpl::bool_< boost::mpl::size<A1>::value==0>      is_0d_t;

    typedef boost::fusion::vector < std::ptrdiff_t
                                  , std::ptrdiff_t
                                  >                                 result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos ) const
    {
      return eval(size,pos,is_0d_t());
    }

    BOOST_DISPATCH_FORCE_INLINE result_type
    eval(const A0& size, const A1& pos, boost::mpl::false_ const& ) const
    {
      index_t const& i = boost::fusion::at_c<0>(pos);
      dims_t  const& s = boost::fusion::at_c<0>(size);

      result_type that( (i-1) % s + 1, (i-1) / s + 1 );
      return that;
    }

    BOOST_DISPATCH_FORCE_INLINE result_type
    eval(const A0&, const A1&, boost::mpl::true_ const& ) const
    {
      result_type that(1,1);
      return that;
    }
  };

  //============================================================================
  // Case for specific base index
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inflate_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                              (fusion_sequence_<A2>)
                            )
  {
    typedef typename boost::fusion::result_of::at_c<A0 const,0 >::type dims_t;
    typedef typename boost::fusion::result_of::at_c<A1 const,0 >::type index_t;
    typedef typename boost::fusion::result_of::at_c<A2 const,0 >::type base_t;

    typedef boost::mpl::bool_< boost::mpl::size<A1>::value==0>      is_0d_t;

    typedef boost::fusion::vector < std::ptrdiff_t
                                  , std::ptrdiff_t
                                  >                                 result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& size, const A1& pos, const A2& base) const
    {
      return eval(size,pos,base,is_0d_t());
    }

    BOOST_DISPATCH_FORCE_INLINE result_type
    eval( const A0& size, const A1& pos, const A2& base
        , boost::mpl::false_ const&
        ) const
    {
      index_t i = boost::fusion::at_c<0>(pos);
      dims_t  s = boost::fusion::at_c<0>(size);
      base_t  b = boost::fusion::at_c<0>(base);

      result_type that( (i-b) % s + b, (i-b) / s + b );
      return that;
    }

    BOOST_DISPATCH_FORCE_INLINE result_type
    eval(const A0&, const A1&, const A2& base, boost::mpl::true_ const&) const
    {
      result_type that( boost::fusion::at_c<0>(base)
                      , boost::fusion::at_c<0>(base)
                      );
      return that;
    }
  };
} }

#endif
