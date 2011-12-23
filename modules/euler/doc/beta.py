[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' :['Beta function','\par Formula',
                            '\\\\f[ B(a_0,a_1)=\int_0^1 t^{a_0-1}(1-t)^{a_1-1}dt = \\\\frac{\Gamma(a_0)\Gamma(a_1)}{\Gamma(a_0+a_1)}\\\\f]'],
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
         'simd_ulp_thresh' : '5',   
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 22/02/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 22/02/2011',
            },
         'ranges' : {
             'real_' : [['nt2::Eps<T>()', 'T(1)'],['nt2::Eps<T>()', 'T(1)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::beta(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['nt2::beta(a0,a1)'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
            },
        },
    },
]
