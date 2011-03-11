/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DETAILS_BITWISE_CAST_HPP_INCLUDED
#define NT2_SDK_DETAILS_BITWISE_CAST_HPP_INCLUDED

#include <nt2/sdk/error/static_assert.hpp>

#include <cstring>
#include <boost/type_traits/is_convertible.hpp>

namespace nt2
{
    namespace details
    {
        struct memcpy_cast
        {
            template<typename To, typename From>
            static To call(From const& from)
            {
                To to;
                std::memcpy(&to, &from, sizeof(From));
                return to;
            }
        };

        struct union_cast
        {
            template<typename To, typename From>
            static To call(From const& from)
            {
                union
                {
                    From from;
                    To to;
                } u = { from };
                return u.to;
            }
        };

        struct convert_cast
        {
            template<typename To, typename From>
            static To call(From const& from)
            {
                return (To)from;
            }
        };

        template<typename To, typename From, typename Enable = void>
        struct bitwise_cast : memcpy_cast {};

        template<typename To, typename From>
        struct bitwise_cast<To, From, typename boost::is_convertible<From, To>::type> : convert_cast {};
    }

    template<typename To, typename From>
    To bitwise_cast(From const& from)
    {
        NT2_STATIC_ASSERT(
            sizeof(From) == sizeof(To)
          , NT2_TARGET_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
          , "target is not the same size as source in nt2::bitwise_cast"
        );
        return details::bitwise_cast<To, From>::template call<To>(from);
    }
}

#endif
