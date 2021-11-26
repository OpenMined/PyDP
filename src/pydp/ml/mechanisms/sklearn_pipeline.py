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
    
    def __init__(self, epsilon=1.0, sensitivity=1, accountant=None, cat_feat_idxs=None, cat_sensitivity=None):
        
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
            
        accountant : BudgetAccountant or None, optional
            Accountant to keep track of privacy budget.
            
        cat_feat_idxs : list or None, optional
            List of integers identifying indicies of categorical features.
            
        cat_feat_idxs : list or None, optional
            List of integers identifying indicies of categorical features.
            
            
        Attributes
        -------
        epsilon
            Privacy budget to calculate noise.
            
        sensitivty
            Sensitivity of the mechanism to calculate noise.
        
        accountant
            Accountant to keep track of privacy budget.
            
        cat_feat_idxs
            List of indicies that identifies categorical features.
            
        cat_sensitivty
            Sensitivity of the mechanism to calculate noise for categorical data.
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
        
        if (cat_feat_idxs is not None and cat_sensitivity is None) or (cat_feat_idxs is None and cat_sensitivity is not None):
            raise ValueError("cat_feat_idxs cannot be None if cat_sensitivity, and vice versa.")
        
        # Check arguments for categorical support is provided
        self.categorical_exists = cat_feat_idxs is not None and cat_sensitivity is not None
            
        if self.categorical_exists:
            
            if not isinstance(sensitivity, numbers.Number):
                if not callable(sensitivity):
                    raise TypeError(f"Sensitivity  must be a number or callable. Got type {type(sensitivity)}.")
                    
            if isinstance(sensitivity, numbers.Number) and sensitivity <= 0:
                raise ValueError("Sensitivity must be at least larger than 0.")
                
            if len(cat_feat_idxs) == 0:
                raise ValueError("At least 1 categorical feature index must be provided.")
                
        self.cat_feat_idxs = cat_feat_idxs
        self.cat_sensitivity = cat_sensitivity
    
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
                if  self.categorical_exists and feature_idx in self.cat_feat_idxs: # Categorical support
                    
                    if isinstance(self.cat_sensitivity, numbers.Number):
                        sensitivity_ = self.cat_sensitivity
                    else:
                        sensitivity_ = self.cat_sensitivity(feature)
                        
                else:
                    if isinstance(self.sensitivity, numbers.Number):
                        sensitivity_ = self.sensitivity
                    else:
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
        X = self.sensitivity_calculation( X)
        return X