/*******************************************************************************
 *               Copyright 2010 Thomas Heller
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef BOOST_PROTO_FUSION_PUSH_BACK_HPP
#define BOOST_PROTO_FUSION_PUSH_BACK_HPP

#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/algorithm/transformation/join.hpp>

namespace boost { namespace proto {

namespace functional {
    
    struct join
    {
        BOOST_PROTO_CALLABLE()

        template <typename Sig>
        struct result;

        template <typename This, typename Seq1, typename Seq2>
        struct result<This(Seq1, Seq2)>
            : result<This(Seq1 const&, Seq2 const&)>
        {};

        template <typename This, typename Seq1, typename Seq2>
        struct result<This(Seq1 &, Seq2 &)>
            : fusion::result_of::join<Seq1 const, Seq2 const>
        {};

        template <typename Seq1, typename Seq2>
        typename fusion::result_of::join<Seq1 const, Seq2 const>::type
        operator()(Seq1 const& seq1, Seq2 const& seq2) const
        {
            return fusion::join(seq1, seq2);
        }
    };
    
    struct push_back
    {
        BOOST_PROTO_CALLABLE()

        template <typename Sig>
        struct result;

        template <typename This, typename Seq, typename T>
        struct result<This(Seq, T const &)>
            : result<This(Seq const&, T const&)>
        {};

        template <typename This, typename Seq, typename T>
        struct result<This(Seq &, T const &)>
            : fusion::result_of::push_back<Seq const, T>
        {};

        template <typename Seq, typename T>
        typename fusion::result_of::push_back<Seq const, T>::type
        operator()(Seq const& seq, T const& t) const
        {
            return fusion::push_back(seq, t);
        }
    };
    
    struct push_front
    {
        BOOST_PROTO_CALLABLE()

        template <typename Sig>
        struct result;

        template <typename This, typename Seq, typename T>
        struct result<This(Seq, T)>
            : result<This(Seq const&, T const&)>
        {};

        template <typename This, typename Seq, typename T>
        struct result<This(Seq &, T const &)>
            : fusion::result_of::push_front<Seq const, T>
        {};

        template <typename Seq, typename T>
        typename fusion::result_of::push_front<Seq const, T>::type
        operator()(Seq const& seq, T const& t) const
        {
            return fusion::push_front(seq, t);
        }
    };
}

template <>
struct is_callable<functional::join> : mpl::true_ {};

template <>
struct is_callable<functional::push_back> : mpl::true_ {};
}}

#endif
