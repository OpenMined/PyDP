import pytest

import pydp._pydp as dp
from pydp.algorithms.quantile_tree import QuantileTree


class TestQuntileTree:
    def test_creation_and_properties(self):
        lower_bound, upper_bound = 0, 123
        height, branching_factor = 5, 10
        tree = QuantileTree(lower_bound, upper_bound, height, branching_factor)

        assert height == tree.height
        assert branching_factor == tree.branching_factor

        memory_used_initial = tree.memory_used
        assert memory_used_initial > 0

        tree.add_entry(10)
        memory_used_after_adding_elements = tree.memory_used
        assert memory_used_after_adding_elements > memory_used_initial

    def test_quantiles(self):
        lower, upper = 0, 1000
        height, branching_factor = 5, 10
        tree = QuantileTree(lower, upper, height, branching_factor)

        # Add elements 0,..1000 to the tree.
        for i in range(1001):
            tree.add_entry(i)

        # Use high epsilon, which means small noise and close to the real quantiles.
        eps, delta = 10000, 0
        quantiles_to_compute = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.9, 0.9]
        dp_quantiles = tree.compute_quantiles(
            eps, delta, 1, 1, quantiles_to_compute, "laplace"
        )

        # Check that DP quantiles are close to expected.
        for quantile, dp_quantile in zip(quantiles_to_compute, dp_quantiles):
            expected_quantile = quantile * upper
            assert abs(expected_quantile - dp_quantile) < 0.1

    def test_quantiles_and_confidence_intervals(self):
        lower, upper = 0, 1000
        height, branching_factor = 5, 10
        tree = QuantileTree(lower, upper, height, branching_factor)

        # Add elements 0,..1000 to the tree.
        for i in range(1001):
            tree.add_entry(i)

        # Use high epsilon, which means small noise and close to the real quantiles.
        eps, delta = 10000, 0
        quantiles_to_compute = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.9, 0.9]
        dp_quantiles_and_confidence_intervals = (
            tree.compute_quantiles_and_confidence_intervals(
                eps, delta, 1, 1, quantiles_to_compute, 0.95, "laplace"
            )
        )

        # Check that DP quantiles are close to expected.
        for quantile, dp_quantile_ci in zip(
            quantiles_to_compute, dp_quantiles_and_confidence_intervals
        ):
            expected_quantile = quantile * upper
            assert abs(expected_quantile - dp_quantile_ci.quantile) < 0.01
            assert (
                dp_quantile_ci.lower_bound
                <= dp_quantile_ci.quantile
                <= dp_quantile_ci.upper_bound
            )
            assert dp_quantile_ci.upper_bound - dp_quantile_ci.lower_bound < 0.01

    def test_serialize_deserialize(self):
        lower, upper = 0, 1000
        height, branching_factor = 5, 10
        tree1 = QuantileTree(lower, upper, height, branching_factor)

        # Add elements 0,..1000 to the tree.
        for i in range(1001):
            tree1.add_entry(i)

        serialized_tree = tree1.serialize().to_bytes()

        # Deserialize
        # 1.Create empty tree with the same parameters.
        tree2 = QuantileTree(lower, upper, height, branching_factor)
        # 2. Merge serialized_tree to tree2.
        tree2.merge(dp.bytes_to_summary(serialized_tree))

        # Check that tree2 computes correct quantiles. For this use high
        # epsilon, which means small noise and close to the real quantiles.
        eps, delta = 10000, 0
        quantiles_to_compute = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.9, 0.9]
        dp_quantiles = tree2.compute_quantiles(
            eps, delta, 1, 1, quantiles_to_compute, "laplace"
        )

        # Check that DP quantiles are close to expected.
        for quantile, dp_quantile in zip(quantiles_to_compute, dp_quantiles):
            expected_quantile = quantile * upper
            assert abs(expected_quantile - dp_quantile) < 0.1
