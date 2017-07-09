/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_UTILS_TEST_HELPERS_H
#define LIBSIMDPP_TEST_UTILS_TEST_HELPERS_H

#include <simdpp/simd.h>
#include <simdpp/detail/align_v128.h>
#include <iostream>
#include "test_results_set.h"
#include "test_reporter.h"
#include <fenv.h>
#include <float.h>


inline void set_round_to_zero()
{
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996) // disable security warning
    _controlfp(_MCW_RC, _RC_CHOP);
#pragma warning(pop)
#else
    ::fesetround(FE_TOWARDZERO);
#endif
#if SIMDPP_USE_SSE2
    _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
#endif
}

inline void set_round_to_nearest()
{
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996) // disable security warning
    _controlfp(_MCW_RC, _RC_NEAR);
#pragma warning(pop)
#else
    ::fesetround(FE_TONEAREST);
#endif
#if SIMDPP_USE_SSE2
    _MM_SET_ROUNDING_MODE(_MM_ROUND_NEAREST);
#endif
}

namespace SIMDPP_ARCH_NAMESPACE {


/*  Certain compilers deduce that we perform tests on constant data and
    precompute the results. We want actual instructions to execute though. This
    class solves the issue by accessing the test data through a volatile
    pointer.
*/
template<class T>
class TestData {
public:

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7, class U8, class U9, class U10,
             class U11, class U12, class U13, class U14, class U15>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7, const U8& u8, const U9& u9, const U10& u10,
             const U11& u11, const U12& u12, const U13& u13, const U14& u14, const U15& u15)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7); add(u8); add(u9); add(u10);
        add(u11); add(u12); add(u13); add(u14); add(u15);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7, class U8, class U9, class U10,
             class U11, class U12, class U13, class U14>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7, const U8& u8, const U9& u9, const U10& u10,
             const U11& u11, const U12& u12, const U13& u13, const U14& u14)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7); add(u8); add(u9); add(u10);
        add(u11); add(u12); add(u13); add(u14);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7, class U8, class U9, class U10,
             class U11, class U12, class U13>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7, const U8& u8, const U9& u9, const U10& u10,
             const U11& u11, const U12& u12, const U13& u13)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7); add(u8); add(u9); add(u10);
        add(u11); add(u12); add(u13);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7, class U8, class U9, class U10,
             class U11, class U12>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7, const U8& u8, const U9& u9, const U10& u10,
             const U11& u11, const U12& u12)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7); add(u8); add(u9); add(u10);
        add(u11); add(u12);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7, class U8, class U9, class U10,
             class U11>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7, const U8& u8, const U9& u9, const U10& u10,
             const U11& u11)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7); add(u8); add(u9); add(u10);
        add(u11);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7, class U8, class U9, class U10>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7, const U8& u8, const U9& u9, const U10& u10)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7); add(u8); add(u9); add(u10);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7, class U8, class U9>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7, const U8& u8, const U9& u9)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7); add(u8); add(u9);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7, class U8>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7, const U8& u8)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7); add(u8);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6, class U7>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6, const U7& u7)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6); add(u7);
    }

    template<class U1, class U2, class U3, class U4, class U5,
             class U6>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5,
             const U6& u6)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
        add(u6);
    }

    template<class U1, class U2, class U3, class U4, class U5>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4, const U5& u5)
    {
        add(u1); add(u2); add(u3); add(u4); add(u5);
    }

    template<class U1, class U2, class U3, class U4>
    TestData(const U1& u1, const U2& u2, const U3& u3, const U4& u4)
    {
        add(u1); add(u2); add(u3); add(u4);
    }

    template<class U1, class U2, class U3>
    TestData(const U1& u1, const U2& u2, const U3& u3)
    {
        add(u1); add(u2); add(u3);
    }

    template<class U1, class U2>
    TestData(const U1& u1, const U2& u2)
    {
        add(u1); add(u2);
    }

    template<class U1>
    TestData(const U1& u1)
    {
        add(u1);
    }

    template<class U>
    void add(const U& u)
    {
        T t = (T) u;
        data_.push_back(t);
        ptr_ = &data_.front();
    }

    unsigned size() const { return data_.size(); }
    const T* data() const { return ptr_; }

private:
    std::vector<T, simdpp::aligned_allocator<T, sizeof(T)> > data_;
    T* volatile ptr_;
};


