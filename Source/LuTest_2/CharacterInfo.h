#pragma once


class CharacterInfo
{

private:

    int m_MaxHP;
    int m_CurentHP;
    int m_DefenseRate;

    int m_MainAttackRate;
    int m_RandomAttackRate;

public:

    CharacterInfo    
    (
          int _DefaultHP
        , int _DefenseRate
        , int _MainAttackRate
    );

    int GetMaxHP();
    int GetCurentHP();

    int GetDefenseRate();

    int GetMainAttackRate();
    int GetRandomAttackRate();

    void SetCurentHP(int _curentHP);

    bool isAlive();


};