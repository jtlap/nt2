#ifndef NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_CONTAINER_TUPLE_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_CONTAINER_TUPLE_HPP_INCLUDED

#include <nt2/toolbox/matlab/details/array/container.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/boost_array.hpp>

namespace nt2 { namespace matlab
{
    namespace details
    {
        template<typename T, typename Dummy = void>
        struct is_container_tuple
          : boost::mpl::false_
        {
        };
        
        template<typename T, typename Dummy = void>
        struct primitive_of_container
        {
            typedef T type;
        };
        
        template<typename T>
        struct primitive_of_container<T, typename boost::enable_if< is_container<T> >::type>
          : primitive_of_container<typename boost::range_value<T>::type>
        {
        };
        
        template<typename T>
        struct is_container_tuple<
            T,
            typename boost::enable_if<
                boost::mpl::and_<
                    meta::is_fundamental<
                        //typename meta::primitive_of<
                            typename meta::strip<
                                typename boost::mpl::eval_if<
                                    is_container<T>,
                                    primitive_of_container<T>,
                                    dummy
                                >::type
                            >::type
                        //>::type
                    >,
                    boost::fusion::traits::is_sequence<T>
                >
            >::type
        >
          : boost::mpl::true_
        {
        };
        
        template<typename In, typename Out>
        typename boost::disable_if<
            is_container<typename std::iterator_traits<In>::value_type>,
            Out
        >::type
        copy(In const& begin, In const& end, Out& out)
        {
            return std::copy(begin, end, out);
        }
        
        template<typename In, typename Out>
        typename boost::enable_if<
            is_container<typename std::iterator_traits<In>::value_type>,
            Out
        >::type
        copy(In const& begin, In const& end, Out& out)
        {
            for(In it = begin; it != end; ++it)
                out = details::copy(boost::begin(*it), boost::end(*it), out);
            return out;
        }
        
        template<typename T>
        typename boost::disable_if<
            is_container_tuple<T>,
            T&
        >::type
        primitive_of_container_access(T& t)
        {
            return t;
        }
            
        template<typename T>
        typename boost::enable_if<
            is_container_tuple<T>,
            typename primitive_of_container<T>::type&
        >::type
        primitive_of_container_access(T& t)
        {
            return primitive_of_container_access(*boost::begin(t));
        }
        
        template<typename T, typename Dummy = void>
        struct container_nesting_level
        {
            static const std::size_t value = 0;
        };
        
        template<typename T>
        struct container_nesting_level<T, typename boost::enable_if< is_container_tuple<T> >::type>
        {
            static const std::size_t value =
                container_nesting_level<typename boost::range_value<T>::type>::value
                + 1
            ;
        };
        
        template<typename T, std::size_t I, std::size_t N>
        typename boost::enable_if_c<I == N>::type
        container_dimensions_fill(boost::array<std::size_t, N>& a)
        {
        }
        
        template<typename T, std::size_t I, std::size_t N>
        typename boost::disable_if_c<I == N>::type
        container_dimensions_fill(boost::array<std::size_t, N>& a)
        {
            a[I] = boost::fusion::result_of::size<T>::value;
            container_dimensions_fill<typename boost::range_value<T>::type, I+1>(a);
        }
    }
    
}
namespace meta
{
    template<typename T, std::size_t N>
    struct primitive_of<boost::array<T, N> >
    {
        typedef T type;
    };
    
    template<typename T, std::size_t N, std::size_t M>
    struct primitive_of<boost::array<boost::array<T, N>, M > >
    {
        typedef T type;
    };
}
namespace matlab {
namespace traits
{
    template<typename T, typename Out>
    struct linearize_impl<T, Out, typename boost::enable_if< details::is_container_tuple<T> >::type>
    {
        static Out call(const T& t, Out out)
        {
            return details::copy(boost::begin(t), boost::end(t), out);
        }
    };
    
    template<typename T, typename Iterator>
    struct assign_from_iterators_impl<T, Iterator, typename boost::enable_if< details::is_container_tuple<T> >::type>
    {
        static void call(Iterator const& begin, Iterator const& end, T& t)
        {
            std::copy(begin, end, &details::primitive_of_container_access(t));
        }
    };
    
    namespace result_of
    {
        template<typename T>
        struct size<T, typename boost::enable_if< details::is_container_tuple<T> >::type>
        {
            typedef boost::array<std::size_t, details::container_nesting_level<T>::value> type;
        };
    }
    
    template<typename T>
    struct size_impl<T, typename boost::enable_if< details::is_container_tuple<T> >::type>
    {
        static typename result_of::size<T>::type call(const T& t)
        {
            typename result_of::size<T>::type a;
            details::container_dimensions_fill<T, 0>(a);
            return a;
        }
    };
}
}}

#endif
