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
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#pragma warning( push )
#pragma warning( disable : 4522 ) // multiple assignment operators specified
#endif

namespace nt2 { namespace container
{
  /* table_view; an expression of a container_ref terminal.
   * allows construction from an expression of a container terminal */
  template<class T, class S = nt2::settings()>
  struct table_view
       : expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_ref<T, S> >, 0l >
                   , memory::container<T, S>&
                   >
  {
    typedef memory::container_ref<T, S> container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0l > basic_expr;
    typedef memory::container<T, S>& semantic;
    typedef expression<basic_expr, semantic> nt2_expression;

    typedef typename container_ref::iterator iterator;
    typedef typename container_ref::const_iterator const_iterator;

    iterator begin() const
    {
      return boost::proto::value(*this).begin();
    }

    iterator end() const
    {
      return boost::proto::value(*this).end();
    }

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

    using nt2_expression::operator=;
  };

  template<class T, class S>
  struct table_view<T const, S>
       : expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_ref<T const, S> >, 0l >
                   , memory::container<T, S> const&
                   >
  {
    typedef memory::container_ref<T const, S> container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0l > basic_expr;
    typedef memory::container<T, S> const& semantic;
    typedef expression<basic_expr, semantic> nt2_expression;

    typedef typename container_ref::iterator iterator;
    typedef typename container_ref::const_iterator const_iterator;

    iterator begin() const
    {
      return boost::proto::value(*this).begin();
    }

    iterator end() const
    {
      return boost::proto::value(*this).end();
    }

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

    using nt2_expression::operator=;
  };

  /* table_shared_view; an expression of a container_shared_ref terminal.
   * allows construction from an expression of a container_shared_ref terminal */
  template<class T, class S = nt2::settings()>
  struct table_shared_view
       : expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_shared_ref< T, S, false > >, 0l >
                   , memory::container<T, S>&
                   >
  {
    typedef memory::container_shared_ref< T, S, false > container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0l > basic_expr;
    typedef memory::container<T, S>& semantic;
    typedef expression<basic_expr, semantic> nt2_expression;

    typedef typename container_ref::iterator iterator;
    typedef typename container_ref::const_iterator const_iterator;

    iterator begin() const
    {
      return boost::proto::value(*this).begin();
    }

    iterator end() const
    {
      return boost::proto::value(*this).end();
    }

    BOOST_FORCEINLINE
    table_shared_view()
    {
    }

    BOOST_FORCEINLINE
    table_shared_view( nt2_expression const& expr )
                     : nt2_expression(expr)
    {
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    table_shared_view( Xpr const& expr )
                     : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class Xpr>
    void reset(Xpr const& other)
    {
      table_shared_view tmp(other);
      boost::proto::value(*this) = boost::proto::value(tmp);
      this->size_ = tmp.size_;
    }

    using nt2_expression::operator=;
  };

  template<class T, class S>
  struct table_shared_view<T const, S>
       : expression< boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term< memory::container_shared_ref< T const, S, false > >, 0l >
                   , memory::container<T, S> const&
                   >
  {
    typedef memory::container_shared_ref< T const, S, false > container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0l > basic_expr;
    typedef memory::container<T, S> const& semantic;
    typedef expression<basic_expr, semantic> nt2_expression;

    typedef typename container_ref::iterator iterator;
    typedef typename container_ref::const_iterator const_iterator;

    iterator begin() const
    {
      return boost::proto::value(*this).begin();
    }

    iterator end() const
    {
      return boost::proto::value(*this).end();
    }

    BOOST_FORCEINLINE
    table_shared_view()
    {
    }

    BOOST_FORCEINLINE
    table_shared_view( nt2_expression const& expr )
                     : nt2_expression(expr)
    {
    }

    template<class Xpr>
    table_shared_view( Xpr const& expr )
                     : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    void reset(Xpr const& other)
    {
      table_shared_view tmp(other);
      boost::proto::value(*this) = boost::proto::value(tmp);
      this->size_ = tmp.size_;
    }

    using nt2_expression::operator=;
  };

} }

#if defined(BOOST_MSVC)
#pragma warning( pop )
#endif

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class S>
  struct semantic_of< nt2::container::table_view<T, S> >
  {
    typedef typename nt2::container::table_view<T, S>::semantic type;
  };

  template<class T, class S>
  struct semantic_of< nt2::container::table_shared_view<T, S> >
  {
    typedef typename nt2::container::table_shared_view<T, S>::semantic type;
  };
} } }

namespace nt2
{
  using nt2::container::table_view;
  using nt2::container::table_shared_view;
}

#endif
