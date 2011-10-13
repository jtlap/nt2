[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['This function is mainly for inner usage and allows',
                         'speedy writing of \c next, \c nextafter and like functions.','\par',
                         'It transform a pattern of bits stored in an integer value',
                         'in a floating point with different formulas according to',
                         'the integer sign (it is the converse of bitinteger)'],
         'return' : ['always a floating point value'],   
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ["int_convert_","uint_convert_"],
         'type_defs' : [],
         'types' : ["int_convert_","uint_convert_"],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/bitinteger.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'int32_t' : [['-100', '100']],
             'int64_t' : [['-100', '100']],
             'uint32_t' : [['0', '100']],
             'uint64_t' : [['0', '100']],
             'int_convert_' :  [['-100', '100']],   
             'uint_convert_' :  [['0', '100']],   
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::bitinteger(boost::simd::bitfloating(a0))'],
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
