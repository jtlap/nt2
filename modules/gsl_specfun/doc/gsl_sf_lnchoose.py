[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'double',
            },
         'simd_types' : [],
         'special' : ['gsl_specfun'],
         'type_defs' : [],
         'types' : ['integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 10/03/2011',
             'included' : [],
             'no_ulp' : 'False',
             'notes' : [],
             'stamp' : 'modified by jt the 10/03/2011',
            },
         'ranges' : {
             'default' : [['T(0)', 'T(10)'], ['T(0)', 'T(10)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::gsl_specfun::gsl_sf_lnchoose(a0+a1,a1)'],
                },
             'property_value' : {
                 'default' : ['nt2::gsl_specfun::gsl_sf_lnchoose(a0+a1,a1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
