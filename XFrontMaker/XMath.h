#pragma once

/****************************************************************************************************************
 *
 *    Brief   : 使用match.h头文件时，abs函数只有int版本。
 *				只有使用cmath时支持函数重载才有float版本abs。
 *
 ****************************************************************************************************************/
#include <cmath>

namespace Smile
{
#define Zero 0
#define One 1
#define PI 3.1415926f
#define ANGLE2RADIAN(angle) ( 2.0f * PI / 360.0f * (angle))

	/****************************************************************************************************************
	*
	*    Brief   : 颜色
	*
	****************************************************************************************************************/
	template<typename T>
	class _BGRA
	{
	public:
		_BGRA() {}
		_BGRA(T b, T g, T r, T a) : _b(b), _g(g), _r(r), _a(a) { }
		_BGRA(unsigned int color) : _color(color) { }

		union
		{
			struct
			{
				T _b;
				T _g;
				T _r;
				T _a;
			};
			unsigned int _color;
		};
	};

	typedef _BGRA<unsigned char> BGRA8U;

	//全局函数
	template<typename T>
	_BGRA<T> operator + (const _BGRA<T>& left, const _BGRA<T>& right)
	{
		return  _BGRA<T>(
			left._b + (255 - left._b) * ((float)right._b / 255),
			left._g + (255 - left._g) * ((float)right._g / 255),
			left._r + (255 - left._r) * ((float)right._r / 255),
			left._a + (255 - left._a) * ((float)right._a / 255)
			);
	}
	
	/****************************************************************************************************************
	 *    Date    : 2017/12/12 14:21
	 *
	 *    Author  : Smile
	 *    Contact : smile@illidan.org
	 *
	 *    Brief   : 2维向量（列）
	 *
	 ****************************************************************************************************************/
	template<typename T>
	class _XVector2
	{
	public:
		_XVector2() {}
		_XVector2(T x, T y) : _x(x), _y(y) {}

		T& operator [] (unsigned int i)
		{
			return _data[i];
		}

		const T& operator [] (unsigned int i) const
		{
			return _data[i];
		}

		_XVector2<T> operator + (const _XVector2<T>& that)
		{
			return _XVector2<T>(_data[0] + that._data[0], _data[1] + that._data[1]);
		}

		_XVector2<T> operator - (const _XVector2<T>& that)
		{
			return _XVector2<T>(_data[0] - that._data[0], _data[1] - that._data[1]);
		}

		_XVector2<T> operator * (const T& factor)
		{
			return _XVector2<T>(_data[0] * factor, _data[1] * factor);
		}

	public:
		union
		{
			struct
			{
				T _x;
				T _y;
			};
			struct
			{
				T _u;
				T _v;
			};
			struct 
			{
				T _w;
				T _h;
			};
			T _data[2];
		};
	};

	typedef _XVector2<float> XVec2f;

	
	/****************************************************************************************************************
	 *    Date    : 2017/12/12 14:21
	 *
	 *    Author  : Smile
	 *    Contact : smile@illidan.org
	 *
	 *    Brief   : 3维向量
	 *
	 ****************************************************************************************************************/
	template<typename T>
	class _XVector3
	{
	public:
		_XVector3() {}
		_XVector3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

		T& operator [] (unsigned int i)
		{
			return _data[i];
		}

		const T& operator [] (unsigned int i) const
		{
			return _data[i];
		}

		_XVector3<T> operator + (const _XVector3<T>& that)
		{
			return _XVector3<T>(_data[0] + that._data[0], _data[1] + that._data[1], _data[2] + that._data[2]);
		}

		_XVector3<T> operator - (const _XVector3<T>& that)
		{
			return _XVector3<T>(_data[0] - that._data[0], _data[1] - that._data[1], _data[2] - that._data[2]);
		}

		_XVector3<T> operator * (T factor)
		{
			return _XVector3<T>(_data[0] * factor, _data[1] * factor, _data[2] * factor);
		}

	public:
		union
		{
			struct
			{
				T _x;
				T _y;
				T _z;
			};
			struct
			{
				T _s;
				T _t;
				T _r;
			};
			T _data[3];
		};
	};

	typedef _XVector3<float> XVec3f;

	
	/****************************************************************************************************************
	 *    Date    : 2017/12/12 14:21
	 *
	 *    Author  : Smile
	 *    Contact : smile@illidan.org
	 *
	 *    Brief   : 4维向量
	 *
	 ****************************************************************************************************************/
	template<typename T>
	class _XVector4
	{
	public:
		_XVector4() {}
		_XVector4(T x, T y, T z, T w) : _x(x), _y(y), _z(z), _w(w) {}

