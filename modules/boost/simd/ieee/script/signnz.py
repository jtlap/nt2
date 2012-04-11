[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "Returns the sign of a0. I.e. -1 or 1, according",
                           "a0 is negative or positive.",
                           "This function never returns zero (zero is considered positive)."],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 '-boost::simd::Zero<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::Inf<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                  'default' : ['boost::simd::signnz(a0)'],
               },
             'property_value' : {
                 'default' : ['(a0>=0) ? 1 : -1'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]
