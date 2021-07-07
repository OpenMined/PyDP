import numpy as np
import pytest
import pydp as dp
from pydp.algorithms import create_partition_strategy

k_N_SIMS = 1000000
k_THRESHOLD = 1e-1


def assert_rel_close(val_true, val_pred, thresh):
    assert np.abs(1 - val_pred / val_true) < thresh


def adjust_epsilon(epsilon, max_partitions):
    return epsilon / max_partitions


def adjust_delta(delta, max_partitions):
    if delta == 1:
        return 1
    return -np.expm1(np.log1p(-delta) / max_partitions)


class TestTruncatedGeometric:
    @staticmethod
    def probability_of_keep(n, adjusted_epsilon, adjusted_delta):
        if n == 0:
            return 0
        crossover1 = 1 + np.floor(
            np.log1p(np.tanh(adjusted_epsilon / 2) * (1 / adjusted_delta - 1))
            / adjusted_epsilon
        )

        if n <= crossover1:
            return (
                np.expm1(n * adjusted_epsilon) / np.expm1(adjusted_epsilon)
            ) * adjusted_delta
        prob_of_keep_crossover1 = TestTruncatedGeometric.probability_of_keep(
            crossover1, adjusted_epsilon, adjusted_delta
        )

        crossover2 = crossover1 + np.floor(
            (1.0 / adjusted_epsilon)
            * np.log1p(
                (np.expm1(adjusted_epsilon) / adjusted_delta)
                * (1 - prob_of_keep_crossover1)
            )
        )
        if n > crossover2:
            return 1

        m = n - crossover1
        return prob_of_keep_crossover1 - (
            1 - prob_of_keep_crossover1 + (adjusted_delta / np.expm1(adjusted_epsilon))
        ) * np.expm1(-m * adjusted_epsilon)

    @pytest.mark.parametrize(
        ["num_users", "epsilon", "delta", "max_partitions_contributed"],
        [
            ([6, 10, 13], 1, 1e-5, 1),
            ([160, 180, 220], 0.1, 1e-10, 1),
            ([30, 50, 70], 1, 1e-5, 5),
            ([1000, 1500, 2000], 0.1, 1e-7, 10),
        ],
    )
    def test_theoretic_values(
        self, num_users, epsilon, delta, max_partitions_contributed
    ):
        adjusted_epsilon = adjust_epsilon(epsilon, max_partitions_contributed)
        adjusted_delta = adjust_delta(delta, max_partitions_contributed)
        partition_selector = create_partition_strategy(
            "truncated_geometric", epsilon, delta, max_partitions_contributed
        )
        for n in num_users:
            true_prob_of_keep = TestTruncatedGeometric.probability_of_keep(
                n, adjusted_epsilon, adjusted_delta
            )
            sims = []
            for _ in range(k_N_SIMS):
                sims.append(partition_selector.should_keep(n))
            pred_prob_of_keep = np.mean(sims)
            assert_rel_close(true_prob_of_keep, pred_prob_of_keep, k_THRESHOLD)


class TestLaplace:
    @staticmethod
    def probability_of_keep(n, epsilon, l1_sensitivity):
        # TODO - implement theoretic probability of keep.
        #   using the python exposed LaplaceMechanism.NoisedValueAboveTreshold
        return

    @pytest.mark.parametrize(
        ["num_users", "epsilon", "delta", "max_partitions_contributed"],
        [
            ([6, 10, 13], 1, 1e-5, 1),
            ([160, 180, 220], 0.1, 1e-10, 1),
            ([30, 50, 70], 1, 1e-5, 5),
            ([1000, 1500, 2000], 0.1, 1e-7, 10),
        ],
    )
    def test_theoretic_values(
        self, num_users, epsilon, delta, max_partitions_contributed
    ):
        # TODO - Uncomment when implemented true_prob_of keep
        # adjusted_epsilon = adjust_epsilon(epsilon, max_partitions_contributed)
        # adjusted_delta = adjust_delta(delta, max_partitions_contributed)
        # partition_selector = create_partition_strategy(
        #     "truncated_geometric", epsilon, delta, max_partitions_contributed
        # )
        # for n in num_users:
        #     true_prob_of_keep = TestLaplace.probability_of_keep(
        #         n, adjusted_epsilon, adjusted_delta
        #     )
        #     sims = []
        #     for _ in range(k_N_SIMS):
        #         sims.append(partition_selector.should_keep(n))
        #     pred_prob_of_keep = np.mean(sims)
        #     assert_rel_close(true_prob_of_keep, pred_prob_of_keep, k_THRESHOLD)
        pass


class TestGaussian:
    @staticmethod
    def probability_of_keep(n, epsilon, l1_sensitivity):
        # TODO - implement theoretic probability of keep.
        #   using GaussianMechanism.NoisedValueAboveTreshold
        return

    @pytest.mark.parametrize(
        ["num_users", "epsilon", "delta", "max_partitions_contributed"],
        [
            ([6, 10, 13], 1, 1e-5, 1),
            ([160, 180, 220], 0.1, 1e-10, 1),
            ([30, 50, 70], 1, 1e-5, 5),
            ([1000, 1500, 2000], 0.1, 1e-7, 10),
        ],
    )
    def test_theoretic_values(
        self, num_users, epsilon, delta, max_partitions_contributed
    ):
        # TODO - Uncomment when implemented true_prob_of keep
        # adjusted_epsilon = adjust_epsilon(epsilon, max_partitions_contributed)
        # adjusted_delta = adjust_delta(delta, max_partitions_contributed)
        # partition_selector = create_partition_strategy(
        #     "truncated_geometric", epsilon, delta, max_partitions_contributed
        # )
        # for n in num_users:
        #     true_prob_of_keep = TestGaussian.probability_of_keep(
        #         n, adjusted_epsilon, adjusted_delta
        #     )
        #     sims = []
        #     for _ in range(k_N_SIMS):
        #         sims.append(partition_selector.should_keep(n))
        #     pred_prob_of_keep = np.mean(sims)
        #     assert_rel_close(true_prob_of_keep, pred_prob_of_keep, k_THRESHOLD)
        pass