		T& operator [] (unsigned int i)
		{
			return _data[i];
		}

		const T& operator [] (unsigned int i) const
		{
			return _data[i];
		}

		_XVector4<T> operator + (const _XVector4<T>& that)
		{
			return _XVector4<T>(_data[0] + that._data[0], _data[1] + that._data[1], _data[2] + that._data[2], _data[3] + that._data[3]);
		}

		_XVector4<T> operator - (const _XVector4<T>& that)
		{
			return _XVector4<T>(_data[0] - that._data[0], _data[1] - that._data[1], _data[2] - that._data[2], _data[3] - that._data[3]);
		}

		_XVector4<T> operator * (const T& factor)
		{
			return _XVector4<T>(_data[0] * factor, _data[1] * factor, _data[2] * factor, _data[3] * factor);
		}

	public:
		union
		{
			struct  
			{
				T _x;
				T _y;
				T _z;
				T _w;
			};
			T _data[4];
		};
	};

	typedef _XVector4<float> XVec4f;


	/****************************************************************************************************************
	 *    Date    : 2017/12/12 14:20
	 *
	 *    Author  : Smile
	 *    Contact : smile@illidan.org
	 *
	 *    Brief   : 3维矩阵
	 *
	 ****************************************************************************************************************/
	template<typename T>
	class _XMatrix3
	{
	public:
		typedef _XVector3<T> _ColType;

		_XMatrix3()
		{
			_col[0] = _ColType(One, Zero, Zero);
			_col[1] = _ColType(Zero, One, Zero);
			_col[2] = _ColType(Zero, Zero, One);
		}

		_XMatrix3(T value)
		{
			_col[0] = _ColType(value, Zero, Zero);
			_col[1] = _ColType(Zero, value, Zero);
			_col[2] = _ColType(Zero, Zero, value);
		}

		_XMatrix3(T value11, T value12, T value13, T value21, T value22, T value23, T value31, T value32, T value33)
		{
			_col[0] = _ColType(value11, value12, value13);
			_col[1] = _ColType(value21, value22, value23);
			_col[2] = _ColType(value31, value32, value33);
		}

		_XMatrix3(const _XMatrix3<T>& that)
		{
			_col[0] = _ColType(that._col[0]);
			_col[1] = _ColType(that._col[1]);
			_col[2] = _ColType(that._col[2]);
		}

		_ColType& operator [] (unsigned int i)
		{
			return _col[i];
		}

		const _ColType& operator [] (unsigned int i) const
		{
			return _col[i];
		}

		_XMatrix3<T> operator * (const T& factor)
		{
			return _XMatrix3<T>
				(
					_col[0][0] * factor, _col[1][0] * factor, _col[2][0] * factor,
					_col[0][1] * factor, _col[1][1] * factor, _col[2][1] * factor,
					_col[0][2] * factor, _col[1][2] * factor, _col[2][2] * factor
					);
		}

		_XVector3<T> operator * (const _XVector3<T>& vector)
		{
			return _XVector3<T>
			(
				_col[0][0] * vector[0] + _col[1][0] * vector[1] + _col[2][0] * vector[2],
				_col[0][1] * vector[0] + _col[1][1] * vector[1] + _col[2][1] * vector[2],
				_col[0][2] * vector[0] + _col[1][2] * vector[1] + _col[2][2] * vector[2]
			);
		}

		_XMatrix3<T> operator * (const _XMatrix3<T>& matrix)
		{
			return _XMatrix3<T>
			(
				_col[0][0] * matrix._col[0][0] + _col[1][0] * matrix._col[0][1] + _col[2][0] * matrix._col[0][2],
				_col[0][1] * matrix._col[0][0] + _col[1][1] * matrix._col[0][1] + _col[2][1] * matrix._col[0][2],
				_col[0][2] * matrix._col[0][0] + _col[1][2] * matrix._col[0][1] + _col[2][2] * matrix._col[0][2],

				_col[0][0] * matrix._col[1][0] + _col[1][0] * matrix._col[1][1] + _col[2][0] * matrix._col[1][2],
				_col[0][1] * matrix._col[1][0] + _col[1][1] * matrix._col[1][1] + _col[2][1] * matrix._col[1][2],
				_col[0][2] * matrix._col[1][0] + _col[1][2] * matrix._col[1][1] + _col[2][2] * matrix._col[1][2],

				_col[0][0] * matrix._col[2][0] + _col[1][0] * matrix._col[2][1] + _col[2][0] * matrix._col[2][2],
				_col[0][1] * matrix._col[2][0] + _col[1][1] * matrix._col[2][1] + _col[2][1] * matrix._col[2][2],
				_col[0][2] * matrix._col[2][0] + _col[1][2] * matrix._col[2][1] + _col[2][2] * matrix._col[2][2],
			);
		}

