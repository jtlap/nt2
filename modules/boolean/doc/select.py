[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The function returns the second entry or the third entry,',
                          'according to the first entry being True or False'],
         'module' : 'boolean',
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
             'included' : ["#include <nt2/toolbox/predicates/include/functions/is_nez.hpp>"],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['T(0)', 'T(0)'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2']],
                [['T(-1)', 'T(-1)'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2']],
                ],
             'real_' : [
                [['T(0)', 'T(0)'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2']],
                [['nt2::Nan<T>()', 'nt2::Nan<T>()'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'nt2::False<T>(),nt2::One<T>(),nt2::Two<T>()' : {'result' : 'nt2::Two<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::True<T>(),nt2::One<T>(),nt2::Two<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                }
            },
         'verif_test' : {
             'property_call' : {
                 'simd_special' : 'nt2::select(nt2::is_nez(a0),a1,a2)', 
                 'default' : ['nt2::select(nt2::is_nez(a0),a1,a2)'],
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
