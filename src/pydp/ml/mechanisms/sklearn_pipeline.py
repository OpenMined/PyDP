import numbers

from ..util.accountant import BudgetAccountant
from .laplace import Laplace

from sklearn.base import BaseEstimator, TransformerMixin

import numpy as np

class LaplaceMechanism(BaseEstimator, TransformerMixin):
    """
        An SKLearn Pipeline operator for applying differentially private noise 
        addition using the laplace mechanism.
        Paper link: https://link.springer.com/content/pdf/10.1007/11681878_14.pdf
    """
    
    def __init__(self, epsilon=1.0, sensitivity=1, accountant=None):
        
        """
        Checks that all parameters of the mechanism have been initialised correctly, and that the mechanism is ready
        to be used.
        
        Parameters
        ----------
        epsilon : float or int
            The value of epsilon for achieving :math:`\epsilon`-differential privacy with the mechanism.  Must have
            `epsilon > 0`.
        
        sensitivity : float or int
            The sensitivity of the mechanism.  Must satisfy `sensitivity` > 0.
            
        accountant : BudgetAccountant, optional
            Accountant to keep track of privacy budget.
            
            
        Attributes
        -------
        epsilon
            Privacy budget to calculate noise.
            
        sensitivty
            Sensitivity of the mechanism to calculate noise.
        
        accountant
            Accountant to keep track of privacy budget.
        
        Raises
        ------
        TypeError
            If epsilon is not a number, or sensitivity is not a number or a callable.
            
        ValueError
            If epsilon less than 0, or sensitivty is a number but less than 0.
        """
        
        if not isinstance(epsilon, numbers.Number):
            raise TypeError(f"Epsilon  must be a number. Got type {type(epsilon)}.")

        if epsilon <= 0:
            raise ValueError("Epsilon must be at least larger than 0.")
            
        self.epsilon = epsilon
        
        if not isinstance(sensitivity, numbers.Number):
            if not callable(sensitivity):
                raise TypeError(f"Sensitivity  must be a number or callable. Got type {type(sensitivity)}.")

            
        if isinstance(sensitivity, numbers.Number) and sensitivity <= 0:
            raise ValueError("Sensitivity must be at least larger than 0.")
        
        self.sensitivity = sensitivity
        self.accountant = BudgetAccountant.load_default(accountant)
        
        self.laplace = None # If sensitivity is callable, set lapalace to None
        
        if not callable(sensitivity):
                self.laplace = Laplace()
    
    def sensitivity_calculation(self, X):
        """
        Perform local differential privacy by adding noise using Laplace mechanismto the dataset if the sensitivity 
        provided if a callable.
        
        
        Parameters
        ----------
        X : numpy.array
            Datset in the form of a 2-dimensional numpy array.
            
        Returns
        ------
        X : numpy.array
            Original parameter X with differentially private noise added.
        """
        
        n_feature = X.shape[-1]
        n_data = X.shape[0]

        
        for data_idx in range(n_data):
            self.accountant.check(self.epsilon, 0)
            for feature_idx in range(n_feature):
                
                # Array with data point data_idx removed for feature_idx
                feature = np.concatenate((X[:data_idx,feature_idx],X[data_idx + 1:,feature_idx]))
                
                # Calculate sensitivity
                sensitivity_ = self.sensitivity(feature)
                
                # Initialized Laplace mechanism instance
                laplace = Laplace().set_epsilon(self.epsilon).set_sensitivity(sensitivity_)
                
                # Add noise to the data point that was removed
                noised_value = laplace.randomise(X[data_idx,feature_idx])
                
                # Replaced data point in the dataset with noised version
                X[data_idx,feature_idx] = noised_value
                
                self.accountant.spend(self.epsilon, 0)
        return X
    
    
    def fit(self, X, y=None):
        return self

    def transform(self, X, y=None):
        if self.laplace is not None:
            self.laplace.set_epsilon(self.epsilon).set_sensitivity(self.sensitivity)
            vector_randomise = np.vectorize(self.laplace.randomise)
            noised_array = vector_randomise(X)
            return noised_array
        else:
            X = self.sensitivity_calculation( X)
            return X