		void Scale(T x, T y)
		{
			_col[0][0] = x;
			_col[1][1] = y;
		}

		void Rotate(T angle)
		{
			T rad = ANGLE2RADIAN(angle);
			T c = cosf(rad);
			T s = sinf(rad);
			_col[0][0] = c;
			_col[0][1] = -s;
			_col[1][0] = s;
			_col[1][1] = c;
		}

		void Translate(T x, T y)
		{
			_col[0][2] = x;
			_col[1][2] = y;
		}

		_XMatrix3<T> Transpose()
		{
			return _XMatrix3<T>
			(
				_col[0][0], _col[1][0], _col[2][0],
				_col[0][1], _col[1][1], _col[2][1],
				_col[0][2], _col[1][2], _col[2][2]
			);
		}

	private:
		_ColType _col[3];
	};

	typedef _XMatrix3<float> XMat3f;


	/****************************************************************************************************************
	 *    Date    : 2017/12/12 14:20
	 *
	 *    Author  : Smile
	 *    Contact : smile@illidan.org
	 *
	 *    Brief   : 4维矩阵
	 *
	 ****************************************************************************************************************/
	template<typename T>
	class _XMatrix4
	{
	public:
		typedef _XVector4<T> _colType;

		_XMatrix4() 
		{
			_col[0] = _colType(One, Zero, Zero, Zero);
			_col[1] = _colType(Zero, One, Zero, Zero);
			_col[2] = _colType(Zero, Zero, One, Zero);
			_col[3] = _colType(Zero, Zero, Zero, One);
		}

		_XMatrix4(T value)
		{
			_col[0] = _colType(value, Zero, Zero, Zero);
			_col[1] = _colType(Zero, value, Zero, Zero);
			_col[2] = _colType(Zero, Zero, value, Zero);
			_col[3] = _colType(Zero, Zero, Zero, value);
		}

		_XMatrix4(T value11, T value12, T value13, T value14,
			T value21, T value22, T value23, T value24,
			T value31, T value32, T value33, T value34,
			T value41, T value42, T value43, T value44)
		{
			_col[0] = _colType(value11, value12, value13, value14);
			_col[1] = _colType(value21, value22, value23, value24);
			_col[2] = _colType(value31, value32, value33, value34);
			_col[3] = _colType(value41, value42, value43, value44);
		}

		_XMatrix4(const _XMatrix4<T>& that)
		{
			_col[0] = _colType(that._col[0]);
			_col[1] = _colType(that._col[1]);
			_col[2] = _colType(that._col[2]);
			_col[3] = _colType(that._col[3]);
		}

		_colType& operator [] (unsigned int i)
		{
			return _col[i];
		}

		const _colType& operator [] (unsigned int i) const
		{
			return _col[i];
		}

		_XMatrix4<T> operator * (const T& factor)
		{
			return _XMatrix4<T>
			(
				_col[0][0] * factor, _col[0][1] * factor, _col[0][2] * factor, _col[0][3] * factor,
				_col[0][1] * factor, _col[1][1] * factor, _col[1][2] * factor, _col[1][3] * factor,
				_col[0][2] * factor, _col[2][1] * factor, _col[2][2] * factor, _col[2][3] * factor,
				_col[0][3] * factor, _col[3][1] * factor, _col[3][2] * factor, _col[3][3] * factor
			);
		}

		_XVector4<T> operator * (const _XVector4<T>& vector)
		{
			return _XVector4<T>
			(
				_col[0][0] * vector[0] + _col[1][0] * vector[1] + _col[2][0] * vector[2] + _col[3][0] * vector[3],
				_col[0][1] * vector[0] + _col[1][1] * vector[1] + _col[2][1] * vector[2] + _col[3][1] * vector[3],
				_col[0][2] * vector[0] + _col[1][2] * vector[1] + _col[2][2] * vector[2] + _col[3][2] * vector[3],
				_col[0][3] * vector[0] + _col[1][3] * vector[1] + _col[2][3] * vector[2] + _col[3][3] * vector[3]
			);
		}

