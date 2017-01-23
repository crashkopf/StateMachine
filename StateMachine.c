#include "debug.h"
#include "StateMachine.h"
/*
  Run tests to check if we need to transition states.  The first positive test will cause a transition.  If all tests come back negative the
  current state operation will run.
*/
void FSMProcess(struct FSMContext * c) {
	(void) c;
	int j = 0;

	while (c->currentState->tests[j].test) {
		// Execute the test function and transition state if it returns true
		if (c->currentState->tests[j].test(c)) {
			debug("Test \"%s\" returned true.\n", c->currentState->tests[j].name);
			FSMTransition(c, c->currentState->tests[j].nextState);
			return; // Return.  Don't run any more tests or the main operation.
		}
		j++;
	}
	// If an operation exists for the current state, run it.
	if (c->currentState->op) c->currentState->op(c);
}

void FSMTransition(struct FSMContext * c, const struct FSMState * s) {
	if (c && s) { // NULL check
		// Call the exit function of the current state, if it exists
		if (c->currentState && c->currentState->exit) {
			c->currentState->exit(c);
			debug ("%s exit function ran.\n", c->currentState->name);
		}
		// Transistion to the new state
		c->currentState = s;
		debug ("State transition to %s.\n", c->currentState->name);
		// Call the entry function of the new state
		if (c->currentState->entry) {
			c->currentState->entry(c);
			debug ("%s entry function ran.\n", c->currentState->name);
		}
	}
}
