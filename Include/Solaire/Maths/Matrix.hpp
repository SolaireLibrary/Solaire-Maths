#ifndef SOLAIRE_MATRIX_HPP
#define SOLAIRE_MATRIX_HPP

//Copyright 2015 Adam Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

// Contact :
// Email             : solairelibrary@mail.com
// GitHub repository : https://github.com/SolaireLibrary/SolaireCPP

/*!
	\file Matrix.hpp
	\brief Contains code for N dimentional Matrices, with typedefs for commonly used configurations.
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 23rd September 2015
	Last Modified	: 9th January 2016
*/

#include "Vector.hpp"

namespace Solaire {

    //! \todo Implement Translation / Rotation / Scale helpers

    /*!
        \brief
        \detail
        \tparam T The scalar type of the elements of this Matrix.
        \tparam WIDTH The width of this Matrix.
        \tparam HEIGHT The height of this Matrix.
        \version 1.0.0
    */
	template<class T, const uint32_t WIDTH, const uint32_t HEIGHT>
	class Matrix{
	public:
		typedef T Scalar;                               //!< The scalar element type.
		enum : uint32_t {
		    Width = WIDTH,                              //!< The width of this Matrix.
		    Height = HEIGHT,                            //!< The height of this Matrix.
		    Min = Width < Height ? Width : Height,      //!< The smaller of Width or Height.
		    Max = Width > Height ? Width : Height       //!< The larger of Width or Height.
		};
		typedef Vector<Scalar, Width> Row;              //!< A Vector that can represent a row of this Matrix.
		typedef Vector<Scalar, Height> Column;          //!< A Vector that can represent a column of this Matrix.
	private:
		Scalar mData[Width * Height];                   //!< Contains the elements of this Matrix in row major order.
	public:

	    /*!
            \brief Create a new matrix.
            \detail This will be equal to the identity Matrix.
            \code
            Matrix<float, 3, 3> matrix(); // This matrix is equivalent to the following :
            Matrix<float, 3, 3> matrix({
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
            });
            \endcode
	    */
	    Matrix() throw() {
	        enum : uint32_t{Size = Width * Height};
            for(uint32_t i = 0; i < Width; ++i) {
                for(uint32_t j = 0; j < Height; ++j) {
                    mData[i * Width + j] = static_cast<Scalar>(i == j ? 1 : 0);
                }
			}
		}

        /*!
            \brief Create a Matrix with a scalar value in the diagonal.
            \detail
            \code
            Matrix<float, 3, 3> matrix(5); // This matrix is equivalent to the following :
            Matrix<float, 3, 3> matrix({
                5, 0, 0,
                0, 5, 0,
                0, 0, 5
            });
            \endcode
            \param aScalar The scalar value.
        */
	    Matrix(const Scalar aScalar) throw() {
	        enum : uint32_t{Size = Width * Height};
            for(uint32_t i = 0; i < Width; ++i) {
                for(uint32_t j = 0; j < Height; ++j) {
                    mData[i * Width + j] = static_cast<Scalar>(i == j ? aScalar : 0);
                }
			}
		}

        /*!
            \brief Create a Matrix with a pre-defined set of elements.
            \param aElements The elements to place into the Matrix.
        */
        Matrix(const std::initializer_list<Scalar> aElements) throw() {
	        enum : uint32_t{Size = Width * Height};
	        auto j = aElements.begin();
	        const uint32_t size = aElements.size();
	        const uint32_t min = Size <= size ? Size : size;

	        // Copy elements into the Matrix
	        for(uint32_t i = 0; i < min; ++i){
                mData[i] = *j;
                ++j;
	        }

            // Replace any remaining elements with default values
            //! \todo Identity values
            for(uint32_t i = min; i < Size; ++i){
                mData[i] = static_cast<Scalar>(0);
	        }
	    }

	    // C++ Operators


        /*!
            \brief Convert this Matrix to a representation in another scalar type.
            \tparam Scalar2 The scalar type to convert to.
            \return The converted Matrix.
        */
		template<class Scalar2>
	    explicit operator Matrix<Scalar2, Width, Height>() const throw() {
	        enum : uint32_t{Size = Width * Height};
	        Matrix<Scalar2, Width, Height> tmp;

	        // Convert each element
	        const Scalar* const ptr = tmp.ptr();
	        for(uint32_t i = 0; i < Size; ++i){
                ptr[i] = static_cast<Scalar2>(mData[i]);
	        }

	        return tmp;
	    }