		_XMatrix4<T> operator * (const _XMatrix4<T>& matrix)
		{
			return _XMatrix4<T>
			{
				_col[0][0] * matrix._col[0][0] + _col[1][0] * matrix._col[0][1] + _col[2][0] * matrix._col[0][2] + _col[3][0] * matrix._col[0][3],
				_col[0][1] * matrix._col[0][0] + _col[1][1] * matrix._col[0][1] + _col[2][1] * matrix._col[0][2] + _col[3][1] * matrix._col[0][3],
				_col[0][2] * matrix._col[0][0] + _col[1][2] * matrix._col[0][1] + _col[2][2] * matrix._col[0][2] + _col[3][2] * matrix._col[0][3],
				_col[0][3] * matrix._col[0][0] + _col[1][3] * matrix._col[0][1] + _col[2][3] * matrix._col[0][2] + _col[3][3] * matrix._col[0][3],

				_col[0][0] * matrix._col[1][0] + _col[1][0] * matrix._col[1][1] + _col[2][0] * matrix._col[1][2] + _col[3][0] * matrix._col[1][3],
				_col[0][1] * matrix._col[1][0] + _col[1][1] * matrix._col[1][1] + _col[2][1] * matrix._col[1][2] + _col[3][1] * matrix._col[1][3],
				_col[0][2] * matrix._col[1][0] + _col[1][2] * matrix._col[1][1] + _col[2][2] * matrix._col[1][2] + _col[3][2] * matrix._col[1][3],
				_col[0][3] * matrix._col[1][0] + _col[1][3] * matrix._col[1][1] + _col[2][3] * matrix._col[1][2] + _col[3][3] * matrix._col[1][3],

				_col[0][0] * matrix._col[2][0] + _col[1][0] * matrix._col[2][1] + _col[2][0] * matrix._col[2][2] + _col[3][0] * matrix._col[2][3],
				_col[0][1] * matrix._col[2][0] + _col[1][1] * matrix._col[2][1] + _col[2][1] * matrix._col[2][2] + _col[3][1] * matrix._col[2][3],
				_col[0][2] * matrix._col[2][0] + _col[1][2] * matrix._col[2][1] + _col[2][2] * matrix._col[2][2] + _col[3][2] * matrix._col[2][3],
				_col[0][3] * matrix._col[2][0] + _col[1][3] * matrix._col[2][1] + _col[2][3] * matrix._col[2][2] + _col[3][3] * matrix._col[2][3],

				_col[0][0] * matrix._col[3][0] + _col[1][0] * matrix._col[3][1] + _col[2][0] * matrix._col[3][2] + _col[3][0] * matrix._col[3][3],
				_col[0][1] * matrix._col[3][0] + _col[1][1] * matrix._col[3][1] + _col[2][1] * matrix._col[3][2] + _col[3][1] * matrix._col[3][3],
				_col[0][2] * matrix._col[3][0] + _col[1][2] * matrix._col[3][1] + _col[2][2] * matrix._col[3][2] + _col[3][2] * matrix._col[3][3],
				_col[0][3] * matrix._col[3][0] + _col[1][3] * matrix._col[3][1] + _col[2][3] * matrix._col[3][2] + _col[3][3] * matrix._col[3][3]
				
			};
		}

