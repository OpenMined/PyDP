import pytest
from pydp.ml.mechanisms.sklearn_pipeline import LaplaceMechanism
import numbers
import numpy as np

class TestLocalDP:
    self.laplace_object=LaplaceMechanism()
    def test_epsilon_type(self):
        assert isinstance(self.laplace_object.epsilon,numbers.Number)
    def test_epsilon_val(self):
        assert self.laplace_object.epsilon > 0
    
    def test_sensitivity(self):
        if(isinstance(self.laplace_object.sensitivity, numbers.Number)):
            assert self.laplace_object.sensitivity > 0

    @pytest.mark.parametrize("array", [np.array([1,2,3,4]), np.array([[1,2,4,5],[7,8,9,10]])])
    def test_sensitivity_calculation(self,array):
        noisy_array=self.laplace_object.sensitivity_calculation(array)
        assert isinstance(noisy_array,np.array)
        assert array.shape==noisy_array.shape
        assert noisy_array.ndim==2
    




