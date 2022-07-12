# third party
import pytest

# pydp absolute
import pydp._pydp as dp
import pydp.algorithms.laplacian as py_algos

import sys
import tempfile


def test_count_serialization_deserialization():
    dp_count1 = py_algos.Count(epsilon=20000.0)  # large epsilon, noise std < 1e-4
    dp_count1.add_entries([1] * 100)

    assert dp_count1.result() == 100

    bytes = dp_count1.serialize().to_bytes()

    # Deserialize from bytes. Unfortunetely the C++ library doesn't have
    # deserialize method, so we need to do it in 3 steps.
    # 1.Create an empty object with the same parameters.
    dp_count2 = py_algos.Count(epsilon=20000.0)
    # 2.Convert bytes to summary
    summary = dp.bytes_to_summary(bytes)
    # 3.Merge summary
    dp_count2.merge(summary)

    assert dp_count2.result() == 100


def test_summary_serialiazation():
    dp_algos = [
        py_algos.Count(epsilon=3),
        py_algos.BoundedSum(epsilon=1),
        py_algos.BoundedMean(epsilon=2),
        py_algos.BoundedVariance(epsilon=1),
    ]

    for algo in dp_algos:
        summary1 = algo.serialize()
        bytes1 = summary1.to_bytes()
        summary2 = dp.bytes_to_summary(bytes1)
        bytes2 = summary2.to_bytes()

        assert bytes1 == bytes2


@pytest.mark.skipif(
    sys.platform == "win32", reason="Save/Load() don't work on Windows."
)
def test_save_load():
    dp_count1 = py_algos.Count(epsilon=20000.0)  # large epsilon, noise std < 1e-4
    dp_count1.add_entries([1] * 100)

    assert dp_count1.result() == 100
    with tempfile.NamedTemporaryFile() as temp_file:
        dp_count1.serialize().save(temp_file.name)

        summary = dp.Summary()
        summary.load(temp_file.name)
        # Create Count algorithm object from summary.
        dp_count2 = py_algos.Count(epsilon=20000.0)
        dp_count2.merge(summary)

        # Check that dp_count2 has the same data as dp_count1.
        assert dp_count2.result() == 100