		_XMatrix4<T> Inverse() const
		{
			T subFactor00 = this->_col[2][2] * this->_col[3][3] - this->_col[3][2] * this->_col[2][3];
			T subFactor01 = this->_col[2][1] * this->_col[3][3] - this->_col[3][1] * this->_col[2][3];
			T subFactor02 = this->_col[2][1] * this->_col[3][2] - this->_col[3][1] * this->_col[2][2];
			T subFactor03 = this->_col[2][0] * this->_col[3][3] - this->_col[3][0] * this->_col[2][3];
			T subFactor04 = this->_col[2][0] * this->_col[3][2] - this->_col[3][0] * this->_col[2][2];
			T subFactor05 = this->_col[2][0] * this->_col[3][1] - this->_col[3][0] * this->_col[2][1];
			T subFactor06 = this->_col[1][2] * this->_col[3][3] - this->_col[3][2] * this->_col[1][3];
			T subFactor07 = this->_col[1][1] * this->_col[3][3] - this->_col[3][1] * this->_col[1][3];
			T subFactor08 = this->_col[1][1] * this->_col[3][2] - this->_col[3][1] * this->_col[1][2];
			T subFactor09 = this->_col[1][0] * this->_col[3][3] - this->_col[3][0] * this->_col[1][3];
			T subFactor10 = this->_col[1][0] * this->_col[3][2] - this->_col[3][0] * this->_col[1][2];
			T subFactor11 = this->_col[1][1] * this->_col[3][3] - this->_col[3][1] * this->_col[1][3];
			T SubFactor12 = this->_col[1][0] * this->_col[3][1] - this->_col[3][0] * this->_col[1][1];
			T subFactor13 = this->_col[1][2] * this->_col[2][3] - this->_col[2][2] * this->_col[1][3];
			T subFactor14 = this->_col[1][1] * this->_col[2][3] - this->_col[2][1] * this->_col[1][3];
			T subFactor15 = this->_col[1][1] * this->_col[2][2] - this->_col[2][1] * this->_col[1][2];
			T subFactor16 = this->_col[1][0] * this->_col[2][3] - this->_col[2][0] * this->_col[1][3];
			T subFactor17 = this->_col[1][0] * this->_col[2][2] - this->_col[2][0] * this->_col[1][2];
			T subFactor18 = this->_col[1][0] * this->_col[2][1] - this->_col[2][0] * this->_col[1][1];

			_XMatrix4<T> res(
				+ this->_col[1][1] * subFactor00 - this->_col[1][2] * subFactor01 + this->_col[1][3] * subFactor02,
				- this->_col[1][0] * subFactor00 + this->_col[1][2] * subFactor03 - this->_col[1][3] * subFactor04,
				+ this->_col[1][0] * subFactor01 - this->_col[1][1] * subFactor03 + this->_col[1][3] * subFactor05,
				- this->_col[1][0] * subFactor02 + this->_col[1][1] * subFactor04 - this->_col[1][2] * subFactor05,
					   																	 
				- this->_col[0][1] * subFactor00 + this->_col[0][2] * subFactor01 - this->_col[0][3] * subFactor02,
				+ this->_col[0][0] * subFactor00 - this->_col[0][2] * subFactor03 + this->_col[0][3] * subFactor04,
				- this->_col[0][0] * subFactor01 + this->_col[0][1] * subFactor03 - this->_col[0][3] * subFactor05,
				+ this->_col[0][0] * subFactor02 - this->_col[0][1] * subFactor04 + this->_col[0][2] * subFactor05,
					   																	 
				+ this->_col[0][1] * subFactor06 - this->_col[0][2] * subFactor07 + this->_col[0][3] * subFactor08,
				- this->_col[0][0] * subFactor06 + this->_col[0][2] * subFactor09 - this->_col[0][3] * subFactor10,
				+ this->_col[0][0] * subFactor11 - this->_col[0][1] * subFactor09 + this->_col[0][3] * SubFactor12,
				- this->_col[0][0] * subFactor08 + this->_col[0][1] * subFactor10 - this->_col[0][2] * SubFactor12,
					   																	 
				- this->_col[0][1] * subFactor13 + this->_col[0][2] * subFactor14 - this->_col[0][3] * subFactor15,
				+ this->_col[0][0] * subFactor13 - this->_col[0][2] * subFactor16 + this->_col[0][3] * subFactor17,
				- this->_col[0][0] * subFactor14 + this->_col[0][1] * subFactor16 - this->_col[0][3] * subFactor18,
				+ this->_col[0][0] * subFactor15 - this->_col[0][1] * subFactor17 + this->_col[0][2] * subFactor18
			);

			T determinant =
				+ this->_col[0][0] * res[0][0]
				+ this->_col[0][1] * res[1][0]
				+ this->_col[0][2] * res[2][0]
				+ this->_col[0][3] * res[3][0];

			res = res * (1.0f / determinant);
			return res;
		}

		void Scale(T x, T y, T z)
		{
			_col[0][0] = x;
			_col[1][1] = y;
			_col[2][2] = z;
		}

		void Rotate(T angle, _XVector3<T> vector)
		{
			T rad = ANGLE2RADIAN(angle);
			T c = cosf(rad);
			T s = sinf(rad);
			_col[0][0] = (vector._x * vector._x + (vector._y * vector._y + vector._z * vector._z) * c)														/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
			_col[0][1] = (vector._x * vector._y * (1 - c) + vector._z * sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z) * s)	/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
			_col[0][2] = (vector._x * vector._z * (1 - c) - vector._y * sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z) * s)	/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
			
