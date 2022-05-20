import pytest
from pydp.ml.mechanisms.sklearn_pipeline import LaplaceMechanism
import numbers
import numpy as np

class TestLocalDP:
    def test_epsilon_type(self):
        assert isinstance(LaplaceMechanism().epsilon,numbers.Number)
    def test_epsilon_val(self):
        assert LaplaceMechanism().epsilon > 0
    
    def test_sensitivity(self):
        if(isinstance(LaplaceMechanism().sensitivity, numbers.Number)):
            assert LaplaceMechanism().sensitivity > 0

    @pytest.mark.parametrize("array", [np.array([[1,2,4,5],[7,8,9,10]])])
    def test_sensitivity_calculation(self,array):
        sensitivity_example=sensitivity_callable()
        noisy_array=LaplaceMechanism(epsilon=1,sensitivity=sensitivity_example).sensitivity_calculation(array)
        assert isinstance(noisy_array,np.ndarray)
        assert array.shape==noisy_array.shape
        assert noisy_array.ndim==2
    
class sensitivity_callable:
    def __call__(self,x):
        return abs(x[0]-0.1)




