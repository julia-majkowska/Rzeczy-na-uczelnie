import numpy as np
from sklearn.neighbors import NearestNeighbors
print("Looking for k closest documents")
vector_matrix = np.array([[4.0, 4.0, 3.0], [2.0, 7.0, 43153.], [312513., 41354, 4315.], [5., 2, 5]])
knn = NearestNeighbors(n_neighbors = 2) #tutaj definiujemy k
knn.fit(vector_matrix)
print(knn.kneighbors(np.array([6, 5, 6]).reshape(1, -1), return_distance=False))

vector = 