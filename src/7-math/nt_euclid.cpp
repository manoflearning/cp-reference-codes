#pragma once
#include "num.hpp"

// what: quick reference for gcd/egcd/inverse/linear congruence identities.
// time: O(log n); memory: O(1)
// constraint: modular ops require mod > 0.
// usage: ll g=euclid::gcd(a,b); auto eg=euclid::egcd(a,b); ll inv=euclid::inv_mod(a,mod);

// goal: keep key formulas handy when using euclid in num.hpp.
// Bezout:
// gcd(a,b)=g => exists x,y: ax+by=g. (euclid::egcd)
//
// modular inverse:
// gcd(a,mod)=1 => exists unique x in [0,mod): a*x=1 (mod mod). (euclid::inv_mod)
//
// linear congruence:
// a*x=b (mod mod) has solution iff gcd(a,mod)|b. (euclid::lin_cong)
