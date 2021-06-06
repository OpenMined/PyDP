# third party
import pytest

# pydp absolute
from pydp.algorithms.laplacian import BoundedMean


class TestInitParams:
    def test_lower_bound_NaN(self):
        with pytest.raises(ValueError):
            mean = BoundedMean(
                1.0, lower_bound=float("NaN"), upper_bound=10.0, dtype="float"
            )

    def test_upper_bound_NaN(self):
        with pytest.raises(ValueError):
            count = BoundedMean(
                1.0, lower_bound=0.0, upper_bound=float("NaN"), dtype="float"
            )

    @pytest.mark.parametrize("lower_bound", ["-inf", "inf"])
    def test_lower_bound_inf(self, lower_bound):
        with pytest.raises(ValueError):
            mean = BoundedMean(
                1.0, lower_bound=float(lower_bound), upper_bound=10.0, dtype="float"
            )

    @pytest.mark.parametrize("upper_bound", ["-inf", "inf"])
    def test_upper_bound_inf(self, upper_bound):
        with pytest.raises(ValueError):
            count = BoundedMean(
                1.0, lower_bound=0.0, upper_bound=float(upper_bound), dtype="float"
            )

    @pytest.mark.parametrize(
        "bounds", [("-inf", "-inf"), ("-inf", "inf"), ("inf", "inf"), ("inf", "-inf")]
    )
    def test_setting_inf_bounds(self, bounds):
        with pytest.raises(ValueError):
            count = BoundedMean(
                1.0,
                lower_bound=float(bounds[0]),
                upper_bound=float(bounds[1]),
                dtype="float",
            )
