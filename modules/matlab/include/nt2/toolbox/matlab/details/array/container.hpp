#ifndef NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_CONTAINER_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_CONTAINER_HPP_INCLUDED

#include <nt2/toolbox/matlab/details/array/traits.hpp>

#include <boost/fusion/include/is_sequence.hpp>
#include <boost/range.hpp>
#include <algorithm>

#include <nt2/sdk/meta/enable_if_type.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

namespace nt2 { namespace matlab
{
    namespace details
    {
        template<typename T, typename Enable = void>
        struct is_container
          : boost::mpl::false_
        {
        };
        
        template<typename T>
        struct is_container<
            T,
            typename meta::enable_if_type<
                typename meta::strip<T>::type::value_type,
                typename meta::enable_if_type<
                    typename meta::strip<T>::type::iterator
                >::type
            >::type
        >
          : boost::mpl::true_
        {
        };
        
        template<typename T, typename Enable = void>
        struct is_basic_container
          : boost::mpl::false_
        {
        };
          
        struct dummy { typedef dummy type; };
          
        template<typename T>
        struct is_basic_container<
            T,
            typename boost::enable_if<
                boost::mpl::and_<
                    meta::is_fundamental<
                        //typename meta::primitive_of<
                            typename meta::strip<
                                typename boost::mpl::eval_if<
                                    is_container<T>,
                                    boost::range_value<T>,
                                    dummy
                                >::type
                            >::type
                        //>::type
                    >,
                    boost::mpl::not_<
                        boost::fusion::traits::is_sequence<T>
                    >
                >
            >::type
        >
          : boost::mpl::true_
        {
        };
    }
    
namespace traits
{
    template<typename T, typename Out>
    struct linearize_impl<T, Out, typename boost::enable_if< details::is_basic_container<T> >::type>
    {
        static Out call(const T& t, Out out)
        {
            return std::copy(boost::begin(t), boost::end(t), out);
        }
    };
    
    template<typename T, typename Iterator>
    struct assign_from_iterators_impl<T, Iterator, typename boost::enable_if< details::is_basic_container<T> >::type>
    {
        static void call(Iterator const& begin, Iterator const& end, T& t)
        {
            std::copy(begin, end, boost::begin(t));
        }
    };
    
    namespace result_of
    {
        template<typename T>
        struct size<T, typename boost::enable_if< details::is_basic_container<T> >::type>
        {
            typedef boost::array<std::size_t, 1> type;
        };
    }
    
    template<typename T>
    struct size_impl<T, typename boost::enable_if< details::is_basic_container<T> >::type>
    {
        static typename result_of::size<T>::type call(const T& t)
        {
            boost::array<std::size_t, 1> a = { boost::size(t) };
            return a;
        }
    };
}
}}

#endif
