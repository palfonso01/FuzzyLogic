#ifndef CVLING_H
#define CVLING_H
#include <FL/cMFunc.h>
#include <cstring>

class cBIOFAM
{
public:
    cBIOFAM(int t_rows=0, int t_cols=0):m_rows(t_rows),m_cols(t_cols)
    {SetDims(t_rows, t_cols);}
    ~cBIOFAM(){}
    void SetDims(int t_rows, int t_cols)
    {if(t_rows!=0 && t_cols!=0) m_biofam = new double[t_rows*t_cols];}
    int GetRows(){return m_rows;}
    int GetCols(){return m_cols;}
    int GetSize(){return m_rows*m_cols;}
private:
    double *m_biofam;
    int m_rows;
    int m_cols;
};

class cVLing
{
public:
    cVLing(std::string t_name = " ");
    ~cVLing();
    void SetName(std::string t_name){m_name = t_name;}
    void AddMembershipFunction(cMFunc::Shape t_shape,
                               double t_p0, double t_p1,
                               double t_p2, double t_p3 = 0.0);
private:
    std::vector<cMFunc> m_MemFcns;
    std::string m_name;
    int m_NumMemFcns;
};
#endif //CVLING_H
