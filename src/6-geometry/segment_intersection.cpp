#include "geom_base.cpp"

// what: test segment intersection and return one intersection point if any.
// time: O(1); memory: O(1)
// constraint: seg_inter_p returns one point; overlapping segments return one endpoint.
// usage: ptd out; if (seg_inter_p(a,b,c,d,out)) ...
bool seg_inter_p(const pt &a, const pt &b, const pt &c, const pt &d, ptd &out) {
    // result: true if segments intersect, out is one point.
    if (!seg_inter(a, b, c, d)) return 0;
    if (ccw(a, b, c) == 0 && ccw(a, b, d) == 0) {
        pt ab_lo = (b < a) ? b : a;
        pt ab_hi = (a < b) ? b : a;
        pt cd_lo = (d < c) ? d : c;
        pt cd_hi = (c < d) ? d : c;
        pt res = (ab_lo < cd_lo) ? cd_lo : ab_lo;
        res = (res < ab_hi) ? res : ab_hi;
        res = (res < cd_hi) ? res : cd_hi;
        out = {(ld)res.x, (ld)res.y};
        return 1;
    }
    ptd pa{(ld)a.x, (ld)a.y};
    ptd p_b{(ld)b.x, (ld)b.y};
    ptd pc{(ld)c.x, (ld)c.y};
    ptd pd{(ld)d.x, (ld)d.y};
    return line_inter(pa, p_b, pc, pd, out);
}
