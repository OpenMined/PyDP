# pydp absolute
from pydp.util import Geometric  # type: ignore
from pydp.util import UniformDouble  # type: ignore


def test_rand_UniformDouble():
    ud = UniformDouble()
    assert isinstance(ud, float)
    assert 0 <= ud < 1


def test_rand_Geometric():
    gn = Geometric()
    assert isinstance(gn, int)
    assert 0 <= gn <= 1025
