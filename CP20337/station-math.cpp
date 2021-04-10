#include <fstream>
#include <limits>
#include <cmath>

using namespace std;

struct vertex {
    double x, y, z;
};

inline bool fcomp(double v1, double v2);
inline ifstream& operator>>(ifstream& in, vertex& v);
inline vertex operator-(const vertex& v1, const vertex& v2);
inline vertex operator+(const vertex& v1, const vertex& v2);
inline vertex operator*(const vertex& v, double val);
inline vertex operator/(const vertex& v, double val);
inline bool operator==(const vertex& v1, const vertex& v2);
inline double dot(vertex v1, vertex v2);
inline vertex cross(vertex v1, vertex v2);
inline double squared_distance(vertex v1, vertex v2 = { 0.0, 0.0, 0.0 });

double shortest_squared_length_point_to_seg(vertex p, vertex l1, vertex l2)
{
    if (l1 == l2)
        return squared_distance(p, l1);

    vertex dir = l2 - l1;
    double length = sqrt(squared_distance(l1, l2));
    dir = dir / length;
    vertex l1top = p - l1;
    double t = dot(l1top, dir);
    t = (t < 0.0) ? 0.0 : ((t > length) ? length : t);
    vertex closest_point = l1 + dir * t;
    return squared_distance(p, closest_point);
}

bool check_intersect(vertex l1, vertex l2, vertex l3, vertex l4)
{
    vertex d1 = l2 - l1;
    vertex d2 = l4 - l3;
    vertex d3 = l3 - l1;
    const vertex crossd1d2 = cross(d1, d2);
    if (crossd1d2 == vertex{ 0.0, 0.0, 0.0 }) //! this mean d1, d2 is same direction or opposite direction.
    {
        if (fcomp(shortest_squared_length_point_to_seg(l1, l3, l4), 0.0) ||
            fcomp(shortest_squared_length_point_to_seg(l2, l3, l4), 0.0))
            return true;
        else
            return false;
    }

    if (!fcomp(dot(crossd1d2, d3), 0.0))
        return false;
    else
    {
        double t = dot(cross(d3, d2), crossd1d2) / squared_distance(crossd1d2);
        return t >= 0.0 ? (t <= 1.0 ? true : false) : false;
    }
}

int main()
{
    ifstream in("station.inp");
    ofstream out("station.out");

    vertex a, b, c, d;
    in >> a >> b >> c >> d;
    double closestDist = numeric_limits<double>::max();

    if (a == b)
    {
        closestDist = shortest_squared_length_point_to_seg(a, c, d);
    }
    else if (c == d)
    {
        closestDist = shortest_squared_length_point_to_seg(c, a, b);
    }
    else if (check_intersect(a, b, c, d))
    {
        closestDist = 0.0;
    }
    else
    {
        const int iterations = 10000;

        for (int i = 0; i < iterations; ++i)
        {
            const double c_dist = shortest_squared_length_point_to_seg(c, a, b);
            const double d_dist = shortest_squared_length_point_to_seg(d, a, b);

            if (c_dist > d_dist)
            {
                c = c * (2.0 / 3.0) + d * (1.0 / 3.0);;
                closestDist = min(closestDist, d_dist);
            }
            else
            {
                d = c * (1.0 / 3.0) + d * (2.0 / 3.0);
                closestDist = min(closestDist, c_dist);
            }
        }
    }

    out << static_cast<size_t>(ceil(sqrt(closestDist)));

    out.close();
    in.close();

    return 0;
}

inline bool fcomp(double v1, double v2)
{
    return fabs(v1 - v2) < 1e-9;
}

inline ifstream& operator>>(ifstream& in, vertex& v)
{
    in >> v.x >> v.y >> v.z;
    return in;
}

inline vertex operator-(const vertex& v1, const vertex& v2)
{
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

inline vertex operator+(const vertex& v1, const vertex& v2)
{
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

inline vertex operator*(const vertex& v, double val)
{
    return { val * v.x, val * v.y, val * v.z };
}

inline vertex operator/(const vertex& v, double val)
{
    return { v.x / val, v.y / val, v.z / val };
}

inline bool operator==(const vertex& v1, const vertex& v2)
{
    return fcomp(v1.x, v2.x) &&
        fcomp(v1.y, v2.y) &&
        fcomp(v1.z, v2.z);
}

inline double dot(vertex v1, vertex v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline vertex cross(vertex v1, vertex v2)
{
    return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

inline double squared_distance(vertex v1, vertex v2)
{
    return (v1.x - v2.x) * (v1.x - v2.x) +
        (v1.y - v2.y) * (v1.y - v2.y) +
        (v1.z - v2.z) * (v1.z - v2.z);
}