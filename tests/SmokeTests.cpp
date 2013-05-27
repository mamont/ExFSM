#include "SmokeTests.hpp"

#include <QtCore/QScopedPointer>

#include <ExFSM/ExStateMachine>
#include <ExFSM/ExState>
#include <ExFSM/ExEvent>
#include <ExFSM/ExEventTransition>
#include <ExFSM/ExMultiEventTransition>

using namespace ExFSM;

class Ev_TestEventOne : public ExEventBase<Ev_TestEventOne> {};
class Ev_TestEventTwo : public ExEventBase<Ev_TestEventTwo> {};
class Ev_TestEventThree : public ExEventBase<Ev_TestEventThree> {};


//------------------------------------------------------------------------------
void ExFsmSmokeTests::check_EventTransition()
{
    QScopedPointer<ExStateMachine> stateMachine(new ExStateMachine());

    ExState * initialState = new ExState("Initial State");
    ExState * finalState = new ExState("Final State");

    stateMachine->addState(initialState);
    stateMachine->addState(finalState);
    
    stateMachine->setInitialState(initialState);

    new ExEventTransition(this, Ev_TestEventOne::eventType(), initialState, finalState);

    QSignalSpy spy(finalState, SIGNAL(entered()));

    stateMachine->start();
    QTestEventLoop::instance().enterLoop(1);

    stateMachine->postEvent(new Ev_TestEventOne());
    QTestEventLoop::instance().enterLoop(1);

    QCOMPARE(spy.count(), 1);
}


//------------------------------------------------------------------------------
void ExFsmSmokeTests::check_UnexpectedEventHandler()
{
    QScopedPointer<ExStateMachine> stateMachine(new ExStateMachine());

    ExState * initialState = new ExState("Initial State");
    ExState * finalState = new ExState("Final State");

    stateMachine->addState(initialState);
    stateMachine->addState(finalState);
    stateMachine->setInitialState(initialState);

    new ExEventTransition(this, Ev_TestEventOne::eventType(), initialState, finalState);
    stateMachine->start();

    QSignalSpy spy(initialState, SIGNAL(unexpectedEvent(ExEvent *)));

    QTestEventLoop::instance().enterLoop(1);

    stateMachine->postEvent(new Ev_TestEventTwo());
    QTestEventLoop::instance().enterLoop(1);

    QCOMPARE(spy.count(), 1);
}


//------------------------------------------------------------------------------
void ExFsmSmokeTests::check_RePostOfNotSuitableEvents()
{
    QScopedPointer<ExStateMachine> stateMachine(new ExStateMachine());

    ExState * initialState = new ExState("Initial State");
    ExState * middleState = new ExState("Middle State");
    ExState * finalState = new ExState("Final State");

    stateMachine->addState(initialState);
    stateMachine->addState(middleState);
    stateMachine->addState(finalState);
    
    stateMachine->setInitialState(initialState);

    initialState->addToSavedEventsList(Ev_TestEventTwo::eventType());

    new ExEventTransition(this, Ev_TestEventOne::eventType(), initialState, middleState);
    new ExEventTransition(this, Ev_TestEventTwo::eventType(), middleState, finalState);

    QSignalSpy spy(finalState, SIGNAL(entered()));

    stateMachine->start();
    QTestEventLoop::instance().enterLoop(1);

    stateMachine->postEvent(new Ev_TestEventTwo());
    QTestEventLoop::instance().enterLoop(1);

    stateMachine->postEvent(new Ev_TestEventOne());
    QTestEventLoop::instance().enterLoop(1);
    
    QCOMPARE(spy.count(), 1);
}


//------------------------------------------------------------------------------
void ExFsmSmokeTests::check_MultiEventTransition()
{
    /*
    QScopedPointer<ExStateMachine> stateMachine(new ExStateMachine());

    ExState * initialState = new ExState("Initial State");
    ExState * finalState = new ExState("Final State");

    stateMachine->addState(initialState);
    stateMachine->addState(finalState);
    stateMachine->setInitialState(initialState);

    QList<QEvent::Type> events;
    events << Ev_TestEventOne::eventType()
           << Ev_TestEventTwo::eventType();

    new ExMultiEventTransition(this, events, initialState, finalState);
    stateMachine->start();
    QTestEventLoop::instance().enterLoop(1);

    QSignalSpy spy(finalState, SIGNAL(entered()));

    stateMachine->postEvent(new Ev_TestEventTwo());
    QTestEventLoop::instance().enterLoop(1);

    QCOMPARE(spy.count(), 0);

    stateMachine->postEvent(new Ev_TestEventOne());
    QTestEventLoop::instance().enterLoop(1);

    QCOMPARE(spy.count(), 1);
    */
}