        /*!
            \brief Transpose conversion operator.
            \tparam W Used for conditional compilation.
            \tparam H Used for conditional compilation.
            \tparam ENABLE Used for conditional compilation.
            \return The transposed Matrix.
            \see transpose
        */
        template<const uint32_t W = Width, const uint32_t H = Height, class ENABLE = typename std::enable_if<W != H>::type>
	    explicit operator Matrix<Scalar, Height, Width>() const throw() {
	       return transpose();
	    }

        /*!
            \brief Get a pointer to the first element in a Row of the Matrix.
            \param aIndex The index of the Row.
            \return The address of the Row.
            \see Row
            \see getRow
        */
		const Scalar* operator[](const uint32_t aIndex) const throw() {
			return mData + (aIndex * Width);
		}

        /*!
            \brief Get a pointer to the first element in a Row of the Matrix.
            \param aIndex The index of the Row.
            \return The address of the Row.
            \see Row
            \see getRow
        */
		Scalar* operator[](const uint32_t aIndex) throw() {
			return mData + (aIndex * Width);
		}

        /*!
            \brief Check if this Matrix is equal to another Matrix.
            \param aOther The second Matrix.
            \return True if the Matrices are the same.
        */
		bool operator==(const Matrix<Scalar, Width, Height>& aOther) const throw() {
			return std::memcmp(mData, aOther.mData, sizeof(Scalar) * Width * Height) == 0;
		}

        /*!
            \brief Check if this Matrix is not equal to another Matrix.
            \param aOther The second Matrix.
            \return True if the Matrices are different.
        */
		bool operator!=(const Matrix<Scalar, Width, Height>& aOther) const throw() {
			return std::memcmp(mData, aOther.mData, sizeof(Scalar) * Width * Height) != 0;
		}

		// Misc

        /*!
            \brief Access the elements of this Matrix as a C-style array.
            \return The address of index [0,0].
        */
		const Scalar* ptr() const throw() {
			return mData;
		}

        /*!
            \brief Access the elements of this Matrix as a C-style array.
            \return The address of index [0,0].
        */
		Scalar* ptr() throw() {
			return mData;
		}

        /*!
            \brief Get a Row of the matrix.
            \param The index of the Row to get.
            \see Row
            \see setRow
        */
		Row& getRow(const uint32_t aIndex) throw() {
		    return *reinterpret_cast<Row*>(mData + (aIndex * Width));
		}

        /*!
            \brief Get a Row of the matrix.
            \param The index of the Row to get.
            \see Row
            \see setRow
        */
		Row getRow(const uint32_t aIndex) const throw() {
		    return *reinterpret_cast<const Row*>(mData + (aIndex * Width));
		}

        /*!
            \brief Get a Column of the matrix.
            \param The index of the Column to get.
            \see Column
            \see setColumn
        */
		Column getColumn(const uint32_t aIndex) const throw() {
		    Column tmp;
			for(uint32_t i = 0; i < Height; ++i) {
				tmp[i] = mData[i * Width + aIndex];
			}
			return tmp;
		}

        /*!
            \brief Set a Row of this Matrix.
            \brief aIndex The index of the Row to set.
            \brief aRow The value to set the Row to.
            \see Row
            \see getRow
        */
		void setRow(const uint32_t aIndex, const Row aRow) throw() {
			std::memcpy(mData + Width * aIndex, aRow.Ptr(), sizeof(Scalar) * Width);
		}

        /*!
            \brief Set a Column of this Matrix.
            \brief aIndex The index of the Column to set.
            \brief aColumn The value to set the column to.
            \see Column
            \see getColumn
        */
		void setColumn(const uint32_t aIndex, const Column aColumn) throw() {
			for(uint32_t i = 0; i < Height; ++i) {
				mData[i * Width + aIndex] = aColumn[i];
			}
		}

		Matrix<Scalar, Height, Width> Inverse() const throw() {
			//! \todo Implement matrix inversion
			return Matrix<Scalar, Height, Width>();
		}

        /*!
            \brief Rotate this Matrix by 90 degrees.
        */
		Matrix<Scalar, Height, Width> transpose() const throw() {
			Matrix<Scalar, Height, Width> tmp;
			for(uint32_t i = 0; i < Width; ++i) {
				tmp.setColumn(i, getRow(i));
			}
			return tmp;
		}
	};

