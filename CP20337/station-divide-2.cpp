#include <fstream>
#include <limits>
#include <cmath>

constexpr double k_interval = 1e-4;
using namespace std;

struct vertex {
    double x, y, z;
};

struct segment {
    vertex l_begin;
    vertex l_end;
    vertex get(double t) const;
};

ifstream& operator>>(ifstream& in, vertex& v);
double squared_length(vertex v1, vertex v2);

//bool check_intersect(vertex l1, vertex l2, vertex l3, vertex l4)
//{
//    vertex d1 = { l2.x - l1.x, l2.y - l1.y, l2.z - l1.z };
//    vertex d2 = { l4.x - l3.x, l4.y - l3.y, l4.z - l3.z };
//    vertex d3 = { l4.x - l3.x, l4.y - l3.y, l4.z - l3.z };
//    const vertex crossd1d2 = cross(d1, d2);
//    if (crossd1d2 == vertex{ 0.0, 0.0, 0.0 }) //! this mean d1, d2 is same direction or opposite direction.
//    {
//        if (fcomp(divide_conquer_point_line(l1, l3, l4), 0.0) ||
//            fcomp(divide_conquer_point_line(l2, l3, l4), 0.0))
//            return true;
//        else
//            return false;
//    }
//
//    if (!fcomp(dot(crossd1d2, d3), 0.0))
//        return false;
//    else
//    {
//        double t = dot(cross(d3, d2), crossd1d2) / squared_distance(crossd1d2);
//        return t >= 0.0 ? (t <= 1.0 ? true : false) : false;
//    }
//}

vertex divide_conquer_point_line(vertex p, segment line, double t_begin, double t_end)
{
    double t_middle = (t_begin + t_end) * 0.5;
    vertex middle_vertex = line.get(t_middle);

    if (t_end - t_begin < k_interval)
        return middle_vertex;

    double t_above_begin = t_begin + k_interval;
    vertex above_begin_point = line.get(t_above_begin);
    double above_begin_dist = squared_length(above_begin_point, p);

    double t_below_end = t_end + k_interval;
    vertex below_end_point = line.get(t_below_end);
    double below_end_dist = squared_length(below_end_point, p);

    if (above_begin_dist < below_end_dist)
        return divide_conquer_point_line(p, line, t_begin, t_middle);
    else
        return divide_conquer_point_line(p, line, t_middle, t_end);
}

int main()
{
    ifstream in("station.inp");
    ofstream out("station.out");

    vertex a, b, c, d;
    in >> a >> b >> c >> d;
    double minDist = numeric_limits<double>::max();

    segment line1 = { a, b };
    segment line2 = { c, d };
    double tempDist = 0.0;
    vertex tempPoint = c;
    for (;;)
    {
        vertex closestPoint = divide_conquer_point_line(tempPoint, line1, 0.0, 1.0);
        tempDist = squared_length(closestPoint, tempPoint);

        if (fabs(tempDist - minDist) < k_interval)
            break;

        minDist = min(minDist, tempDist);
        tempPoint = closestPoint;
        swap(line1, line2);
    }

    out << ceil(sqrt(minDist));

    out.close();
    in.close();

    return 0;
}

ifstream& operator>>(ifstream& in, vertex& v)
{
    in >> v.x >> v.y >> v.z;
    return in;
}

vertex segment::get(double t) const
{
    return { (1.0 - t) * l_begin.x + t * l_end.x,
             (1.0 - t) * l_begin.y + t * l_end.y,
             (1.0 - t) * l_begin.z + t * l_end.z };
}

double squared_length(vertex v1, vertex v2)
{
    return (v1.x - v2.x) * (v1.x - v2.x) +
        (v1.y - v2.y) * (v1.y - v2.y) +
        (v1.z - v2.z) * (v1.z - v2.z);
}

