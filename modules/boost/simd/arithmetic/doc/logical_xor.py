[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ["returns the logical xor of  a0 and a1, i.e. returns true ",
                          "if and only if one of the two parameter is zero andthe other non zero."],  
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0', 
         'rturn' : {
             'default' : 'bool',
            },
         'special' : ['predicate'],
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'default' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(0),T(1)' : 'true',
                 'T(3),T(0)' : 'true',
                 'boost::simd::Inf<T>()' : 'false',
                 'boost::simd::Minf<T>()' : 'false',
                 'boost::simd::Mone<T>()' : 'false',
                 'boost::simd::Nan<T>()' : 'false',
                 'boost::simd::One<T>()' : 'false',
                 'boost::simd::Zero<T>()' : 'false',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'false',
                 'boost::simd::One<T>()' : 'false',
                 'boost::simd::Zero<T>()' : 'false',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'false',
                 'boost::simd::Zero<T>()' : 'false',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::logical_xor(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['(a0!=0)^(a1!=0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
