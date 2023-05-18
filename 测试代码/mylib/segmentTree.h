#ifndef MYLIB_SEGMENTTREE_H_
#define MYLIB_SEGMENTTREE_H_

#include <vector>
#include <memory>
#include <limits>

namespace mylib {

    template<typename T=int>
    struct node {
        node(T _l, T _r) : l{_l}, r{_r} {}

        T l{}, r{};
        T sum{}, min{}, max{};
        std::unique_ptr<node<T>> L, R;
        T lazy{};
    };

    struct sum_t {};
    inline sum_t sum;

    namespace rmq {
        struct max_t {};
        inline max_t max;
        struct min_t {};
        inline min_t min;
    }

    template<typename T=int>
    struct segmentTree {

    private:
        std::vector<T> &a;
        bool flag{};
    public:
        node<T> top;

        segmentTree(int l, int r, std::vector<T> &arr, bool mark = false) : top{l, r}, a{arr}, flag{mark} {
            build(top, l, r);
        }

        void build(node<T> &p, int l, int r) noexcept {
            p = {l, r};
            if (l == r) {
                p.sum = p.min = p.max = a[l];
                return;
            }

            T mid = (l + r) / 2;
            p.L = std::make_unique<node<T>>(l, mid);
            p.R = std::make_unique<node<T>>(mid + 1, r);
            build(*(p.L), l, mid), build(*(p.R), mid + 1, r);
            pushup(p);
        }

        void pushup(node<T> &p) noexcept {
            auto &lson = *(p.L), &rson = *(p.R);
            p.sum = lson.sum + rson.sum;
            p.min = std::min(lson.min, rson.min);
            p.max = std::max(lson.max, rson.max);
        }

        void pushdown(node<T> &p) noexcept {
            auto &Lson = *(p.L), &Rson = *(p.R);
            if (p.lazy) {
                Lson.max += p.lazy, Lson.min += p.lazy;
                Rson.max += p.lazy, Rson.min += p.lazy;
                Lson.sum += (Lson.r - Lson.l + 1) * p.lazy;
                Rson.sum += (Rson.r - Rson.l + 1) * p.lazy;
                Lson.lazy += p.lazy, Rson.lazy += p.lazy;
                p.lazy = 0;
            }
        }

        T query(node<T> &p, int l, int r, sum_t v) noexcept {
            if (p.l >= l && p.r <= r) {
                return p.sum;
            }

            if (flag) pushdown(p);
            T mid = (p.l + p.r) / 2;
            T res = 0;
            if (r <= mid) res += query(*(p.L), l, r, v);
            else if (l > mid) res += query(*(p.R), l, r, v);
            else res += (query(*(p.L), l, mid, v) + query(*(p.R), mid + 1, r, v));
            return res;
        }

        T query(node<T> &p, int l, int r, rmq::max_t v) noexcept {
            if (p.l >= l && p.r <= r) {
                return p.max;
            }

            if (flag) pushdown(p);
            T mid = (p.l + p.r) / 2;
            T res = std::numeric_limits<T>::min();
            if (r <= mid)res = std::max(res, query(*(p.L), l, r, v));
            else if (l > mid) res = std::max(res, query(*(p.R), l, r, v));
            else res = std::max(res, std::max(query(*(p.L), l, mid, v), query(*(p.R), mid + 1, r, v)));
            return res;
        }

        T query(node<T> &p, int l, int r, rmq::min_t v) noexcept {
            if (p.l >= l && p.r <= r) {
                return p.min;
            }

            if (flag) pushdown(p);
            T mid = (p.l + p.r) / 2;
            T res = std::numeric_limits<T>::max();

            if (r <= mid)res = std::min(res, query(*(p.L), l, r, v));
            else if (l > mid) res = std::min(res, query(*(p.R), l, r, v));
            else res = std::min(res, std::min(query(*(p.L), l, mid, v), query(*(p.R), mid + 1, r, v)));
            return res;
        }

        void modify(node<T> &p, int l, int r, int k) {
            if (p.l >= l && p.r <= r) {
                p.max += k, p.min += k;
                p.sum += (r - l + 1) * k;
                p.lazy += k;
                return;
            }
            pushdown(p);
            int mid = (p.r + p.l) / 2;
            if (r <= mid) modify(*(p.L), l, r, k);
            else if (l > mid) modify(*(p.R), l, r, k);
            else modify(*(p.L), l, mid, k), modify(*(p.R), mid + 1, r, k);
            pushup(p);
        }
    };
}
#endif