    // Matrix / Vector
    //! \todo Implement matrix / vector maths

    // Vector / Matrix
    //! \todo Implement vector / matrix maths

    // Typedefs

	template<class T>
	using Matrix2 = Matrix<T, 2, 2>;            //!< A 2x2 Matrix.

	template<class T>
	using Matrix3 = Matrix<T, 3, 3>;            //!< A 3x3 Matrix.

	template<class T>
	using Matrix4 = Matrix<T, 4, 4>;            //!< A 4x4 Matrix.

	typedef Matrix2<uint8_t>	Matrix2U8;      //!< A 2x2 Matrix using unsigned 8 bit scalars.
	typedef Matrix2<int8_t>		Matrix2I8;      //!< A 2x2 Matrix using signed 8 bit scalars.
	typedef Matrix2<uint16_t>	Matrix2U16;     //!< A 2x2 Matrix using unsigned 16 bit scalars.
	typedef Matrix2<int16_t>	Matrix2I16;     //!< A 2x2 Matrix using signed 16 bit scalars.
	typedef Matrix2<uint32_t>	Matrix2U32;     //!< A 2x2 Matrix using unsigned 32 bit scalars.
	typedef Matrix2<int32_t>	Matrix2I32;     //!< A 2x2 Matrix using signed 32 bit scalars.
	typedef Matrix2<uint64_t>	Matrix2U64;     //!< A 2x2 Matrix using unsigned 64 bit scalars.
	typedef Matrix2<int64_t>	Matrix2I64;     //!< A 2x2 Matrix using signed 64 bit scalars.
	typedef Matrix2<float>		Matrix2F;       //!< A 2x2 Matrix using single precision scalars.
	typedef Matrix2<double>		Matrix2D;       //!< A 2x2 Matrix using double precision scalars.

	typedef Matrix3<uint8_t>	Matrix3U8;      //!< A 3x3 Matrix using unsigned 8 bit scalars.
	typedef Matrix3<int8_t>		Matrix3I8;      //!< A 3x3 Matrix using signed 8 bit scalars.
	typedef Matrix3<uint16_t>	Matrix3U16;     //!< A 3x3 Matrix using unsigned 16 bit scalars.
	typedef Matrix3<int16_t>	Matrix3I16;     //!< A 3x3 Matrix using signed 16 bit scalars.
	typedef Matrix3<uint32_t>	Matrix3U32;     //!< A 3x3 Matrix using unsigned 32 bit scalars.
	typedef Matrix3<int32_t>	Matrix3I32;     //!< A 3x3 Matrix using signed 32 bit scalars.
	typedef Matrix3<uint64_t>	Matrix3U64;     //!< A 3x3 Matrix using unsigned 64 bit scalars.
	typedef Matrix3<int64_t>	Matrix3I64;     //!< A 3x3 Matrix using signed 64 bit scalars.
	typedef Matrix3<float>		Matrix3F;       //!< A 3x3 Matrix using single precision scalars.
	typedef Matrix3<double>		Matrix3D;       //!< A 3x3 Matrix using double precision scalars.

	typedef Matrix4<uint8_t>	Matrix4U8;      //!< A 4x4 Matrix using unsigned 8 bit scalars.
	typedef Matrix4<int8_t>		Matrix4I8;      //!< A 4x4 Matrix using signed 8 bit scalars.
	typedef Matrix4<uint16_t>	Matrix4U16;     //!< A 4x4 Matrix using unsigned 16 bit scalars.
	typedef Matrix4<int16_t>	Matrix4I16;     //!< A 4x4 Matrix using signed 16 bit scalars.
	typedef Matrix4<uint32_t>	Matrix4U32;     //!< A 4x4 Matrix using unsigned 32 bit scalars.
	typedef Matrix4<int32_t>	Matrix4I32;     //!< A 4x4 Matrix using signed 32 bit scalars.
	typedef Matrix4<uint64_t>	Matrix4U64;     //!< A 4x4 Matrix using unsigned 64 bit scalars.
	typedef Matrix4<int64_t>	Matrix4I64;     //!< A 4x4 Matrix using signed 64 bit scalars.
	typedef Matrix4<float>		Matrix4F;       //!< A 4x4 Matrix using single precision scalars.
	typedef Matrix4<double>		Matrix4D;       //!< A 4x4 Matrix using double precision scalars.
}

#include "Matrix.inl"

#endif
