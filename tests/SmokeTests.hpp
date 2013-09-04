// =====================================================================================
// 
//       Filename:  SmokeTests.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/25/2013 08:47:05 PM EEST
//       Revision:  none
//       Compiler:  gcc
// 
//         Author:  Sergey A Chertkov, aka hunter, chertkov.s.a@gmail.com
//        Company:  HSoft
// 
// =====================================================================================

#ifndef  __EXFSM_SMOKETESTS_HPP__
#define  __EXFSM_SMOKETESTS_HPP__

#include <QtCore/QObject>
#include <QtTest/QtTest>

class MyTest : public QObject
{
    Q_OBJECT
    bool m_is_called;
public:
    explicit MyTest()
        : m_is_called(false)
    {}

    void clear()
    {m_is_called = false;}

    bool isCalled()
    {return m_is_called;}

private Q_SLOTS:

    void doTest()
    {m_is_called = true;}

};


class ExFsmSmokeTests : public QObject
{
    Q_OBJECT
    MyTest m_test;
public:        
    
private Q_SLOTS:

    void check_EventTransition();
    void check_UnexpectedEventHandler();
    void check_RePostOfNotSuitableEvents();
    void check_MultiEventTransition();
    void check_ConditionalTransition();
    void check_Actions();

};



#endif //__EXFSM_SMOKETESTS_HPP__


