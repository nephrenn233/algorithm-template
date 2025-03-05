struct BigInt {
    int _sgn;
    std::vector<int> _val;
    static const int _base = 1e4;
    static const int _wid = 4;

    enum div_type { division, remainder };
    enum cmp_type { with_sign, without_sign };

    BigInt(int x = 0) : _sgn(0) {
        if (x < 0) _sgn = -1, x = -x;
        else if (x > 0) _sgn = 1;
        do {
            _val.push_back(x % _base);
            x /= _base;
        } while (x);
    }
    BigInt(std::string s) : _sgn(0) {
        if (s.front() == '-') {
            _sgn = -1;
            s.erase(s.begin());
        } else {
            _sgn = 1;
        }
        int p = s.size();
        while ( (p -= _wid) >= 0 ) {
            std::stringstream ss(s.substr(p, _wid));
            int x;
            ss >> x;
            _val.push_back(x);
        }
        if ( (p += _wid) > 0 ) {
            std::stringstream ss(s.substr(0, p));
            int x;
            ss >> x;
            _val.push_back(x);
        }
        del_zero();
    }
    BigInt(int s, const std::vector<int> &v) : _sgn(s), _val(v) {}
    BigInt del_zero() {
        while (_val.back() == 0 && _val.size() > 1) _val.pop_back();
        if (_val.back() == 0) _sgn = 0;
        return *this;
    }

    friend std::istream &operator >> (std::istream &is, BigInt &x) {
        std::string s;
        is >> s;
        x = BigInt(s);
        return is;
    }
    friend std::ostream &operator << (std::ostream &os, const BigInt &x) {
        if (x._sgn == -1) {
            os << "-";
        }
        for (int i = x._val.size() - 1; i >= 0; --i) {
            if (i == x._val.size() - 1) os << x._val[i];
            else {
                os << std::setw(x._wid) << std::setfill('0') << x._val[i];
            }
        }
        return os;
    }

    int cmp(const BigInt &rhs, cmp_type typ = with_sign) const {
        if (typ == with_sign && _sgn != rhs._sgn) return _sgn - rhs._sgn;
        int sign = typ == with_sign ? _sgn : 1;
        if (_val.size() != rhs._val.size()) return sign * (int(_val.size()) - int(rhs._val.size()));
        for (int i = _val.size() - 1; i >= 0; i--)
            if (_val[i] != rhs._val[i]) return sign * (_val[i] - rhs._val[i]);
        return 0;
    }

    BigInt operator - () { return BigInt(-_sgn, _val); }

    BigInt add(const BigInt &rhs) {
        int ts = _val.size(), os = rhs._val.size();
        for (int i = 0; i < os; i++) _val[i] += rhs._val[i];
        _val.push_back(0);
        for (int i = 0; i < ts; i++)
            if (_val[i] >= _base) _val[i] -= _base, ++_val[i + 1];
        return del_zero();
    }
    BigInt operator + (const BigInt &rhs) const {
        if (_sgn * rhs._sgn == 1) {
            BigInt temp;
            return cmp(rhs, without_sign) >= 0 ? (temp = *this).add(rhs) : (temp = rhs).add(*this);
        }
        else if (_sgn * rhs._sgn == -1) return *this - BigInt(-rhs._sgn, rhs._val);
        else return _sgn == 0 ? rhs : *this;
    }

    BigInt sub(const BigInt &rhs) {
        int pos = rhs._val.size();
        for (int i = 0; i < pos; i++)
            if ((_val[i] -= rhs._val[i]) < 0) _val[i] += _base, --_val[i + 1];
        while (_val[pos] < 0) _val[pos] += _base, --_val[++pos];
        return del_zero();
    }
    BigInt operator - (const BigInt &rhs) const {
        if (_sgn * rhs._sgn == 1) {
            BigInt temp;
            return cmp(rhs, without_sign) >= 0 ? (temp = *this).sub(rhs) : (temp = BigInt(-rhs._sgn, rhs._val)).sub(*this);
        }
        else if (_sgn * rhs._sgn == -1) return *this + BigInt(-rhs._sgn, rhs._val);
        else return _sgn == 0 ? BigInt(-rhs._sgn, rhs._val) : *this;
    }

    BigInt mul(const BigInt &a, const BigInt &b)
    {
        int as = a._val.size(), bs = b._val.size();
        _val.resize(as + bs);
        for (int i = 0; i < as; i++) {
            for (int j = 0; j < bs; j++) {
                int x = i + j;
                _val[x] += a._val[i] * b._val[j];
                _val[x + 1] += _val[x] / _base;
                _val[x] %= _base;
            }
        }
        return del_zero();   
    }
    BigInt operator * (const BigInt &rhs) const {
        BigInt temp;
        return (temp._sgn = _sgn * rhs._sgn) == 0 ? temp : temp.mul(*this, rhs);
    }

    BigInt div(BigInt &a, BigInt b, div_type typ = division) {
        int move = a._val.size() - b._val.size();
        _val.resize(move + 1);
        b._val.insert(b._val.begin(), move, 0);
        for (int i = move; i >= 0; i--) {
            int left = 0, right = _base;
            while (left + 1 < right) {
                int mid = (left + right) >> 1;
                if (a.cmp(b * BigInt(mid), without_sign) >= 0) left = mid;
                else right = mid;
            }
            _val[i] = left;
            a.sub(b * BigInt(left));
            b._val.erase(b._val.begin());
        }
        return typ == division ? del_zero() : a;
    }

    BigInt operator / (const BigInt &rhs) const {
        BigInt temp, mod = *this;
        return cmp(rhs, without_sign) < 0 || (temp._sgn = _sgn * rhs._sgn) == 0 ? temp : temp.div(mod, rhs);
    }

    BigInt operator % (const BigInt &rhs) const {
        BigInt temp, mod = *this;
        return cmp(rhs, without_sign) < 0 || (temp._sgn = _sgn) == 0 ? mod : temp.div(mod, rhs, remainder);
    }

    BigInt &operator += (const BigInt &rhs) { return *this = *this + rhs; }
    BigInt &operator -= (const BigInt &rhs) { return *this = *this - rhs; }
    BigInt &operator *= (const BigInt &rhs) { return *this = *this * rhs; }
    BigInt &operator /= (const BigInt &rhs) { return *this = *this / rhs; }
    BigInt &operator %= (const BigInt &rhs) { return *this = *this % rhs; }

    bool operator < (const BigInt &rhs) const { return cmp(rhs) < 0; }
    bool operator > (const BigInt &rhs) const { return cmp(rhs) > 0; }
    bool operator <= (const BigInt &rhs) const { return cmp(rhs) <= 0; }
    bool operator >= (const BigInt &rhs) const { return cmp(rhs) >= 0; }
    bool operator == (const BigInt &rhs) const { return cmp(rhs) == 0; }
    bool operator != (const BigInt &rhs) const { return cmp(rhs) != 0; }

    BigInt &operator ++ () { return *this += 1; }
    BigInt &operator -- () { return *this -= 1; }
};