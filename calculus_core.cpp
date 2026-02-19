#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <cmath>
#include <sstream>

namespace py = pybind11;

// ================= Scalar =================
class Scalar {
    double v;
public:
    Scalar(double val = 0.0) : v(val) {}

    Scalar operator+(const Scalar& o) const { return Scalar(v + o.v); }
    Scalar operator-(const Scalar& o) const { return Scalar(v - o.v); }
    Scalar operator*(const Scalar& o) const { return Scalar(v * o.v); }
    Scalar operator/(const Scalar& o) const { return Scalar(v / o.v); }

    double sin()  const { return std::sin(v); }
    double cos()  const { return std::cos(v); }
    double tan()  const { return std::tan(v); }
    double exp()  const { return std::exp(v); }
    double log()  const { return std::log(v); }
    double sqrt() const { return std::sqrt(v); }

    std::string toString() const {
        std::ostringstream ss;
        ss << v;
        return ss.str();
    }
};

// ================= Vec3 =================
class Vec3 {
public:
    double x, y, z;
    Vec3(double a, double b, double c) :x(a), y(b), z(c) {}

    Vec3 operator+(const Vec3& o) const { return Vec3(x + o.x, y + o.y, z + o.z); }
    Vec3 operator-(const Vec3& o) const { return Vec3(x - o.x, y - o.y, z - o.z); }
    Vec3 operator*(double s) const { return Vec3(x * s, y * s, z * s); }

    double dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }

    Vec3 cross(const Vec3& o) const {
        return Vec3(
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        );
    }

    double magnitude() const { return std::sqrt(x * x + y * y + z * z); }

    Vec3 normalize() const {
        double m = magnitude();
        return Vec3(x / m, y / m, z / m);
    }
};

// ================= Solver =================
class Solver {
public:
    static double integrate(py::function f, double a, double b, int n) {
        double h = (b - a) / n, sum = 0;
        for (int i = 0; i < n; i++) {
            double x = a + i * h;
            sum += f(x).cast<double>() * h;
        }
        return sum;
    }
};

// ================= Constants =================
namespace Constants {
    const double pi = 3.141592653589793;
    const double e = 2.718281828459045;
    const double g = 9.80665;
}

// ================= PYBIND =================
PYBIND11_MODULE(calculus_core, m) {
    m.doc() = "CalCulus Scientific Engine";

    py::class_<Scalar>(m, "Scalar")
        .def(py::init<double>())
        .def("__add__", &Scalar::operator+)
        .def("__sub__", &Scalar::operator-)
        .def("__mul__", &Scalar::operator*)
        .def("__truediv__", &Scalar::operator/)
        .def("__repr__", &Scalar::toString)
        .def("sin", &Scalar::sin)
        .def("cos", &Scalar::cos)
        .def("tan", &Scalar::tan)
        .def("exp", &Scalar::exp)
        .def("log", &Scalar::log)
        .def("sqrt", &Scalar::sqrt);

    py::class_<Vec3>(m, "Vec3")
        .def(py::init<double, double, double>())
        .def("__add__", &Vec3::operator+)
        .def("__sub__", &Vec3::operator-)
        .def("__mul__", &Vec3::operator*)
        .def("dot", &Vec3::dot)
        .def("cross", &Vec3::cross)
        .def("magnitude", &Vec3::magnitude)
        .def("normalize", &Vec3::normalize);

    py::class_<Solver>(m, "Solver")
        .def_static("integrate", &Solver::integrate);

    py::module_ c = m.def_submodule("Constants");
    c.attr("pi") = Constants::pi;
    c.attr("e") = Constants::e;
    c.attr("g") = Constants::g;
}
