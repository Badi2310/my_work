import numpy as np
import time


class LinearModel:
    def __init__(
        self,
        loss_function,
        batch_size=None,
        step_alpha=1,
        step_beta=0, 
        tolerance=1e-5,
        max_iter=1000,
        random_seed=153,
        **kwargs
    ):
        """
        Parameters
        ----------
        loss_function : BaseLoss inherited instance
            Loss function to use
        batch_size : int
        step_alpha : float
        step_beta : float
            step_alpha and step_beta define the learning rate behaviour
        tolerance : float
            Tolerace for stop criterio. CRITERIO: np.linalg.norm(current_w - previous_w) < tolerance
        max_iter : int
            Max amount of epoches in method.
        """
        self.loss_function = loss_function
        self.batch_size = batch_size
        self.step_alpha = step_alpha
        self.step_beta = step_beta
        self.tolerance = tolerance
        self.max_iter = max_iter
        self.random_seed = random_seed
        self.kwargs = kwargs
        self.w = None

    def fit(self, X, y, w_0=None, trace=False, X_val=None, y_val=None):
        """

        Parameters
        ----------
        X : numpy.ndarray or scipy.sparse.csr_matrix
            2d matrix, training set.
        y : numpy.ndarray
            1d vector, target values.
        w_0 : numpy.ndarray
            1d vector for initial approximation for SGD method.
        trace : bool
            If True need to calculate metrics on each iteration.
        X_val : numpy.ndarray or scipy.sparse.csr_matrix
            2d matrix, validation set.
        y_val: numpy.ndarray
            1d vector, target values for validation set.

        Returns
        -------
        : dict
            Keys are 'time', 'func', 'func_val'.
            Each key correspond to list of metric values after each training epoch.
        """
        np.random.seed(self.random_seed)
        N = X.shape[0]
        D = X.shape[1]
        if w_0 is None:
            w_0 = np.zeros(D)
        self.w = w_0.copy()

        if self.batch_size is None:
            self.batch_size = N
        history = {
            "time" : [],
            "func" : [],
            "func_val" : []
        }

        if type(X) is not np.ndarray:
            X = X.toarray().copy()
       
        
        start_time = time.time()
        for epoch in np.arange(1, self.max_iter + 1):
            indices = np.random.permutation(N)
            lr_epoch = self.step_alpha / (epoch**self.step_beta)
            w_prev = self.w.copy()

            for i in np.arange(0, N, self.batch_size):
                start = i
                end = int(np.min([i + self.batch_size, float(N)]))
                indices_batch = indices[start: end]
                X_batch = X[indices_batch]
                y_batch = y[indices_batch]
                grad_batch = self.loss_function.grad(X_batch, y_batch, self.w)
                self.w = self.w - lr_epoch * grad_batch
            
            if trace:
                history['time'].append(time.time() - start_time)
                history['func'].append(self.loss_function.func(X, y, self.w))
                if X_val is not None and y_val is not None:
                    if type(X_val) is not np.ndarray:
                        X_val = X_val.toarray().copy()
                    history['func_val'].append(self.loss_function.func(X_val, y_val, self.w))

            if np.linalg.norm(self.w - w_prev) < self.tolerance:
                break
        return history

    def predict(self, X):
        """

        Parameters
        ----------
        X : numpy.ndarray or scipy.sparse.csr_matrix
            2d matrix, test set.

        Returns
        -------
        : numpy.ndarray
            answers on a test set
        """
        return X@self.w

    def get_weights(self):
        """
        Get model weights

        Returns
        -------
        : numpy.ndarray
            1d model weights vector.
        """
        return self.w

    def get_objective(self, X, y):
        """
        Get objective.

        Parameters
        ----------
        X : numpy.ndarray or scipy.sparse.csr_matrix
            2d matrix.
        y : numpy.ndarray
            1d vector, target values for X.

        Returns
        -------
        : float
        """
        return self.loss_function.func(X, y, self.w)