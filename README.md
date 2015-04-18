### TDD trial using C++

#### License
- MIT License
   - **See LICENSE file**

#### Depends on:
- **Boost**
- **C++11 compiler** *(makefile sets -std=c++14, but it's easily changed)*
  - I used g++ 4.9.1

#### Notes:
- Don't be too harsh, I know I kinda didn't follow TDD directives fully, but this is just some practice programming.
- Mostly naive implementation.
- I gave almost no care to performance and there's a lot of duplicated code waiting for refactor

#### Vector
- A great deal has already been done!
- ***Class only compiles for if T == float, double or long double***
- Couldn't figure out yet how to limit class to floating point without creating dummy pointer _class_enable...
- I'll refactor this in the near future.

#### Matrix
- Matrix can be acessed by matrix[line][column]
- Operations defined:
    - matrix * scalar and matrix *= scalar
    - matrix / scalar and matrix /= scalar
    - matrix + scalar and matrix += scalar
    - matrix - scalar and matrix -= scalar
    - matrix * matrix
    - matrix / matrix (element by element division)
    - matrix + matrix
    - matrix - matrix
    - matrix2 = matrix1
- Determinant for NxN done
- Generates:
    - Minors matrix
    - Identity matrixes
    - Transposed matrix
    - Cofactors matrix
    - Adjoint matrix
    - Inverse matrix

- Many refactors are needed and will be done.