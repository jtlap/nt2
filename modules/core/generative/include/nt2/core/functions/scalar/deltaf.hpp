//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_DELTAF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_DELTAF_HPP_INCLUDED

#include <nt2/core/functions/deltaf.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/details/deltaf.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::deltaf_, tag::cpu_
                            , (A0)(A1)(D1)(D2)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<D1> >)
                              (scalar_<integer_<D2> >)
                              (target_<scalar_< unspecified_<T> > > )
                            )
  {
    typedef _2D                                                    size_type;
    typedef meta::constant_<nt2::tag::deltaf_,typename T::type>    constant_t;
    typedef meta::as_<typename constant_t::result_type>             target_t;
    typedef typename  boost::proto::result_of
      ::make_expr < nt2::tag::deltaf_
      , container::domain
      , box<size_type>
      , box<constant_t>
      , target_t
      >::type     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& i, A1 const& j,
                                             D1 const& d1, D2 const& d2, T const& ) const
    {
      size_type sizee;
      sizee[0] = d1;
      sizee[1] = d2;
      return  boost::proto
        ::make_expr < nt2::tag::deltaf_
        , container::domain
        > ( boxify(sizee)
          , boxify(constant_t(i, j))
          , target_t()
          );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::deltaf_, tag::cpu_
                            , (A0)(A1)(D1)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<D1> >)
                              (target_<scalar_< unspecified_<T> > > )
                            )
  {
    typedef _2D                                                    size_type;
    typedef meta::constant_<nt2::tag::deltaf_,typename T::type>    constant_t;
    typedef meta::as_<typename constant_t::result_type>             target_t;
    typedef typename  boost::proto::result_of
      ::make_expr < nt2::tag::deltaf_
      , container::domain
      , box<size_type>
      , box<constant_t>
      , target_t
      >::type     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& i, A1 const& j,
                                             D1 const& d1, T const& ) const
    {
      size_type sizee;
      sizee[1] = sizee[0] = d1;
      return  boost::proto
        ::make_expr < nt2::tag::deltaf_
        , container::domain
        > ( boxify(sizee)
          , boxify(constant_t(i, j))
          , target_t()
          );
    }
  };

/// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::deltaf_, tag::cpu_
                            , (A0)(A1)(FS)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (fusion_sequence_<FS>)
                              (target_<scalar_< unspecified_<T> > > )
                            )
  {
    typedef typename boost::remove_const<FS>::type                 size_type;
    typedef meta::constant_<nt2::tag::deltaf_,typename T::type>    constant_t;
    typedef meta::as_<typename constant_t::result_type>             target_t;
    typedef typename  boost::proto::result_of
      ::make_expr < nt2::tag::deltaf_
      , container::domain
      , box<size_type>
      , box<constant_t>
      , target_t
      >::type     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& i, A1 const& j,
                                             FS const& fs, T const& ) const
    {
      return  boost::proto
        ::make_expr < nt2::tag::deltaf_
        , container::domain
        > ( boxify(fs)
          , boxify(constant_t(i, j))
          , target_t()
          );
    }
  };
} }

#endif
