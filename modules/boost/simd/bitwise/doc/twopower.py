[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The function returns greatest power of two less or equal to the input.'],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T>::type',
            },
         'simd_types' : ['unsigned_int_'],
         'type_defs' : [],
         'types' : ['unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include <boost/simd/include/functions/shli.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [['0', 'sizeof(T)*8-1']],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                },
             'unsigned_int_   ' : {
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'unsigned_int_' : ['boost::simd::twopower(a0)'],
                },
             'property_value' : {
                 'unsigned_int_' : ['boost::simd::shli(T(1),a0)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
    },
]
