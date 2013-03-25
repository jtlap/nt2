//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_TABLE_TABLE_VIEW_HPP_INCLUDED
#define NT2_CORE_CONTAINER_TABLE_TABLE_VIEW_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/container_ref.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <nt2/core/container/table/adapted/table_view.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#pragma warning( push )
#pragma warning( disable : 4522 ) // multiple assignment operators specified
#endif

namespace nt2 { namespace tag
{
  struct table_;
} }

namespace nt2 { namespace container
{
  /* table_view; an expression of a container_ref terminal.
   * allows construction from an expression of a container terminal */
  template<typename T, typename S>
  struct table_view
       : expression< boost::proto::basic_expr < boost::proto::tag::terminal
                                              , boost::proto::term
                                                < memory::container_ref < T
                                                                        , S
                                                                        , nt2::tag::table_
                                                                        >
                                                >
                                              , 0l
                                              >
                   , memory::container<T, S, nt2::tag::table_>&
                   >
  {
    typedef memory::container_ref<T, S, nt2::tag::table_>             container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal
                                    , boost::proto::term<container_ref>
                                    , 0l
                                    >               basic_expr;
    typedef memory::container<T, S, nt2::tag::table_>&                container_type;
    typedef expression<basic_expr, container_type>  nt2_expression;

    typedef typename container_ref::iterator        iterator;
    typedef typename container_ref::const_iterator  const_iterator;

    iterator begin()  const { return boost::proto::value(*this).begin(); }
    iterator end()    const { return boost::proto::value(*this).end(); }

    BOOST_FORCEINLINE
    table_view()
    {
    }

    BOOST_FORCEINLINE
    table_view( nt2_expression const& expr )
              : nt2_expression(expr)
    {
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    table_view( Xpr& expr )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    table_view( Xpr const& expr )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class Xpr>
    void reset(Xpr& other)
    {
      table_view tmp(other);
      boost::proto::value(*this) = boost::proto::value(tmp);
      this->size_ = tmp.size_;
    }

    //==========================================================================
    // Enable base expression handling of assignment
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , table_view&
                              >::type
    operator=(Xpr const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE table_view& operator=(table_view const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , table_view const&
                              >::type
    operator=(Xpr const& xpr) const
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE table_view const& operator=(table_view const& xpr) const
    {
      nt2_expression::operator=(xpr);
      return *this;
    }
  };

  template<typename T, typename S>
  struct table_view<T const, S>
       : expression< boost::proto::basic_expr < boost::proto::tag::terminal
                                              , boost::proto::term< memory::container_ref < T const
                                                                                          , S
                                                                                          , nt2::tag::table_
                                                                                          >
                                                                  >
                                              , 0l
                                              >
                   , memory::container<T, S, nt2::tag::table_> const&
                   >
  {
    typedef memory::container_ref<T const, S, nt2::tag::table_>       container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal
                                    , boost::proto::term< memory::container_ref < T const
                                                                                , S
                                                                                , nt2::tag::table_
                                                                                >
                                                        >
                                    , 0l
                                    >               basic_expr;
    typedef memory::container<T, S, nt2::tag::table_> const&          container_type;
    typedef expression<basic_expr, container_type>  nt2_expression;

    typedef typename container_ref::iterator        iterator;
    typedef typename container_ref::const_iterator  const_iterator;

    iterator begin()  const { return boost::proto::value(*this).begin();  }
    iterator end()    const { return boost::proto::value(*this).end();    }

    BOOST_FORCEINLINE
    table_view()
    {
    }

    BOOST_FORCEINLINE
    table_view( nt2_expression const& expr )
              : nt2_expression(expr)
    {
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    table_view( Xpr const& expr )
              : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class Xpr>
    void reset(Xpr const& other)
    {
      table_view tmp(other);
      boost::proto::value(*this) = boost::proto::value(tmp);
      this->size_ = tmp.size_;
    }

    //==========================================================================
    // Enable base expression handling of assignment
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , table_view&
                              >::type
    operator=(Xpr const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE table_view& operator=(table_view const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , table_view const&
                              >::type
    operator=(Xpr const& xpr) const
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE table_view const& operator=(table_view const& xpr) const
    {
      nt2_expression::operator=(xpr);
      return *this;
    }
  };
} }

namespace nt2 { using nt2::container::table_view; }

#endif