/*  A bunch of overloads that wrap the TestResultsSet::push() method. The push()
    method accepts a type enum plus a pointer; the wrapper overloads determine
    the type enum from the type of the supplied argument.
*/
inline void test_push_internal(TestResultsSet& t, int8_t data, const char* file, unsigned line)
{
    t.push(TYPE_INT8, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, uint8_t data, const char* file, unsigned line)
{
    t.push(TYPE_UINT8, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, int16_t data, const char* file, unsigned line)
{
    t.push(TYPE_INT16, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, uint16_t data, const char* file, unsigned line)
{
    t.push(TYPE_UINT16, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, int32_t data, const char* file, unsigned line)
{
    t.push(TYPE_INT32, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, uint32_t data, const char* file, unsigned line)
{
    t.push(TYPE_UINT32, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, int64_t data, const char* file, unsigned line)
{
    t.push(TYPE_INT64, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, uint64_t data, const char* file, unsigned line)
{
    t.push(TYPE_UINT64, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, float data, const char* file, unsigned line)
{
    t.push(TYPE_FLOAT32, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, double data, const char* file, unsigned line)
{
    t.push(TYPE_FLOAT64, 1, file, line).set(0, &data);
}

template<class V>
void test_push_internal_vec(TestResultsSet::Result& res, const V& data)
{
    for (unsigned i = 0; i < data.vec_length; ++i) {
        typedef typename V::base_vector_type Base;
        simdpp::detail::mem_block<Base> block(data.vec(i));
        for (unsigned j = 0; j < Base::length; j++) {
            res.set(i*Base::length + j, &block[j]);
        }
    }
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::int8<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_INT8, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::uint8<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_UINT8, N, file, line), data);
}
template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::int16<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_INT16, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::uint16<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_UINT16, N, file, line), data);
}
template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::int32<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_INT32, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::uint32<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_UINT32, N, file, line), data);
}
template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::int64<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_INT64, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::uint64<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_UINT64, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::float32<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_FLOAT32, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::float64<N>& data, const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_FLOAT64, N, file, line), data);
}
} // namespace SIMDPP_ARCH_NAMESPACE

// we are supposed to call this from within the test function which is in
// SIMDPP_ARCH_NAMESPACE namespace

/*
    T - type
    D - an object of type T to push
    A - array of objects to push
    O1, Q2 - arguments to apply OP to
    OP - operation to apply to the array or arguments
    R - type to cast the object to be pushed to
*/
#define TEST_PUSH(TC,T,D)   { test_push_internal((TC), (T)(D), __FILE__, __LINE__); }

#define TEST_ARRAY_PUSH(TC, T, A)                                       \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        const T* lp = reinterpret_cast<const T*>((A) + i);              \
        TEST_PUSH(TC, T, *lp);                                          \
    }                                                                   \
}

#define TEST_ARRAY_HELPER1(TC, T, OP, A)                                \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        const T* lp = reinterpret_cast<const T*>((A).data() + i);       \
        TEST_PUSH(TC, T, OP(*lp));                                      \
    }                                                                   \
}

#define TEST_ARRAY_HELPER1_T(TC, R, T, OP, A)                           \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        const T* lp = reinterpret_cast<const T*>((A).data() + i);       \
        TEST_PUSH(TC, R, OP(*lp));                                      \
    }                                                                   \
}

#define TEST_ARRAY_HELPER2(TC, T, OP, A, B)                             \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        const T* lp = reinterpret_cast<const T*>((A).data() + i);       \
        const T* rp = reinterpret_cast<const T*>((B).data() + i);       \
        TEST_PUSH(TC, T, OP(*lp, *rp));                                 \
    }                                                                   \
}

// tests OP on all pairs of elements within array A
#define TEST_ALL_COMB_HELPER1(TC, T, OP, A, EL_SIZE)                    \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        const T* lp = reinterpret_cast<const T*>((A).data() + i);       \
        T l = *lp;                                                      \
        for (unsigned rot = 0; rot < sizeof(T)/EL_SIZE; rot++) {        \
            TEST_PUSH(TC, T, OP(l));                                    \
            l = simdpp::detail::align_v128<1>(l, l);                    \
        }                                                               \
    }                                                                   \
}

#define TEST_ALL_COMB_HELPER1_T(TC, R, T, OP, A, EL_SIZE)               \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        const T* lp = reinterpret_cast<const T*>((A).data() + i);       \
        T l = *lp;                                                      \
        for (unsigned rot = 0; rot < sizeof(T)/EL_SIZE; rot++) {        \
            TEST_PUSH(TC, R, OP(l));                                    \
            l = simdpp::detail::align_v128<1>(l, l);                    \
        }                                                               \
    }                                                                   \
}

