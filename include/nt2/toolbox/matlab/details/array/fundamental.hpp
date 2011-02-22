#ifndef NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_FUNDAMENTAL_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_FUNDAMENTAL_HPP_INCLUDED

#include <nt2/toolbox/matlab/details/array/traits.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>

namespace nt2 { namespace matlab { namespace traits
{
    #define NT2_MATLAB_CLASS_DEF(size, signed, name)                           \
    template<typename T>                                                       \
    struct class_< T                                                           \
                 , typename boost::enable_if_c< sizeof(T)*CHAR_BIT == size     \
                                                && boost::is_signed<T>::value == signed\
                                              >::type                          \
                 >                                                             \
    {                                                                          \
        static const mxClassID value = name;                                   \
    };

    NT2_MATLAB_CLASS_DEF(8,  true,  mxINT8_CLASS  )
    NT2_MATLAB_CLASS_DEF(16, true,  mxINT16_CLASS )
    NT2_MATLAB_CLASS_DEF(32, true,  mxINT32_CLASS )
    NT2_MATLAB_CLASS_DEF(64, true,  mxINT64_CLASS )
    NT2_MATLAB_CLASS_DEF(8,  false, mxUINT8_CLASS )
    NT2_MATLAB_CLASS_DEF(16, false, mxUINT16_CLASS)
    NT2_MATLAB_CLASS_DEF(32, false, mxUINT32_CLASS)
    NT2_MATLAB_CLASS_DEF(64, false, mxUINT64_CLASS)
    
    #undef NT2_MATLAB_CLASS_DEF

    template<> struct class_<float>  { static const mxClassID value = mxSINGLE_CLASS; };
    template<> struct class_<double> { static const mxClassID value = mxDOUBLE_CLASS; };
    
    template<typename T>
    struct get_buffer_impl<T, typename boost::enable_if< meta::is_fundamental<T> >::type>
    {
        static T* call(T& t)
        {
            return &t;
        }
    };
    
    template<typename T>
    struct size_impl<T, typename boost::enable_if< meta::is_fundamental<T> >::type>
    {
        static std::vector<std::size_t> call(const T&)
        {
            return std::vector<std::size_t>(1, 1);
        }
    };
}
}}

#endif
