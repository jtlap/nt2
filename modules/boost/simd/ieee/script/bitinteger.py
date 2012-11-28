[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['This function is mainly for inner usage and allows',
                         'speedy writing of \c next, \c nextafter and like functions','\par',
                         'It transforms a floating point value in a pattern of bits',
                         'stored in an integer with different formulas according to',
                         'the floating point sign (it is the converse of bitfloating)'],
         'return' : ['always an integer value'],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_integer<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/bitfloating.hpp>', '#include <boost/dispatch/meta/as_integer.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::bitfloating(boost::simd::bitinteger(a0))'],
                },
             'property_value' : {
                 'default' : ['a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
