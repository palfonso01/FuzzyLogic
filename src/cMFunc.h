#ifndef CMFUCN_H
#define CMFUCN_H

#include <vector>
#include <tuple>

class cMFunc
{
public:
    //Type of shapes availabes:
    // ----  3 Point shapes  ----
    // TPP: Positive trapezoidal
    // TPN: Negative trapezoidal
    // TRG: Triangular
    enum Shape {TPP, TPN, TRG};
    cMFunc(Shape t_shape = TPP);
    ~cMFunc();
    void SetShape(Shape t_shape);
    void SetX(double t_val, int t_pos){m_points[t_pos] = t_val;}
    double GetX(int t_pos){return m_points[t_pos];}
    void GetX(double &t_val, int t_pos){t_val = m_points[t_pos];}
    // -- Evaluation of any point over the Membership function
    double EvalPoint(double t_point);
    void EvalPoint(double t_point, double &t_out);
    // -- Centroid computation
    double GetCentroid(double t_val);
    void GetCentroid(double &t_val, double t_in){t_val = GetCentroid(t_in);}
    // -- Area
    double GetArea(void){return m_area;}
    void GetArea(double &t_val){t_val = m_area;}
private:
    Shape m_shape; //Shape
    std::vector<double> m_points; //points defined in the shape
    std::vector<std::tuple<double, double> > m_strCent;
    double m_centroid;
    double m_area;
    void SetVSize(void);
    double EvalFunction(double t_point);
};
#endif //CMFUCN_H
