//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_OPTION_OPTION_EXPR_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTION_EXPR_HPP_INCLUDED

#include <nt2/sdk/option/option_expr_fwd.hpp>
#include <nt2/sdk/option/option_domain.hpp>
#include <nt2/sdk/option/option_not_found.hpp>
#include <nt2/sdk/option/option_term.hpp>
#include <nt2/sdk/option/option_pack.hpp>

#include <boost/proto/core.hpp>
#include <nt2/sdk/error/static_assert.hpp>

namespace nt2 { namespace details
{
  template<class Expr> struct option_expr
  {
    BOOST_PROTO_BASIC_EXTENDS(Expr, option_expr, option_domain)
    BOOST_PROTO_EXTENDS_ASSIGN()

    template <class Sig>struct result;

    template <class Option>
    struct  has_option
          : boost::mpl::bool_<
              !boost::is_same < typename result<option_expr const(Option)>::type
                              , option_not_found
                              >::value
                            >
    {};

    template <class This, class Option>
    struct result<This(Option)> : std::tr1::result_of<option_pack(This, Option)>
    {};

    template <class This, class Option, class Default>
    struct result<This(Option, Default)>
        : boost::mpl::if_c< has_option<Option>::value
                          , typename result<This(Option)>::type
                          , Default
                          >
    {};

    template<class Option>
    typename result<option_expr const(Option const)>::type
    operator()(Option const &opt) const
    {
      NT2_STATIC_ASSERT ( (boost::proto::matches<Option const,option_term>::value)
                        , UNKNOWN_NAMED_OPTIONS
                        , "Trying to retrieve unknown named option."
                        );

      NT2_STATIC_ASSERT ( (has_option<Option const>::value)
                        , NO_SUCH_OPTION_IN_CURRENT_OPTIONS_PACK
                        , "Named option is not used in this options pack."
                        );

      return option_pack()(*this, opt);
    }

      template<class Option, class Default>
      typename result<option_expr const(Option const, Default const)>::type
      operator()(Option const &opt, Default const &def) const
      {
      NT2_STATIC_ASSERT ( (boost::proto::matches<Option const,option_term>::value)
                        , UNKNOWN_NAMED_OPTIONS
                        , "Trying to retrieve unknown named option."
                        );

        return this->with_default(opt, def, has_option<Option const>());
      }

    private:

    template<class Option, class Default>
    typename result<option_expr const(Option const, Default const)>::type
    with_default(Option const &opt, Default const &, boost::mpl::true_) const
    {
      return option_pack()(*this, opt);
    }

    template<class Option, class Default>
    typename result<option_expr const(Option const, Default const)>::type
    with_default(Option const &, Default const &def, boost::mpl::false_) const
    {
      return def;
    }
  };
} }

#endif
