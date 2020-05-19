import pydp as dp


class TestBoundedStandardDeviation:
    def test_c_api(self):
        a = [1, 5, 7, 9, 13]

        bsd = dp.BoundedStandardDeviation(1.0, 0, 15)
        result = bsd.result(a)
        assert type(result) is float