# for gaussian
class GaussianMechanism(BaseEstimator, TransformerMixin):
    """
        An SKLearn Pipeline operator for applying differentially private noise 
        addition using the gaussian mechanism.
        
    """
    """ 
      static std::unique_ptr<dp::GaussianMechanism> build(double epsilon, double delta,
                                                      double l2_sensitivity) {
    dp::GaussianMechanism::Builder builder;
    builder.SetEpsilon(epsilon);
    builder.SetDelta(delta);
    builder.SetL2Sensitivity(l2_sensitivity);
    return downcast_unique_ptr<dp::GaussianMechanism, dp::NumericalMechanism>(
        builder.Build().value());
  }; 

  Gaussian depends on these parameters
  """
    def __init__(self, epsilon=1.0, delta=1.0, sensitivity=1, accountant=None):
        """
        Checks that all parameters of the mechanism have been initialised correctly, and that the mechanism is ready
        to be used.
        
        Parameters
        ----------
        epsilon : float or int
            The value of epsilon for achieving :math:`\epsilon`-differential privacy with the mechanism.  Must have
            `epsilon > 0`.
        
        sensitivity : float or int
            The sensitivity of the mechanism.  Must satisfy `sensitivity` > 0.
            
        accountant : BudgetAccountant, optional
            Accountant to keep track of privacy budget.
            
            
        Attributes
        -------
        epsilon
            Privacy budget to calculate noise.
            
        sensitivty
            Sensitivity of the mechanism to calculate noise.
        
        accountant
            Accountant to keep track of privacy budget.
        
        Raises
        ------
        TypeError
            If epsilon is not a number, or sensitivity is not a number or a callable.
            
        ValueError
            If epsilon less than 0, or sensitivty is a number but less than 0.
        """
        
        if not isinstance(epsilon, numbers.Number):
            raise TypeError(f"Epsilon  must be a number. Got type {type(epsilon)}.")

        if epsilon <= 0:
            raise ValueError("Epsilon must be at least larger than 0.")
            
        self.epsilon = epsilon
        
        if not isinstance(sensitivity, numbers.Number):
            if not callable(sensitivity):
                raise TypeError(f"Sensitivity  must be a number or callable. Got type {type(sensitivity)}.")

            
        if isinstance(sensitivity, numbers.Number) and sensitivity <= 0:
            raise ValueError("Sensitivity must be at least larger than 0.")
        
        self.sensitivity = sensitivity
        self.accountant = BudgetAccountant.load_default(accountant)
        
        self.gaussian = None
        
        if not callable(sensitivity):
                self.gaussian = Gaussian()

    def sensitivity_calculation(self, X):
        """
        Perform local differential privacy by adding noise using Laplace mechanismto the dataset if the sensitivity 
        provided if a callable.
        
        
        Parameters
        ----------
        X : numpy.array
            Datset in the form of a 2-dimensional numpy array.
            
        Returns
        ------
        X : numpy.array
            Original parameter X with differentially private noise added.
        """
        
        n_feature = X.shape[-1]
        n_data = X.shape[0]

        
        for data_idx in range(n_data):
            self.accountant.check(self.epsilon, 0)
            for feature_idx in range(n_feature):
                
                # Array with data point data_idx removed for feature_idx
                feature = np.concatenate((X[:data_idx,feature_idx],X[data_idx + 1:,feature_idx]))
                
                # Calculate sensitivity
                sensitivity_ = self.sensitivity(feature)
                
                # Initialized Gaussian mechanism instance
                gaussian = Gaussian().set_epsilon(self.epsilon).set_sensitivity(sensitivity_)
                
                # Add noise to the data point that was removed
                noised_value = gaussian.randomise(X[data_idx,feature_idx])
                
                # Replaced data point in the dataset with noised version
                X[data_idx,feature_idx] = noised_value
                
                self.accountant.spend(self.epsilon, 0)
        return X

    def fit(self, X, y=None):
        return self

    def transform(self, X, y=None):
        if self.gaussian is not None:
            self.gaussian.set_epsilon(self.epsilon).set_sensitivity(self.sensitivity)
            vector_randomise = np.vectorize(self.gaussian.randomise)
            noised_array = vector_randomise(X)
            return noised_array
        else:
            X = self.sensitivity_calculation( X)
            return X

        
    


# geometric has lambda
def GeometricMechanism(BaseEstimator, TransformerMixin):
    """
        An SKLearn Pipeline operator for applying differentially private noise 
        addition using the geometric mechanism.
        
    """

    def __init__(self, lambda_=1.0, sensitivity=1, accountant=None):
            
            """
            Checks that all parameters of the mechanism have been initialised correctly, and that the mechanism is ready
            to be used.
            
            Parameters
            ----------
            lambda_ : float or int
                The value of lambda for achieving :math:`\lambda`-differential privacy with the mechanism.  Must have
                `lambda > 0`.
            
            sensitivity : float or int
                The sensitivity of the mechanism.  Must satisfy `sensitivity` > 0.
                
            accountant : BudgetAccountant, optional
                Accountant to keep track of privacy budget.
                
                
            Attributes
            -------
            lambda_
                Privacy budget to calculate noise.
                
            sensitivty
                Sensitivity of the mechanism to calculate noise.
            
            accountant
                Accountant to keep track of privacy budget.
            
            Raises
            ------
            TypeError
                If lambda_ is not a number, or sensitivity is not a number or a callable.
                
            ValueError
                If lambda_ less than 0, or sensitivty is a number but less than 0.
            """
            
            if not isinstance(lambda_, numbers.Number):
                raise TypeError(f"Lambda  must be a number. Got type {type(lambda_)}.")
    
            if lambda_ <= 0:
                raise ValueError("Lambda must be at least larger than 0.")
                
            self.lambda_ = lambda_
            
            if not isinstance(sensitivity, numbers.Number):
                if not callable(sensitivity):
                    raise TypeError(f"Sensitivity  must be a number or callable. Got type {type(sensitivity)}.")
    
                
            if isinstance(sensitivity, numbers.Number) and sensitivity <= 0:
                raise ValueError("Sensitivity must be at least larger than 0.")
            
            self.sensitivity = sensitivity
            self.accountant = BudgetAccountant.
            self.BaseEstimator = BaseEstimator
            self.TransformerMixin = TransformerMixin
             
    def fit(self, X, y=None):
        return self

    def transform(self, X, y=None):
        if self.geometric is not None:
            self.geometric.set_delta(self.delta).set_sensitivity(self.sensitivity)
            vector_randomise = np.vectorize(self.geometric.randomise)
            noised_array = vector_randomise(X)
            return noised_array
        else:
            X = self.sensitivity_calculation( X)
            return X
    