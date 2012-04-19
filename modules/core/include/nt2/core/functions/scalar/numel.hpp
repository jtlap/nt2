//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_NUMEL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_NUMEL_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <nt2/core/functions/numel.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/iterator_range.hpp>
#include <boost/fusion/include/advance.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0), (scalar_< unspecified_<A0> >)
                            )
  {
    typedef boost::mpl::size_t<1> result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&) const { return result_type(); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (mpl_integral_< scalar_< unspecified_<A1> > >)
                            )
  {
    typedef boost::mpl::size_t<1> result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&, const A1&) const { return result_type(); }
  };

  // INTERNAL ONLY
  // Less strict multiply functor
  struct local_multiply
  {
    typedef std::size_t result_type;

    template<class A, class B> result_type
    operator()(A const& a, B const& b) const
    {
      return result_type(a) * result_type(b);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0)
                            , (fusion_sequence_<A0>)
                            )
  {
    typedef typename boost::fusion::result_of::
            fold< A0
                , boost::mpl::size_t<1> const
                , local_multiply
                >::type                                        result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0 const& a0) const
    {
      return boost::fusion::fold( a0
                                , boost::mpl::size_t<1>()
                                , local_multiply()
                                );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (mpl_integral_< scalar_< unspecified_<A1> > >)
                            )
  {
    typedef typename boost::fusion::result_of::begin<A0>::type  begin_t;
    typedef typename boost::fusion::result_of::end<A0>::type    end_t;
    typedef typename boost::fusion::result_of::
                            advance<begin_t, A1>::type          new_begin_t;
    typedef boost::fusion::iterator_range<new_begin_t, end_t>   it_t;

    typedef typename  boost::fusion::result_of
                           ::fold< it_t const
                                 , boost::mpl::size_t<1> const
                                 , local_multiply
                                 >::type                      result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0 const& a0, const A1&) const
    {
      return boost::fusion::fold( it_t(new_begin_t(a0), end_t(a0))
                                , boost::mpl::size_t<1>()
                                , local_multiply()
                                );
    }
  };
} }

#endif
