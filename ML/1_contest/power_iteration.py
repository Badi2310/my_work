import numpy as np

def get_dominant_eigenvalue_and_eigenvector(data, num_steps):
    """
    data: np.ndarray – symmetric diagonalizable real-valued matrix
    num_steps: int – number of power method steps
    
    Returns:
    eigenvalue: float – dominant eigenvalue estimation after `num_steps` steps
    eigenvector: np.ndarray – corresponding eigenvector estimation
    """
    ### YOUR CODE HERE

    return [pr := [0, np.random.randn(len(data))]] and [pr := [float(pr[1].dot(data.dot(pr[1])) / (pr[1].dot(pr[1]))), data.dot(pr[1])/np.linalg.norm(data.dot(pr[1]))] for _ in range(1, num_steps)][-1]