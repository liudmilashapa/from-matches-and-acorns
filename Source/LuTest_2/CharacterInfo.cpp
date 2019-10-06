

#include "CharacterInfo.h"


#include "Math/UnrealMathUtility.h"



CharacterInfo::CharacterInfo
(
      int _MaxHP
    , int _DefenseRate
    , int _MainAttackRate
)
{
    if (_MaxHP > 0)
    {
        m_MaxHP = m_CurentHP = _MaxHP;
    }
    if (_DefenseRate > 0)
    {
        m_DefenseRate = _DefenseRate;
    }
    if (_MainAttackRate > 0)
    {
        m_MainAttackRate = _MainAttackRate;
    }
}

int CharacterInfo::GetMaxHP()
{
    return m_MaxHP;
}

int CharacterInfo::GetCurentHP()
{
    return m_CurentHP;
}

int CharacterInfo::GetDefenseRate()
{
    return m_DefenseRate;
}

int CharacterInfo::GetMainAttackRate()
{
    return m_MainAttackRate;
}

int CharacterInfo::GetRandomAttackRate()
{
    int random1 = m_MainAttackRate - m_MaxHP * 0.1;
    int random2 = m_MainAttackRate + m_MaxHP * 0.1;
    m_RandomAttackRate = FMath::RandRange(random1, random2);

    return m_RandomAttackRate;
}

void CharacterInfo::SetCurentHP(int _curentHP)
{
    _curentHP >= 0 ?  m_CurentHP = _curentHP : m_CurentHP = 0;
}

bool CharacterInfo::isAlive()
{
    return m_CurentHP > 0;
}
