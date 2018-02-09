#include <FL/cMFunc.h>

cMFunc::cMFunc(Shape t_shape):m_centroid(0.0),m_area(0.0)
{
    SetShape(t_shape);
}
cMFunc::~cMFunc()
{
    
}

void cMFunc::SetShape(Shape t_shape)
{
    m_shape = t_shape;
    SetVSize();
}

double cMFunc::EvalPoint(double t_point)
{
    return ((t_point >= *(m_points.begin()))
            && (t_point <= *(m_points.end()-1)))?
                EvalFunction(t_point):0.0;
}

void cMFunc::EvalPoint(double t_point, double &t_out)
{
    t_out = EvalPoint(t_point);
}

double cMFunc::GetCentroid(double t_point)
{
    double t_out;
    switch (m_shape) {
    double t_a, t_b;
    case TPN:
        t_a = (t_point*m_points[1])+(m_points[0]*(1.0-t_point));
        std::get<0>(m_strCent[0]) = (t_a - m_points[0])*t_point/2.0;// Area 1
        std::get<0>(m_strCent[1]) = (m_points[2] - t_a)*t_point;    // Area 2
        std::get<1>(m_strCent[0]) = m_points[0] + (t_a - m_points[0])/3.0;// Centroid 1
        std::get<1>(m_strCent[1]) = t_a + (m_points[2] - t_a)/2.0;        // Centroid 2
        m_area = std::get<0>(m_strCent[0]) + std::get<0>(m_strCent[1]);
        m_centroid = (std::get<1>(m_strCent[0])*std::get<0>(m_strCent[0]) +
                      std::get<1>(m_strCent[1])*std::get<0>(m_strCent[1]) )/ m_area;
        break;
    case TPP:
        t_a = (t_point*m_points[1])+(m_points[2]*(1.0-t_point));
        std::get<0>(m_strCent[0]) = (t_a - m_points[0])*t_point;        // Area 1
        std::get<0>(m_strCent[1]) = (m_points[2] - t_a)*t_point/2.0;    // Area 2
        std::get<1>(m_strCent[0]) = m_points[0] + (t_a - m_points[0])/2.0;// Centroid 1
        std::get<1>(m_strCent[1]) = t_a + (m_points[2] - t_a)/3.0;        // Centroid 2
        m_area = std::get<0>(m_strCent[0]) + std::get<0>(m_strCent[1]);
        m_centroid = (std::get<1>(m_strCent[0])*std::get<0>(m_strCent[0]) +
                      std::get<1>(m_strCent[1])*std::get<0>(m_strCent[1]) )/ m_area;
        break;
    case TRG:
        t_a = (t_point*m_points[1])+(m_points[0]*(1.0-t_point));
        t_b = (t_point*m_points[1])+(m_points[2]*(1.0-t_point));
        std::get<0>(m_strCent[0]) = (t_a - m_points[0])*t_point/2.0;// Area 1
        std::get<0>(m_strCent[1]) = (t_b - t_a)*t_point;            // Area 2
        std::get<0>(m_strCent[2]) = (m_points[2] - t_b)*t_point/2.0;// Area 3
        std::get<1>(m_strCent[0]) = m_points[0] + (t_a - m_points[0])/3.0;// Centroid 1
        std::get<1>(m_strCent[1]) = t_a + (t_b - t_a)/2.0;                // Centroid 2
        std::get<1>(m_strCent[2]) = t_b + (m_points[2] - t_b)/3.0;        // Centroid 3
        m_area = std::get<0>(m_strCent[0]) + std::get<0>(m_strCent[1]) + std::get<0>(m_strCent[2]);
        m_centroid = (std::get<1>(m_strCent[0])*std::get<0>(m_strCent[0]) +
                      std::get<1>(m_strCent[1])*std::get<0>(m_strCent[1]) +
                      std::get<1>(m_strCent[2])*std::get<0>(m_strCent[2]) )/ m_area;
        break;
    default:
        m_area = 0.0;
        m_centroid = 0.0;
        break;
    }
    return t_out;
}

void cMFunc::SetVSize(void)
{
    switch (m_shape) {
    case (TPN||TPP||TRG):
        m_points = std::vector<double>(3,0.0);
        m_strCent = std::vector<std::tuple<double, double> >(3,std::make_tuple(0.0,0.0));
        break;
    default:
        m_points = std::vector<double>(3,0.0);
        m_strCent = std::vector<std::tuple<double, double> >(3,std::make_tuple(0.0,0.0));
        break;
    }
}

double cMFunc::EvalFunction(double t_point)
{
    double t_out;
    switch (m_shape) {
    case TPN:
        t_out = ((t_point >= m_points[0])
                && (t_point <= m_points[1]))?
                (t_point-m_points[0])/(m_points[1]-m_points[0]):1.0;
        break;
    case TPP:
        t_out = ((t_point >= m_points[0])
                && (t_point <= m_points[1]))?
                1.0:(t_point-m_points[1])/(m_points[1]-m_points[2]) + 1.0;
        break;
    case TRG:
        t_out = ((t_point >= m_points[0])
                && (t_point <= m_points[1]))?
                (t_point-m_points[0])/(m_points[1]-m_points[0]):
                (t_point-m_points[1])/(m_points[1]-m_points[2]) + 1.0;
        break;
    default:
        t_out = 0.0;
        break;
    }
    return t_out;
}
