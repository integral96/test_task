#pragma once

#include <type_traits>
#include <unordered_set>
#include <iostream>
#include <array>
#include <thread>
#include <mutex>

/*!
* struct numbers a(i, j, k, ...)
*/
struct numbers {
     int A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12;
     numbers(int a0, int a1, int a2, int a3, int a4,
                      int a5, int a6, int a7, int a8, int a9,
                      int a10, int a11, int a12) :
                      A0(a0), A1(a1), A2(a2), A3(a3), A4(a4), A5(a5),
                      A6(a6), A7(a7), A8(a8), A9(a9), A10(a10), A11(a11), A12(a12) {}

    inline bool operator == (const numbers& num) const {
         return A0 == num.A0 && A1 == num.A1 && A2 == num.A2 && A3 == num.A3 &&
                A4 == num.A4 && A5 == num.A5 && A6 == num.A6 && A7 == num.A7 &&
                A8 == num.A8 && A9 == num.A9 && A10 == num.A10 && A11 == num.A11
                && A12 == num.A12;
    }
};
/*!
* Hash for set
*/
struct TenzorHush {
    inline size_t operator()(const numbers& num) const {
        return (std::hash<int>()(num.A0))^(std::hash<int>()(num.A1))^(std::hash<int>()(num.A2))^
               (std::hash<int>()(num.A3))^(std::hash<int>()(num.A4))^(std::hash<int>()(num.A5))^
               (std::hash<int>()(num.A6))^(std::hash<int>()(num.A7))^(std::hash<int>()(num.A8))^
               (std::hash<int>()(num.A9))^(std::hash<int>()(num.A10))^(std::hash<int>()(num.A11))^
               (std::hash<int>()(num.A12));
    }
};

typedef std::unordered_set<numbers, TenzorHush> Tenzor_type;

/*!
 * struct meta_loop
 */
template <size_t N, size_t I, class Closure>
typename std::enable_if_t<(I == N)> is_meta_loop(Closure& closure) {}

template <size_t N, size_t I, class Closure>
typename std::enable_if_t<(I < N)> is_meta_loop(Closure& closure) {
    closure.template apply<I>();
    is_meta_loop<N, I + 1>(closure);
}
template <size_t N, class Closure>
void meta_loop(Closure& closure) {
    is_meta_loop<N, 0>(closure);
}


/*!
* struct Tenzor
*/
template<size_t A0, size_t A1, size_t A2, size_t A3, size_t A4, size_t A5, size_t A6,
         size_t A7, size_t A8, size_t A9, size_t A10, size_t A11, typename Set>
struct tenzor_closure_level0 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level0(const Set& set_, size_t count) : set(set_), count(count) {}
    template<size_t A12>
    void apply() const {
        if constexpr (A0 + A1 + A2 + A3 + A4 + A5 == A7 + A8 + A9 + A10 + A11 + A12) {
            count + 1;
        }
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, size_t A3, size_t A4, size_t A5, size_t A6,
          size_t A7, size_t A8, size_t A9, size_t A10, typename Set>
struct tenzor_closure_level1 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level1(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A11>
    void apply() {
        tenzor_closure_level0<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, size_t A3, size_t A4, size_t A5, size_t A6,
          size_t A7, size_t A8, size_t A9, typename Set>
struct tenzor_closure_level2 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level2(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A10>
    void apply() {
        tenzor_closure_level1<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, size_t A3, size_t A4, size_t A5, size_t A6,
          size_t A7, size_t A8, typename Set>
struct tenzor_closure_level3 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level3(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A9>
    void apply() {
        tenzor_closure_level2<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, size_t A3, size_t A4, size_t A5, size_t A6,
          size_t A7, typename Set>
struct tenzor_closure_level4 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level4(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A8>
    void apply() {
        tenzor_closure_level3<A0, A1, A2, A3, A4, A5, A6, A7, A8, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, size_t A3, size_t A4, size_t A5, size_t A6,
          typename Set>
struct tenzor_closure_level5 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level5(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A7>
    void apply() {
        tenzor_closure_level4<A0, A1, A2, A3, A4, A5, A6, A7, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, size_t A3, size_t A4, size_t A5, typename Set>
struct tenzor_closure_level6 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level6(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A6>
    void apply() {
        tenzor_closure_level5<A0, A1, A2, A3, A4, A5, A6, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, size_t A3, size_t A4, typename Set>
struct tenzor_closure_level7 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level7(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A5>
    void apply() {
        tenzor_closure_level6<A0, A1, A2, A3, A4, A5, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, size_t A3, typename Set>
struct tenzor_closure_level8 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level8(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A4>
    void apply() {
        tenzor_closure_level7<A0, A1, A2, A3, A4, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, size_t A2, typename Set>
struct tenzor_closure_level9 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level9(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A3>
    void apply() {
        tenzor_closure_level8<A0, A1, A2, A3, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, size_t A1, typename Set>
struct tenzor_closure_level10 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level10(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A2>
    void apply() {
        tenzor_closure_level9<A0, A1, A2, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <size_t A0, typename Set>
struct tenzor_closure_level11 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level11(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A1>
    void apply() {
        tenzor_closure_level10<A0, A1, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <typename Set>
struct tenzor_closure_level12 {
private:
    const Set& set;
    size_t count;
public:
    tenzor_closure_level12(const Set& set_, size_t count) : set(set_), count(count) {}
    template <size_t A0>
    void apply() {
        tenzor_closure_level11<A0, Set> closure(set, count);
        meta_loop<N>(closure);
    }
};
//=================================================================================
template <typename Set>
void calc_tenzor(const Set& set, size_t count) {
    tenzor_closure_level12<Set> closure(set, count);
    meta_loop<N>(closure);
}
