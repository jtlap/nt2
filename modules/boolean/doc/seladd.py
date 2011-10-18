[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The function returns the second entry or the sum of the second and third entries,',
                          'according to the first entry being True or False'],
         'param_1' : ['must be an integer value'],   
           'module' : 'boolean',
         'arity' : '3',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<boost::dispatch::meta::arithmetic(T,T)>::type',
            },
         'simd_types' : ['real_', 'integer_'],
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
            'real_' : {
                 'T(0),T(1),T(2)' : {'result' : 'T(1)','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>(),T(1),T(2)' : {'result' : 'T(3)','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>(),boost::simd::Inf<T>(),boost::simd::Inf<T>()' : {'result' : 'boost::simd::Inf<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>(),boost::simd::Minf<T>(),boost::simd::Minf<T>()' : {'result' : 'boost::simd::Minf<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>(),boost::simd::Nan<T>(),boost::simd::Nan<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>(),boost::simd::Zero<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'integer_' : {
                 'T(0),T(1),T(2)' : {'result' : 'T(1)','ulp_thresh' : '0.5',},
                 'T(-1),T(1),T(2)' : {'result' : 'T(3)','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>(),boost::simd::Zero<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'simd_special' : 'boost::simd::seladd(boost::simd::is_nez(a0),a1,a2)',
                 'integer_' : ['boost::simd::seladd(boost::simd::is_nez(a0),a1,a2)'],
                },
             'property_value' : {
                 'integer_' : ['r_t(a0?a1+a2:a1)'],
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
