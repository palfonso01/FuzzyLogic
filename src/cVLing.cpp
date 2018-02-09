#include <FL/cVLing.h>

cVLing::cVLing(std::string t_name):m_name(t_name)
{
    m_NumMemFcns = 0;
}
cVLing::~cVLing()
{
    
}

void cVLing::AddMembershipFunction(cMFunc::Shape t_shape, double t_p0, double t_p1, double t_p2, double t_p3)
{
    switch (t_shape) {
    case (cMFunc::TPN||cMFunc::TPP||cMFunc::TRG):
        m_MemFcns.push_back(cMFunc(t_shape));
        m_MemFcns.at(m_NumMemFcns).SetX(t_p0, 0);
        m_MemFcns.at(m_NumMemFcns).SetX(t_p1, 1);
        m_MemFcns.at(m_NumMemFcns).SetX(t_p2, 2);
        break;
    default:
        break;
    }
    m_NumMemFcns++;
}