			_col[1][0] = (vector._x * vector._y * (1 - c) - vector._z * sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z) * s)	/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
			_col[1][1] = (vector._y * vector._y + (vector._x * vector._x + vector._z * vector._z) * c)														/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
			_col[1][2] = (vector._y * vector._z * (1 - c) + vector._x * sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z) * s)	/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);

			_col[2][0] = (vector._x * vector._z * (1 - c) + vector._y * sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z) * s)	/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
			_col[2][1] = (vector._y * vector._z * (1 - c) - vector._x * sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z) * s)	/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
			_col[2][2] = (vector._z * vector._z + (vector._x * vector._x + vector._y * vector._y) * c)														/ (vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
		}

		void Translate(T x, T y, T z)
		{
			_col[0][3] = x;
			_col[1][3] = y;
			_col[2][3] = z;
		}

		_XMatrix4<T> Transpose()
		{
			return _XMatrix4<T>
			(
				_col[0][0], _col[1][0], _col[2][0], _col[3][0],
				_col[0][1], _col[1][1], _col[2][1], _col[3][1],
				_col[0][2], _col[1][2], _col[2][2], _col[3][2],
				_col[0][3], _col[1][3], _col[2][3], _col[3][3]
			);
		}

		T* GetData() { return &_col[0][0]; }

	private:
		_colType _col[4];
	};

	typedef _XMatrix4<float> XMat4f;


	/****************************************************************************************************************
	 *    Date    : 2017/12/14 14:27
	 *
	 *    Author  : Smile
	 *    Contact : smile@illidan.org
	 *
	 *    Brief   : 射线类
	 *
	 ****************************************************************************************************************/
	template<typename T>
	class _XRay
	{
	public:
		_XRay() {}
		_XRay(_XVector3<T> origin, _XVector3<T> dir) { _origin = origin, _dir = dir; }

		_XVector3<T> GetPoint(T time) { return _origin + _dir * time; }

		_XVector3<T> GetOrigin() { return _origin; }
		_XVector3<T> GetDir() { return _dir; }

	private:
		_XVector3<T> _origin;
		_XVector3<T> _dir;
	};

	typedef _XRay<float> XRayf;

	/****************************************************************************************************************
	*    Date    : 2017/12/12 14:19
	*
	*    Author  : Smile
	*    Contact : smile@illidan.org
	*
	*    Brief   : 平面抽象
	*
	****************************************************************************************************************/
	template<typename T>
	class _XPlane
	{
	public:
		_XPlane() {}
		_XPlane(T a, T b, T c, T d) : _a(a), _b(b), _c(c), _d(d) {}

		T Compute(T x, T y, T z)
		{
			return _a * x + _b * y + _c * z + _d;
		}

		T Compute(_XVector3<T> vector)
		{
			return _a * vector._x + _b * vector._y + _c * vector._z + _d;
		}

	public:
		union
		{
			struct
			{
				T _a;
				T _b;
				T _c;
				T _d;
			};
			T _data[4];
		};

	};

	typedef _XPlane<float> XPlanef;


	/****************************************************************************************************************
	*    Date    : 2017/12/12 14:19
	*
	*    Author  : Smile
	*    Contact : smile@illidan.org
	*
	*    Brief   : 视椎体抽象
	*
	****************************************************************************************************************/
	template<typename T>
	class _XFrustum
	{
	private:
		enum
		{
			TopFace = 0,
			DownFace = 1,
			LeftFace = 2,
			RightFace = 3,
			FrontFace = 4,
			BackFace = 5
		};

	public:
		_XFrustum() {}

		void Init(_XMatrix4<T> pvMat)
		{
			_planes[TopFace] = _XPlane<T>(pvMat[0][3] - pvMat[0][1], pvMat[1][3] - pvMat[1][1], pvMat[2][3] - pvMat[2][1], pvMat[3][3] - pvMat[3][1]);
			_planes[DownFace] = _XPlane<T>(pvMat[0][3] + pvMat[0][1], pvMat[1][3] + pvMat[1][1], pvMat[2][3] + pvMat[2][1], pvMat[3][3] + pvMat[3][1]);

			_planes[LeftFace] = _XPlane<T>(pvMat[0][3] + pvMat[0][0], pvMat[1][3] + pvMat[1][0], pvMat[2][3] + pvMat[2][0], pvMat[3][3] + pvMat[3][0]);
			_planes[RightFace] = _XPlane<T>(pvMat[0][3] - pvMat[0][0], pvMat[1][3] - pvMat[1][0], pvMat[2][3] - pvMat[2][0], pvMat[3][3] - pvMat[3][0]);

			_planes[FrontFace] = _XPlane<T>(pvMat[0][3] - pvMat[0][2], pvMat[1][3] - pvMat[1][2], pvMat[2][3] - pvMat[2][2], pvMat[3][3] - pvMat[3][2]);
			_planes[BackFace] = _XPlane<T>(pvMat[0][3] + pvMat[0][2], pvMat[1][3] + pvMat[1][2], pvMat[2][3] + pvMat[2][2], pvMat[3][3] + pvMat[3][2]);
		}

		bool PointInFrustum(_XVector3<T> point)
		{
			for (int i = TopFace; i <= BackFace; ++i)
			{
				if (_planes[i].Compute(point) < 0)
					return false;
			}
			return true;
		}

	private:
		_XPlane<T> _planes[6];
	};

	typedef _XFrustum<float> XFrustumf;

	/****************************************************************************************************************
	 *
	 *    Brief   : Point
	 *
	 ****************************************************************************************************************/
	template<typename T>
	class _XPoint
	{
	public:
		_XPoint() {}
		_XPoint(T x, T y) : _x(x), _y(y) {}

		struct 
		{
			T _x;
			T _y;
		};
	};

	typedef _XPoint<float> XPointf;

	/****************************************************************************************************************
	*
	*    Brief   : Rect
	*
	****************************************************************************************************************/
	template<typename T>
	class _XRect
	{
	public:
		_XRect() {}
		_XRect(T x, T y, T w, T h) : _x(x), _y(y), _w(w), _h(h) {}

		struct
		{
			T _x;
			T _y;
			T _w;
			T _h;
		};
	};

	typedef _XRect<float> XRectf;

	/****************************************************************************************************************
	 *
	 *    Brief   : 全局函数
	 *
	 ****************************************************************************************************************/
	template<typename T>
	bool PointInRect(_XPoint<T> point, _XRect<T> rect)
	{
		if (point._x < rect._x || point._x > rect._x + rect._w || point._y < rect._y || point._y > rect._y + rect._h)
			return false;

		return true;
	}

	/****************************************************************************************************************
	 *    Date    : 2017/12/12 14:20
	 *
	 *    Author  : Smile
	 *    Contact : smile@illidan.org
	 *
	 *    Brief   : 全局函数
	 *
	 ****************************************************************************************************************/
	template<typename T>
	_XVector3<T> RotateX(const _XVector3<T>& vector, T angle)
	{
		T c = cosf(ANGLE2RADIAN(angle));
		T s = sinf(ANGLE2RADIAN(angle));

		_XVector3<T> res;
		res._x = vector._x;
		res._y = vector._y * c - vector._z * s;
		res._z = vector._y * s + vector._z * c;

		return res;
	}

	template<typename T>
	_XVector3<T> RotateY(const _XVector3<T>& vector, T angle)
	{
		T c = cosf(ANGLE2RADIAN(angle));
		T s = sinf(ANGLE2RADIAN(angle));

		_XVector3<T> res;
		res._x = vector._x * c + vector._z * s;
		res._y = vector._y;
		res._z = -vector._x * s + vector._z * c;

		return res;
	}

	template<typename T>
	_XVector3<T> RotateZ(const _XVector3<T>& vector, T angle)
	{
		T c = cosf(ANGLE2RADIAN(angle));
		T s = sinf(ANGLE2RADIAN(angle));

		_XVector3<T> res;
		res._x = vector._x * c - vector._y * s;
		res._y = vector._x * s + vector._y * c;
		res._z = vector._z;

		return res;
	}

	template<typename T>
	T Length(const _XVector3<T>& vector)
	{
		return sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
	}

	template<typename T>
	_XVector3<T> Normalize(_XVector3<T> vector)
	{
		T sqr = sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
		return _XVector3<T>(vector._x / sqr, vector._y / sqr, vector._z / sqr);
	}

	template<typename T>
	T Dot(_XVector3<T> vector1, _XVector3<T> vector2)
	{
		return vector1._x * vector2._x + vector1._y * vector2._y + vector1._z * vector2._z;
	}

	template<typename T>
	_XVector3<T> Cross(_XVector3<T> vector1, _XVector3<T> vector2)
	{
		return _XVector3<T>
		(
			vector1._y * vector2._z - vector2._y * vector1._z,
			vector1._z * vector2._x - vector2._z * vector1._x,
			vector1._x * vector2._y - vector2._x * vector1._y
		);
	}

	template<typename T>
	_XMatrix4<T> LookAt(_XVector3<T> eye, _XVector3<T> aim, _XVector3<T> up)
	{
		_XVector3<T> u = Normalize<T>(up);

		_XVector3<T> f = Normalize<T>(eye - aim);
		_XVector3<T> r = Normalize<T>(Cross<T>(u, f));
		_XVector3<T> v = Normalize<T>(Cross<T>(f, r));

		_XMatrix4<T> vMatrix(1);

		vMatrix[0][0] = r._x;
		vMatrix[1][0] = r._y;
		vMatrix[2][0] = r._z;
		vMatrix[3][0] = -Dot<T>(r, eye);

		vMatrix[0][1] = v._x;
		vMatrix[1][1] = v._y;
		vMatrix[2][1] = v._z;
		vMatrix[3][1] = -Dot<T>(v, eye);

		vMatrix[0][2] = f._x;
		vMatrix[1][2] = f._y;
		vMatrix[2][2] = f._z;
		vMatrix[3][2] = -Dot<T>(f, eye);

		return vMatrix;
	}

	template<typename T>
	_XMatrix4<T> Perspective(T fovy, T aspect, T zNear, T zFar)
	{
		T range = tanf(ANGLE2RADIAN(fovy * 0.5f)) * zNear;
		T left = -range * aspect;
		T right = range * aspect;
		T bottom = -range;
		T top = range;

		_XMatrix4<T> pMatrix(0);

		pMatrix[0][0] = zNear / right;
		pMatrix[1][1] = zNear / top;
		pMatrix[2][2] = -(zFar + zNear) / (zFar - zNear);
		pMatrix[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
		pMatrix[2][3] = -1.0f;

		return  pMatrix;
	}

	template<typename T>
	void Swap(T& a, T& b)
	{
		T t = a;
		a = b;
		b = t;
	}

	template<typename T>
	T Inverse(const _XMatrix4<T>& mIn, _XMatrix4<T>& mOut)
	{
		_XMatrix4<T> m(mIn);
		int is[4];
		int js[4];
		T fDet = 1.0f;
		T f = 1;

		for (int k = 0; k < 4; k++)
		{
			// 第一步，全选主元
			float fMax = 0.0f;
			for (int i = k; i < 4; i++)
			{
				for (int j = k; j < 4; j++)
				{
					float f = abs(m[i][j]);
					if (f > fMax)
					{
						fMax = f;
						is[k] = i;
						js[k] = j;
					}
				}
			}

			if (abs(fMax) < 0.0001f)
				return 0;

			if (is[k] != k)
			{
				f = -f;
				Swap(m[k][0], m[is[k]][0]);
				Swap(m[k][1], m[is[k]][1]);
				Swap(m[k][2], m[is[k]][2]);
				Swap(m[k][3], m[is[k]][3]);
			}
			if (js[k] != k)
			{
				f = -f;
				Swap(m[0][k], m[0][js[k]]);
				Swap(m[1][k], m[1][js[k]]);
				Swap(m[2][k], m[2][js[k]]);
				Swap(m[3][k], m[3][js[k]]);
			}

			// 计算行列值
			fDet *= m[k][k];

			// 计算逆矩阵

			// 第二步
			m[k][k] = 1.0f / m[k][k];

			// 第三步
			for (int j = 0; j < 4; j++)
			{
				if (j != k)
					m[k][j] *= m[k][k];
			}
			// 第四步
			for (int i = 0; i < 4; i++)
			{
				if (i != k)
				{
					for (int j = 0; j < 4; j++)
					{
						if (j != k)
							m[i][j] = m[i][j] - m[i][k] * m[k][j];
					}
				}
			}
			// 第五步
			for (int i = 0; i < 4; i++)
			{
				if (i != k)
					m[i][k] *= -m[k][k];
			}
		}

		for (int k = 3; k >= 0; k--)
		{
			if (js[k] != k)
			{
				Swap(m[k][0], m[js[k]][0]);
				Swap(m[k][1], m[js[k]][1]);
				Swap(m[k][2], m[js[k]][2]);
				Swap(m[k][3], m[js[k]][3]);
			}
			if (is[k] != k)
			{
				Swap(m[0][k], m[0][is[k]]);
				Swap(m[1][k], m[1][is[k]]);
				Swap(m[2][k], m[2][is[k]]);
				Swap(m[3][k], m[3][is[k]]);
			}
		}

		mOut = m;
		return fDet * f;
	}
}