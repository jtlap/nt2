[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T','A_t'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'simd_types' : ['real_'],
         'special' : ["polynomials"],
         'type_defs' : ['typedef std::vector<T> A_t;'],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 06/03/2011',
             'included' : ['#include <vector>'],
             'notes' : [],
             'stamp' : 'modified by jt the 06/03/2011',
            },
         'ranges' : {
             'default' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
            },
         'specific_values' : {
             'default' : {
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::plevl(a0,A1)'],
                },
             'property_value' : {
                 'real_' : ['nt2::plevl(a0,A1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'real_' : ['0.5'],
                },
            },
        },
    },

]
