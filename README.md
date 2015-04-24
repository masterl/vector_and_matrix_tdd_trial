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
- Vector can be accessed by vector[position]
- This is a class template, example use:
   - Vector<3,double> vec; *this creates a tridimensional vector of doubles
- Operations defined:
    - initializer_list constructor
    - vector.dimensions() **returns how many dimensions the vector has**
    - vector * vector **dot product**
    - vector.dot(vector) **dot product**
    - vector.cross(vector) **cross product**
    - vector.set({1,2,3,...}) **set ignores extra elements after all dimensions are set**

- ***Class only compiles for if Scalar == float, double or long double***

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
- Most duplicated code has been removed!