#define TEST_ALL_COMB_HELPER2(TC, T, OP, A, EL_SIZE)                    \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        for (unsigned j = 0; j < (A).size(); j++) {                     \
            const T* lp = reinterpret_cast<const T*>((A).data() + i);   \
            const T* rp = reinterpret_cast<const T*>((A).data() + j);   \
            T l = *lp; T r = *rp;                                       \
            for (unsigned rot = 0; rot < sizeof(T)/EL_SIZE; rot++) {    \
                TEST_PUSH(TC, T, OP(l, r));                             \
                l = simdpp::detail::align_v128<1>(l, l);                \
            }                                                           \
        }                                                               \
    }                                                                   \
}

#define TEST_ALL_COMB_HELPER2_T(TC, R, T, OP, A, EL_SIZE)               \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        for (unsigned j = 0; j < (A).size(); j++) {                     \
            const T* lp = reinterpret_cast<const T*>((A).data() + i);   \
            const T* rp = reinterpret_cast<const T*>((A).data() + j);   \
            T l = *lp; T r = *rp;                                       \
            for (unsigned rot = 0; rot < sizeof(T)/EL_SIZE; rot++) {    \
                TEST_PUSH(TC, R, OP(l, r));                             \
                l = simdpp::detail::align_v128<1>(l, l);                \
            }                                                           \
        }                                                               \
    }                                                                   \
}

#define TEST_ALL_COMB_HELPER3(TC, T, OP, A, EL_SIZE)                    \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i0 = 0; i0 < (A).size(); i0++) {                      \
    for (unsigned i1 = 0; i1 < (A).size(); i1++) {                      \
    for (unsigned i2 = 0; i2 < (A).size(); i2++) {                      \
        const T* p0 = reinterpret_cast<const T*>((A).data() + i0);      \
        const T* p1 = reinterpret_cast<const T*>((A).data() + i1);      \
        const T* p2 = reinterpret_cast<const T*>((A).data() + i2);      \
        T v0 = *p0; T v1 = *p1; T v2 = *p2;                             \
        for (unsigned rot0 = 0; rot0 < sizeof(T)/EL_SIZE % 4; rot0++) { \
            for (unsigned rot1 = 0; rot1 < sizeof(T)/EL_SIZE % 4; rot1++) { \
                TEST_PUSH(TC, T, OP(v0, v1, v2));                       \
                v0 = simdpp::detail::align_v128<1>(v0, v0);             \
            }                                                           \
            v1 = simdpp::detail::align_v128<1>(v1, v1);                 \
        }                                                               \
    }}}                                                                 \
}

/**
    Used to test functions that depend on a template parameter. Essentially
    implements a for loop realised in templates.

    The template calls F<V, i>::test(tc, a) for each i from 0 to F<V, 0>::limit.
*/
template<template<class, unsigned> class F, class V, bool large, unsigned i, unsigned limit>
struct TemplateTestHelperImpl;

template<template<class, unsigned> class F, class V, unsigned i, unsigned limit>
struct TemplateTestHelperImpl<F, V, false, i, limit> {

    static void run(TestResultsSet& tc, const V& a)
    {
        F<V, i>::test(tc, a);
        const bool is_large = i + 30 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+1, limit>::run(tc, a);
    }

