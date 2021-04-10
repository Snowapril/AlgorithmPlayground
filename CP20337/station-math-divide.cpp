#include <fstream>
#include <limits>
#include <cmath>

constexpr double k_epsilon = 1e-7;
using namespace std;

struct vertex2 {
    double x, y;
};

struct vertex3 {
    double x, y, z;
};

struct segment {
    vertex3 l_begin;
    vertex3 l_end;
    vertex3 get(double t) const;
};

ifstream& operator>>(ifstream& in, vertex3& v);
double squared_length(vertex3 v1, vertex3 v2 = { 0.0, 0.0, 0.0 });

vertex3 divide_conquer_point_line(vertex3 p, segment line, double t_begin, double t_end)
{
    double t_middle = (t_begin + t_end) * 0.5;
    vertex3 middle_vertex3 = line.get(t_middle);

    if (t_end - t_begin < k_epsilon)
        return middle_vertex3;

    double t_above_begin = t_begin + k_epsilon;
    vertex3 above_begin_point = line.get(t_above_begin);
    double above_begin_dist = squared_length(above_begin_point, p);

    double t_below_end = t_end - k_epsilon;
    vertex3 below_end_point = line.get(t_below_end);
    double below_end_dist = squared_length(below_end_point, p);

    if (above_begin_dist < below_end_dist)
        return divide_conquer_point_line(p, line, t_begin, t_middle);
    else
        return divide_conquer_point_line(p, line, t_middle, t_end);
}

double signed_area(vertex2 a, vertex2 b, vertex2 c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

bool check_intersect(segment s1, segment s2)
{
    //! projection on xy
    vertex2 v1{ s1.l_begin.x, s1.l_begin.y }, v2{ s1.l_end.x, s1.l_end.y };
    vertex2 v3{ s2.l_begin.x, s2.l_begin.y }, v4{ s2.l_end.x, s2.l_end.y };
    bool xy_intersect = signed_area(v1, v2, v3) * signed_area(v1, v2, v4) <= 0;
    //! projection on yz
    v1 = { s1.l_begin.y, s1.l_begin.z }; v2 = { s1.l_end.y, s1.l_end.z };
    v3 = { s2.l_begin.y, s2.l_begin.z }; v4 = { s2.l_end.y, s2.l_end.z };
    bool yz_intersect = signed_area(v1, v2, v3) * signed_area(v1, v2, v4) <= 0;
    //! projection on xz
    v1 = { s1.l_begin.x, s1.l_begin.z }; v2 = { s1.l_end.x, s1.l_end.z };
    v3 = { s2.l_begin.x, s2.l_begin.z }; v4 = { s2.l_end.x, s2.l_end.z };
    bool xz_intersect = signed_area(v1, v2, v3) * signed_area(v1, v2, v4) <= 0;

    return xy_intersect && yz_intersect && xz_intersect;
}

int main()
{
    ifstream in("station.inp");
    ofstream out("station.out");

    vertex3 a, b, c, d;
    in >> a >> b >> c >> d;
    double minDist, old_minDist;

    segment line1 = { a, b };
    segment line2 = { c, d };

    if (check_intersect(line1, line2))
    {
        minDist = 0.0;
    }
    else
    {
        minDist = old_minDist = numeric_limits<double>::max();
        vertex3 tempPoint = c;
        for (;;)
        {
            vertex3 closestPoint = divide_conquer_point_line(tempPoint, line1, 0.0, 1.0);
            minDist = min(minDist, squared_length(closestPoint, tempPoint));

            if (fabs(old_minDist - minDist) < k_epsilon)
                break;

            old_minDist = minDist;
            tempPoint = closestPoint;
            swap(line1, line2);
        }
    }

    out << ceil(sqrt(minDist));
    out.close();
    in.close();

    return 0;
}

ifstream& operator>>(ifstream& in, vertex3& v)
{
    in >> v.x >> v.y >> v.z;
    return in;
}

vertex3 segment::get(double t) const
{
    return { (1.0 - t) * l_begin.x + t * l_end.x,
             (1.0 - t) * l_begin.y + t * l_end.y,
             (1.0 - t) * l_begin.z + t * l_end.z };
}

double squared_length(vertex3 v1, vertex3 v2)
{
    return (v1.x - v2.x) * (v1.x - v2.x) +
        (v1.y - v2.y) * (v1.y - v2.y) +
        (v1.z - v2.z) * (v1.z - v2.z);
}

//double dot(vertex3 v1, vertex3 v2)
//{
//    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
//}
//
//vertex3 cross(vertex3 v1, vertex3 v2)
//{
//    return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
//}