#ifndef MATN_HPP
#define MATN_HPP

#include"matnxm.hpp"

// Square matrix struct
template <typename T, int N>
struct tmatnxm<T,N,N> {
    T data[N*N];
    tmatnxm() {}
    template <typename S>
    tmatnxm(const tmatnxm<S,N,N> &m) {
        for(int i = 0; i < N*N; ++i) {
            data[i] = static_cast<T>(m.data[i]);
        }
    }
    template <typename S>
    tmatnxm(const S *p, int dy = 0, int dx = 1) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                data[i*N + j] = static_cast<T>(p[(dx*N + dy)*i + dx*j]);
            }
        }
    }
    template <typename S>
    tmatnxm(S diag) {
        for(int iy = 0; iy < N; ++iy) {
            for(int ix = 0; ix < N; ++ix) {
                if(ix == iy) {
                    (*this)(ix,iy) = static_cast<T>(diag);
                } else {
                    (*this)(ix,iy) = static_cast<T>(0);
                }
            }
        }
    }
    template <typename S>
    tmatnxm<T,N,N> &operator =(const tmatnxm<S,N,N> &m) {
        for(int i = 0; i < N*N; ++i) {
            data[i] = static_cast<T>(m.data[i]);
        }
        return *this;
    }
    //Access operators
    T &operator ()(int x, int y) {
        return data[y*N + x];
    }
    T operator ()(int x, int y) const {
        return data[y*N + x];
    }
    T &operator ()(const tvecn<int,2> &v) {
        return data[v(1)*N + v(0)];
    }
    T operator ()(const tvecn<int,2> &v) const {
        return data[v(1)*N + v(0)];
    }
    tvecn<T,N> row(int n) const {
        return tvecn<T,N>(data + n*N);
    }
    tvecn<T,N> col(int n) const {
        return tvecn<T,N>(data + n, N);
    }
    tmatnxm<T,N,N> t() const {
        return tmatnxm<T,N,N>(data,-N*N+1,N);
    }
    //Submatrix
    tmatnxm<T,N-1,N-1> sub(int x, int y) const {
        tmatnxm<T,N-1,N-1> c;
        for(int ix = 0, jx = 0; ix < N; ++ix,++jx) {
            if(ix == x) {
                --jx;
                continue;
            }
            for(int iy = 0, jy = 0; iy < N; ++iy,++jy) {
                if(iy == y) {
                    --jy;
                    continue;
                }
                c(jx,jy) = (*this)(ix,iy);
            }
        }
        return c;
    }
	//Determinant
	T cofactor(int x, int y) {
		return (1 - 2*((x+y)%2))*this->sub(x,y).det();
	}
	T det() {
		if(N <= 1) {
			return *(this->data);
		} else {
			T c = static_cast<T>(0);
			const int rc = 0;
			for(int i = 0; i < N; ++i) {
				c += cofactor(i,rc);
			}
			return c;
		}
	}
};

#endif // MATN_HPP
