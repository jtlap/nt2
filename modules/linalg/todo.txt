
// Elementary Matrices and Arrays

// blkdiag         Construct block diagonal matrix from input arguments            | 
// colon (:)       Create vectors, array subscripting, and for-loop iterators      | done _(i, j),  _,  _(i, h, j)
// diag            Diagonal matrices and diagonals of matrix                       | must be done with diag_of and from_diag which themselves are to be done     
// eye             Identity matrix                                                 | done
// freqspace       Frequency spacing for frequency response                        | done differently
// ind2sub         Subscripts from linear index                                    | done
// linspace        Generate linearly spaced vectors                                | done
// logspace        Generate logarithmically spaced vectors                         | done     
// ndgrid          Rectangular grid in N-D space                                   | 
// ones            Create array of all ones                                        | done 
// rand            Uniformly distributed pseudorandom numbers                      |     
// randi           Uniformly distributed pseudorandom integers                     |          
// randn           Normally distributed pseudorandom numbers                       |
// RandStream      Random number stream                                            |               
// rng             Control random number generation                                |
// sub2ind         Convert subscripts to linear indices                            | done 
// zeros           Create array of all zeros                                       | done 
                                                                               
// Matrix Analysis
// cond              Condition number with respect to inversion                    | done
// condeig           Condition number with respect to eigenvalues                  |
// det               Matrix determinant                                            | done also 2 versions of absdet one with no overflow
// norm              Vector and matrix norms                                       | done
// normest           2-norm estimate                                               | done
// null              Null space                                                    | done
// orth              Range space of matrix                                         | done
// rank              Rank of matrix                                                | done
// rcond             Matrix reciprocal condition number estimate                   | done
// rref              Reduced row echelon form                                      | done
// subspace          Angle between two subspacestraceSum of diagonal elements      | done
                                                                                
// Linear Equations                                                             
// chol              Cholesky factorization
// cholinc           Sparse incomplete Cholesky and Cholesky-Infinity              |  SPARSE
// cond              Condition number with respect to inversion                    | done
// condest           1-norm condition number estimate                              | done 
// funm              Evaluate general matrix function                              |
// ichol             Incomplete Cholesky factorization                             |  SPARSE
// ilu               Sparse incomplete LU factorization                            |  SPARSE
// inv               Matrix inverse                                                | done
// ldl               Block LDLt factorization for Hermitian indefinite matrices    |
// linsolve          Solve linear system of equations                              |
// lscov             Least-squares solution in presence of known covariance        |
// lsqnonneg         Solve nonnegative least-squares constraints problem           |
// lu                LU matrix factorization                                       | done
// luinc             Sparse incomplete LU factorization                            |   SPARSE
// pinv              Moore-Penrose pseudoinverse of matrix                         | done
// qr                Orthogonal-triangular decomposition                           | done
// rcond             Matrix reciprocal condition number estimate                   | done

// Eigenvalues and Singular Values
// balance              Diagonal scaling to improve eigenvalue accuracy            |
// cdf2rdf              Convert complex diagonal form to real block diagonal form  |
// condeig              Condition number with respect to eigenvalues               |
// eig                  Eigenvalues and eigenvectors                               | partially done
// eigs                 Largest eigenvalues and eigenvectors of matrix             |
// gsvd                 Generalized singular value decomposition                   | 
// hess                 Hessenberg form of matrix                                  |
// ordeig               Eigenvalues of quasitriangular matrices                    |
// ordqz                Reorder eigenvalues in QZ factorization                    |
// ordschur             Reorder eigenvalues in Schur factorization                 |
// poly                 Polynomial with specified roots                            |
// polyeig              Polynomial eigenvalue problemrs                            |
// f2csf                Convert real Schur form to complex Schur form              |
// schur                Schur decomposition                                        |
// sqrtm                Matrix square root                                         |
// ss2tf                Convert state-space filter parameters to transfer func form|
// svd                  Singular value decomposition                               | done
// svds                 Find singular values and vectors                           |    SPARSE

// Matrix Logarithms and Exponentials
// expm                   Matrix exponential                                       |
// logm                   Matrix logarithm                                         |
// sqrtm                  Matrix square root                                       |

// Factorization
// balance                Diagonal scaling to improve eigenvalue accuracy          |
// cdf2rdf                Convert complex diagonal form to real block diagonal form|
// cholupdate             Rank 1 update to Cholesky factorization                  |
// planerot               Givens plane rotation                                    |
// qrdelete               Remove column or row from QR factorization               |
// qrinsert               Insert column or row into QR factorization               |
// qrupdate               Rank 1 update to QR factorization                        |
// qz                     QZ factorization for generalized eigenvalues             |
// rsf2csf                Convert real Schur form to complex Schur form            |

