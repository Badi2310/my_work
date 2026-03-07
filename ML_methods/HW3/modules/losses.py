import numpy as np


class BaseLoss:
    """
    Base class for loss function.
    """

    def func(self, X, y, w):
        """
        Get loss function value at w.
        """
        raise NotImplementedError('Func oracle is not implemented.')

    def grad(self, X, y, w):
        """
        Get loss function gradient value at w.
        """
        raise NotImplementedError('Grad oracle is not implemented.')


class LinearLoss(BaseLoss):
    """
    Loss function for linear regression.
    It should support l2 regularization.
    """

    def __init__(self, l2_coef):
        """
        Parameters
        ----------
        l2_coef - l2 regularization coefficient
        """
        self.l2_coef = l2_coef

    def func(self, X, y, w):
        """
        Get loss function value for data X, target y and coefficient w.

        Parameters
        ----------
        X : scipy.sparse.csr_matrix or numpy.ndarray
        y : 1d numpy.ndarray
        w : 1d numpy.ndarray

        Returns
        -------
        : float
        """

        N = X.shape[0]
        mse_part = np.dot((X @ w - y),(X @ w - y)) / N
        reg_part = self.l2_coef * (w[1:].T @ w[1:])
        
        return float(mse_part + reg_part)

    def grad(self, X, y, w):
        """
        Get loss function gradient for data X, target y and coefficient w.

        Parameters
        ----------
        X : scipy.sparse.csr_matrix or numpy.ndarray
        y : 1d numpy.ndarray
        w : 1d numpy.ndarray
        Returns
        -------
        : 1d numpy.ndarray
        """

        N = X.shape[0]
        mse_part = 2*X.T.dot(X@w - y) / N
        reg_part = np.zeros_like(w)
        reg_part[1:] = 2*self.l2_coef * w[1:]
        
        return mse_part + reg_part
