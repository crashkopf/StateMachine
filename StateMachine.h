/*
 * This structure defines the current context of the state machine.
 * Right now it is just a name and a pointer to the current state
 */
struct FSMContext {
	const char * name;
	const struct FSMState * currentState;
};
/*
 * This structure defines a test, which consists of a name, a function that
 * returns non-zero for true and zero for false, and a pointer to the state
 * that should be tranisitioned to if the test function returns true.
 */
struct FSMTest {
	const char * name;
	int (*test)(struct FSMContext *);
	const struct FSMState * nextState;
};
/*
 * .name - the name of the state
 * .op - processing function of the state
 * .entry - function called when the state is entered
 * .exit - function called when the state is exited
 * .tests[] - array of tests to perform, must be terminated by a NULL test
 */
struct FSMState {
	const char * name;
	void (*op)(struct FSMContext *);
	void (*entry)(struct FSMContext *);
	void (*exit)(struct FSMContext *);
	const struct FSMTest tests[];
};

/*
 * FSMProcess - process the current state.  All tests are executed in the
 * order they are stored in the .tests[] array of the current state.  The
 * first positive test will result in a state transition.  If all tests are
 * negative the .op() function is executed.
 */
void FSMProcess(struct FSMContext *);
/*
 * FSMTransition - transition from the current state to a new state.  If an
 * exit function exists for the current state it is executed.  The context
 * state pointer is updated to the new state, then the entry function of the
 * new state is executed, if it exists.
 */
void FSMTransition(struct FSMContext *, const struct FSMState *);
