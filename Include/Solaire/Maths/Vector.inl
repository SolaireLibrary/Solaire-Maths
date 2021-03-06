#ifndef SOLAIRE_VECTOR_INL
#define SOLAIRE_VECTOR_HPP

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
	\file Vector.inl
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 5th September 2015
	Last Modified	: 8th January 2016
*/

namespace Solaire{

	// Vector / Vector

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length>& operator+=(Vector<Scalar, Length>& aFirst, const Vector<Scalar, Length> aSecond) {
	    for(uint32_t i = 0; i < Length; ++i) {
            aFirst[i] += aSecond[i];
	    }
	    return aFirst;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length>& operator-=(Vector<Scalar, Length>& aFirst, const Vector<Scalar, Length> aSecond) {
	    for(uint32_t i = 0; i < Length; ++i) {
            aFirst[i] -= aSecond[i];
	    }
	    return aFirst;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length>& operator*=(Vector<Scalar, Length>& aFirst, const Vector<Scalar, Length> aSecond) {
	    for(uint32_t i = 0; i < Length; ++i) {
            aFirst[i] *= aSecond[i];
	    }
	    return aFirst;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length>& operator/=(Vector<Scalar, Length>& aFirst, const Vector<Scalar, Length> aSecond) {
	    for(uint32_t i = 0; i < Length; ++i) {
            aFirst[i] /= aSecond[i];
	    }
	    return aFirst;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator+(const Vector<Scalar, Length> aFirst, const Vector<Scalar, Length> aSecond) {
	    Vector<Scalar, Length> tmp;
	    for(uint32_t i = 0; i < Length; ++i) {
            tmp[i] = aFirst[i] + aSecond[i];
	    }
	    return tmp;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator-(const Vector<Scalar, Length> aFirst, const Vector<Scalar, Length> aSecond) {
        Vector<Scalar, Length> tmp;
	    for(uint32_t i = 0; i < Length; ++i) {
            tmp[i] = aFirst[i] - aSecond[i];
	    }
	    return tmp;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator*(const Vector<Scalar, Length> aFirst, const Vector<Scalar, Length> aSecond) {
        Vector<Scalar, Length> tmp;
	    for(uint32_t i = 0; i < Length; ++i) {
            tmp[i] = aFirst[i] * aSecond[i];
	    }
	    return tmp;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator/(const Vector<Scalar, Length> aFirst, const Vector<Scalar, Length> aSecond) {
	    return Vector<Scalar, Length>(aFirst) /= aSecond;
	}

	// Vector / Scalar

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length>& operator+=(Vector<Scalar, Length>& aFirst, const Scalar aSecond) {
	    for(uint32_t i = 0; i < Length; ++i) {
            aFirst[i] += aSecond;
	    }
	    return aFirst;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length>& operator-=(Vector<Scalar, Length>& aFirst, const Scalar aSecond) {
	    for(uint32_t i = 0; i < Length; ++i) {
            aFirst[i] -= aSecond;
	    }
	    return aFirst;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length>& operator*=(Vector<Scalar, Length>& aFirst, const Scalar aSecond) {
	    for(uint32_t i = 0; i < Length; ++i) {
            aFirst[i] *= aSecond;
	    }
	    return aFirst;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length>& operator/=(Vector<Scalar, Length>& aFirst, const Scalar aSecond) {
	    for(uint32_t i = 0; i < Length; ++i) {
            aFirst[i] /= aSecond;
	    }
	    return aFirst;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator+(const Vector<Scalar, Length> aFirst, const Scalar aSecond) {
	    return Vector<Scalar, Length>(aFirst) += aSecond;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator-(const Vector<Scalar, Length> aFirst, const Scalar aSecond) {
	    return Vector<Scalar, Length>(aFirst) -= aSecond;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator*(const Vector<Scalar, Length> aFirst, const Scalar aSecond) {
	    return Vector<Scalar, Length>(aFirst) *= aSecond;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator/(const Vector<Scalar, Length> aFirst, const Scalar aSecond) {
	    return Vector<Scalar, Length>(aFirst) /= aSecond;
	}

	// Scalar / Vector

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator+(const Scalar aFirst, const Vector<Scalar, Length> aSecond) {
	    Vector<Scalar, Length> tmp;
	    for(uint32_t i = 0; i < Length; ++i) {
            tmp[i] = aFirst + aSecond[i];
	    }
	    return tmp;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator-(const Scalar aFirst, const Vector<Scalar, Length> aSecond) {
	    Vector<Scalar, Length> tmp;
	    for(uint32_t i = 0; i < Length; ++i) {
            tmp[i] = aFirst - aSecond[i];
	    }
	    return tmp;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator*(const Scalar aFirst, const Vector<Scalar, Length> aSecond) {
	    Vector<Scalar, Length> tmp;
	    for(uint32_t i = 0; i < Length; ++i) {
            tmp[i] = aFirst * aSecond[i];
	    }
	    return tmp;
	}

	template<class Scalar, const uint32_t Length>
	Vector<Scalar, Length> operator/(const Scalar aFirst, const Vector<Scalar, Length> aSecond) {
	    Vector<Scalar, Length> tmp;
	    for(uint32_t i = 0; i < Length; ++i) {
            tmp[i] = aFirst / aSecond[i];
	    }
	    return tmp;
	}
}


#endif
