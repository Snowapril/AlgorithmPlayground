#include <fstream>
#include <limits>
#include <cmath>

constexpr double k_dividestep = 1e-1;
constexpr double k_epsilon = 1e-9;

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
double squared_length(vertex v1, vertex v2 = { 0.0, 0.0, 0.0 });

vertex divide_conquer_point_line(vertex p, segment line)
{
    double t_begin = 0.0, t_end = 1.0;
    while (t_end - t_begin >= k_epsilon)
    {
        double t_above_begin = t_begin + k_epsilon;
        vertex above_begin_point = line.get(t_above_begin);
        double above_begin_dist = squared_length(above_begin_point, p);

        double t_below_end = t_end - k_epsilon;
        vertex below_end_point = line.get(t_below_end);
        double below_end_dist = squared_length(below_end_point, p);

        if (above_begin_dist < below_end_dist)
            t_end = t_begin * k_dividestep + t_end * (1.0 - k_dividestep);
        else
            t_begin = t_end * k_dividestep + t_begin * (1.0 - k_dividestep);
    }

    return line.get((t_begin + t_end) * 0.5);
}

int main()
{
    ifstream in("station.inp");
    ofstream out("station.out");

    vertex a, b, c, d;
    in >> a >> b >> c >> d;

    segment line1 = { a, b };
    segment line2 = { c, d };

    double minDist, old_minDist;
    minDist = old_minDist = numeric_limits<double>::max();
    vertex tempPoint = c;
    for (;;)
    {
        vertex closestPoint = divide_conquer_point_line(tempPoint, line1);
        minDist = min(minDist, squared_length(closestPoint, tempPoint));

        if (fabs(old_minDist - minDist) < k_epsilon)
            break;

        old_minDist = minDist;
        tempPoint = closestPoint;
        swap(line1, line2);
    }

    minDist = static_cast<size_t>(sqrt(minDist) * 1e4) / 1e4;
    out << ceil(minDist);
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