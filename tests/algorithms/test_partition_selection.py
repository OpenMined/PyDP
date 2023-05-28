import numpy as np
import pytest
from pydp.algorithms.partition_selection import create_partition_strategy

N_SIMULATIONS = 100000
ACCURACY_THRESHOLD = 1e-1


class TestPartitionSelection:
    @pytest.mark.parametrize(
        [
            "num_users",
            "epsilon",
            "delta",
            "max_partitions_contributed",
            "expected_prob",
        ],
        [
            (10, 1, 1e-5, 1, 0.12818308050524607),
            (700, 0.2, 1e-7, 10, 0.5800625857189882),
        ],
    )
    def test_truncated_geometric(
        self, num_users, epsilon, delta, max_partitions_contributed, expected_prob
    ):
        partition_selector = create_partition_strategy(
            "truncated_geometric", epsilon, delta, max_partitions_contributed
        )
        assert epsilon == partition_selector.epsilon
        assert delta == partition_selector.delta
        assert (
            max_partitions_contributed == partition_selector.max_partitions_contributed
        )
        prob_of_keep = partition_selector.probability_of_keep(num_users)
        assert prob_of_keep == pytest.approx(expected_prob)

        sims = [partition_selector.should_keep(num_users) for _ in range(N_SIMULATIONS)]
        pred_prob_of_keep = np.mean(sims)
        assert pred_prob_of_keep == pytest.approx(expected_prob, ACCURACY_THRESHOLD)

    @pytest.mark.parametrize(
        [
            "num_users",
            "epsilon",
            "delta",
            "max_partitions_contributed",
            "expected_prob",
        ],
        [
            (10, 1, 1e-5, 1, 0.08103083927575383),
            (700, 0.2, 1e-7, 10, 0.011787911768969317),
        ],
    )
    def test_laplace_keep_and_return_noised_value(
        self, num_users, epsilon, delta, max_partitions_contributed, expected_prob
    ):
        partition_selector = create_partition_strategy(
            "laplace", epsilon, delta, max_partitions_contributed
        )
        assert epsilon == partition_selector.epsilon
        assert delta == partition_selector.delta
        assert (
            max_partitions_contributed == partition_selector.max_partitions_contributed
        )
        prob_of_keep = partition_selector.probability_of_keep(num_users)
        assert prob_of_keep == pytest.approx(expected_prob)

        sims = [partition_selector.should_keep(num_users) for _ in range(N_SIMULATIONS)]
        pred_prob_of_keep = np.mean(sims)
        assert pred_prob_of_keep == pytest.approx(expected_prob, ACCURACY_THRESHOLD)

        noised_values = [
            partition_selector.noised_value_if_should_keep(num_users)
            for _ in range(N_SIMULATIONS)
        ]
        noised_values = [v for v in noised_values if v]
        assert len(noised_values) / N_SIMULATIONS == pytest.approx(
            expected_prob, ACCURACY_THRESHOLD
        )
        assert all([(v >= partition_selector.threshold) for v in noised_values])

    @pytest.mark.parametrize(
        [
            "num_users",
            "epsilon",
            "delta",
            "max_partitions_contributed",
            "expected_prob",
        ],
        [
            (10, 1, 1e-5, 1, 0.017845473615190732),
            (1100, 0.2, 1e-7, 10, 1.0),
        ],
    )
    def test_gaussian_keep_and_return_noised_value(
        self, num_users, epsilon, delta, max_partitions_contributed, expected_prob
    ):
        partition_selector = create_partition_strategy(
            "gaussian", epsilon, delta, max_partitions_contributed
        )
        assert epsilon == partition_selector.epsilon
        assert delta == partition_selector.delta
        assert (
            max_partitions_contributed == partition_selector.max_partitions_contributed
        )
        prob_of_keep = partition_selector.probability_of_keep(num_users)
        assert prob_of_keep == pytest.approx(expected_prob)

        sims = [partition_selector.should_keep(num_users) for _ in range(N_SIMULATIONS)]
        pred_prob_of_keep = np.mean(sims)
        assert pred_prob_of_keep == pytest.approx(expected_prob, ACCURACY_THRESHOLD)

        noised_values = [
            partition_selector.noised_value_if_should_keep(num_users)
            for _ in range(N_SIMULATIONS)
        ]
        noised_values = [v for v in noised_values if v]
        assert len(noised_values) / N_SIMULATIONS == pytest.approx(
            expected_prob, ACCURACY_THRESHOLD
        )
        assert all([(v >= partition_selector.threshold) for v in noised_values])

    @pytest.mark.parametrize(
        [
            "num_users",
            "strategy",
            "epsilon",
            "delta",
            "max_partitions_contributed",
            "pre_threshold",
            "expected_probs",
        ],
        [
            (
                [10, 99, 109, 200],
                "truncated_geometric",
                1,
                1e-5,
                1,
                100,
                [0, 0, 0.12818308050524607, 1],
            ),
            (
                [10, 99, 109, 200],
                "laplace",
                1,
                1e-5,
                1,
                100,
                [0, 0, 0.08103083927575383, 1],
            ),
            (
                [10, 99, 109, 200],
                "gaussian",
                1,
                1e-5,
                1,
                100,
                [0, 0, 0.017845473615190732, 1],
            ),
        ],
    )
    def test_pre_thresholding(
        self,
        num_users,
        strategy,
        epsilon,
        delta,
        max_partitions_contributed,
        pre_threshold,
        expected_probs,
    ):
        partition_selector = create_partition_strategy(
            strategy, epsilon, delta, max_partitions_contributed, pre_threshold
        )
        assert epsilon == partition_selector.epsilon
        assert delta == partition_selector.delta
        assert (
            max_partitions_contributed == partition_selector.max_partitions_contributed
        )
        assert pre_threshold == partition_selector.pre_threshold

        for n_users, expected_prob in zip(num_users, expected_probs):
            prob_of_keep = partition_selector.probability_of_keep(n_users)
            assert prob_of_keep == pytest.approx(expected_prob)

            sims = [
                partition_selector.should_keep(n_users) for _ in range(N_SIMULATIONS)
            ]
            if n_users < pre_threshold:
                assert sum(sims) == 0
            else:
                pred_prob_of_keep = np.mean(sims)
                assert pred_prob_of_keep == pytest.approx(
                    expected_prob, ACCURACY_THRESHOLD
                )
