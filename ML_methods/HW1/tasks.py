import numpy as np

# __all__ = [euclidean_distance, cosine_distance, manhattan_distance]


# 2 points
def euclidean_distance(X, Y) -> np.ndarray:
    """
    Compute element wise euclidean distance.

    Parameters
    ----------
    X: np.ndarray of size M * K
    Y: np.ndarray of size N * K

    Returns
    -------
    np.ndarray of size M * N
        Each element of which is the Euclidean distance between the corresponding pair of vectors from the arrays X and Y
    """
    # raise NotImplementedError()
    X_shape = X.shape
    Y_shape = Y.shape
    M = X_shape[0]
    N = Y_shape[0]
    K = X_shape[-1]

    X_copy = X.copy().reshape([M, 1, K])
    Y_copy = Y.copy().reshape([1, N, K])
    return np.sqrt((np.abs(X_copy - Y_copy)**2).sum(axis=-1))

# 2 points
def cosine_distance(X, Y) -> np.ndarray:
    """
    Compute element wise cosine distance.

    Parameters
    ----------
    X: np.ndarray of size M * K
    Y: np.ndarray of size N * K

    Returns
    -------
    np.ndarray of size M * N
        Each element of which is the cosine distance between the corresponding pair of vectors from the arrays X and Y
    """
    # raise NotImplementedError()

    X_shape = X.shape
    Y_shape = Y.shape
    M = X_shape[0]
    N = Y_shape[0]
    K = X_shape[-1]

    X_copy = X.copy() / np.linalg.norm(X, axis=-1).reshape(M, 1)
    X_copy = X_copy.reshape([M, 1, K])
    Y_copy = Y.copy() / np.linalg.norm(Y, axis=-1).reshape(N, 1)
    Y_copy = Y_copy.reshape([1, N, K])   
    return 1 - (X_copy * Y_copy).sum(axis=-1)



# 1 point
def manhattan_distance(X, Y) -> np.ndarray:
    """
    Compute element wise manhattan distance.

    Parameters
    ----------
    X: np.ndarray of size M * K
    Y: np.ndarray of size N * K

    Returns
    -------
    np.ndarray of size M * N
        Each element of which is the manhattan distance between the corresponding pair of vectors from the arrays X and Y
    """
    # raise NotImplementedError()
    X_shape = X.shape
    Y_shape = Y.shape
    M = X_shape[0]
    N = Y_shape[0]
    K = X_shape[-1]

    X_copy = X.copy().reshape([M, 1, K])
    Y_copy = Y.copy().reshape([1, N, K])
    return (np.abs(X_copy - Y_copy)).sum(axis=-1)