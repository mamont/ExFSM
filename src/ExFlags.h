#ifndef __EX_FSM_FLAGS_H__
#define __EX_FSM_FLAGS_H__

#include <QtCore/QtGlobal>

namespace ExFSM {

class ExFlag
{
    quint64 m_flag;
    friend class ExFlags;
public:
    ExFlag(quint64 val) : m_flag(val) {;}
    operator quint64() const { return m_flag; }
};


template<typename T>
class ExFlagBase : public ExFlag
{
    T val;

public:
    ExFlagBase(T const& _val) : val(_val) {;}
    ExFlagBase(int _val) : val(T(_val)) {;}
};



class ExFlags
{
    quint64 m_flags;

public:
    ExFlags();
    ExFlags(quint64 val);
    ~ExFlags();

    bool testFlag(ExFlag const & val) const;

    ExFlags & operator = (ExFlags const &);
    ExFlags & operator |= (ExFlags const &);
    ExFlags & operator &= (ExFlags const &);
    ExFlags & operator ^= (ExFlags const &);

    ExFlags operator~() const;
};

} // ExFSM

#endif //__EX_FSM_FLAGS_H__
