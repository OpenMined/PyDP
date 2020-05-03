import pytest
import pydp as dp

def test_rand_UniformDouble():
	ud = dp.UniformDouble()
	assert isinstance(ud,float)
def test_rand_Geometric():
	gn = dp.Geometric()
	assert isinstance(gn,int)