    static void run(TestResultsSet& tc, const V& a, const V& b)
    {
        F<V, i>::test(tc, a, b);
        const bool is_large = i + 30 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+1, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V, unsigned i, unsigned limit>
struct TemplateTestHelperImpl<F, V, true, i, limit> {

    static void run(TestResultsSet& tc, const V& a)
    {
        F<V, i>::test(tc, a);
        F<V, i+1>::test(tc, a);
        F<V, i+2>::test(tc, a);
        F<V, i+3>::test(tc, a);
        F<V, i+4>::test(tc, a);
        F<V, i+5>::test(tc, a);
        F<V, i+6>::test(tc, a);
        F<V, i+7>::test(tc, a);
        F<V, i+8>::test(tc, a);
        F<V, i+9>::test(tc, a);
        F<V, i+10>::test(tc, a);
        F<V, i+11>::test(tc, a);
        F<V, i+12>::test(tc, a);
        F<V, i+13>::test(tc, a);
        F<V, i+14>::test(tc, a);
        F<V, i+15>::test(tc, a);
        F<V, i+16>::test(tc, a);
        F<V, i+17>::test(tc, a);
        F<V, i+18>::test(tc, a);
        F<V, i+19>::test(tc, a);
        F<V, i+20>::test(tc, a);
        F<V, i+20>::test(tc, a);
        F<V, i+21>::test(tc, a);
        F<V, i+22>::test(tc, a);
        F<V, i+23>::test(tc, a);
        F<V, i+24>::test(tc, a);
        F<V, i+25>::test(tc, a);
        F<V, i+26>::test(tc, a);
        F<V, i+27>::test(tc, a);
        F<V, i+28>::test(tc, a);
        F<V, i+29>::test(tc, a);
        const bool is_large = i + 60 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+30, limit>::run(tc, a);
    }

    static void run(TestResultsSet& tc, const V& a, const V& b)
    {
        F<V, i>::test(tc, a, b);
        F<V, i+1>::test(tc, a, b);
        F<V, i+2>::test(tc, a, b);
        F<V, i+3>::test(tc, a, b);
        F<V, i+4>::test(tc, a, b);
        F<V, i+5>::test(tc, a, b);
        F<V, i+6>::test(tc, a, b);
        F<V, i+7>::test(tc, a, b);
        F<V, i+8>::test(tc, a, b);
        F<V, i+9>::test(tc, a, b);
        F<V, i+10>::test(tc, a, b);
        F<V, i+11>::test(tc, a, b);
        F<V, i+12>::test(tc, a, b);
        F<V, i+13>::test(tc, a, b);
        F<V, i+14>::test(tc, a, b);
        F<V, i+15>::test(tc, a, b);
        F<V, i+16>::test(tc, a, b);
        F<V, i+17>::test(tc, a, b);
        F<V, i+18>::test(tc, a, b);
        F<V, i+19>::test(tc, a, b);
        F<V, i+20>::test(tc, a, b);
        F<V, i+20>::test(tc, a, b);
        F<V, i+21>::test(tc, a, b);
        F<V, i+22>::test(tc, a, b);
        F<V, i+23>::test(tc, a, b);
        F<V, i+24>::test(tc, a, b);
        F<V, i+25>::test(tc, a, b);
        F<V, i+26>::test(tc, a, b);
        F<V, i+27>::test(tc, a, b);
        F<V, i+28>::test(tc, a, b);
        F<V, i+29>::test(tc, a, b);
        const bool is_large = i + 60 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+30, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V, unsigned i>
struct TemplateTestHelperImpl<F, V, true, i, i> {
    static void run(TestResultsSet&, const V&) {}
    static void run(TestResultsSet&, const V&, const V&) {}
};

template<template<class, unsigned> class F, class V, unsigned i>
struct TemplateTestHelperImpl<F, V, false, i, i> {
    static void run(TestResultsSet&, const V&) {}
    static void run(TestResultsSet&, const V&, const V&) {}
};

template<template<class, unsigned> class F, class V>
struct TemplateTestHelper {
    static void run(TestResultsSet& tc, const V& a)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, a);
    }

    static void run(TestResultsSet& tc, const V& a, const V& b)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V>
struct TemplateTestArrayHelper {
    static void run(TestResultsSet& tc, V* a, unsigned n)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        for (unsigned i = 0; i < n; i++) {
            TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, *(a+i));
        }
    }

    static void run(TestResultsSet& tc, V* a, V* b, unsigned n)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        for (unsigned i = 0; i < n; i++) {
            TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, *(a+i), *(b+i));
        }
    }
};

template<class V1, class V2>
void test_cmp_vectors(TestReporter& tr, const V1& q1, const V2& q2, bool expected_equal,
                      unsigned line, const char* file)
{
    typedef typename simdpp::detail::get_expr_nomask<V1>::type V;
    V v1, v2;
    v1 = q1.eval(); v2 = q2.eval();

    bool success = expected_equal ? std::memcmp(&v1, &v2, sizeof(v1)) == 0 :
                                    std::memcmp(&v1, &v2, sizeof(v1)) != 0;
    tr.add_result(success);

    if (!success) {
        print_separator(tr.out());
        print_file_info(tr.out(), file, line);
        tr.out() << (expected_equal ? "Vectors not equal:\n" : "Vectors equal:\n");
        print_vector_diff(tr.out(), GetVectorType<V>::value, V::length, &v1, &v2);
    }
}

#define TEST_CMP_VEC(TR, V1, V2)    do { test_cmp_vectors(TR, V1, V2, true, __LINE__, __FILE__); } while(0)
#define TEST_CMPNE_VEC(TR, V1, V2)  do { test_cmp_vectors(TR, V1, V2, false, __LINE__, __FILE__); } while(0)

#endif
