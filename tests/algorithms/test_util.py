# stdlib
import math

# pydp absolute
import pydp as dp


def test_default_epsilon():
    assert dp.util.default_epsilon() == math.log(3)


def test_next_power_positive():
    kTolerance = 1e-5
    npp1 = dp.util.get_next_power_of_two(3.0)
    npp2 = dp.util.get_next_power_of_two(5.0)
    npp3 = dp.util.get_next_power_of_two(7.9)
    assert abs(npp1 - 4) < kTolerance
    assert abs(npp2 - 8) < kTolerance
    assert abs(npp3 - 8) < kTolerance


def test_next_power_exact_positive():
    kTolerance = 1e-5
    npep1 = dp.util.get_next_power_of_two(2.0)
    npep2 = dp.util.get_next_power_of_two(8.0)
    assert abs(npep1 - 2) < kTolerance
    assert abs(npep2 - 8) < kTolerance


def test_next_power_one():
    kTolerance = 1e-5
    npo = dp.util.get_next_power_of_two(1.0)
    assert abs(npo - 1) < kTolerance


def test_next_power_negative():
    kTolerance = 1e-5
    npn1 = dp.util.get_next_power_of_two(0.4)
    npn2 = dp.util.get_next_power_of_two(0.2)
    assert abs(npn1 - 0.5) < kTolerance
    assert abs(npn2 - 0.25) < kTolerance


def test_next_power_exact_negative():
    kTolerance = 1e-5
    npn1 = dp.util.get_next_power_of_two(0.5)
    npn2 = dp.util.get_next_power_of_two(0.125)
    assert abs(npn1 - 0.5) < kTolerance
    assert abs(npn2 - 0.125) < kTolerance


# def test_round_positive():
#     kTolerance = 1e-5
#     rp1 = dp.util.round_to_nearest_multiple(4.9, 2.0)
#     rp2 = dp.util.round_to_nearest_multiple(5.1, 2.0)
#     assert abs(rp1 - 4) < kTolerance
#     assert abs(rp2 - 6) < kTolerance


# def test_round_negative():
#     kTolerance = 1e-5
#     rn1 = dp.util.round_to_nearest_multiple(-4.9, 2.0)
#     rn2 = dp.util.round_to_nearest_multiple(-5.1, 2.0)
#     assert abs(rn1 + 4) < kTolerance
#     assert abs(rn2 + 6) < kTolerance


# def test_round_positive_ties():
#     kTolerance = 1e-5
#     rpt = dp.util.round_to_nearest_multiple(5.0, 2.0)
#     assert abs(rpt - 6.0) < kTolerance


# def test_round_negative_ties():
#     kTolerance = 1e-5
#     rnt = dp.util.round_to_nearest_multiple(-5.0, 2.0)
#     assert abs(rnt + 4.0) < kTolerance


def test_statistics():
    a = [1.0, 5.0, 7.0, 9.0, 13.0]
    assert dp.util.mean(a) == 7.0
    assert dp.util.variance(a) == 16.0
    assert dp.util.standard_deviation(a) == 4.0
    assert dp.util.order_statistics(0.6, a) == 8.0
    assert dp.util.order_statistics(0, a) == 1.0
    assert dp.util.order_statistics(1, a) == 13.0


def test_vector_filter():
    v = [1.0, 2.0, 2.0, 3.0]
    selection = [False, True, True, False]
    expected = [2.0, 2.0]
    assert expected == dp.util.vector_filter(v, selection)


def test_vector_to_string():
    v = [1.0, 2.0, 2.0, 3.0]
    expected = "[1, 2, 2, 3]"
    assert dp.util.vector_to_string(v) == expected
