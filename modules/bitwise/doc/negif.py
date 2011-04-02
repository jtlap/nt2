[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::arithmetic(T)>::type',
            },
         'simd_types' : ['real_', 'signed_int_'],
         'type_defs' : [],
         'types' : ['real_', 'integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [['T(0)', 'T(1)'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2']],
            },
         'specific_values' : {
             'default' : {
                 '0,1' : {'result' : '1','ulp_thresh' : '0.5',},
                 '1,1' : {'result' : '-1','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '0,1' : {'result' : '1','ulp_thresh' : '0.5',},
                 '1,1' : {'result' : '-1','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>(),1' : {'result' : '-1','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>(),1' : {'result' : '-1','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>(),1' : {'result' : '-1','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>(),1' : {'result' : '1','ulp_thresh' : '0.5',},
                },
             'signed_int_   ' : {
                 '0,1' : {'result' : '1','ulp_thresh' : '0.5',},
                 '1,1' : {'result' : '-1','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['nt2::negif(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['a0?-r_t(a1):r_t(a1)'],
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
