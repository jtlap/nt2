[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The function returns the second entry or the third entry,',
                          'according to the first entry being True or False'],
         'module' : 'boost',
         'arity' : '3',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'type_defs' : [],
         'types' : ['real_', 'integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ["#include <boost/simd/toolbox/predicates/include/functions/is_nez.hpp>"],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['T(0)', 'T(0)'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                [['T(-1)', 'T(-1)'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                ],
             'real_' : [
                [['T(0)', 'T(0)'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                [['boost::simd::Nan<T>()', 'boost::simd::Nan<T>()'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::False< boost::simd::logical<T> >(),boost::simd::One<T>(),boost::simd::Two<T>()' : {'result' : 'boost::simd::Two<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::True< boost::simd::logical<T> >(),boost::simd::One<T>(),boost::simd::Two<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                }
            },
         'verif_test' : {
             'property_call' : {
                 'simd_special' : 'boost::simd::select(boost::simd::is_nez(a0),a1,a2)',
                 'default' : ['boost::simd::select(boost::simd::is_nez(a0),a1,a2)'],
                },
             'property_value' : {
                 'default' : ['a0?a1:a2'],
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
