pragma experimental SMTChecker;
contract C {
	int public x;

	function f() public view {
		try this.x() returns (int v) {
			assert(x == v); // should hold
		} catch {
			assert(false); // this fails, because we over-approximate every external call in the way that it can both succeed and fail
		}
	}
}
// ----
// Warning 6328: (171-184): CHC: Assertion violation happens here.\nCounterexample:\nx = 0\n\n\n\nTransaction trace:\nC.constructor()\nState: x = 0\nC.f()