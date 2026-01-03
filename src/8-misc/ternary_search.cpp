#include "../0-common/common.hpp"

// what: maximize/minimize a unimodal function with ternary search (int/real).
// time: int O(log range); real O(it); memory: O(1)
// constraint: single peak/valley; use max/min versions accordingly.
// usage: auto [x, v] = ternary_int_max(l, r, f); ld x = ternary_real_min(l, r, f);

template <class F>
pll ternary_int_max(ll l, ll r, F f) {
    // goal: maximize f on integer domain
    while (r - l >= 3) {
        ll m1 = (2 * l + r) / 3;
        ll m2 = (l + 2 * r) / 3;
        ll v1 = f(m1), v2 = f(m2);
        if (v1 < v2) l = m1;
        else r = m2;
    }
    ll best_x = l;
    ll best_v = f(l);
    for (ll x = l + 1; x <= r; x++) {
        ll v = f(x);
        if (v > best_v) best_v = v, best_x = x;
    }
    return {best_x, best_v};
}

template <class F>
pll ternary_int_min(ll l, ll r, F f) {
    // goal: minimize f on integer domain
    while (r - l >= 3) {
        ll m1 = (2 * l + r) / 3;
        ll m2 = (l + 2 * r) / 3;
        ll v1 = f(m1), v2 = f(m2);
        if (v1 > v2) l = m1;
        else r = m2;
    }
    ll best_x = l;
    ll best_v = f(l);
    for (ll x = l + 1; x <= r; x++) {
        ll v = f(x);
        if (v < best_v) best_v = v, best_x = x;
    }
    return {best_x, best_v};
}

template <class F>
ld ternary_real_max(ld l, ld r, F f, int it = 80) {
    // goal: maximize f on real domain
    for (int i = 0; i < it; i++) {
        ld m1 = (2 * l + r) / 3;
        ld m2 = (l + 2 * r) / 3;
        if (f(m1) < f(m2)) l = m1;
        else r = m2;
    }
    return (l + r) * 0.5L;
}

template <class F>
ld ternary_real_min(ld l, ld r, F f, int it = 80) {
    // goal: minimize f on real domain
    for (int i = 0; i < it; i++) {
        ld m1 = (2 * l + r) / 3;
        ld m2 = (l + 2 * r) / 3;
        if (f(m1) > f(m2)) l = m1;
        else r = m2;
    }
    return (l + r) * 0.5L;
}
