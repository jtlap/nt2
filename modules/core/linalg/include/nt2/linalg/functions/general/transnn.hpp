//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_TRANSNN_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_TRANSNN_HPP_INCLUDED

#include <nt2/linalg/functions/transnn.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/trans44.hpp>
#include <nt2/include/functions/trans33.hpp>
#include <nt2/include/functions/trans22.hpp>
#include <nt2/core/container/dsl.hpp>


namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transnn_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              )
  {
    typedef typename A0::value_type value_type;
    typedef nt2::container::table<value_type,  nt2::of_size_<A2::value, A1::value>> result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const & , A2 const & ) const
    {
      return tr(a0, A1(), A2());
    }
  private:
    BOOST_FORCEINLINE result_type tr(A0 const & a0
                                    , boost::mpl::long_<1> const&
                                    , A2 const&) const
    {
      result_type a = nt2::colvect(a0);
      return a;
    }

    BOOST_FORCEINLINE result_type tr(A0 const & a0
                                    , A1 const&
                                    , boost::mpl::long_<1> const&) const
    {
      result_type a = nt2::rowvect(a0);
      return a;
    }

    BOOST_FORCEINLINE result_type tr(A0 const & a0
                                    , boost::mpl::long_<2> const&
                                    , boost::mpl::long_<2> const&) const
    {
      result_type a = a0;
      trans22(a);
      return a;
    }

    BOOST_FORCEINLINE result_type tr(A0 const & a0
                                    , boost::mpl::long_<3> const&
                                    , boost::mpl::long_<3> const&) const
    {
      result_type a = a0;
      trans33(a);
      return a;
    }

    BOOST_FORCEINLINE result_type tr(A0 const & a0
                                    , boost::mpl::long_<2> const&
                                    , boost::mpl::long_<3> const&) const
    {
      result_type a = nt2::reshape(a0, 3, 2);
      nt2::swap(a(1,2), a(2,1));
      nt2::swap(a(2,2), a(2,1));
      nt2::swap(a(2,1), a(3,1));
      return a;
    }

    BOOST_FORCEINLINE result_type tr(A0 const & a0
                                    , boost::mpl::long_<3> const&
                                    , boost::mpl::long_<2> const&) const
    {
      result_type a = nt2::reshape(a0, 2, 3);
      nt2::swap(a(2, 1), a(2, 2));
      nt2::swap(a(2, 2), a(1, 3));
      nt2::swap(a(1, 2), a(1, 3));
      return a;
    }

    BOOST_FORCEINLINE result_type tr(A0 const & a0
                                    , boost::mpl::long_<4> const&
                                    , boost::mpl::long_<4> const&) const
    {
      result_type a = a0;
      trans44(a);
      return a;
    }

    template < class T1, class T2 >
    BOOST_FORCEINLINE result_type tr(A0 const & a0
                                    , T1 const&
                                    , T2 const&) const
    {
      return nt2::trans(a0);
    }

  };

} }

#endif
