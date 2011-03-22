#ifndef NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_TRAITS_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_TRAITS_HPP_INCLUDED

#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <boost/mpl/bool.hpp>
#include <vector>
#include <numeric>
#include <cstring>
#include <functional>

#include <mat.h>

namespace nt2 { namespace matlab
{
    namespace details
    {
        template<typename T>
        typename meta::primitive_of<typename meta::strip<T>::type>::type* get_data(mxArray* p)
        {
            return (typename meta::primitive_of<typename meta::strip<T>::type>::type*)mxGetData(p);
        }
    }

    namespace traits
    {
        template<typename T, typename Dummy = void>
        struct class_;
        
        template<typename T, typename Out, typename Dummy = void>
        struct linearize_impl;
        
        template<typename T, typename Out>
        Out linearize(const T& t, Out out)
        {
            return linearize_impl<T, Out>::call(t, out);
        }
        
        template<typename T, typename Iterator, typename Dummy = void>
        struct assign_from_iterators_impl;
        
        template<typename T, typename Iterator>
        void assign_from_iterators(Iterator const& begin, Iterator const& end, T& t)
        {
            assign_from_iterators_impl<T, Iterator>::call(begin, end, t);
        }
        
        template<typename T, typename Dummy = void>
        struct is_complex : boost::mpl::false_
        {
        };
        
        namespace result_of
        {
            template<typename T, typename Dummy = void>
            struct size;
        }
        
        template<typename T, typename Dummy = void>
        struct size_impl;
        
        template<typename T>
        typename result_of::size<T>::type size(const T& t)
        {
            return size_impl<T>::call(t);
        }

        template<typename T, typename Dummy = void>
        struct to_matlab_impl
        {
            static mxArray* call(const T& t)
            {
                typename result_of::size<T>::type dims = traits::size(t);
                
                typedef typename meta::primitive_of<typename meta::strip<T>::type>::type Primitive;
                mxArray* p = 
                    mxCreateNumericArray(
                        dims.size(),
                        dims.data(), 
                        class_<Primitive>::value,
                        is_complex<T>::value ? mxCOMPLEX : mxREAL
                    )
                ;
                
                traits::linearize(t, details::get_data<T>(p));
                return p;
            }
        };
        
        template<typename T>
        mxArray* to_matlab(const T& t)
        {
            return to_matlab_impl<T>::call(t);
        }
        
        template<typename T, typename Dummy = void>
        struct from_matlab_impl
        {
            static T call(mxArray* t)
            {
                typedef typename meta::primitive_of<typename meta::strip<T>::type>::type Primitive;
                
                const mwSize* dims = mxGetDimensions(t);
                mwSize dims_size = mxGetNumberOfDimensions(t);
                
                mwSize nb_elems =
                    std::accumulate(
                        dims,
                        dims + dims_size,
                        1,
                        std::multiplies<mwSize>()
                    )
                ;
                
                T out;
                traits::assign_from_iterators(
                    details::get_data<T>(t),
                    details::get_data<T>(t) + nb_elems*sizeof(Primitive),
                    out
                );
                
                return out;
            }
        };
        
        template<typename T>
        T from_matlab(mxArray* t)
        {
            return from_matlab_impl<T>::call(t);
        }
    }
    
}}

#endif
