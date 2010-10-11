/*******************************************************************************
 *               Copyright 2010 Thomas Heller
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef BOOST_PROTO_VISITOR_HPP
#define BOOST_PROTO_VISITOR_HPP

#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/matches.hpp>

namespace boost { namespace proto {

    namespace detail
    {
        template <
            template <typename> class Visitor
          , template <typename> class Grammar
        >
        struct visitor_cases
        {
            template <typename Tag>
            struct case_
                : proto::when<
                    Grammar<Tag>
                  , Visitor<Tag>
                >
            {};
        };
    }

    template <
        template <typename> class Visitor
      , template <typename> class Grammar
    >
    struct visitor
        : proto::switch_<
            detail::visitor_cases<Visitor, Grammar>
        >
    {};

    template <
        template <typename> class Visitor
      , template <typename> class Grammar
    >
    struct is_callable<visitor<Visitor, Grammar> >
        : mpl::true_
    {};

}}

#endif
