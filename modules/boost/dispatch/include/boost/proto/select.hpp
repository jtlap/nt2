//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_PROTO_SELECT_HPP_INCLUDED
#define BOOST_PROTO_SELECT_HPP_INCLUDED

#include <boost/proto/transform.hpp>
#include <boost/result_of.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace proto
{
  //============================================================================
  /** \brief For matching one of a set of alternate grammars, which
   *  are looked up based on the result of a transform applied on the
   *  Expression type. When used as a transform, \c switch_\<\> applies the
   *  transform associated with the grammar that matches the expression.
   *
   *  An expression type \c E matches <tt>select_\<C,T\></tt> if \c E
   *  matches <tt>C::case_\<result_of<T(E)\></tt>.
   *
   *  When applying <tt>select_\<C,T\></tt> as a transform with an
   *  expression \c e of type \c E, state \c s and data \c d, it is
   *  equivalent to <tt>C::case_\<result_of<T(E)\>()(e, s, d)</tt>.
   */
  //============================================================================
  template<typename Cases, typename Transform>
  struct select_ : transform< select_<Cases,Transform> >
  {
    typedef select_ proto_grammar;
    typedef when<_,Transform> applicant;

    template<typename Expr, typename State, typename Data>
    struct impl
      : Cases::template
        case_ < typename boost::result_of<applicant(Expr)>::type >
                              ::template impl<Expr, State, Data>
    {};

    template<typename Expr, typename State, typename Data>
    struct impl<Expr &, State, Data>
    : Cases::template
      case_ < typename boost::result_of<applicant(Expr)>::type >
                            ::template impl<Expr&, State, Data>
    {};
  };

  //============================================================================
  // Make match aware of select_
  //============================================================================
  namespace detail
  {
    template< typename Expr, typename Tag, typename Args, long Arity
            , typename Cases, typename Transform
            >
    struct matches_ < Expr, proto::basic_expr<Tag, Args, Arity>
                    , select_<Cases,Transform>
                    >
      : matches_< Expr
                , proto::basic_expr<Tag, Args, Arity>
                , typename  Cases::template
                  case_<typename boost::
                        result_of< when<_,Transform>(Expr)>::type
                       >::proto_grammar
        >
    {
      typedef when<_,Transform> applicant;
      typedef typename boost::result_of<applicant(Expr)>::type selected_type;
      typedef typename Cases::template case_<selected_type> which;
    };
  }

  //============================================================================
  // Make select_ callable
  //============================================================================
  template<typename Cases, typename Transform>
  struct is_callable<select_<Cases,Transform> > : mpl::true_ {};
} }

#endif
