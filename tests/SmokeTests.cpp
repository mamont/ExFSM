#include "SmokeTests.hpp"

#include <QtCore/QScopedPointer>

#include <ExFSM/ExStateMachine>
#include <ExFSM/ExState>
#include <ExFSM/ExEvent>
#include <ExFSM/ExEventTransition>
#include <ExFSM/ExMultiEventTransition>
#include <ExFSM/ExConditionalTransition>

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

    stateMachine->putEvent(new Ev_TestEventOne());
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

    stateMachine->putEvent(new Ev_TestEventTwo());
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

    stateMachine->putEvent(new Ev_TestEventTwo());
    QTestEventLoop::instance().enterLoop(1);

    stateMachine->putEvent(new Ev_TestEventOne());
    QTestEventLoop::instance().enterLoop(1);
    
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void ExFsmSmokeTests::check_ConditionalTransition()
{
    QScopedPointer<ExStateMachine> stateMachine(new ExStateMachine());

    ExState * initialState = new ExState("Initial State");
    ExState * middleState = new ExState("Middle State");
    ExState * deadLockState = new ExState("DeadLock State");
    ExState * finalState = new ExState("Final State");

    stateMachine->addState(initialState);
    stateMachine->addState(middleState);
    stateMachine->addState(deadLockState);
    stateMachine->addState(finalState);

    stateMachine->setInitialState(initialState);

    new ExEventTransition(this, Ev_TestEventOne::eventType(), initialState, middleState);

    new ExConditionalTransition(this
                                       , Ev_TestEventTwo::eventType()
                                       , middleState
                                       , deadLockState
                                       , [this](QEvent * ev) { return false; });

    new ExConditionalTransition(this
                                       , Ev_TestEventThree::eventType()
                                       , middleState
                                       , finalState
                                       , [this](QEvent * ev) {
                                            Ev_TestEventThree* answer = dynamic_cast<Ev_TestEventThree*> (ev);
                                            Q_ASSERT_X(answer, "Error", "Received wrong event");
                                            return true; }
                                );

    QSignalSpy spy(finalState, SIGNAL(entered()));

    stateMachine->start();
    QTestEventLoop::instance().enterLoop(1);

    stateMachine->putEvent(new Ev_TestEventOne());
    QTestEventLoop::instance().enterLoop(1);

    stateMachine->putEvent(new Ev_TestEventTwo());
    QTestEventLoop::instance().enterLoop(1);

    stateMachine->putEvent(new Ev_TestEventThree());
    QTestEventLoop::instance().enterLoop(1);

    QCOMPARE(spy.count(), 1);
}

void ExFsmSmokeTests::check_Actions()
{
    QScopedPointer<ExStateMachine> stateMachine(new ExStateMachine());

    ExState * initialState = new ExState("Initial State");
    ExState * middleState = new ExState("Middle State");
    ExState * finalState = new ExState("Final State");

    stateMachine->addState(initialState);
    stateMachine->addState(middleState);
    stateMachine->addState(finalState);

    stateMachine->setInitialState(initialState);

    new ExEventTransition(this, Ev_TestEventOne::eventType(), initialState, middleState
                          , ExTransitionActionsSequence()
                            << ExTransitionAction(&m_test, SLOT(doTest())));

    new ExConditionalTransition(this
                                       , Ev_TestEventTwo::eventType()
                                       , middleState
                                       , finalState
                                       , [this](QEvent * ev) { return true; }
                                       , ExTransitionActionsSequence()
                                         << ExTransitionAction(&m_test, SLOT(doTest())));

    QSignalSpy spy(finalState, SIGNAL(entered()));

    stateMachine->start();
    QTestEventLoop::instance().enterLoop(1);

    stateMachine->putEvent(new Ev_TestEventOne());
    QTestEventLoop::instance().enterLoop(1);
    QCOMPARE(m_test.isCalled(), true);
    m_test.clear();

    stateMachine->putEvent(new Ev_TestEventTwo());
    QTestEventLoop::instance().enterLoop(1);
    QCOMPARE(m_test.isCalled(), true);
    m_test.clear();


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

    stateMachine->putEvent(new Ev_TestEventTwo());
    QTestEventLoop::instance().enterLoop(1);

    QCOMPARE(spy.count(), 0);

    stateMachine->putEvent(new Ev_TestEventOne());
    QTestEventLoop::instance().enterLoop(1);

    QCOMPARE(spy.count(), 1);
    */
}

