# third party
import pytest

# pydp absolute
import pydp._pydp as dp
import pydp.algorithms.laplacian as py_algos

# Regression tests for #413: the bindings used to collapse every non-OK
# absl::Status coming back from the DP library into a plain RuntimeError,
# no matter what actually went wrong. That made it impossible to tell "you
# passed a bad argument" apart from "something failed internally" without
# parsing the exception message. These tests pin down the exception types
# for the status codes that are easy to trigger deterministically from
# Python: InvalidArgument (now ValueError) and Internal (still RuntimeError,
# since there's no better built-in fit).


def test_double_result_raises_value_error_not_runtime_error():
    # The DP library refuses to hand out a result twice for the same
    # epsilon/delta budget and returns an InvalidArgument status for the
    # second call. That should surface as a ValueError.
    count = py_algos.Count(epsilon=1.0)
    count.add_entries([1] * 10)

    count.result()
    with pytest.raises(ValueError):
        count.result()


def test_double_result_error_is_not_a_bare_runtime_error():
    # Guard against a ValueError subclassing RuntimeError one day and this
    # test passing for the wrong reason.
    count = py_algos.Count(epsilon=1.0)
    count.add_entries([1] * 10)
    count.result()

    with pytest.raises(ValueError) as exc_info:
        count.result()
    assert not isinstance(exc_info.value, RuntimeError)


def test_merge_empty_summary_still_raises_runtime_error():
    # Merging an empty Summary trips an Internal status in the DP library
    # (there's no count data to merge). Internal errors don't have an
    # obviously-better built-in Python exception, so they should keep
    # raising RuntimeError, same as before this change.
    count = py_algos.Count(epsilon=1.0)

    with pytest.raises(RuntimeError):
        count.merge(dp.Summary())
