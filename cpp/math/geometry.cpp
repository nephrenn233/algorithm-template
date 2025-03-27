namespace Geometry {
    template<typename T>
    struct Point {
        T x, y;
        Point(const T &_x = 0, const T &_y = 0) : x(_x), y(_y) {}

        template<typename U>
        operator Point<U>() {
            return Point<U>(U(x), U(y));
        }

        Point &operator += (const Point &p) & {
            x += p.x;
            y += p.y;
            return *this;
        }
        Point &operator -= (const Point &p) & {
            x -= p.x;
            y -= p.y;
            return *this;
        }
        Point &operator *= (const T &v) & {
            x *= v;
            y *= v;
            return *this;
        }
        Point &operator /= (const T &v) & {
            x /= v;
            y /= v;
            return *this;
        }
        Point operator - () const {
            return Point(-x, -y);
        }
        friend Point operator + (Point a, const Point &b) {
            return a += b;
        }
        friend Point operator - (Point a, const Point &b) {
            return a -= b;
        }
        friend Point operator * (Point a, const T &b) {
            return a *= b;
        }
        friend Point operator / (Point a, const T &b) {
            return a /= b;
        }
        friend Point operator * (const T &a, Point b) {
            return b *= a;
        }
        friend bool operator == (const Point &a, const Point &b) {
            return a.x == b.x && a.y == b.y;
        }
        friend std::istream &operator >> (std::istream &is, Point &p) {
            return is >> p.x >> p.y;
        }
        friend std::ostream &operator << (std::ostream &os, const Point &p) {
            return os << p.x << " " << p.y;
        }
    };

    template<typename T>
    struct Line {
        Point<T> a, b;
        Line(const Point<T> &_a = Point<T>(), const Point<T> &_b = Point<T>()) : a(_a), b(_b) {}
    };

    template<typename T>
    T dot(const Point<T> &a, const Point<T> &b) {
        return a.x * b.x + a.y * b.y;
    }

    template<typename T>
    T cross(const Point<T> &a, const Point<T> &b) {
        return a.x * b.y - a.y * b.x;
    }

    template<typename T>
    T square(const Point<T> &p) {
        return dot(p, p);
    }

    template<typename T>
    double length(const Point<T> &p) {
        return std::sqrt(square(p));
    }

    template<typename T>
    double length(const Line<T> &l) {
        return length(l.a - l.b);
    }

    template<class T>
    Point<T> normalize(const Point<T> &p) {
        return p / length(p);
    }

    template<class T>
    double distance(const Point<T> &a, const Point<T> &b) {
        return length(a - b);
    }

    template<class T>
    double distancePL(const Point<T> &p, const Line<T> &l) {
        return std::abs(cross(l.a - l.b, l.a - p)) / length(l);
    }

    template<class T>
    double distancePS(const Point<T> &p, const Line<T> &l) {
        if (dot(p - l.a, l.b - l.a) < 0) {
            return distance(p, l.a);
        }
        if (dot(p - l.b, l.a - l.b) < 0) {
            return distance(p, l.b);
        }
        return distancePL(p, l);
    }

    template<class T>
    bool pointOnLineLeft(const Point<T> &p, const Line<T> &l) {
        return cross(l.b - l.a, p - l.a) > 0;
    }

    template<class T>
    Point<T> lineIntersection(const Line<T> &l1, const Line<T> &l2) {
        return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
    }
    
    template<class T>
    bool pointOnSegment(const Point<T> &p, const Line<T> &l) {
        return cross(p - l.a, l.b - l.a) == 0 && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
            && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
    }

    template<class T>
    bool pointInPolygon(const Point<T> &a, const std::vector<Point<T>> &p) {
        int n = p.size();
        for (int i = 0; i < n; i++) {
            if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
                return true;
            }
        }
        
        int t = 0;
        for (int i = 0; i < n; i++) {
            auto u = p[i];
            auto v = p[(i + 1) % n];
            if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
                t ^= 1;
            }
            if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
                t ^= 1;
            }
        }
        
        return t == 1;
    }
};