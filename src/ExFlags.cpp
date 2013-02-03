#include "ExFlags.h"

namespace ExFSM {

ExFlags::ExFlags()
	: m_flags(0)
{
    ;
}

//--------------------------------------------------------------------------------------------------
ExFlags::ExFlags(quint64 flags)
    : m_flags(flags)
{
    ;
}

//--------------------------------------------------------------------------------------------------
ExFlags::~ExFlags()
{
    ;
}

//--------------------------------------------------------------------------------------------------
bool ExFlags::testFlag(ExFlag const& val) const
{
    return (m_flags&val) != 0;
}

//--------------------------------------------------------------------------------------------------
ExFlags & ExFlags::operator = (ExFlags const & o)
{
    m_flags = o.m_flags;
    return * this;
}

//--------------------------------------------------------------------------------------------------
ExFlags & ExFlags::operator |= (ExFlags const & o)
{
    m_flags |= o.m_flags;
    return * this;
}

//--------------------------------------------------------------------------------------------------
ExFlags & ExFlags::operator &= (ExFlags const & o)
{
    m_flags &= o.m_flags;
    return * this;
}

//--------------------------------------------------------------------------------------------------
ExFlags & ExFlags::operator ^= (ExFlags const & o)
{
    m_flags ^= o.m_flags;
    return * this;
}

//--------------------------------------------------------------------------------------------------
ExFlags ExFlags::operator~() const
{
    return ExFlags(~m_flags);
}

} // ExFSM
